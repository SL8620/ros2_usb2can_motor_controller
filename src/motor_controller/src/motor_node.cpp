#include "rclcpp/rclcpp.hpp"
#include "motor_interfaces/msg/motor_command.hpp"
#include "motor_interfaces/msg/motor_status.hpp"
#include "can_usb_driver/can_usb_device.hpp"

// 不同电机类型对应的解析器头文件
#include "motor_controller/rs03_parser.hpp"
// #include "motor_controller/se_motor_parser.hpp"
#include "motor_controller/motor_parser_base.hpp"

#include <yaml-cpp/yaml.h>
#include <memory>
#include <unordered_map>

using std::placeholders::_1;
using motor_interfaces::msg::MotorCommand;
using motor_interfaces::msg::MotorStatus;

class MotorNode : public rclcpp::Node 
{
public:
    MotorNode() : Node("motor_node") 
    {
        // 声明并获取 YAML 配置文件路径参数
        declare_parameter<std::string>("motors_yaml", "");
        declare_parameter<std::string>("devices_yaml", "");

        std::string motors_path = get_parameter("motors_yaml").as_string();
        std::string devices_path = get_parameter("devices_yaml").as_string();

        // 加载设备与电机信息
        load_devices(devices_path);
        load_motors(motors_path);

        // 订阅控制指令
        command_sub_ = create_subscription<MotorCommand>(
            "/motor_command", 10, std::bind(&MotorNode::on_command, this, _1)
        );

        // 发布反馈状态
        status_pub_ = create_publisher<MotorStatus>("/motor_status", 10);
    }

private:
    // 单个电机的配置结构
    struct MotorInfo 
    {
        std::string name;
        std::string type;
        std::string device;
        uint8_t channel;
        uint8_t id;
    };

    // 保存 USB-CAN 设备对象
    std::unordered_map<std::string, std::shared_ptr<can_usb_driver::CanUsbDevice>> device_map_;
    // 所有电机的配置列表
    std::vector<MotorInfo> motors_;
    // 每个电机名 -> 解析器对象
    std::unordered_map<std::string, std::shared_ptr<MotorParserBase>> parser_map_;

    rclcpp::Subscription<MotorCommand>::SharedPtr command_sub_;
    rclcpp::Publisher<MotorStatus>::SharedPtr status_pub_;

    // 加载设备配置：打开设备、设置回调
    void load_devices(const std::string& path) 
    {
        auto config = YAML::LoadFile(path);
        for (const auto& item : config["devices"]) 
        {
            std::string name = item.first.as<std::string>();
            std::string dev_path = item.second["path"].as<std::string>();

            auto dev = std::make_shared<can_usb_driver::CanUsbDevice>(dev_path);

            // 设置接收 CAN 数据的回调函数
            dev->set_feedback_callback([this, name](const can_usb_driver::CanMessage& msg) { handle_can_feedback(name, msg);});

            device_map_[name] = dev;
        }
    }

    // 加载电机配置，并根据类型实例化对应解析器
    void load_motors(const std::string& path) 
    {
        auto config = YAML::LoadFile(path);
        for (const auto& item : config["motors"]) 
        {
            MotorInfo info;
            info.name = item["name"].as<std::string>();
            info.type = item["type"].as<std::string>();
            info.device = item["device"].as<std::string>();
            info.channel = item["can_channel"].as<uint8_t>();
            info.id = item["can_id"].as<uint8_t>();
            motors_.push_back(info);

            // 为该电机创建解析器（只创建一次）
            if (parser_map_.count(info.name) == 0) 
            {
                if (info.type == "RS03") 
                {
                    parser_map_[info.name] = std::make_shared<RS03Parser>();
                } 
                else if (info.type == "SEMotor") 
                {
                    parser_map_[info.name] = std::make_shared<SEMotorParser>();
                } 
                else 
                {
                    RCLCPP_WARN(get_logger(), "Unknown motor type: %s", info.type.c_str());
                }
            }
        }
    }

    // 接收并处理 CAN 总线反馈消息
    void handle_can_feedback(const std::string& device_name, const can_usb_driver::CanMessage& msg) 
    {
        for (const auto& motor : motors_) 
        {
            if (motor.device == device_name && motor.channel == msg.channel && motor.id == msg.id) 
            {
                auto parser = parser_map_[motor.name];

                MotorStatus status_msg;
                status_msg.device = motor.channel;  // 可改成设备编号映射
                status_msg.channel = motor.channel;
                status_msg.id = motor.id;

                // 交给具体电机解析器解包数据
                parser->unpackStatus(msg.data, status_msg);

                status_pub_->publish(status_msg);
            }
        }
    }

    // 接收电机控制指令，打包成 CAN 数据发送
    void on_command(const MotorCommand::SharedPtr msg) 
    {
        for (const auto& motor : motors_) 
        {
            if (motor.channel == msg->channel && motor.id == msg->id) 
            {
                can_usb_driver::CanMessage can_msg;
                can_msg.channel = msg->channel;
                can_msg.id = msg->id;

                // 使用对应的解析器将命令打包成 CAN 数据
                parser_map_[motor.name]->packCommand(*msg, can_msg.data);

                device_map_[motor.device]->send(can_msg);
                break;
            }
        }
    }
};

int main(int argc, char** argv) 
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<MotorNode>());
    rclcpp::shutdown();
    return 0;
}


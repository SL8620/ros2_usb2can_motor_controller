// motor_node.cpp - CAN总线电机控制节点
// 功能：管理USB-CAN设备，处理电机控制指令和状态反馈

#include <yaml-cpp/yaml.h>       // YAML配置文件解析
#include <memory>               // 智能指针
#include <mutex>                // 互斥锁（线程安全）
#include <unordered_map>        // 哈希表容器
#include "rclcpp/rclcpp.hpp"    // ROS 2核心功能

// CAN设备驱动和消息接口
#include "can_usb_driver/can_usb_device.hpp"
#include "motor_interfaces/msg/motor_command.hpp"  // 电机运动指令
#include "motor_interfaces/msg/motor_status.hpp"   // 电机状态反馈
#include "motor_interfaces/msg/motor_control.hpp" // 电机控制指令

// 电机协议解析器
#include "motor_controller/motor_parser_base.hpp"  // 解析器基类
#include "motor_controller/rs03_motor_parser.hpp"        // 灵足电机协议实现

// 简化类型引用
using std::placeholders::_1;
using motor_interfaces::msg::MotorCommand;
using motor_interfaces::msg::MotorStatus;
using motor_interfaces::msg::MotorControl;

/**
 * @brief CAN总线电机控制节点
 * 
 * 主要功能：
 * 1. 加载USB-CAN设备和电机配置
 * 2. 接收ROS控制指令并转发到CAN总线
 * 3. 处理CAN总线反馈数据并发布状态
 */
class MotorNode : public rclcpp::Node {
public:
    /**
     * @brief 构造函数
     * 
     * 初始化节点、加载配置、创建ROS接口
     */
    MotorNode() : Node("motor_node") {
        // 声明并获取YAML配置文件路径参数
        declare_parameter<std::string>("motors_yaml", "");    // 电机配置文件路径
        declare_parameter<std::string>("devices_yaml", "");   // 设备配置文件路径

        // 从参数服务器获取配置路径
        std::string motors_path = get_parameter("motors_yaml").as_string();
        std::string devices_path = get_parameter("devices_yaml").as_string();

        // 初始化设备与电机
        load_devices(devices_path);  // 加载USB-CAN设备配置
        load_motors(motors_path);    // 加载电机配置并初始化解析器

        // 订阅控制指令（ROS 2话题）
        command_sub_ = create_subscription<MotorCommand>(
            "/motor_command",  // 话题名称
            10,                // 消息队列长度
            std::bind(&MotorNode::on_command, this, _1)  // 回调绑定
        );

        // 订阅控制指令（模式/使能等）
        control_sub_ = create_subscription<MotorControl>(
            "/motor_control", 
            10, 
            std::bind(&MotorNode::on_control, this, _1)
        );

        // 创建状态发布器
        status_pub_ = create_publisher<MotorStatus>("/motor_status", 10);
    }

private:
    /// @brief 电机配置信息结构体
    struct MotorInfo {
        std::string name;       // 电机名称（如"leg_motor1"）
        std::string type;       // 电机类型（如"RS03"）
        std::string device;     // 所属CAN设备名称
        uint8_t channel;        // CAN通道号（如CAN1, CAN2）
        uint8_t id;             // CAN节点ID
    };

    /**
     * @brief 生成电机唯一键值
     * @param device 设备名称
     * @param channel CAN通道
     * @param id CAN节点ID
     * @return 格式为"device_channel_id"的字符串
     */
    std::string get_key(const std::string& device, uint8_t channel, uint8_t id) const {
        return device + "_" + std::to_string(channel) + "_" + std::to_string(id);
    }

    // 关键数据结构
    std::unordered_map<std::string, std::shared_ptr<can_usb_driver::CanUsbDevice>> device_map_;  // CAN设备列表（key=设备名）
    std::unordered_map<std::string, MotorInfo> motor_map_;      // 电机配置表（key=设备_通道_ID）
    std::unordered_map<std::string, std::shared_ptr<MotorParserBase>> parser_map_;  // 电机协议解析器（key=电机名）

    // ROS 2通信接口
    rclcpp::Subscription<MotorCommand>::SharedPtr command_sub_;  // 运动指令订阅（位置/速度控制）
    rclcpp::Subscription<MotorControl>::SharedPtr control_sub_;  // 控制指令订阅（使能/模式设置）
    rclcpp::Publisher<MotorStatus>::SharedPtr status_pub_;       // 状态发布

    /**
     * @brief 加载USB-CAN设备配置
     * @param path YAML配置文件路径
     * 
     * 典型YAML格式：
     * devices:
     *   - name: can0
     *     path: /dev/ttyACM0
     */
    void load_devices(const std::string& path) 
    {
        try 
        {
            YAML::Node config = YAML::LoadFile(path);
            
            // 遍历设备配置项
            for (const auto& item : config["devices"]) 
            {
                std::string name = item["name"].as<std::string>();      // 设备名称
                std::string dev_path = item["path"].as<std::string>();   // 设备路径（如/dev/ttyACM0）

                // 创建设备实例
                auto device = std::make_shared<can_usb_driver::CanUsbDevice>(dev_path, name);
                
                // 设置数据回调函数（收到CAN数据时触发）
                // device->setReceiveCallback(
                //     [this](const can_usb_driver::CanUsbDevice* dev, const can_usb_driver::CanMessage& msg) {this->handle_can_message(dev, msg);
                // });


                device_map_[name] = device;  // 加入设备列表
                RCLCPP_INFO(get_logger(), "Loaded device: %s at %s", name.c_str(), dev_path.c_str());
            }
        } 
        catch (const YAML::Exception& e) 
        {
            RCLCPP_FATAL(get_logger(), "Device config error: %s", e.what());
            throw;
        }
    }

    /**
     * @brief 加载电机配置并初始化协议解析器
     * @param path YAML配置文件路径
     * 
     * 典型YAML格式：
     * motors:
     *   - name: motor1
     *     type: RS03
     *     device: can0
     *     can_channel: 1
     *     can_id: 1
     */
    void load_motors(const std::string& path) 
    {
        try 
        {
            YAML::Node config = YAML::LoadFile(path);

            // 定义合法性检查常量
            constexpr uint8_t MIN_CAN_CHANNEL = 1;
            constexpr uint8_t MAX_CAN_CHANNEL = 2;
            constexpr uint8_t MIN_CAN_ID = 1;
            constexpr uint8_t MAX_CAN_ID = 127;
            
            // 遍历电机配置项
            for (const auto& item : config["motors"]) 
            {
                MotorInfo info;
                info.name = item["name"].as<std::string>();          // 电机名称
                info.type = item["type"].as<std::string>();          // 电机型号
                info.device = item["device"].as<std::string>();      // 所属设备
                info.channel = item["can_channel"].as<uint8_t>();    // CAN通道
                info.id = item["can_id"].as<uint8_t>();              // CAN ID

                // 检查CAN通道合法性（1或2）
                info.channel = item["can_channel"].as<uint8_t>();
                if (info.channel < MIN_CAN_CHANNEL || info.channel > MAX_CAN_CHANNEL) 
                {
                    RCLCPP_FATAL(get_logger(), "FATAL: Motor %s has invalid CAN channel %d (must be %d or %d)", info.name.c_str(), info.channel, MIN_CAN_CHANNEL, MAX_CAN_CHANNEL);
                    rclcpp::shutdown();
                    throw std::runtime_error("Invalid CAN channel configuration");
                }

                // 检查CAN ID合法性（1-127）
                info.id = item["can_id"].as<uint8_t>();
                if (info.id < MIN_CAN_ID || info.id > MAX_CAN_ID) 
                {
                    RCLCPP_FATAL(get_logger(), "FATAL: Motor %s has invalid CAN ID %d (must be %d-%d)", info.name.c_str(), info.id, MIN_CAN_ID, MAX_CAN_ID);
                    rclcpp::shutdown();
                    throw std::runtime_error("Invalid CAN ID configuration");
                }

                 // 检查设备是否存在
                if (device_map_.find(info.device) == device_map_.end()) 
                {
                    RCLCPP_FATAL(get_logger(), "FATAL: Motor %s requires non-existent device %s", info.name.c_str(), info.device.c_str());
                    rclcpp::shutdown();
                    throw std::runtime_error("Missing CAN device");
                }

                // 生成唯一键并存储配置
                std::string key = get_key(info.device, info.channel, info.id);
                motor_map_[key] = info;

                // 为每种电机类型创建协议解析器（单例）
                if (parser_map_.count(info.name) == 0) 
                {
                    if (info.type == "RS03") 
                    {
                        // 初始化灵足电机解析器（需传入CAN设备和地址信息）
                        parser_map_[info.name] = std::make_shared<RS03Parser>(
                            device_map_[info.device],  // 关联的CAN设备
                            info.channel,             // CAN通道
                            info.id                   // 节点ID
                        );
                        RCLCPP_INFO(get_logger(), "Initialized RS03 parser for %s", info.name.c_str());
                    } 
                    else 
                    {
                        RCLCPP_WARN(get_logger(), "Unsupported motor type: %s", info.type.c_str());
                    }
                }
            }
        } catch (const YAML::Exception& e) {
            RCLCPP_FATAL(get_logger(), "Motor config error: %s", e.what());
            throw;
        }
    }

    /**
     * @brief 处理CAN总线反馈数据
     * @param dev_name 设备名称
     * @param msg CAN消息
     * 
     * 将CAN数据解析为电机状态并发布ROS话题
     */
    void handle_can_feedback(const std::string& dev_name, const can_usb_driver::CanMessage& msg) 
    {
        // 通过设备+通道+ID定位电机
        std::string key = get_key(dev_name, msg.canPort, msg.id);
        
        if (motor_map_.count(key)) 
        {
            const auto& motor = motor_map_[key];      // 获取电机配置
            auto parser = parser_map_[motor.name];    // 获取对应解析器

            // 解析CAN数据并发布状态
            MotorStatus status;
            status.device = motor.device;    // 填充设备信息
            status.channel = motor.channel;
            status.id = motor.id;
            
            parser->unpackStatus(msg.data, status);  // 协议解析
            status_pub_->publish(status);            // 发布状态
            
            RCLCPP_DEBUG(get_logger(), "Published status for %s", key.c_str());
        } 
        else 
        {
            RCLCPP_WARN(get_logger(), "Unknown CAN message from %s", key.c_str());
        }
    }

    /**
     * @brief 运动指令回调（位置/速度/力矩控制）
     * @param msg 运动指令消息
     * 
     * 将ROS指令转换为CAN数据帧并发送
     */
    void on_control(const MotorControl::SharedPtr msg) 
    {
        std::string key = get_key(msg->device, msg->channel, msg->id);
        
        if (motor_map_.count(key)) 
        {
            const auto& motor = motor_map_[key];      // 获取电机配置
            auto parser = parser_map_[motor.name];    // 获取协议解析器

            // 构造CAN消息
            can_usb_driver::CanMessage can_msg;
            can_msg.canPort = msg->channel;  // 设置CAN通道
            can_msg.id = msg->id;            // 设置目标ID
            can_msg.canIdType = CanId_classic;
            
            // 将ROS指令转换为CAN数据帧
            parser->packCommand(*msg, can_msg.data);
            
            // 通过对应设备发送CAN消息
            device_map_[motor.device]->sendCanMessage(can_msg);
            
            RCLCPP_DEBUG(get_logger(), "Sent command to %s", key.c_str());
        } 
        else 
        {
            RCLCPP_WARN(get_logger(), "Motor not found for command: %s", key.c_str());
        }
    }

    /**
     * @brief 控制指令回调（使能/模式设置等）
     * @param msg 控制指令消息
     */
    void on_command(const MotorCommand::SharedPtr msg) 
    {
        std::string key = get_key(msg->device, msg->channel, msg->id);
        
        if (motor_map_.count(key)) 
        {
            const auto& motor = motor_map_[key];
            auto parser = parser_map_[motor.name];

            // 执行控制指令
            switch (msg->command_type) 
            {
                case 0: 
                    parser->enable_motor();  // 使能电机
                    RCLCPP_INFO(get_logger(), "Enabled motor %s", key.c_str());
                    break;
                case 1: 
                    parser->disable_motor(); // 禁用电机
                    RCLCPP_INFO(get_logger(), "Disabled motor %s", key.c_str());
                    break;
                case 2: 
                    parser->zero_position();  // 零点校准
                    RCLCPP_INFO(get_logger(), "Zeroed motor %s", key.c_str());
                    break;
                case 3: 
                    parser->set_mode(msg->mode_type);  // 设置工作模式
                    RCLCPP_INFO(get_logger(), "Set mode %d for motor %s", 
                               msg->mode_type, key.c_str());
                    break;
                default:
                    RCLCPP_WARN(get_logger(), "Unknown command type: %d", 
                               msg->command_type);
            }
        } 
        else 
        {
            RCLCPP_WARN(get_logger(), "Motor not found for control: %s", key.c_str());
        }
    }
};

/**
 * @brief 主函数
 * 
 * 初始化ROS 2并启动电机控制节点
 */
int main(int argc, char** argv) 
{
    rclcpp::init(argc, argv);  // 初始化ROS 2
    auto node = std::make_shared<MotorNode>();  // 创建节点实例
    
    RCLCPP_INFO(node->get_logger(), "Motor control node started");
    rclcpp::spin(node);        // 进入事件循环
    rclcpp::shutdown();        // 关闭节点
    
    return 0;
}
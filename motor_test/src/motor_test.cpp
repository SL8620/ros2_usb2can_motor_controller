#include "rclcpp/rclcpp.hpp"
#include "motor_interfaces/msg/motor_command.hpp"
#include "motor_interfaces/msg/motor_control.hpp"
#include "motor_interfaces/msg/motor_status.hpp"
#include <yaml-cpp/yaml.h>
#include <chrono>
#include <memory>
#include <unordered_map>
#include <atomic>

using namespace std::chrono_literals;

class MotorTestNode : public rclcpp::Node {
public:
    MotorTestNode() : Node("motor_test_node") {
        // 1. 加载配置文件
        declare_parameter<std::string>("config_file", "");
        auto config_path = get_parameter("config_file").as_string();
        if (config_path.empty()) {
            RCLCPP_FATAL(get_logger(), "Config file path not provided!");
            rclcpp::shutdown();
            return;
        }
        load_config(config_path);

        // 2. 初始化通信接口
        init_communications();

        // 3. 打印测试参数
        print_test_config();

        // 4. 启动测试
        start_test();
    }

private:
    struct MotorConfig {
        std::string name;
        std::string device;
        uint8_t channel;
        uint8_t id;
    };

    void load_config(const std::string& path) {
        try {
            YAML::Node config = YAML::LoadFile(path);
            
            // 解析测试参数
            publish_frequency_ = config["test"]["publish_frequency_hz"].as<double>();
            test_duration_ = config["test"]["duration_sec"].as<double>();
            log_interval_ = config["test"]["log_interval_sec"].as<double>();

            // 解析电机配置（移除test_frequency）
            for (const auto& node : config["motors"]) {
                MotorConfig mc;
                mc.name = node["name"].as<std::string>();
                mc.device = node["device"].as<std::string>();
                mc.channel = node["channel"].as<uint8_t>();
                mc.id = node["id"].as<uint8_t>();
                motors_.push_back(mc);

                // 初始化统计计数器
                msg_counts_[mc.id] = 0;
                last_msg_time_[mc.id] = rclcpp::Time(0);
            }

            RCLCPP_INFO(get_logger(), "Loaded config for %zu motors", motors_.size());
        } catch (const YAML::Exception& e) {
            RCLCPP_FATAL(get_logger(), "Config error: %s", e.what());
            rclcpp::shutdown();
        }
    }

    void init_communications() {
        // 最佳性能QoS配置
        auto qos = rclcpp::QoS(rclcpp::KeepLast(10))
            .reliability(RMW_QOS_POLICY_RELIABILITY_BEST_EFFORT)
            .durability(RMW_QOS_POLICY_DURABILITY_VOLATILE);

        // 创建发布器
        command_pub_ = create_publisher<motor_interfaces::msg::MotorCommand>(
            "/motor_command", qos);
        control_pub_ = create_publisher<motor_interfaces::msg::MotorControl>(
            "/motor_control", qos);

        // 状态订阅器
        status_sub_ = create_subscription<motor_interfaces::msg::MotorStatus>(
            "/motor_status", qos,
            [this](const motor_interfaces::msg::MotorStatus::SharedPtr msg) {
                const auto now = this->now();
                const uint8_t id = msg->id;

                // 更新消息计数
                msg_counts_[id]++;

                // 计算瞬时频率
                if (last_msg_time_[id].nanoseconds() > 0) {
                    const double interval = (now - last_msg_time_[id]).seconds();
                    if (interval > 0) {
                        current_freq_[id] = 1.0 / interval;
                    }
                }
                last_msg_time_[id] = now;
            });

        // 统计定时器（严格1秒间隔）
        stats_timer_ = create_wall_timer(
            std::chrono::duration<double>(log_interval_),
            [this]() { print_statistics(); });
    }

    void print_test_config() {
        RCLCPP_INFO(get_logger(), "\n===== Test Configuration =====");
        RCLCPP_INFO(get_logger(), "Publish Frequency: %.1f Hz", publish_frequency_);
        RCLCPP_INFO(get_logger(), "Test Duration: %.1f sec", test_duration_);
        RCLCPP_INFO(get_logger(), "Log Interval: %.1f sec", log_interval_);
        RCLCPP_INFO(get_logger(), "Motor Count: %zu", motors_.size());
    }

    void start_test() {
        // 1. 发送使能命令
        send_enable_commands();

        // 2. 创建集中发布定时器
        const auto period = std::chrono::duration<double>(1.0 / publish_frequency_);
        control_timer_ = create_wall_timer(
            period,
            [this]() { publish_all_commands(); });

        // 3. 设置测试超时
        test_timer_ = create_wall_timer(
            std::chrono::duration<double>(test_duration_),
            [this]() {
                RCLCPP_INFO(get_logger(), "\n===== Test Completed =====");
                print_final_statistics();
                rclcpp::shutdown();
            });
    }

    void send_enable_commands() {
        auto cmd_msg = motor_interfaces::msg::MotorCommand();
        
        for (const auto& motor : motors_) {
            cmd_msg.device = motor.device;
            cmd_msg.channel = motor.channel;
            cmd_msg.id = motor.id;
            cmd_msg.command_type = 0; // 使能命令
            command_pub_->publish(cmd_msg);
        }
        RCLCPP_INFO(get_logger(), "Sent enable commands to all motors");
    }

    void publish_all_commands() {
        auto ctrl_msg = motor_interfaces::msg::MotorControl();
        
        for (const auto& motor : motors_) {
            ctrl_msg.device = motor.device;
            ctrl_msg.channel = motor.channel;
            ctrl_msg.id = motor.id;
            ctrl_msg.position = 0.0;
            ctrl_msg.velocity = 0.0;
            ctrl_msg.torque = 0.0;
            control_pub_->publish(ctrl_msg);
        }

        // 更新发布计数
        publish_count_++;
    }

    void print_statistics() {
        RCLCPP_INFO(get_logger(), "\n===== Real-time Statistics =====");
        RCLCPP_INFO(get_logger(), "Publish Count: %zu (%.1f Hz)", 
                   publish_count_, publish_count_ / elapsed_time());

        for (const auto& motor : motors_) {
            const uint8_t id = motor.id;
            RCLCPP_INFO(get_logger(), 
                "[%s] ID: %-2d | Current Freq: %6.1f Hz | Total Received: %zu",
                motor.name.c_str(), id, current_freq_[id], msg_counts_[id]);
        }
    }

    void print_final_statistics() {
        const double total_time = elapsed_time();
        RCLCPP_INFO(get_logger(), "\n===== Final Test Results =====");
        RCLCPP_INFO(get_logger(), "Total Test Time: %.3f sec", total_time);
        RCLCPP_INFO(get_logger(), "Actual Publish Rate: %.3f Hz", 
                   publish_count_ / total_time);

        for (const auto& motor : motors_) {
            const uint8_t id = motor.id;
            const double avg_freq = msg_counts_[id] / total_time;
            RCLCPP_INFO(get_logger(), 
                "[%s] ID: %-2d | Avg Freq: %6.1f Hz | Total Received: %zu",
                motor.name.c_str(), id, avg_freq, msg_counts_[id]);
        }
    }

    double elapsed_time() const {
        return (now() - start_time_).seconds();
    }

    // 配置参数
    std::vector<MotorConfig> motors_;
    double publish_frequency_;
    double test_duration_;
    double log_interval_;

    // ROS2接口
    rclcpp::Publisher<motor_interfaces::msg::MotorCommand>::SharedPtr command_pub_;
    rclcpp::Publisher<motor_interfaces::msg::MotorControl>::SharedPtr control_pub_;
    rclcpp::Subscription<motor_interfaces::msg::MotorStatus>::SharedPtr status_sub_;
    rclcpp::TimerBase::SharedPtr control_timer_;
    rclcpp::TimerBase::SharedPtr test_timer_;
    rclcpp::TimerBase::SharedPtr stats_timer_;

    // 测试状态
    rclcpp::Time start_time_ = now();
    std::atomic<size_t> publish_count_{0};
    std::unordered_map<uint8_t, std::atomic<size_t>> msg_counts_;
    std::unordered_map<uint8_t, std::atomic<double>> current_freq_;
    std::unordered_map<uint8_t, rclcpp::Time> last_msg_time_;
};

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    
    // 设置实时优先级（需要root权限）
    sched_param sch{};
    sch.sched_priority = 80;
    if (pthread_setschedparam(pthread_self(), SCHED_FIFO, &sch)) {
        std::cerr << "Warning: Failed to set thread priority (run as root)\n";
    }

    auto node = std::make_shared<MotorTestNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
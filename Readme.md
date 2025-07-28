# ROS2_USB2CAN


**协议**：MIT  
**兼容版本**：ROS2 Humble  
**主分支**：`Ros2_Humble` (推荐使用)

## 功能特性
- ✅ 支持MIT协议控制的电机
- ✅ 三通道控制模式（位置&速度&力矩）

## 安装部署
```bash
git clone --branch Ros2_Humble https://github.com/your_repo/can2usb_ros2.git
colcon build --packages-select can2usb_driver
```

## 节点说明
主节点 motor_controller

## 消息类型说明
- MotorCommand
    - 消息作用说明：用于电机使能/失能/模式切换(暂未适配)指令
    - device：从哪个can2usb设备发送
    - channel：从设备哪一个can口(1/2)发送
    - id：目标电机canId
    - command_type：消息类型，目前仅支持0(使能)，1(失能)
    - mode_type：保留参数，用于后续电机运行模式切换
- MotorControl
    - 消息作用说明：用于控制电机转动
    - device：从哪个can2usb设备发送
    - channel：从设备哪一个can口(1/2)发送
    - id：目标电机canId
    - position：期望位置
    - velocity：期望速度
    - torque：期望力矩
    - kp：kp参数
    - kd: kd参数
- MotorStatus
    - 消息作用说明：收到电机反馈信息时自动解析，并从节点发布该种类型消息
    - device：从哪个can2usb设备收到的消息
    - channel：从设备哪一个can口(1/2)收到的消息
    - id：解析出来的电机canId(有的电机反馈消息报文不是本身id，需要解析报文)
    - current_position：上一时刻(发送运动命令时)电机的位置，高频率发送可忽略时间差
    - current_velocity：上一时刻(发送运动命令时)电机的速度，高频率发送可忽略时间差
    - current_torque：上一时刻(发送运动命令时)电机的速度，高频率发送可忽略时间差

## 启动流程

1. 连接can转usb模块，绑定设备号（执行can_usb_driver/scripts中的py文件实现）  

2. 修改config文件，需要修改motor_controller/config下面的两个config文件，devices.yaml用于描述usb转can模块；motors.yaml用于描述电机，具体如何修改可参照已有内容或交一个commit  

3. 修改motor_controller/launch下面的launch文件，把里面两个yaml的绝对路径换成自己电脑的绝对路径

4. 编译功能包 colcon build 编译通过后source一下install，后续每打开一个新终端都推荐source一下，或者直接把install加入bashrc里去

5. 执行launch文件 
```bash
ros2 launch motor_controller motor_node.launch.py
```

6. 使能电机 某些电机上电一段时间后会自己使能，可跳过这一步，对于那些不能自己使能的电机，需要我们这边发送MotorCommand话题让他使能，如使能挂载在设备usb2can_0通道1下面，id是1的电机，需要发送
```bash  
ros2 topic pub /motor_command motor_interfaces/msg/MotorCommand "device: 'usb2can_0' channel: 1 id: 1 command_type: 0 mode_type: 0"
```
7. 控制电机 发布MotorControl话题，如下述命令  
**⚠️ 警告：对于装有限位的电机，请谨慎给参数，不要随便执行下面的例子！**  
（确保电机不会因超调撞击限位开关）
```bash
ros2 topic pub --once /motor_command motor_interfaces/msg/MotorCommand "
device: 'usb2can_0'
channel: 1
id: 1
position: 3.14
velocity: 0.0
torque: 0.0
kp: 100.0
kd: 10.0
"
```
8. 订阅电机状态 有些电机在收到控制指令后会自动返回包含有pvt信息的报文，程序内部会自动解析并通过/MotorStatus进行发布，如遇到没有消息回来，请排查接线&程序&电机id&source等问题，这一版程序在灵足电机RS03上测试过，发送和接受都是正常的。可通过模块上的led灯闪烁观察是否有报文反馈，如果确实有can消息回来了，会闪烁对应的led灯，此种情况下如果/MotorStatus仍没有消息发布，请提交issue，咱一起解决

## 已知问题

1. 对于空写的电机（即实际没有连接但是在yaml文件里写了的电机，后续以“幽灵电机"代替）没有检测，即会造成电机正常使能，正常发命令但是没有返回状态报文，因为没有做闭环检测。后续对于这些幽灵电机会加入使能检测，消灭幽灵电机的影响。
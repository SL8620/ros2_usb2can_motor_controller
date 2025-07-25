<!--
 * @Author: SL8620
 * @Date: 2025-07-25 22:23:57
 * @LastEditTime: 2025-07-25 22:27:58
 * @LastEditors: SL8620
 * @Description: 
 * @FilePath: \ros2_usb2can_motor_controller\Readme.md
 * 
-->
# CAN2USB ROS2 驱动包

**协议**：MIT  
**兼容版本**：ROS2 Humble  
**主分支**：`Ros2_Humble` (推荐使用)

## 功能特性
- ✅ 支持MIT协议控制的电机
- ✅ 三通道控制模式（位置/速度/力矩）
- ✅ 双闭环控制（刚度/阻尼系数可调）
- ⚠️ 当前限制：仅处理反馈报文ID=电机ID的标准协议

## 安装部署
```bash
git clone --branch Ros2_Humble https://github.com/your_repo/can2usb_ros2.git
colcon build --packages-select can2usb_driver
```

## 节点说明
主节点 motor_controller

## 已知问题

    ​​ID协议限制​​
    当前版本要求反馈报文ID必须与电机ID严格一致，该问题已在以下commit修复

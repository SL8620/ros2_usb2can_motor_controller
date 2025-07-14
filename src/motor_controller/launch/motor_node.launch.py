from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='motor_controller',
            executable='motor_node',
            name='motor_node',
            parameters=[
                {'motors_yaml': '/home/nvidia/ros2_usb2can_motor_controller/src/motor_controller/config/motors.yaml'},
                {'devices_yaml': '/home/nvidia/ros2_usb2can_motor_controller/src/motor_controller/config/devices.yaml'}
            ]
        )
    ])
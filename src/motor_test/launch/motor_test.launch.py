from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import os

def generate_launch_description():
    # 获取当前包路径
    pkg_dir = get_package_share_directory('motor_test')
    
    # 构建配置路径
    config_file = os.path.join(pkg_dir, 'config', 'test.yaml')
    
    # 创建测试节点
    test_node = Node(
        package='motor_test',
        executable='motor_test_node',
        name='motor_test_node',
        output='screen',
        parameters=[{
            'config_file': config_file
        }]
    )
    
    return LaunchDescription([
        test_node
    ])
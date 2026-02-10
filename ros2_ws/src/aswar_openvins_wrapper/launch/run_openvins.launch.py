from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, LogInfo
from launch.substitutions import LaunchConfiguration

def generate_launch_description():
    # Placeholder launch file.
    # Later, we will add the OpenVINS node here (ov_msckf) once the workspace builds.
    config_name = LaunchConfiguration("config_name")

    return LaunchDescription([
        DeclareLaunchArgument("config_name", default_value="euroc_mav"),
        LogInfo(msg=["aswar_openvins_wrapper: launch placeholder, config_name=", config_name]),
    ])

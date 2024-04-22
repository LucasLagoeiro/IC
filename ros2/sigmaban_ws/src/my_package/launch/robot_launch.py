import os
import pathlib
import shutil
import launch
from launch_ros.actions import Node
from launch import LaunchDescription
from ament_index_python.packages import get_package_share_directory
from webots_ros2_driver.webots_launcher import WebotsLauncher
from webots_ros2_driver.utils import controller_url_prefix
from webots_ros2_driver.urdf_spawner import URDFSpawner, get_webots_driver_node


def generate_launch_description():
    package_dir = get_package_share_directory('my_package')
    robot_description = pathlib.Path(os.path.join(package_dir, 'resource', 'my_robot.urdf')).read_text()
    urdf_path = os.path.join(package_dir, 'protos', 'robot.urdf')
    # Directory 
    directory_mkdir = "as/Desktop/RoboFEI/IC/ros2/sigmaban_ws/install/my_package/share/my_package/protos/"
    directory_cp = "/tmp/as/Desktop/RoboFEI/IC/ros2/sigmaban_ws/install/my_package/share/my_package/protos/"
   
    # Parent Directory path 
    parent_dir = "/tmp"
    stlBody_dir = "/home/lucas/Desktop/RoboFEI/IC/ros2/sigmaban_ws/src/my_package/protos/body.stl"
    stlWheel_dir = "/home/lucas/Desktop/RoboFEI/IC/ros2/sigmaban_ws/src/my_package/protos/wheel.stl"

    path = os.path.join(parent_dir, directory_mkdir) 


    try:
        mesh_path = os.makedirs(path)
        print("Directory '%s' created successfully" % directory_mkdir)
    except OSError as error:
        print("Directory '%s' already exist")

    shutil.copy(stlBody_dir, directory_cp)
    shutil.copy(stlWheel_dir, directory_cp)

    spawn_URDF_robot = URDFSpawner(
        name='my_robot',
        urdf_path=urdf_path,
        translation='0 0 1',
        rotation='0 0 1 -1.5708',
    )

    webots = WebotsLauncher(
        world=os.path.join(package_dir, 'worlds', 'my_world.wbt'),
        ros2_supervisor=True
    )

    my_robot_driver = Node(
        package='webots_ros2_driver',
        executable='driver',
        output='screen',
        additional_env={'WEBOTS_CONTROLLER_URL': controller_url_prefix() + 'my_robot'},
        parameters=[
            {'robot_description': robot_description},
        ]
    )

    # obstacle_avoider = Node(
    #     package='my_package',
    #     executable='obstacle_avoider',
    # )

    return LaunchDescription([
        #mesh_path,
        webots,
        webots._supervisor,
        # my_robot_driver,
        #lspawn_URDF_robot,
        # obstacle_avoider,
        launch.actions.RegisterEventHandler(
            event_handler=launch.event_handlers.OnProcessExit(
                target_action=webots,
                on_exit=[launch.actions.EmitEvent(event=launch.events.Shutdown())],
            )
        )
    ])
#include <vector>
#include <fstream>
#include <string>
#include <map>
#include <stdint.h>
#include "ros/ros.h"
#include <ros/package.h>
#include <Eigen/Dense>
#include "std_msgs/MultiArrayLayout.h"
#include "std_msgs/MultiArrayDimension.h"
#include "std_msgs/Int32MultiArray.h"
#include "std_msgs/Float32MultiArray.h"
#include "std_msgs/Int32.h"
#include "std_msgs/Int8.h"
#include "tf/transform_listener.h"
#include "tf/message_filter.h"
#include "tf/tf.h"
#include <tf/transform_datatypes.h>
#include <geometry_msgs/PoseStamped.h>
#include "geometry_msgs/PoseArray.h"
#include <std_msgs/Bool.h>
#include <sensor_msgs/JointState.h>
#include <sensor_msgs/PointCloud2.h>

#include "visualization_msgs/Marker.h"
#include "visualization_msgs/MarkerArray.h"
#include <move_base_msgs/MoveBaseActionGoal.h>
#include <pcl_ros/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/kdtree/kdtree.h>





class DMP_Manager{

public:
	DMP_Manager();
	DMP_Manager(int numofhuman);
	~DMP_Manager();


	ros::Publisher static_belief_map_pub;
	ros::Publisher belief_pub;
	ros::Publisher human_target_pub;

	int index;
	bool IsHeadMoving;
	void Init_parameters();

    void global_pose_callback(const geometry_msgs::PoseStamped::ConstPtr &msg);
    void joint_state_callback(const sensor_msgs::JointState::ConstPtr &msg);
};

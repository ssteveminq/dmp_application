#include <vector>
#include <iostream>
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


using namespace std;

#define arm_flex_joint 0
#define arm_lift_joint 1
#define arm_roll_joint 2
#define wrist_flex joint 3
#define wrist_roll_joint 4


class DMP_Manager{

public:
	DMP_Manager();
	DMP_Manager(int numofhuman);
	~DMP_Manager();


    int dimension;
    
	ros::Publisher dmp_pub;
	ros::Publisher jointtrajectory_pub;

    ofstream basisTrajectory;
    
    vector< vector <double> > JointTrajectoryset;
    sensor_msgs::JointState JointStates_traj;
    map<int,sensor_msgs::JointState> trajectory_map;


	int index;
	void Init_parameters();

    void global_pose_callback(const geometry_msgs::PoseStamped::ConstPtr &msg);
    void joint_state_callback(const sensor_msgs::JointState::ConstPtr &msg);
    void saveTrajectory();

};

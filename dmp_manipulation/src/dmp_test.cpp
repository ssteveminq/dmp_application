#include "ros/ros.h"
#include "dmp_manager.h"
#include "std_msgs/String.h"
#include "std_msgs/Int8.h"
#include "geometry_msgs/Pose2D.h"
#include "geometry_msgs/PointStamped.h"
#include "geometry_msgs/PoseArray.h"
#include <geometry_msgs/PoseStamped.h>
#include <nav_msgs/OccupancyGrid.h>
#include <nav_msgs/Odometry.h>
#include <Eigen/Dense>
#include <sstream>
#include <boost/thread/thread.hpp>


using namespace Eigen;

int num_x=12;
int num_y=12;

//variables & functions for service

int main(int argc, char **argv)
{
  ros::init(argc, argv, "Human_tracker");

    DMP_Manager dmpmanager;

  
  // MDPManager problemmanager = humantracking(&mapParam);
  // ros::Rate r(5);
  
  // ros::Publisher  Human_pHuman_tracker
  ros::Subscriber Human_detected_sub;  
  ros::Subscriber dynlocalmap_sub;
  ros::Subscriber Basepos_sub;
  ros::Subscriber Human_markerarray_sub;
  ros::Subscriber global_pos_sub;
  ros::Subscriber edge_leg_sub;
  ros::Subscriber jointstates_sub;
  ros::Subscriber laser_pcl_sub;
  ros::Subscriber laser_scan_sub;

  ros::NodeHandle n;
  //Human_tracker.human_target_Intcmd_pub=n.advertise<std_msgs::Int8>("/Int_cmd_trackhuman", 10, true);
  //Human_tracker.belief_pub=n.advertise<nav_msgs::OccupancyGrid>("/human_belief_map", 10, true);
  //Human_tracker.human_target_pub= n.advertise<visualization_msgs::Marker>("/human_target", 10, true);
  //Human_tracker.static_belief_map_pub=n.advertise<nav_msgs::OccupancyGrid>("/static_belief_map", 10, true);
  //Human_tracker.Headscan_pub=n.advertise<std_msgs::Int8>("/gui_movebase_cmd", 10, true);
  //Human_tracker.setNavTarget_pub=n.advertise<move_base_msgs::MoveBaseActionGoal>("/move_base/move/goal",50,true);
  //Human_tracker.Human_boxes_pub= n.advertise<visualization_msgs::MarkerArray>("/human_leg_boxes", 50, true);
  //Human_tracker.human_leg_target_pub=n.advertise<visualization_msgs::Marker>("/human_leg_target", 10, true);
  //Human_tracker.Gaze_point_pub= n.advertise<geometry_msgs::Point>("/gazed_point_fixing_node/target_point", 50, true);
  //Human_tracker.Gaze_activate_pub= n.advertise<std_msgs::Bool>("/gazed_point_fixing_node/activate", 50, true);
  //Human_tracker.human_laser_pub= n.advertise<sensor_msgs::PointCloud2>("/modified_scan_cloud", 50, true);
  //Human_tracker.human_laser_scan_pub=n.advertise<sensor_msgs::LaserScan>("/modifiedlaserscan", 50, true);

  global_pos_sub= n.subscribe<geometry_msgs::PoseStamped>("/global_pose", 10, &DMP_Manager::global_pose_callback,&dmpmanager);
  jointstates_sub =n.subscribe<sensor_msgs::JointState>("/hsrb/joint_states", 10, &DMP_Manager::joint_state_callback,&dmpmanager);
  //ros::Timer timer = n.createTimer(ros::Duration(5.0), &Human_Belief::scanforhuman, &Human_tracker);

  ros::Rate loop_rate(5);


  while (ros::ok())
  {
	   
  ros::spin();

  }
  return 0;
}





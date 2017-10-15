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

static int saveiter=0;

int main(int argc, char **argv)
{
  ros::init(argc, argv, "Human_tracker");

  DMP_Manager dmpmanager;
 
  ros::NodeHandle n;
  ros::Subscriber global_pos_sub;
  ros::Subscriber jointstates_sub;
 

  global_pos_sub= n.subscribe<geometry_msgs::PoseStamped>("/global_pose", 10, &DMP_Manager::global_pose_callback,&dmpmanager);
  jointstates_sub =n.subscribe<sensor_msgs::JointState>("/hsrb/joint_states", 10, &DMP_Manager::joint_state_callback,&dmpmanager);
  ros::Rate loop_rate(5);

  dmpmanager.loadTrajectory();
  dmpmanager.loadTrajectory();

  while (ros::ok())
  {

    ros::spinOnce();
  	
    // if(saveiter%50==0) 
    // {
    //     dmpmanager.saveTrajectory();
    //     saveiter=0;
    // }
   

    loop_rate.sleep();
      // saveiter++;
  }
  ros::spin();
  return 0;
}





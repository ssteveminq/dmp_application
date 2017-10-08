#include "dmp_manager.h"


DMP_Manager::DMP_Manager(){
	// Init_parameters();
}
DMP_Manager::~DMP_Manager(){}

void DMP_Manager::Init_parameters()
{

    int dim=2;
    JointTrajectoryset.resize(dim);  //create size of joint trajectory




}
void DMP_Manager::global_pose_callback(const geometry_msgs::PoseStamped::ConstPtr &msg)
{




}


void DMP_Manager::joint_state_callback(const sensor_msgs::JointState::ConstPtr &msg)
{
ROS_INFO("recieved sensor_msgs");
    vector<double> tempJointTraj(5,0.0);
    
    tempJointTraj[0]=static_cast<double>( msg->position[0]);
    tempJointTraj[1]=static_cast<double>( msg->position[1]);
    tempJointTraj[2]=static_cast<double>( msg->position[2]);
    tempJointTraj[3]=static_cast<double>( msg->position[11]);
    tempJointTraj[4]=static_cast<double>( msg->position[12]);


    JointTrajectoryset.push_back(tempJointTraj);


    
}

void DMP_Manager::saveTrajectory()
{
    ROS_INFO("save trajectory");

    basisTrajectory.open("/home/mk/data_dmp/dmp_trajectories.csv");

    for(int i=0; i<JointTrajectoryset.size();i++ )
    {
        basisTrajectory<<i<<"\t";

        for(int j=0;j<JointTrajectoryset[i].size();j++) 
            basisTrajectory<<JointTrajectoryset[i][j]<<"\t";
    
        basisTrajectory<<endl;
    }
    
    basisTrajectory.close();


}

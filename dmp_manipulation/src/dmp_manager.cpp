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
//ROS_INFO("recieved sensor_msgs");
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

void DMP_Manager::printTrajectory()
{
    int time_size = JointTrajectoryset.size();
    int dof_trj=JointTrajectoryset[0].size();
    ROS_INFO("joint trajectory : time : %d , dof : %d \n", time_size, dof_trj); 
    
    // for(int i(0);i<JointTrajectoryset.size();i++)
    // {
    //     std::cout<<"time : "<<i<<": \t" ;
    //     for(int j=0;j<JointTrajectoryset[i].size();j++) 
    //     {
    //         std::cout<<JointTrajectoryset[i][j]<<"\t";
    //     }

    //     std::cout<<std::endl;
    // }
}


void DMP_Manager::loadTrajectory()
{
    bool    columncheck=false;
    char    spell[150]; 
    int     iter=0;
    float   tempdata=0.0;
    char    *data_seg[50];
    char    *strtokens[5];
    int     i,j=0;
    int     res;
    int     DataLenth=0;
    string  str;
    int     Dim=0;
    std::vector<double> tempDataVec;

    ROS_INFO("load trajectory");
    ifstream laodtrjfile;
    laodtrjfile.open("/home/mk/data_dmp/dmp_trajectories.csv");

    //clear joint trajectory
    JointTrajectoryset.clear();

    //read data file
    if(!laodtrjfile.is_open()){
            cout << "Data file load error... check the data file" << endl;
            exit(0);
        }
    else{
        iter=0;
        while(!laodtrjfile.eof()) 
        {
            laodtrjfile.getline(spell, 100);              //read lines

            if (spell[0]=='\0')     //empty line
                continue;

            i=0;
            data_seg[i] = strtok(spell,"\t");

            while(data_seg[i]!=NULL)                       //write data_segment with "\t"
                data_seg[++i] = strtok(NULL,"\t");
            
            Dim=i-1;                                         //check dimension : time-1

            cout<<"Feature dimension is"<<Dim<<endl;
            tempDataVec.resize(Dim);
            
            for(j=1;j<Dim;j++)
            {
                str=data_seg[j];
                str.erase(str.length(),1) ;
                tempdata = static_cast<float>(atof(str.c_str())) ;
                tempDataVec[j]=tempdata;

            }

            JointTrajectoryset.push_back(tempDataVec);
            iter++;
        } 
    }

   laodtrjfile.close();

   //setDimension
   dimension=Dim;

   //print trajectory
   printTrajectory();
}

bool DMP_Manager::makeLFDRequest()
{
    dmp::DMPTraj trajectory_msgs;
    int time_length = JointTrajectoryset.size();
    int trj_length = JointTrajectoryset[0].size();
    float dt=0.01;
    float K = 100.0;
    float D = 2.0 * sqrt(K);

    for(int i(0);i<time_length;i++)
    {
        dmp::DMPPoint dmp_point;        
        for(int j(0);j<JointTrajectoryset[i].size();j++)
        {
            float tempdata = static_cast<float> (JointTrajectoryset[i][j]);
            dmp_point.positions.push_back(tempdata);
        }

       trajectory_msgs.points.push_back(dmp_point);
       trajectory_msgs.times.push_back(static_cast<float>(i*dt));
    }

    Kgains.resize(dimension);
    Dgains.resize(dimension);
           
    for(int i(0);i<dimension;i++)
    {
        Kgains[i]=K;
        Dgains[i]=D;
    }

}


bool DMP_Manager::makeSetActiveRequest()
{




}


bool DMP_Manager::makeGetPlanRequest()
{




}
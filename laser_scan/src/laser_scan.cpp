#include <ros/ros.h>
#include <iostream>
#include <std_msgs/String.h>
#include <math.h>       
#include <sstream>
#include <sensor_msgs/LaserScan.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Int16.h>
using namespace std;

sensor_msgs::LaserScan laser;
std::vector<float> laser_ranges;
std_msgs::Int16 speed;
int i=0, vmax=1000;
float obs_1=0, obs_2=0,obs_3=0,aux=0,dmin=0.5,dmax=1.5,obs=0, caja_0=0,caja_1=0,caja_2=0,caja_3=0,caja_4=0,caja_5=0;

void Callback_laser(const sensor_msgs::LaserScan::ConstPtr& msg)
{
    laser_ranges.clear();
    for(size_t i=0; i < msg->ranges.size(); i++)
    {
       laser_ranges.push_back(msg->ranges[i]);
       cout<<i<<" - " << laser_ranges[i] << "\n ";
    }    

for(int j=240; j < 271; j++)
    {
       cout<<j<<" - " << laser_ranges[j] << "\n ";
    } 

    if(laser_ranges[0] < 10)
        obs_1=laser_ranges[0];
    if(laser_ranges[1] < 10)
        obs_2=laser_ranges[1];
    if(laser_ranges[359] < 10)
        obs_3=laser_ranges[359];
    //cout << "obs_1: " << obs_1 << "\n";
    //cout << "obs_2: " << obs_2 << "\n";
    //cout << "obs_3: " << obs_3 << "\n";
    /*if(laser_ranges[268] < 10) 
        caja_0=laser_ranges[268];
    if(laser_ranges[269] < 10) 
        caja_1=laser_ranges[269];
    if(laser_ranges[270] < 10) 
        caja_2=laser_ranges[270];*/
    /*if(laser_ranges[253] < 10) 
        caja_0=laser_ranges[253];
    if(laser_ranges[254] < 10) 
        caja_1=laser_ranges[254];
    if(laser_ranges[255] < 10) 
        caja_2=laser_ranges[255];
    
    if(laser_ranges[256] < 10) 
        caja_3=laser_ranges[256];
    if(laser_ranges[257] < 10) 
        caja_4=laser_ranges[257];
    if(laser_ranges[258] < 10) 
        caja_5=laser_ranges[258];
    */
    cout << "269: " << caja_0 << "\n";
    cout << "270: " << caja_1 << "\n";
    cout << "271: " << caja_2 << "\n";
    cout << "269: " << caja_0 << "\n";
    cout << "270: " << caja_1 << "\n";
    cout << "271: " << caja_2 << "\n\n";         
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "object_detection"); 
    ros::NodeHandle n;
    ros::Subscriber laser_subscriber;

    laser_subscriber = n.subscribe<sensor_msgs::LaserScan>("/scan", 100, Callback_laser);
    ros::Publisher speeds_pub = n.advertise<std_msgs::Int16>("/object_detection/speed", 1);
    
    while (ros::ok())
    {    
        ros::Rate loop_rate(10); 
        obs=(obs_1+obs_2+obs_3)/3;  
        ros::spinOnce(); 
        
        if (obs <= 1.5){
                    aux =(obs-dmin)*100;
                    if (aux <= 0)
                        aux=0;
                    //cout <<"aux: "<< aux << "\n";
                    //cout <<"dmin: "<< dmin << "\n";    
                    speed.data = (vmax/((dmax-dmin)*100) * aux)*-1;
                    if(speed.data <= 10 && speed.data>=-10){
                                speed.data=0;    
                                }

                    speeds_pub.publish(speed);                

        }        
        
        loop_rate.sleep();
    }
}

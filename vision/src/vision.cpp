#include <ros/ros.h>
#include <iostream>
#include <std_msgs/String.h>
#include <math.h>       
#include <sstream>
#include <sensor_msgs/LaserScan.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Int16.h>
#include "std_msgs/Int32MultiArray.h"
#include "nav_msgs/Path.h"

using namespace std;

std_msgs::Int32MultiArray pos;
nav_msgs::Path path;
geometry_msgs::PoseStamped p;


void loadMap()
{
    /////1
    p.pose.position.x = 0;
    p.pose.position.y = 0;
    p.pose.position.z = 0;
    path.poses.push_back(p);
    /////2
    p.pose.position.x = 0;
    p.pose.position.y = 2;
    p.pose.position.z = 0;
    path.poses.push_back(p);
    /////3
    p.pose.position.x = 0;
    p.pose.position.y = 2;
    p.pose.position.z = 0;
    path.poses.push_back(p);

}
/*
nav_msgs::Path newPath;
newPath.poses.push_back(path.poses[i]);
    newPath.header.frame_id = "map";

    geometry_msgs::PoseStamped p;
    int currentCell = startCell;
    
    p.pose.orientation.w = 1;
    p.header.frame_id = "map";
    resultPath.poses.clear();
    resultPath.poses.push_back(p);

    geometry_msgs::Point old_p = path.poses[i].pose.position;
    geometry_msgs::Point new_p = newPath.poses[i].pose.position;
    geometry_msgs::Point new_p_next = newPath.poses[i+1].pose.position;
    geometry_msgs::Point new_p_prev = newPath.poses[i-1].pose.position;
*/

int main(int argc, char** argv)
{
    ros::init(argc, argv, "vision"); 
    
    ros::NodeHandle n;

    ros::Publisher position = n.advertise<nav_msgs::Path>("/path", 1);
    
    while (ros::ok())
    {    

        ros::Rate loop_rate(10); 
        ros::spinOnce(); 

        loadMap();
        position.publish(path);    

        sleep(5);
/*
        pos.data[0]=1;
        pos.data[1]=0;
        position.publish(pos);
              
        sleep(5);
     
        pos.data[0]=2;
        pos.data[1]=2;
        position.publish(pos);
        
        sleep(5);

        pos.data[0]=1;
        pos.data[1]=0;
        position.publish(pos);
        
        sleep(5);

        pos.data[0]=2;
        pos.data[1]=2;
        position.publish(pos);
        
        sleep(5);
      
        pos.data[0]=1;
        pos.data[1]=0;
        position.publish(pos);
        
        sleep(5);
*/
        loop_rate.sleep();

    }
}

#include <ros/ros.h>
#include <iostream>
#include <std_msgs/String.h>
#include <math.h>       
#include <sstream>
#include <sensor_msgs/LaserScan.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Int16.h>
#include "std_msgs/Int32MultiArray.h"

using namespace std;

std_msgs::Int32MultiArray pos;

/*
nav_msgs::Path newPath;
newPath.poses.push_back(path.poses[i]);
    newPath.header.frame_id = "map";

    geometry_msgs::PoseStamped p;
    int currentCell = startCell;
    p.pose.position.x = (currentCell % map.info.width)*map.info.resolution + map.info.origin.position.x;
    p.pose.position.y = (currentCell / map.info.width)*map.info.resolution + map.info.origin.position.y;
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

    ros::Publisher position = n.advertise<std_msgs::Int32MultiArray>("/position", 1);
    
    while (ros::ok())
    {    
        ros::Rate loop_rate(10); 
        ros::spinOnce(); 

        pos.data.clear();
        pos.data.push_back(11);
        pos.data.push_back(11);
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

        pos.data[0]=2;
        pos.data[1]=2;
        position.publish(pos);
        
        sleep(5);
      
        pos.data[0]=1;
        pos.data[1]=0;
        position.publish(pos);
        
        sleep(5);

        loop_rate.sleep();

    }
}

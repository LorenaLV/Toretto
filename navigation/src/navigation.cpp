#include <ros/ros.h>
#include <iostream>
#include <std_msgs/String.h>
#include <math.h>       
#include <sstream>
#include <sensor_msgs/LaserScan.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Int16.h>
#include <math.h>
#include "std_msgs/Int32MultiArray.h"
#include "nav_msgs/Path.h"

#define PI 3.14159265
#define E 2.7182818284590
#define Steering_max = 0.57

using namespace std;

sensor_msgs::LaserScan laser;
std::vector<float> laser_ranges;
std_msgs::Int16 speed;
std_msgs::Int16 speed_obj;
std_msgs::Int16 steering;

bool object=false;

int i=0, vmax=1000;

float time_s=0, t_100=77.3;
float x_i=10, y_i=10, theta_i=0;
float x_i1=0, y_i1=0, theta_i1=0;
float err_theta=0;
float V=0, Vmax=2;
float alfa=1, vy=0, vx=0;

ros::Publisher speeds_pub;
ros::Publisher steering_pub;


float navigation(){

        theta_i1= atan((y_i - y_i1)/(x_i-x_i1));
        
        
        cout << "ti: " << theta_i1 << "\n";

        return theta_i1;
    /*
        err_theta = theta_i1 - theta_i;

        V= Vmax*pow(E,((pow(err_theta,2)/ 2* alfa))*-1);

        cout << "t: " << theta_i1 << "\n";
        cout << "V: " << V << "\n";

        vx = Vmax * cos(theta_i1);
        vy = Vmax * sin(theta_i1);

        y_i1 = vy + y_i1;
        x_i1 = vx + x_i1;

        cout << "xi: " << x_i1 << "\n";
*/
}

void giro(float theta)
{
        time_s=(t_100*100/speed.data)*-1;
        steering.data=290;
        steering_pub.publish(steering);  
        cout << "Steering: " << steering.data <<"\n" ; 
        cout << "Time: " << time_s <<"\n" ; 
        sleep(time_s);
        steering.data=120;
        steering_pub.publish(steering);  
        cout << "Steering: " << steering.data <<"\n" ; 
            
}

void Callback_vision(const nav_msgs::Path& path)
{
    float theta;


    x_i = path.poses[1].pose.position.x;
    y_i = path.poses[1].pose.position.y;

    cout << "x_i: "<< x_i << "\n";
    cout << "y_i: "<< y_i << "\n";
    theta= navigation();
    cout << "theta" << theta << "\n";
    /*
    if (theta < -0.1 || theta > 0.1)
    {
            giro(theta);
            
    }

    else{
            steering.data=120;
            steering_pub.publish(steering);   
            cout << "Steering: " << steering.data <<"\n" ;
    }  */
        
}



void Callback_object(const std_msgs::Int16::ConstPtr& msg)
{
      cout << "object true" << "\n";
      object=true;
      speed_obj.data = msg->data ;
                
}


int main(int argc, char** argv)
{
    ros::init(argc, argv, "navigation");       
    ros::NodeHandle n;   
   
    speeds_pub = n.advertise<std_msgs::Int16>("/manual_control/speed", 1);
    steering_pub = n.advertise<std_msgs::Int16>("/manual_control/steering", 1);
    
    ros::Subscriber position_subscriber = n.subscribe("/path", 1, Callback_vision);
    ros::Subscriber object_subscriber = n.subscribe("/object_detection/speed", 1, Callback_object);
    
    
    while (ros::ok())
    {    
        ros::Rate loop_rate(10); 
        ros::spinOnce(); 

        if(object){
            speeds_pub.publish(speed_obj);
            cout << "Speed Object: " << speed_obj.data <<"\n" ;
        }

        else{
            speed.data=-1000;
            speeds_pub.publish(speed);
            cout << "Speed: " << steering.data <<"\n" ;
        }

        loop_rate.sleep();

    }
}

#include <iostream>
#include "ros/ros.h"
#include "std_msgs/Int16.h"
#include "nav_msgs/Path.h"
#include "math.h"

std_msgs::Int16 speedP;
std_msgs::Int16 steeringP;

float x_i=0, y_i=0, error_ang=0;

void callback_errorcalc(const nav_msgs::Path& path)
{
        std::cout<<"Leyendo Path"<<std::endl;
        x_i = path.poses[0].pose.position.x;
        y_i = path.poses[0].pose.position.y;
        std::cout << "x_i: "<< x_i << "\n"<<std::endl;
        std::cout << "y_i: "<< y_i << "\n"<<std::endl;
       
        

        /*Funcion que calcula el error*/
        error_ang=atan(x_i-.25/y_i);

        if(error_ang <= 0.57 && error_ang>=-0.57){
           steeringP.data = error_ang*(170/0.57)+120;
        }else if(error_ang > 0.57){
                 steeringP.data = 290; 
                 }else if(error_ang <- 0.57){
                           steeringP.data=-50;
                           }
        
        
        /*Funcion que calcula las nuevas velocidades y steering*/
        speedP.data = 3000;
        //steeringP.data = 290;

}

int main(int argc,char **  argv)
{
        std::cout << "Inicializando sigue el camino..." <<std::endl;
        ros::init(argc,argv,"followPath");
        ros::NodeHandle n;
        ros::Publisher pubSpeed = n.advertise<std_msgs::Int16>("/manual_control/speed" ,1);
        ros::Publisher pubSteering = n.advertise<std_msgs::Int16>("/manual_control/steering",1);
        ros::Subscriber subPath = n.subscribe("/lane",1,callback_errorcalc);
        ros::Rate loop(30);

        while(ros::ok())
        {
                pubSpeed.publish(speedP);
                pubSteering.publish(steeringP);
                ros::spinOnce();
                loop.sleep();
        }

        return 0;
}


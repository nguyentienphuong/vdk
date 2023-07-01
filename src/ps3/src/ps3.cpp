#include <ros/ros.h>
#include <sensor_msgs/Joy.h>
#include <geometry_msgs/Twist.h>
#include "std_msgs/Float32.h"
#include "std_msgs/Int16.h"
#include "std_msgs/Int8.h"


// vi tri cua mang button
#define nhan 0
#define tron 1
#define tam_giac 2
#define vuong 3
#define trai_tren 4
#define phai_tren 5
#define trai_duoi 6
#define phai_duoi 7
#define select 8
#define start 9
#define connect 10
#define analog_trai 11
#define analog_phai 12
#define up 13
#define down 14
#define left 15
#define right 16


// vi tri cua mang axes
#define trai_sang 0
#define trai_len 1
#define nut_duoi_trai 2
#define phai_sang 3
#define phai_len 4
#define nut_duoi_phai 5


ros::Publisher pub;
ros::Publisher pub_type;
geometry_msgs::Twist data;
std_msgs::Int8 type;


double v_dai = 0, v_goc = 0;
int8_t count;


std::string topic_vdai_vgoc;


void joyTwistCallback(const sensor_msgs::JoyConstPtr &joy)
{
    if(joy->axes[trai_len]>0.5)     //tien
    {
        if(joy->buttons[trai_tren])
        {
            data.angular.z=v_goc;
        }
        else  if(joy->buttons[phai_tren])
        {
            data.angular.z=-v_goc;
        }
        else
        {
            data.angular.z=0;
        }
        data.linear.x=v_dai;
        
    }
    else if(joy->axes[trai_len]<-0.5)   //lui
    {
        if(joy->buttons[trai_tren])
        {
            data.angular.z=-v_dai/3;
        }
        else  if(joy->buttons[phai_tren])
        {
            data.angular.z=v_goc;
        }
        else
        {
            data.angular.z=0;
        }
        data.linear.x=-v_dai;
    }
    else
    {
        if(joy->buttons[trai_tren])
        {
            data.linear.x=0;
            data.angular.z=v_goc;
        }
        else if(joy->buttons[phai_tren])
        {
            data.linear.x=0;
            data.angular.z=-v_goc;
        }
        else
        {
            data.linear.x=0;
            data.angular.z=0;
        }
        
    }

    
    if(joy->axes[phai_sang]>0.5) // Di sang trai
    {
        
        data.linear.y = -v_dai;
       
    }
    else if(joy->axes[phai_sang]<-0.5) // Di sang phai
    {
      
        data.linear.y = v_dai;
     
    }
    else
    {
        data.linear.y = 0;
    }

    // if(joy->buttons[tam_giac]) // di tien xien phai
    // {
    //     data.linear.x = v_dai;
    //     data.linear.y = -v_dai;
        
    // }
    // else
    // {
    //     data.linear.x= 0;
    //     data.linear.y = 0;
    // }

    // if(joy->buttons[vuong]) // di tien xien trai
    // {
    //     data.linear.x = v_dai;
    //     data.linear.y = v_dai;
    // }
    // else
    // {
    //     data.linear.x= 0;
    //     data.linear.y = 0;
    // }

    // if(joy->buttons[tam_giac]) // di lui xien trai
    // {
    //     data.linear.x = -v_dai;
    //     data.linear.y = v_dai;
    // }
    // else
    // {
    //     data.linear.x= 0;
    //     data.linear.y = 0;
    // }

    // if(joy->buttons[tron]) // di lui xien phai
    // {
    //     data.linear.x = -v_dai;
    //     data.linear.y = -v_dai;
    // }
    // else
    // {
    //     data.linear.x= 0;
    //     data.linear.y = 0;
    // }

    if(joy->buttons[start]) //quay tai cho
    {
        data.linear.x= 0;
        data.linear.y = 0;
        data.angular.z= v_goc;
    }



    if(joy->buttons[select]) //chuyen dang chan di
    {
        
        count++;
        if (count ==4)
        {
            count = 0;
        }
        type.data = count;
 
        pub_type.publish(type);
        // ROS_INFO("count=%d",count);
    }
    
}

int main(int argc, char **argv)
{
 ros::init(argc, argv, "ps3_node");
 ros::NodeHandle node_handle;
 ros::NodeHandle private_node_handle("~");//node param
 ros::Subscriber joy_subsriber = node_handle.subscribe<sensor_msgs::Joy>("joy",10,joyTwistCallback) ;
 private_node_handle.param<std::string>("topic_vdai_vgoc", topic_vdai_vgoc, "Twist");//cong usb
 private_node_handle.param<double>("v_dai", v_dai, 0);
 private_node_handle.param<double>("v_goc", v_goc, 0);
 pub = node_handle.advertise<geometry_msgs::Twist>(topic_vdai_vgoc, 2);
 pub_type = node_handle.advertise<std_msgs::Int8>("type",1000);
 ROS_INFO("Start ");
 ros::Rate loop_rate(50);//khai bao vong lap 10hz
 while(ros::ok())
 {
    pub.publish(data);
    pub_type.publish(type);
    ros::spinOnce();
    loop_rate.sleep();
 }
 return 0;
}
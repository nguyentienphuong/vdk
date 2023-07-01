#include "ros/ros.h"
#include "serial/serial.h"
#include "std_msgs/Float32.h"
#include "std_msgs/Int16.h"
#include "std_msgs/Int8.h"
#include "serial/serial.h"
#include "math.h"
#include "stdio.h"
#include <geometry_msgs/Twist.h>

uint8_t nhan_data,count;
uint8_t doc_mcu[4];
uint8_t gui_mcu[6]={0x02,0,0,0,0,0x03};
int16_t angle;

uint32_t pi = 3.14159265358979323846264338327950288419716939937510;
std::string port = "/dev/ttyUSB0";
serial::Serial ser;
std_msgs::Int16 msg;

int8_t vx;
int8_t vy;
int8_t alpha;
int8_t gate_type;



void ket_noi_serial()
{
    try
    {
        ser.setPort(port);
        ser.setBaudrate(115200);
        serial::Timeout to = serial::Timeout::simpleTimeout(1000);
        ser.setTimeout(to);
        ser.open();
    }
    catch (serial::IOException &e)
    {
        ROS_ERROR_STREAM("Khong the ket noi serial " << ser.getPort() << ". Thu lai.");
        ros::Duration(5).sleep();
    }
    if (ser.isOpen())
    {
        ROS_DEBUG_STREAM("Mo cong serial " << ser.getPort() << " Qua trinh khoi tao hoan tat.");
    }
}

int16_t nhan_serial()
{
    while (ser.available())
        {
            ser.read(&nhan_data,1);
            if(count==0&&nhan_data!=0x02)
                break;
            if(count==3&&nhan_data!=0x03)
                break;
            if(count==3&&nhan_data==0x03)
            {  
                angle =doc_mcu[1]<<8|doc_mcu[2];
                // ROS_INFO("IMU: angle = %d ", angle);
                count=0;
            }
            else
            {
                doc_mcu[count]=nhan_data;
                count++;
            }
        }
        return angle;
}

void nhan_joy(const geometry_msgs::Twist::ConstPtr& data)
{
    vx = data->linear.x;
    vy = data->linear.y;
    alpha = data->angular.z;

}
void nhan_type(const std_msgs::Int8::ConstPtr& type)
{
    gate_type = type->data;
}

void ghi_serial( int8_t vx, int8_t vy, int8_t alpha, int8_t gate_type)    //gui xuong vdk
{
    gui_mcu[1]= vy;
    gui_mcu[2]= vx;
    gui_mcu[3]= alpha;
    gui_mcu[4]= gate_type;
    ser.write(gui_mcu,6);
}



int main(int argc, char **argv)
{
	ros::init(argc, argv, "send_speed_node");
    ros::NodeHandle nh1;
    ros::Subscriber twist_subscriber = nh1.subscribe<geometry_msgs::Twist>("Twist", 10, nhan_joy);
    ros::NodeHandle nh2;
    ros::Subscriber type_subscriber = nh2.subscribe<std_msgs::Int8>("type", 10, nhan_type);
    ros::NodeHandle n;
    ros::Publisher pub = n.advertise<std_msgs::Int16>("angle", 1000);

    ket_noi_serial();

    for(uint8_t i = 0; i < 100; i++)
    {
        ghi_serial(0, 0, 0, 0);//time out ghi_serial
    }

    ros::Rate rate_sleep(100);
	while (ros::ok())
    {
    msg.data=nhan_serial();
    pub.publish(msg);

    ghi_serial(vx, vy, alpha, gate_type);
   
    // ghi_serial(-6, 0, 56, 1);
    ROS_INFO("Pram Send Speed(vx, vy, al, gatetype): [%d, %d, %d, %d]",vx, vy, alpha, gate_type);
    ROS_INFO("IMU: angle = %d ", msg.data);
    

      rate_sleep.sleep();
      ros::spinOnce();
    }
	return 0;
}

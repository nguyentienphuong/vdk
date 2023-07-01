
#include "ros/ros.h"	
#include "serial/serial.h"
#include "std_msgs/Int16.h"
//#include "std_msgs/Int8MultiArray.h"

uint8_t nhan_data,count;
uint8_t doc_mcu[4];
uint8_t gui_mcu[4]={0x02,0,0,0x03};
int16_t angle;
std::string port = "/dev/ttyUSB0";
serial::Serial ser;
std_msgs::Int16 msg, portmsg;

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
                ROS_INFO("Xung nhan: en = %d ", angle);
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

int main(int argc, char **argv)
{
	ros::init(argc, argv, "en_imu");//Khaibao node
	ros::NodeHandle n;//Handle
	ros::Publisher pub = n.advertise<std_msgs::Int16>("left_ticks", 1000);
    ros::Publisher pub1 = n.advertise<std_msgs::Int16>("right_ticks", 1000);
    ros::Publisher pub2 = n.advertise<std_msgs::Int16>("imu", 1000);
	ros::Rate loop_rate(100);//tan so lam viec Hz
    ket_noi_serial();

	while(ros::ok())
	{
        msg.data=nhan_serial();
		
        pub.publish(msg);
        //write_serial(1,0, 100);
		ros::spinOnce();//Dung tai cho
		loop_rate.sleep();//Delay
	}
	return 0;
}

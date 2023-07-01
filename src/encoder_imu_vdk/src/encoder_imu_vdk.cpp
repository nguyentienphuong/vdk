#include "ros/ros.h"//Khai bao		
#include "serial/serial.h"
#include "std_msgs/Int16.h"
//#include "std_msgs/Int8MultiArray.h"

uint8_t nhan_data,count;
uint8_t doc_mcu[4];
uint8_t gui_mcu[6]={0x02,0,0,0,0,0x03};
int16_t angle;
uint8_t recv;
uint32_t pi = 3.14159265358979323846264338327950288419716939937510;
std::string port = "/dev/ttyUSB0";
serial::Serial ser;
std_msgs::Int16 msg, portmsg;

// uint8_t vx = 6;
// uint8_t vy = 0;
// uint8_t alpha = 0;
// uint8_t gate_type = 1;

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


// int16_t nhan_serial()
// {
//     while (ser.available())
//         {
//             ser.read(&nhan_data,1);
//             if(count==0&&nhan_data!=0x02)
//                 break;
//             if(count==3&&nhan_data!=0x03)
//                 break;
//             if(count==3&&nhan_data==0x03)
//             {  
//                 angle =doc_mcu[1]<<8|doc_mcu[2];
//                 ROS_INFO("IMU: angle = %d ", angle);
//                 count=0;
//             }
//             else
//             {
//                 doc_mcu[count]=nhan_data;
//                 count++;
//             }
//         }
//         return angle;
// }

void ghi_serial(uint8_t vx, uint8_t vy, uint8_t alpha, uint8_t gate_type)//gui day byte gia tri van toc xuong vdk
{
    gui_mcu[1]= vx;
    gui_mcu[2]= vy;
    gui_mcu[3]= alpha;
    gui_mcu[4]= gate_type;

    ser.write(gui_mcu,6);
}

// void pwm_nhan(const std_msgs::Int8::ConstPtr& pwmmsg)
// {
//     ROS_INFO("Gia tri pwm nhan duoc: pwm = [%d]", pwmmsg->data);
//     recv=pwmmsg->data;
//     if (recv<0)
//     {
//         pwm=abs(recv);
//         chieu=1;
//     }
//     else
//     {
//         pwm=recv;
//         chieu=0;
//     }
//     ghi_serial(pwm,chieu);
// }

int main(int argc, char **argv)
{
	ros::init(argc, argv, "vi_dieu_khien");//Khaibao node
	ros::NodeHandle n;//Handle
	// ros::Publisher pub = n.advertise<std_msgs::Int16>("vt_hien_tai", 1000);//pub: ten topic hien thi; vam_toc_hien_tai: ten topic link voi "sub" hien thi trong info; 1000: so ki tu nhan dc trong 1 vong lap
    // ros::Subscriber sub = n.subscribe("van_toc_dat", 1, pwm_nhan);
	ros::Rate loop_rate(1000);//tan so lam viec Hz
    ket_noi_serial();
    
    for(uint8_t i = 0; i < 100; i++)
    {
        ghi_serial(0, 0, 0, 0);//time out ghi_serial
    }
    
	// while(ros::ok())//KHi ros chay ok[ INFO] [1621072881.337249973]: Xung nhan: e1 = 0 
	// {
    //     // msg.data=nhan_serial();
        
		//ROS_INFO("Giadelta_en tri nhan encoder doc duoc: en1 = [%d]", msg.data);
        // pub.publish(msg);
        //write_serial(1,0, 100);
        ghi_serial(6, 6, (4*pi)/225, 1);
		// ros::spinOnce();//Dung tai cho
		loop_rate.sleep();//Delay
	// }
    // ser.close();
	// return 0;
}

#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include <iostream>

using namespace ros;

int main(int argc, char **argv){
	init(argc,argv,"demo_topic_publisher");
	NodeHandle node_obj;
	Publisher number_publisher = node_obj.advertise<std_msgs::Int32>("/numbers",10);
	Rate loop_rate(10);
	int nc = 0;
	while(ok()){
		std_msgs::Int32 msg;
		msg.data = nc;
		ROS_INFO("%d",msg.data);
		number_publisher.publish(msg);
		spinOnce();
		loop_rate.sleep();
		++nc;
		
	}
	return 0;
}
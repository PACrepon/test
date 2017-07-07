#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include <iostream>

using namespace ros;

void n_cb(const std_msgs::Int32::ConstPtr& msg){
	ROS_INFO("Received [%d]",msg->data);
}

int main(int argc,char **argv){
	init(argc,argv,"demo_topic_subscriber");
	NodeHandel node_obj;
	Subscriber n-s = node_obj.subscribe("/numbers",10,n_cb);
	spin();
	return 0;
}
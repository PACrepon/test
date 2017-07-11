/* 
 * rosserial Subscriber Example
 * Blinks an LED on callback
 */
#define pin_blink 10
#include <ros.h>
#include <std_msgs/Empty.h>

ros::NodeHandle  nh;

void messageCb( const std_msgs::Empty& toggle_msg){
  digitalWrite(pin_blink, HIGH-digitalRead(pin_blink));   // blink the led
}

ros::Subscriber<std_msgs::Empty> sub("toggle_led", &messageCb );

void setup(){ 
  pinMode(pin_blink, OUTPUT);
  nh.getHardware()->setBaud(57600);
  nh.initNode();
  nh.subscribe(sub);
}

void loop(){
  nh.spinOnce();
  delay(1);
}


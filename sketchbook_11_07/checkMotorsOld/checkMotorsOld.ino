#include "constant.h"
#include <ros.h>
#include <geometry_msgs/Twist.h>

ros::NodeHandle nh; // node ros
float v = 0.0, w = 0.0;

void update_motors(const geometry_msgs::Twist& cmd_speed) { 
  v = cmd_speed.linear.x;
  w = cmd_speed.angular.z;
}


void controlBot(){
  float wr = (2*v+w*taille)/(2*radius);
  float wl = (2*v-w*taille)/(2*radius);
  if(wr>0){
    digitalWrite(rightDir,LOW);
  }else{
    digitalWrite(rightDir,HIGH);
  }
  
  if(wl>0){
    digitalWrite(leftDir,LOW);
  }else{
    digitalWrite(leftDir,HIGH);
  }

  analogWrite( leftPWM, map( abs(wl) , 0.0 , 1.0 , leftMin , leftMax ));
  analogWrite( rightPWM, map( abs(wr) , 0.0 , 1.0 , rightMin , rightMax ));
}

ros::Subscriber<geometry_msgs::Twist> speed_sub("cmd_vel",&update_motors); 

void setup() {
  pinMode( leftPWM, OUTPUT ); 
  pinMode( rightPWM, OUTPUT );
  pinMode( leftDir, OUTPUT );
  pinMode( rightDir, OUTPUT );
  pinMode( ledPin, OUTPUT );
  
  digitalWrite( leftDir, LOW );
  digitalWrite( rightDir, LOW );

  digitalWrite( ledPin, HIGH );
  analogWrite( leftPWM, 0 );
  analogWrite( rightPWM, 0 );

  nh.getHardware()->setBaud(57600);
  nh.initNode();
  nh.subscribe(speed_sub);
}

void loop() {
  controlBot();
  nh.spinOnce();
  delay(1);
}

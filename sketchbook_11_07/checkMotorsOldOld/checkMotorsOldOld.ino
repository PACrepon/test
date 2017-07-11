#define leftPWM 3 // PWM B
#define leftDir 12//DIR B
#define leftMin 75 //147
#define leftMax 255


#define rightPWM 11   // PWM A
#define rightDir 13  //DIR A
#define rightMin 65 //126
#define rightMax 255



#define ledPin 10   //Led


#include <ros.h>
#include <std_msgs/Float32.h>

ros::NodeHandle nh; // node ros
float locale_cmd_speed = 0;

void update_motors(const std_msgs::Float32& cmd_speed) { 
  locale_cmd_speed = cmd_speed.data;
}

ros::Subscriber<std_msgs::Float32> speed_sub("cmd_vel",&update_motors); 


void setup() {

  pinMode( leftPWM, OUTPUT ); 
  pinMode( rightPWM, OUTPUT );
  pinMode( leftDir, OUTPUT );
  pinMode( rightDir, OUTPUT );
  pinMode( ledPin, OUTPUT ); 

  digitalWrite( ledPin, HIGH );
  analogWrite( leftPWM, 0 );
  analogWrite( rightPWM, 0 );

  nh.getHardware()->setBaud(57600);
  nh.initNode();
  nh.subscribe(speed_sub);

}

void loop() {
  
  if (locale_cmd_speed < 0){
    digitalWrite( rightDir, HIGH );
   digitalWrite( leftDir, HIGH );
  }

  else{
    digitalWrite( rightDir, LOW );
    digitalWrite( leftDir, LOW );
  }

  if (locale_cmd_speed == 0){
    analogWrite( leftPWM , 0 ); 
    analogWrite( rightPWM ,0 );
  }

  else{
   analogWrite( leftPWM, map( abs(locale_cmd_speed) , 0.0 , 1.0 , leftMin , leftMax ));
   analogWrite( rightPWM, map( abs(locale_cmd_speed) , 0.0 , 1.0 , rightMin , rightMax ));
  }

  nh.spinOnce();
  delay(1);
}


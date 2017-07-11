#include <ros.h>
#include <unicycle_mp/differential.h>

ros::NodeHandle nh; // node ros - to subscribe and publish what speed is given to the wheels

float locale_cmd_speed_right = 0;
float locale_cmd_speed_left = 0;
//float locale_cmd_speed_right1 = 0;
//float locale_cmd_speed_left1 = 0;

void update_motors(const unicycle_mp::differential& cmd_speed) { 

  locale_cmd_speed_right = cmd_speed.cmd_vel_right; // receive speed value from ros
  locale_cmd_speed_left = cmd_speed.cmd_vel_left; // receive speed value from ros

}

//unicycle_mp::differential rlvel;
ros::Subscriber<unicycle_mp::differential> speed_sub("cmd_vel",&update_motors); //waiting this info from ros and when receive it them update the speed
// cmd_vel is the ifo from topic
//ros::Publisher speedfromArdu_pub("speedfromArdu",&rlvel);// to publish

const int rightPWM = 3; // pins PWM A
const int leftPWM = 11; // PWM B

//const int rightDir = 12; // DIR A
//const int leftDir = 13; // DIR B

const int ledPin = 10; // Led

void setup() {
  pinMode( rightPWM, OUTPUT ); //Defining pins as output
  pinMode( leftPWM, OUTPUT );
  pinMode( rightDir, OUTPUT );
  pinMode( leftDir, OUTPUT );
  pinMode( ledPin, OUTPUT ); 

  digitalWrite( ledPin, HIGH );
  analogWrite( rightPWM, 0 );// start motors speed at 0
  analogWrite( leftPWM, 0 );

  nh.getHardware()->setBaud(57600);// need to be set before the initNode

  nh.initNode();

  nh.subscribe(speed_sub);

  //nh.advertise(speedfromArdu_pub);
}

float mapf(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void loop() {   
  //locale_cmd_speed_right1 = locale_cmd_speed_right; // receive speed value from ros
  //locale_cmd_speed_left1 = locale_cmd_speed_left; // receive speed value from ros
  //for right wheel
  if (locale_cmd_speed_right > 0){
    digitalWrite( rightDir, LOW );
    analogWrite( rightPWM, mapf(locale_cmd_speed_right,0,0.63,51,255)); //speed value normalization (0.63 is the vmax mesured with the camera and 51-0.2 is the value at with the robot start moving)
  }
  else if (locale_cmd_speed_right < 0) {
    digitalWrite( rightDir, HIGH );
    analogWrite( rightPWM, mapf(-locale_cmd_speed_right,0,0.63,51,255));  //speed value normalization 
  }
  else analogWrite( rightPWM , 0 ); 

  //for left wheel
  if (locale_cmd_speed_left > 0){
    digitalWrite( leftDir, LOW );
    analogWrite( leftPWM, mapf(locale_cmd_speed_left,0,0.63,51,255)); //speed value normalization 
  }
  else if (locale_cmd_speed_left < 0) {
    digitalWrite( leftDir, HIGH );
    analogWrite( leftPWM, mapf(-locale_cmd_speed_left,0,0.63,51,255));  //speed value normalization 
  }
  else analogWrite( leftPWM , 0 ); 

  //rlvel.cmd_vel_right = locale_cmd_speed_right1;
  // rlvel.cmd_vel_left = locale_cmd_speed_left1;

  // speedfromArdu_pub.publish(&rlvel);
  nh.spinOnce();
  delay(1);// 1 ms

}





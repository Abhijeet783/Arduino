/* in this code robot can change direction according to 
command given by Key topic. also having MPU installed
and able to get any angle passed as argument */


#include <ros.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Int8.h>
#include <std_msgs/String.h>
#include <Wire.h>

const int M1_plus=28;
const int M1_minus=29;
const int M2_plus=30;
const int M2_minus=31;
const int pwm1=5;
const int pwm2=4;
const int encoder1A=2;
const int encoder1B=22;
volatile unsigned long pos_i;
volatile unsigned long pos_i2;
ros::NodeHandle nh;

unsigned char KEY[2]={'m'};
bool angle_complete=0;

void message3(const std_msgs::String &msg)
{
nh.spinOnce();
KEY[0]=msg.data[0];

}

ros::Subscriber<std_msgs::String>sub2("/Keys",&message3);

void setup()
{
  nh.initNode();
  nh.subscribe(sub2);
  encoderInit();
  pinMode(M1_plus,OUTPUT);
  pinMode(M1_minus,OUTPUT);
  pinMode(M2_plus,OUTPUT);
  pinMode(M2_minus,OUTPUT);

  pinMode(pwm1,OUTPUT);
  pinMode(pwm2,OUTPUT);

  
  Serial.begin(57600);
}
void encoderInit()
{
    attachInterrupt(digitalPinToInterrupt(encoder1A),updateEncoder1,RISING);
    //attachInterrupt(digitalPinToInterrupt(encoder2A),updateEncoder2,RISING);
}

void updateEncoder1()
{   //Serial.print("interrupt");
    int b= digitalRead(encoder1B);
    int increment=0;
    if(b>0)
    {increment=1;}
    else
    {increment=-1;}
    pos_i=pos_i +increment;
  }

void forward(int pwm)
{
   digitalWrite(M1_plus,HIGH);
   digitalWrite(M1_minus,LOW);
   digitalWrite(M2_plus,HIGH);
   digitalWrite(M2_minus,LOW);
   digitalWrite(pwm1,pwm);
   digitalWrite(pwm2,pwm);
  }

void slow(int pwm)
{
   digitalWrite(M1_plus,HIGH);
   digitalWrite(M1_minus,LOW);
   digitalWrite(M2_plus,HIGH);
   digitalWrite(M2_minus,LOW);
   digitalWrite(pwm1,pwm);
   digitalWrite(pwm2,pwm);
  }

void right(int pwm)
{
   digitalWrite(M1_plus,HIGH);
   digitalWrite(M1_minus,LOW);
   digitalWrite(M2_plus,LOW);
   digitalWrite(M2_minus,HIGH);
   digitalWrite(pwm1,pwm);
   digitalWrite(pwm2,pwm);
  }
void left(int pwm)
{
   digitalWrite(M1_plus,LOW);
   digitalWrite(M1_minus,HIGH);
   digitalWrite(M2_plus,HIGH);
   digitalWrite(M2_minus,LOW);
   digitalWrite(pwm1,pwm);
   digitalWrite(pwm2,pwm);
  }

void stop_bro(int pwm)
{
     digitalWrite(M1_plus,HIGH);
   digitalWrite(M1_minus,HIGH);
   digitalWrite(M2_plus,HIGH);
   digitalWrite(M2_minus,HIGH);
   digitalWrite(pwm1,pwm);
   digitalWrite(pwm2,pwm);
  }


void manual_mode()
  {   Serial.println(KEY[0]);
      Serial.println("hi");
      nh.spinOnce();
      
      if(KEY[0]==119)//w
      {
         forward(250);
         nh.spinOnce();
      }
      else if(KEY[0]==97)//a
      {
         left(60);
         nh.spinOnce();
      }
      else if(KEY[0]==100)//d
      {
         right(60);
         nh.spinOnce();
      }
      else if(KEY[0]==115)//s
      {
         slow(100);
         nh.spinOnce();
      }
      else if(KEY[0]==120)//x
      {
         stop_bro(0);
         nh.spinOnce();
      }

      nh.spinOnce();

  }

void loop() 
  {
    forward(130);
    
    //manual_mode();
    Serial.println(pos_i);

  }

#include "HCPCA9685.h"

/* I2C slave address for the device/module. For the HCMODU0097 the default I2C address
 
is 0x40 */
 
#define  I2CAdd 0x40
 
/* Create an instance of the library */
 
HCPCA9685 HCPCA9685(I2CAdd);
 
void setup()
 
{
 
  /* Initialise the library and set it to 'servo mode' */
 
HCPCA9685.Init(SERVO_MODE);
 
  /* Wake the device up */
 
HCPCA9685.Sleep(false);
 
}

void head_downward(unsigned int Pos, int motor, int endd , int startt)
{
  for(Pos = startt; Pos< endd; Pos++)
 
  {
 
HCPCA9685.Servo(motor, Pos);
 
//HCPCA9685.Servo(8, Pos);
 
delay(10);
 
  }
  
  }


 void head_upward(unsigned int Pos, int motor, int endd , int startt)
 {
  for(Pos = endd; Pos>= startt; Pos--)
 
  {
 
HCPCA9685.Servo(motor, Pos);
 
//HCPCA9685.Servo(8, Pos);
 
delay(10);
 
  }
  }

  
void loop()
 
{
unsigned int Pos;
head_downward(Pos,3,200,100);
delay(1000);
 head_upward(Pos,3,200,100);
 delay(1000);
 head_downward(Pos,3,200,100);
delay(1000);
 head_downward(Pos,3,300,200);
delay(1000);
 head_upward(Pos,3,300,200);
 delay(1000);
 //....................
 head_downward(Pos,8,200,100);
delay(1000);
 head_upward(Pos,8,200,100);
 delay(1000);
 head_downward(Pos,8,200,100);
delay(1000);
 head_downward(Pos,8,300,200);
delay(1000);
 head_upward(Pos,8,300,200);
 delay(1000);
}

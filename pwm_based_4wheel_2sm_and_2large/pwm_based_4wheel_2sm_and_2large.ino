#define NMOTORS 4
#define M0 0
#define M1 1
#define M2 2
#define M3 3
const int enca[] = {20,18,19,21};
const int encb[]= {22,23,32,33};
const int pwm[] = {4,5,6,7};
const int in1[] = {28,36,32,34};
const int in2[] = {29,37,33,35};

#define CH1 8
#define CH2 9

int ch1Value;
int ch2Value;

int readChannel(int channelInput, int minLimit, int maxLimit, int defaultValue) {
  int ch = pulseIn(channelInput, HIGH, 30000);
  if (ch < 100) return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}

void setMotor(int dir, int pwmVal, int pwm, int in1, int in2){
  analogWrite(pwm,pwmVal);
  if(dir == 1){
    Serial.println("inside plus 1");
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
  }
  else if(dir == -1){
    Serial.println("inside -1");
    digitalWrite(in1,LOW);
    digitalWrite(in2,HIGH);
  }
  else{
    digitalWrite(in1,LOW);
    digitalWrite(in2,LOW);
  }  
}

void setup() {
  // Set up serial monitor
  Serial.begin(115200);

  // Set all pins as inputs
  pinMode(CH1, INPUT);
  pinMode(CH2, INPUT);
}


void loop() {

  // Get values for each channel
  ch1Value = readChannel(CH1, -100, 100, 0);
  ch2Value = readChannel(CH2, -100, 100, 0);

  // Print to Serial Monitor
  
  Serial.print("Ch1: ");
  Serial.print(ch1Value);
  Serial.print(" | Ch2: ");
  Serial.println(ch2Value);

//   setMotor(-1,100,5,36,37);
//   delay(1000);
//    setMotor(1,0,5,36,37);
//     delay(1000);
     setMotor(1,100,6,34,35);
     delay(1000);
  
//  
//  if(ch1Value>10 && ch1Value<105 && ch2Value>-10 && ch2Value<2 )
//  {
//    Serial.println("R");
////    int dir[]={-1,1,-1,1};
////    int pwr[]={100,100,100,100};
//    /*
//   for(int k = 0; k < NMOTORS; k++){
//      setMotor(dir[k],pwr[k],pwm[k],in1[k],in2[k]); // signal the motor
//   }
//   */
////   setMotor(-1,100,4,28,29);
//   setMotor(1,100,5,36,37);
////   setMotor(-1,100,6,32,33);
////   setMotor(1,100,7,34,35);
//  }
//  
//    else if(ch1Value>-10 && ch1Value<2 && ch2Value>-105 && ch2Value<-10 )
//  {
//    Serial.println("F");
////    int dir[]={1,1,1,1};
////    int pwr[]={100,100,100,100};
////   for(int k = 0; k < NMOTORS; k++){
////      setMotor(dir[k],pwr[k],pwm[k],in1[k],in2[k]); // signal the motor
////   }
////      setMotor(1,100,4,28,29);
//   setMotor(1,100,5,36,37);
////   setMotor(1,100,6,32,33);
////   setMotor(1,100,7,34,35);
//  }
//  
//    else if(ch1Value>-10 && ch1Value<2 && ch2Value>10 && ch2Value<105 )
//  {
//    Serial.println("B");
////    int dir[]={-1,-1,-1,-1};
////    int pwr[]={100,100,100,100};
////   for(int k = 0; k < NMOTORS; k++){
////      setMotor(dir[k],pwr[k],pwm[k],in1[k],in2[k]); // signal the motor
////   }
////      setMotor(-1,100,4,28,29);
//   setMotor(-1,100,5,36,37);
////   setMotor(-1,100,6,32,33);
////   setMotor(-1,100,7,34,35);
//  }
//  
//    else if(ch1Value>-105 && ch1Value<-10 && ch2Value>-10 && ch2Value<2 )
//  {
//    Serial.println("L");
////    int dir[]={1,-1,1,-1};
////    int pwr[]={100,100,100,100};
////   for(int k = 0; k < NMOTORS; k++){
////      setMotor(dir[k],pwr[k],pwm[k],in1[k],in2[k]); // signal the motor
////   }
////      setMotor(1,100,4,28,29);
//   setMotor(-1,100,5,36,37);
////   setMotor(1,100,6,32,33);
////   setMotor(-1,100,7,34,35);
//  }
//  
//  else
//  { 
////    int dir[]={-1,1,-1,1};
////    int pwr[]={0,0,0,0};
////   for(int k = 0; k < NMOTORS; k++){
////      setMotor(dir[k],pwr[k],pwm[k],in1[k],in2[k]); // signal the motor
////  }
////      setMotor(-1,0,4,28,29);
//   setMotor(1,0,5,36,37);
////   setMotor(-1,0,6,32,33);
////   setMotor(1,0,7,34,35);
//  Serial.println("IDLE");
//    }
  delay(5);
  
}

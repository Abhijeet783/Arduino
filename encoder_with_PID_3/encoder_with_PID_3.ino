#include <util/atomic.h> 

#include <math.h>

#define one_rev 3780
#define Wheel_circum 34.5714
#define Distance 3

/*------------ CLASS ------------*/
class SimplePID{
  private:
    float kp, kd, ki, umax;
    float eprev, eintegral;
    
  public:
    // Default initialization list
    SimplePID() : kp(1), kd(0), ki(0), umax(255), eprev(0.0), eintegral(0.0) {}
    
    // Set the parameters
    void setParams(float kpIn, float kdIn, float kiIn, float umaxIn){
      kp = kpIn; kd = kdIn; ki = kiIn; umax = umaxIn;
    }

    // Evaluate the signal
    void evalu(int value, int target, float deltaT,int &pwr, int &dir){
        
      // error
      int e = target - value;
      
      float dedt = (e-eprev)/(deltaT);
      eintegral = eintegral + e*deltaT;
      float u = kp*e + kd*dedt + ki*eintegral;
      //Abhijeet code for motor sync.
      
      //code ends
     
      // motor power
      pwr = (int) fabs(u);
      if( pwr > umax ){
        pwr = umax;
      }
           
      // motor direction
      dir = 1;
      if(u<0){
        dir = -1;
      }
            
      // store previous error
      eprev = e;
      //Serial.print("  ");
      //Serial.print(u);
    }
    
};

/*------------ GLOBALS AND DEFINITIONS ------------*/
// Define the motors
#define NMOTORS 4
#define M0 0
#define M1 1
#define M2 2
#define M3 3
const int enca[] = {20,18,19,21};
const int encb[]= {27,28,29,26};
const int pwm[] = {7,6,5,4};
const int in1[] = {23,24,31,32};
const int in2[] = {22,25,30,33};

// Global variables
long prevT = 0;
int posPrev[] = {0,0};

// positions
volatile int posi[] = {0,0,0,0};

// PID classes
SimplePID pid[NMOTORS];


/*------------ FUNCTIONS ------------*/
void setMotor(int dir, int pwmVal, int pwm, int in1, int in2){
  analogWrite(pwm,pwmVal);
  if(dir == 1){
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
  }
  else if(dir == -1){
    digitalWrite(in1,LOW);
    digitalWrite(in2,HIGH);
  }
  else{
    digitalWrite(in1,LOW);
    digitalWrite(in2,LOW);
  }  
}

template <int j>
void readEncoder(){
  int b = digitalRead(encb[j]);
  if(b > 0){
    posi[j]++;
  }
  else{
    posi[j]--;
  }
}


// targets
float target_f[] = {0,0,0,0};
long target[] = {0,0,0,0};

void setTarget(float t, float deltat){

  float positionChange[4] = {0.0,0.0,0.0,0.0};
  float pulsesPerTurn = 3780;//16*18.75; 
  float pulsesPerMeter = pulsesPerTurn*2.94;//3.5368;



  for(int k = 0; k < 4; k++){
    target[k] = (long) Distance*pulsesPerMeter;
  }
  

  
}

/*------------ SETUP ------------*/
void setup() {
  Serial.begin(9600);
  for(int k = 0; k < NMOTORS; k++){
    pinMode(enca[k],INPUT);
    pinMode(encb[k],INPUT);
    pinMode(pwm[k],OUTPUT);
    pinMode(in1[k],OUTPUT);
    pinMode(in2[k],OUTPUT);
    pid[k].setParams(1,0.1,0,255);
  }
  attachInterrupt(digitalPinToInterrupt(enca[M0]),readEncoder<M0>,RISING);
  attachInterrupt(digitalPinToInterrupt(enca[M1]),readEncoder<M1>,RISING);
  attachInterrupt(digitalPinToInterrupt(enca[M2]),readEncoder<M2>,RISING);
  attachInterrupt(digitalPinToInterrupt(enca[M3]),readEncoder<M3>,RISING);
}

/*------------ LOOP ------------*/
void loop() {
  long pos[4];
  // time difference
  long currT = micros();
  float deltaT = ((float) (currT - prevT))/( 1.0e6 );
  prevT = currT;
  //Serial.print(deltaT,6);
  // set target position
  setTarget(currT/1.0e6,deltaT);
  

  // Read the position in an atomic block to avoid a potential misread 
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    for(int k = 0; k < NMOTORS; k++){
      pos[k] = posi[k];
    }
  }
  int pwr[]={0,0,0,0};
  int dir[]={0,0,0,0};
  // Loop through the motors
  for(int k = 0; k < NMOTORS; k++){
    
    pid[k].evalu(pos[k],target[k],deltaT,pwr[k],dir[k]); // compute the position
  }
  for(int k = 0; k < NMOTORS-1; k++){
  if(pos[k]-pos[k+1]<0) {pwr[k]++;}
  else{pwr[k]--;}
  }
  
  for(int k = 0; k < NMOTORS; k++){
    setMotor(dir[k],pwr[k],pwm[k],in1[k],in2[k]); // signal the motor
  }

  for(int i = 0; i<4; i++){
    Serial.print(target[i]);
    Serial.print(" ");
  }
  for(int i = 0; i<4; i++){
    Serial.print(posi[i]);
    Serial.print(" ");
  }
  Serial.println();
  
}

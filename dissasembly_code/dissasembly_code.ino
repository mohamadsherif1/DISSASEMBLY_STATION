#include <Servo.h>  
Servo armservo; 
Servo suctionservo; 
#include <SpeedyStepper.h>
//const int LED_PIN = 13;
const int MOTOR_STEP_PIN = 2;
const int MOTOR_DIRECTION_PIN = 3;
const int LIMIT_SWITCH_PIN = 5;
const int Relaysuction = 13;
const int Relaypiston =12 ;
const int feedingsignal = 13;
const int armpin = 8;
const int suctionpin = 10;
int flag = 0;
int pos =0;
const int armcenter = 102;
const int suctioncenter = 85 ;
const int armbody = 0;
const int suctionbody = 179;
const int armface = 15;
const int suctionface = 165 ;
const int armfeed = 180;
const int suctionfeed = 10;
// const int feedingsignal = 9 ;
int loop1 =1;
int loop2 =1;
int armsteps = 0;
int suctionsteps =0;
SpeedyStepper stepper;
 

void setup() 
{
delay(5000);
  pinMode(9,OUTPUT);   // signal to feeding
  pinMode(11,INPUT);  // signal from conveyer
  armservo.attach(armpin);
  armservo.write(102);
  suctionservo.attach(suctionpin);
 suctionservo.write(87);
  //pinMode(IRsensor, INPUT );
  pinMode(Relaysuction, OUTPUT);
  pinMode(Relaypiston, OUTPUT);
  pinMode(LIMIT_SWITCH_PIN, INPUT_PULLUP);
  Serial.begin(9600);
  stepper.connectToPins(MOTOR_STEP_PIN, MOTOR_DIRECTION_PIN);
  digitalWrite(Relaypiston, HIGH);
  digitalWrite(Relaysuction, HIGH);
 
}



void loop() 
{
 delay(500);
int state = digitalRead(11);  // reading  conveyer
if(state==HIGH){
flag = 1;
}
while ( flag == 1){
 Serial.println("signal transferd");
  stepper.setStepsPerMillimeter(2.5*8);   
  stepper.setSpeedInMillimetersPerSecond(65);
  stepper.setAccelerationInMillimetersPerSecondPerSecond(20);
  const float homingSpeedInMMPerSec = 50.0;
  const float maxHomingDistanceInMM = 600;   
  const int directionTowardHome = -1;    
  if(stepper.moveToHomeInMillimeters(directionTowardHome, homingSpeedInMMPerSec, maxHomingDistanceInMM, LIMIT_SWITCH_PIN) != true)
  { 
  }
  Serial.println("homingdone");
  digitalWrite(9,HIGH);  // sending signal to feeding
  delay(2000);


 stepper.setSpeedInStepsPerSecond(1100);
 stepper.setAccelerationInStepsPerSecondPerSecond(400);
 stepper.moveRelativeInSteps(750*8);  // moving to the first location
  Serial.println("gone to the product location");
  delay(1000);

 
 digitalWrite(Relaypiston, LOW);// Let's turn on the relay of the piston
 Serial.println(" piston on SEQ1 ");
  delay(1000);
 /*  digitalWrite(Relaypiston, HIGH);// Let's turn on the relay of the piston
 Serial.println(" piston OFF   ");
  delay(1000);
   digitalWrite(Relaypiston, LOW);// Let's turn on the relay of the piston
 Serial.println(" piston on SEQ2 ");
  delay(1000);*/

 
 armservo.write(armface); // heading to the part face ////////////////////////////////////////////////////////////////////////////////
  suctionservo.write(suctionface); // suction brdo
Serial.println("suction and arm servos are in left to get the lead " );
 delay(1000);
  digitalWrite(Relaysuction, LOW);// Let's turn on the relay of the suction
  Serial.println(" suction on ");
 delay(1000); 
 
  
  armsteps= armface;
  suctionsteps = suctionface;
  while((loop1 == 1)||( loop2==1 )){
    armservo.write(armsteps);
    Serial.println("armstepsdone");
    if (armsteps == armcenter){
      loop1 = 0;
       Serial.println("armstepsdone");
    }
    else {
     armsteps ++; 
      }
      delay(15);
     suctionservo.write(suctionsteps);
      if (suctionsteps == suctioncenter){
      loop2 = 0;
      Serial.println("suctionstepsdone"); 
    }
    else {
     suctionsteps --; 
    }
   delay(15);
}
armservo.write(armcenter);
suctionservo.write(suctioncenter);
 Serial.println("arm and suction servo centered " );
 loop1=1;
 loop2=1;
 delay(1000);

 
 stepper.moveRelativeInSteps(-650*8);  // moving to the first indexer
  Serial.println("gone to the  first index");
  delay(1000);
// heading to the first indexer


  armsteps= armcenter;
  suctionsteps = suctioncenter;
  while((loop1 == 1)||( loop2==1 )){
    armservo.write(armsteps);
    Serial.println("armstepsdone");
    if (armsteps == armfeed){
      loop1 = 0;
       Serial.println("armstepsdone");
    }
    else {
     armsteps ++; 
      }
      delay(15);
     suctionservo.write(suctionsteps);
      if (suctionsteps == suctionfeed){
      loop2 = 0;
      Serial.println("suctionstepsdone"); 
    }
    else {
     suctionsteps --; 
    }
   delay(15);
}

 loop1=1;

TRGS'ML NJ; O; ++M=
 loop2=1;
 armservo.write(armfeed);
 suctionservo.write(suctionfeed); ةى ةتئينلاز
delay(2000);
Serial.println("servo and suction gone to the  first index");

//sending to the feeding to center the first indexer position

 digitalWrite(Relaysuction, HIGH);// Let's turn off the relay of the suction
 Serial.println(" SUCTION OFF ");
 
 delay(1000);
   armservo.write(armcenter);  // centring
 suctionservo.write(suctioncenter);  // centring
 Serial.println(" CENTRING ");
 delay(1000);

 stepper.moveRelativeInSteps(650*8);  // moving to the body 
  Serial.println("gone to the  body again");
  delay(1000);
  
armservo.write(armbody); // heading to the part body
  suctionservo.write(suctionbody); // suction brdo to part body
  Serial.println(" suction and arm servos are in left to get the body " );
 delay(1000);
 
  digitalWrite(Relaysuction, LOW);// Let's turn on the relay of the suction
  Serial.println(" suction on ");
 delay(1000); 

 digitalWrite(Relaypiston, HIGH);// Let's turn OFF the relay of the piston
 Serial.println(" piston OFF ");
 delay(1000);
 

  armsteps= armbody;
  suctionsteps = suctionbody;
  while((loop1 == 1)&&( loop2==1 )){
    armservo.write(armsteps);
    Serial.println("armstepsdone");
    if (armsteps == armcenter){
      loop1 = 0;
       Serial.println("armstepsdone");
    }
    else {
     armsteps ++; 
      }
      delay(15);
     suctionservo.write(suctionsteps);
      if (suctionsteps == suctioncenter){
      loop2 = 0;
      Serial.println("suctionstepsdone"); 
    }
    else {
     suctionsteps --; 
    }
   delay(15);
}
armservo.write(armcenter);
suctionservo.write(suctioncenter);
 Serial.println("arm and suction servo centered " );
 loop1=1;
 loop2=1;
 delay(1000);
 
    stepper.moveRelativeInSteps(550*8);  // moving to the second indexer
  Serial.println("gone to the  second index");
  delay(1000);

  armsteps= armcenter;
  suctionsteps = suctioncenter;
  while((loop1 == 1)&&( loop2==1 )){
    armservo.write(armsteps);
    Serial.println("armstepsdone");
    if (armsteps == armfeed){
      loop1 = 0;
       Serial.println("armstepsdone");
    }
    else {
     armsteps ++; 
      }
      delay(15);
     suctionservo.write(suctionsteps);
      if (suctionsteps == suctionfeed){
      loop2 = 0;
      Serial.println("suctionstepsdone"); 
    }
    else {
     suctionsteps --; 
    }
   delay(15);
}

 loop1=1;
 loop2=1;
 armservo.write(armfeed);
 suctionservo.write(suctionfeed);
delay(2000);
    Serial.println("suction and arm gone to the  second index");
 digitalWrite(Relaysuction, HIGH);// Let's turn off the relay of the suction
 Serial.println(" SUCTION OFF ");
 delay(2000); 
   armservo.write(armcenter);  // centring
 suctionservo.write(suctioncenter);  // centring
 Serial.println(" CENTRING ");
 
 delay(2000);
 digitalWrite(9,HIGH);  // sending signal to feeding
 delay(1000);
 digitalWrite(9,LOW);  // sending signal to feeding
 
  if(stepper.moveToHomeInMillimeters(directionTowardHome, homingSpeedInMMPerSec, maxHomingDistanceInMM, LIMIT_SWITCH_PIN) != true)
  { 
  }
flag =0 ;
  }
 
}

#include <Wire.h>
#include <SoftwareSerial.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

#define MAXCHAR 30

SoftwareSerial Bluetooth(2, 3); // Arduino(RX, TX) - HC-05 Bluetooth (TX, RX)

Adafruit_MotorShield AFMS = Adafruit_MotorShield();

Adafruit_DCMotor *LeftFrontWheel  = AFMS.getMotor(1);
Adafruit_DCMotor *RightFrontWheel   = AFMS.getMotor(2); 
Adafruit_DCMotor *LeftBackWheel = AFMS.getMotor(3);
Adafruit_DCMotor *RightBackWheel  = AFMS.getMotor(4);

int defaultSpeed = 60;
char message[MAXCHAR] ;
int index = 0;
String cmd = "";
void setup() {

  Serial.begin(115200);
  // put your setup code here, to run once:
  AFMS.begin();
  
  LeftFrontWheel->setSpeed(defaultSpeed);
  LeftBackWheel->setSpeed(defaultSpeed);
  
  RightBackWheel->setSpeed(defaultSpeed);
  RightFrontWheel->setSpeed(defaultSpeed);

  Bluetooth.begin(115200); // Default baud rate of the Bluetooth module
  Bluetooth.setTimeout(1);
  delay(20);
  
}

void loop() {
  
  // put your main code here, to run repeatedly:
  if(Bluetooth.available())  // If the bluetooth sent any characters
  {
    while(Bluetooth.available()){
      
        message[index] = (char)Bluetooth.read();  // Add the character to the message buffer
       // Serial.println(index);
        index++;
        if( index > MAXCHAR ){ 
          index =0;
          break;
        }
            
    
    }
    Serial.println( message);
    index = 0;
    String msg = message;

    clearMessage();

    setSpeed();
    
    if(msg.equals("Forward")){
        moveForward();
    }
    else if( msg.equals("Backward")){
        moveBackward();
    }
    else if( msg.equals("SidewaysRight")){
        moveSidewaysRight();
    }
    else if( msg.equals("SidewaysLeft")){
        moveSidewaysLeft();
    }
    else if( msg.equals("RotateLeft")){
       rotateLeft();
    }
    else if( msg.equals("RotateRight")){
       rotateRight();
    }
    else if( msg.equals("RightForward")){
        moveRightForward();
    }
    else if( msg.equals("LeftForward")){
        moveLeftForward();
    }
    else if( msg.equals("Stop")){
        motorStop();
    }

    delay(10);
    
  }
}
void moveForward()
{
   LeftFrontWheel->run(FORWARD);
   LeftBackWheel->run(FORWARD);
   
   RightFrontWheel->run(FORWARD); 
   RightBackWheel->run(FORWARD);
  
}
void moveBackward() {
  
   LeftFrontWheel->run(BACKWARD);
   LeftBackWheel->run(BACKWARD);
   
   RightFrontWheel->run(BACKWARD);
   RightBackWheel->run(BACKWARD);
   
}
void moveSidewaysRight() {

   LeftFrontWheel->setSpeed(120);
   LeftBackWheel->setSpeed(120);
  
   RightBackWheel->setSpeed(120);
   RightFrontWheel->setSpeed(120);

   LeftFrontWheel->run(FORWARD);
   LeftBackWheel->run(BACKWARD);

   RightFrontWheel->run(FORWARD);
   RightBackWheel->run(BACKWARD);
   
}
void moveSidewaysLeft() {

   LeftFrontWheel->setSpeed(120);
   LeftBackWheel->setSpeed(100);

   RightFrontWheel->setSpeed(100);
   RightBackWheel->setSpeed(120);
   
  
   LeftFrontWheel->run(BACKWARD);
   LeftBackWheel->run(FORWARD);
   
   RightFrontWheel->run(BACKWARD);
   RightBackWheel->run(FORWARD);
   
}
void rotateLeft() {
  
   LeftFrontWheel->run(BACKWARD);
   LeftBackWheel->run(BACKWARD);
   
   RightFrontWheel->run(FORWARD);
   RightBackWheel->run(FORWARD);
   
}
void rotateRight() {
  
   LeftFrontWheel->run(FORWARD);
   LeftBackWheel->run(FORWARD);
   
   RightFrontWheel->run(BACKWARD);
   RightBackWheel->run(BACKWARD);
   
}
void moveRightForward() {
  
   LeftFrontWheel->run(FORWARD);
  // LeftBackWheel->run(FORWARD);
   
 //  RightFrontWheel->run(BACKWARD);
   RightBackWheel->run(BACKWARD);
   
}
void moveRightBackward() {
  
  // LeftFrontWheel->run(FORWARD);
   LeftBackWheel->run(BACKWARD);
   
   RightFrontWheel->run(BACKWARD);
 //  RightBackWheel->run(BACKWARD);
   
}
void moveLeftForward() {
  // LeftFrontWheel->run(FORWARD);
   LeftBackWheel->run(FORWARD);
   
   RightFrontWheel->run(FORWARD);
 //  RightBackWheel->run(BACKWARD);
}
void moveLeftBackward() {
  
   LeftFrontWheel->run(BACKWARD);
  // LeftBackWheel->run(FORWARD);
   
 //  RightFrontWheel->run(FORWARD);
   RightBackWheel->run(BACKWARD);
}
void motorStop(){
  
   LeftFrontWheel->run(RELEASE);
   LeftBackWheel->run(RELEASE);
   
   RightFrontWheel->run(RELEASE);
   RightBackWheel->run(RELEASE);
}
void clearMessage()
{
    for(int i=0 ;i< MAXCHAR; i++){
       message[i] = (char)0;
    }
}
void setSpeed()
{
   LeftFrontWheel->setSpeed(defaultSpeed);
  LeftBackWheel->setSpeed(defaultSpeed);
  
  RightBackWheel->setSpeed(defaultSpeed);
  RightFrontWheel->setSpeed(defaultSpeed);
}

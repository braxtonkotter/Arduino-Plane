/*
* Arduino Wireless Communication Tutorial
*       Example 1 - Receiver Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <string.h>
#include <Servo.h>

#define RIGHT_SERVO_PORT 4
#define LEFT_SERVO_PORT 3
#define MOTOR_PORT 2

//Define Servos & ports
Servo rightWing; //Port 4
Servo leftWing; //Port 3
Servo Motor; //Port 2

//Radio Stuff
const byte address[6] = "22565";
RF24 radio(7, 8); // CE, CSN
int currentTime;
int lastRecieveTime;

//values sent from controller
struct Plane_Values{
  int motorSpeed;
  int rightServoRotation;
  int leftServoRotation;
};
struct Plane_Values fromRadio;

int defaultServoAngle = -10; //AKA Trim
 
void setup() {
  //Computer Output Start
  Serial.begin(115200);
  //Radio Start
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  //Attach Servos
  Motor.attach(MOTOR_PORT);
  rightWing.attach(RIGHT_SERVO_PORT);
  leftWing.attach(LEFT_SERVO_PORT);
  lastRecieveTime = millis();
}
void loop() {
   //Set Current Time
   currentTime = millis();
   
   //activate failsafe function if disconnected for 1 sec
   if(currentTime - lastRecieveTime > 1000){
    failsafe();
   }
   //if radio working
   if(radio.available()){
    radio.read(&fromRadio, sizeof(fromRadio));
    lastRecieveTime = millis();
    //Serial.println(fromRadio.motorSpeed);
    Serial.println(String(fromRadio.leftServoRotation) + ", " + String(fromRadio.rightServoRotation));
   }
   //Motor & servo movements   
   Motor.writeMicroseconds(fromRadio.motorSpeed);
   rightWing.write(fromRadio.rightServoRotation);
   leftWing.write(fromRadio.leftServoRotation);
}

//Set all values to 0 if disconnected
void failsafe(){
  Serial.println("...Failsafe Engaged...");
  fromRadio.motorSpeed = 1000;
  Serial.println("Motor Value @ 0");
  fromRadio.rightServoRotation = 90;
  Serial.println("Right Wing Reset");
  fromRadio.leftServoRotation = 90;
  Serial.println("Left Wing Reset");
 }

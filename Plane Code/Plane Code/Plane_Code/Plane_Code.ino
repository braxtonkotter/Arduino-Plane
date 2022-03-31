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

//Define Servos
Servo rightWing; //Port 10
Servo leftWing; //Port 11
Servo Motor; //Port 9

//Radio Stuff
const byte address[6] = "12345";
RF24 radio(7, 8); // CE, CSN
int currentTime;
int lastRecieveTime;

//values sent from controller
struct Plane_Values{
  byte motorSpeed;
  byte rightServoRotation;
  byte leftServoRotation;
};
struct Plane_Values fromRadio;

int defaultServoAngle = 0; //AKA Trim
 
void setup() {
  //Computer Output Start
  Serial.begin(115200);
  //Radio Start
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  //Attach Servos
  Motor.attach(9);
  rightWing.attach(10);
  leftWing.attach(11);
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
    //Serial.println(String(defaultServoAngle + fromRadio.leftServoRotation) + ", " + String(defaultServoAngle + fromRadio.rightServoRotation));
   }
   //Motor & servo movements   
   Motor.writeMicroseconds(fromRadio.motorSpeed);
   Serial.println(fromRadio.motorSpeed);
   rightWing.write(defaultServoAngle + fromRadio.rightServoRotation);
   leftWing.write(defaultServoAngle + fromRadio.leftServoRotation);

   
}

//Set all values to 0 if disconnected
void failsafe(){
  Serial.println("...Failsafe Engaged...");
  Motor.write(0);
  Serial.println("Motor Value @ 0");
  rightWing.write(defaultServoAngle);
  Serial.println("Right Wing Reset");
  leftWing.write(defaultServoAngle);
  Serial.println("Left Wing Reset");
 }

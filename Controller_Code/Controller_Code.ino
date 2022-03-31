/*
* Arduino Wireless Communication Tutorial
*     Example 1 - Transmitter Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//creates radio object
RF24 radio(7, 8); // CE, CSN

struct planeValues{
  byte motorSpeed;
  byte rightServoRotation;
  byte leftServoRotation;
};

//setup of up to six radios
const byte address[6] = "12345";

//Setup an object of Send
planeValues toRadio;

//joystick values
int pitchValue;
int rollValue;
int motorMotion;
int defaultMotorMotion;

//function to run on start
void setup() {
  defaultMotorMotion = analogRead(5);
  //start the radio
  radio.begin();
  //open a writing channel using the address defined above
  radio.openWritingPipe(address);
  //set the power, for long range do RF24_PA_MAX
  radio.setPALevel(RF24_PA_MIN);
  //set the radio to writing
  radio.stopListening();
  //start the serial if attached to a computer
  Serial.begin(115200);
}

//runs every time the microcontroller cycles
void loop() {
  motorMotion = analogRead(5) - defaultMotorMotion;
  //get the value of the joystick
  toRadio.motorSpeed = map(motorMotion, -20, 70, 1000, 2000);
  Serial.println(toRadio.motorSpeed);
  ServoValues();
  //write to the radio pipeline the struct Send
  radio.write(&toRadio, sizeof(toRadio));
  //print the joystick value to the terminal (Serial)
  //Serial.println(toRadio.motorSpeed);
  //Serial.println(analogRead(2)); 
}

void ServoValues(){
  pitchValue = analogRead(2);
  rollValue = analogRead(1);
  //if right
  if(rollValue > 520){
    pitchValue = map(pitchValue, 0, 1023, 45, 135);
    rollValue = map(rollValue, 518, 1023, 0, 45);
    
    //right servo = pitchValue + rollValue
    toRadio.rightServoRotation = pitchValue + rollValue;
    //left servo = pitchValue-rollValue
    toRadio.leftServoRotation = pitchValue - rollValue;
    toRadio.leftServoRotation = map(toRadio.leftServoRotation, 0, 180, 180, 0);  
  }
  //if left
  else if(rollValue < 516){
    pitchValue = map(pitchValue, 0, 1023, 45, 135);
    rollValue = map(rollValue, 0, 518, 45, 0);
    //right servo = pitchValue - rollValue
    toRadio.rightServoRotation = pitchValue - rollValue;
    //left servo = pitchValue + rollValue
    toRadio.leftServoRotation = pitchValue + rollValue;
    
    toRadio.leftServoRotation = map(toRadio.leftServoRotation, 0, 180, 180, 0);
  }
  //if 518
  else if (rollValue > 516 || rollValue < 520){
    toRadio.rightServoRotation = map(pitchValue, 0, 1023, 45, 135);
    toRadio.leftServoRotation = map(pitchValue, 0, 1023, 135, 45) - 35;
  }
 }

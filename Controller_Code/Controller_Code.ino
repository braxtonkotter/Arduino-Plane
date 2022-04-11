/*
  Arduino Wireless Communication Tutorial
      Example 1 - Transmitter Code

  by Dejan Nedelkovski, www.HowToMechatronics.com

  Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define MOTOR_PIN 0
#define PITCH_PIN 2
#define ROLL_PIN 3

//creates radio object
RF24 radio(7, 8); // CE, CSN

struct planeValues {
  int motorSpeed;
  int rightServoRotation;
  int leftServoRotation;
};

//setup of up to six radios
const byte address[6] = "22565";

//Setup an object of Send
planeValues toRadio;

//joystick values
int pitchValue;
int rollValue;
int motorMotion;
int defaultMotorMotion;
int defaultPitchMotion;
int defaultRollMotion;

//function to run on start
void setup() {
  //Set zero point
  defaultMotorMotion = 0; //change when I get Accelerometer
  defaultPitchMotion = analogRead(PITCH_PIN);
  defaultRollMotion = analogRead(ROLL_PIN);

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
  motorMotion = analogRead(MOTOR_PIN) - defaultMotorMotion;
  //get the value of the joystick
  toRadio.motorSpeed = map(motorMotion, 512, 1023, 1000, 2000);
  ServoValues();
  
  //write to the radio pipeline the struct toRadio
  radio.write(&toRadio, sizeof(toRadio));

  //print the joystick value to the terminal (Serial)
  //Serial.println(toRadio.motorSpeed);
  //Serial.println(String(toRadio.rightServoRotation) + ", " + String(toRadio.leftServoRotation));
}

void ServoValues() {
  pitchValue = analogRead(PITCH_PIN) - defaultPitchMotion; //min -55 max 70
  rollValue = analogRead(ROLL_PIN) - defaultRollMotion; //min -70 max 70
  //Serial.println(String(pitchValue) + ", " + String(rollValue));

  //if right
  if (rollValue > 10) {
    Serial.println("Right");
    pitchValue = map(pitchValue, -55, 70, 45, 135);
    rollValue = map(rollValue, 10, 70, 0, 45);
    //right servo = pitchValue + rollValue
    toRadio.rightServoRotation = pitchValue + rollValue-10;
    //left servo = pitchValue-rollValue
    toRadio.leftServoRotation = pitchValue - rollValue+7;
    toRadio.leftServoRotation = map(toRadio.leftServoRotation, 0, 180, 180, 0);
  }
  //if left
  else if (rollValue < -10) {
    Serial.println("Left");
    pitchValue = map(pitchValue, -55, 70, 45, 135);
    rollValue = map(rollValue, -70, -10, 45, 0);
    //right servo = pitchValue - rollValue
    toRadio.rightServoRotation = pitchValue - rollValue-10;
    //left servo = pitchValue + rollValue
    toRadio.leftServoRotation = pitchValue + rollValue+7;

    toRadio.leftServoRotation = map(toRadio.leftServoRotation, 0, 180, 180, 0);
  }
  //if 518..
  else if (rollValue > -10 || rollValue < 10) {
    Serial.println("Center");
    toRadio.rightServoRotation = map(pitchValue, -55, 90, 45, 135)-10;
    toRadio.leftServoRotation = map(pitchValue, -55, 90, 135, 45)+7;
  }
}

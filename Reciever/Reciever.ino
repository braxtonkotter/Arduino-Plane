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
#include <Servo.h>

RF24 radio(7, 8); // CE, CSN
Servo motor;
Servo rightAlerion;
Servo leftAlerion;

const byte address[6] = "12345";

//This is the struct to send to the plane
struct Send{
  //creates joystick Value X&Y
  int servoRight;
  int servoLeft;

  //creates the potentiometer or motor value
  int motorValue;
};

struct Send fromRadio;

void setup() {
  Serial.begin(115200);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  motor.attach(2);
  rightAlerion.attach(10);
  leftAlerion.attach(9);
}

void loop() {
  if(radio.available()){
    radio.read(&fromRadio, sizeof(fromRadio));
    motor.writeMicroseconds(fromRadio.motorValue);
    rightAlerion.write(fromRadio.servoRight);
    leftAlerion.write(fromRadio.servoLeft);
    Serial.print("Motor: ");
    Serial.print(fromRadio.motorValue);
    Serial.print(" Right Servo: ");
    Serial.print(fromRadio.servoRight);
    Serial.print(" Left Servo: ");
    Serial.println(fromRadio.servoLeft);
    
    
  }         
}

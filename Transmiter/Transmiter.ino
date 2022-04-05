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

//creates a definition for the joystick pin
#define MOTOR_POT 0
#define X_PIN_JOYSTICK 1
#define Y_PIN_JOYSTICK 2

//creates radio object
RF24 radio(7, 8); // CE, CSN

//This is the struct to send to the plane
struct Send{
  //creates joystick Value X&Y
  int servoRight;
  int servoLeft;

  //creates the potentiometer or motor value
  int motorValue;
};


//setup of up to six radios
const byte address[6] = "12345";

//setup button state variable
int buttonState = 0;

//Setup an object of Send
struct Send toRadio;

int x, x_radio;
int y, y_radio;

bool motionControls;

//function to run on start
void setup() {
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
  motionControls = false;
}

//runs every time the microcontroller cycles
void loop() {  
  //get the value of the joystick
  toRadio.motorValue = map(analogRead(MOTOR_POT), 508, 1023, 998, 2000);
  x = analogRead(X_PIN_JOYSTICK);
  //elevator control
  y = analogRead(Y_PIN_JOYSTICK);
  Serial.println(toRadio.motorValue);

  if(analogRead(MOTOR_POT) == 0){
    motionControls = !motionControls;
  }

  if(motionControls){
    x_radio = analogRead(A5);
    y_radio = analogRead(A4);

    x_radio = map(x_radio, 270, 405, 0, 45);
    y_radio = map(y_radio, 270, 405, 45, 135);      
  }

  
  //if right
  if(x > 520){
    y = map(y, 0, 1023, 45, 135);
    x = map(x, 518, 1023, 0, 45);
    
    //right servo = y + x
    toRadio.servoRight = y + x;
    //left servo = y-x
    toRadio.servoLeft = y - x;
    toRadio.servoLeft = map(toRadio.servoLeft, 0, 180, 180, 0);  
  }
  //if left
  else if(x < 516){
    y = map(y, 0, 1023, 45, 135);
    x = map(x, 0, 518, 45, 0);
    //right servo = y - x
    toRadio.servoRight = y - x;
    //left servo = y + x
    toRadio.servoLeft = y + x;
    
    toRadio.servoLeft = map(toRadio.servoLeft, 0, 180, 180, 0); 
  }
  //if 518
  else if (x > 516 || x < 520) {
    toRadio.servoRight = map(y, 0, 1023, 45, 135);
    toRadio.servoLeft = map(y, 0, 1023, 135, 45) - 35;
  }
  
  //write to the radio pipeline the struct Send
  radio.write(&toRadio, sizeof(toRadio));

  //Testing servo values
  Serial.print("Right Servo: ");
  Serial.print(toRadio.servoRight);
  Serial.print(" Left Servo: ");
  Serial.println(toRadio.servoLeft);
  
}

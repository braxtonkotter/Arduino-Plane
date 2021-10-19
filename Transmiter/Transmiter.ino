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

int getPitchR(int);
int getPitchL(int);

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
}

//runs every time the microcontroller cycles
void loop() {  
  //get the value of the joystick
  toRadio.motorValue = map(analogRead(MOTOR_POT), 509, 1023, 1000, 2000);
  x = analogRead(X_PIN_JOYSTICK);
  //elevator control
  y = analogRead(Y_PIN_JOYSTICK);
  y = map(y, 0, 1023, 45, 135);
  
  toRadio.servoRight = map(y+getPitchR(x), 0, 180, 180, 0);
  toRadio.servoLeft = y+getPitchL(x);

  Serial.print("Right Servo: ");
  Serial.print(toRadio.servoRight);
  Serial.print(" Left Servo: ");
  Serial.println(toRadio.servoLeft);
  
  /*//pull up - both up 
  if(y > 512 && x == 518){
    y_radio = map(y, 512, 1023, 90, 135); 
    toRadio.servoRight = y_radio;
    toRadio.servoLeft = y_radio;
  }
  //pull down - both down
  else if(y < 512 && x == 518){
    y_radio = map(y, 0, 512, 45, 90);
    Serial.println("Yes");
    toRadio.servoRight = y_radio;
    toRadio.servoLeft = y_radio;
  }
  //roll right - right up
  else if(y == 512 && x > 512){
    x_radio = map(x, 512, 1023, 90, 135);
    toRadio.servoRight = x_radio;
    toRadio.servoLeft = 90;
  }
  //roll left - left up
  else if(y == 512 && x < 512){
    x_radio = map(x, 0, 512, 45, 90);
    toRadio.servoRight = 90;
    toRadio.servoLeft = x_radio;
  }
  //bank and yank - down + right
  else if(y > 512 && x > 512){
    y_radio = map(y, 512, 1023, 45, 90);
    x_radio = map(x, 512, 1023, 45, 0);
    toRadio.servoRight = x_radio+y_radio;
    toRadio.servoLeft = y_radio;
  }
  //bank and yank - down + left
  else if (y > 512 && x < 512){
    y_radio = map(y, 512, 1023, 45, 90);
    x_radio = map(x, 0, 512, 90, 0);
    toRadio.servoRight = y_radio;
    toRadio.servoLeft = y_radio+x_radio;
 }
  
  else{
    toRadio.servoRight = 90;
    toRadio.servoLeft = 90;
  }*/  
  
  //write to the radio pipeline the struct Send
  radio.write(&toRadio, sizeof(toRadio));
  
  
}

int getPitchR(int fire){
  if(fire < 518){
    return 0;
  }
  fire = map(fire, 518, 1023, 0, 45);
  return fire;
}

int getPitchL(int fire){
  if(fire > 518){
    return 0;
  }
  fire = map(fire, 0, 518, 45, 0); 
  return fire;
}


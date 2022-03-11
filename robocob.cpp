//LCD libraries
#include <Wire.h>
#include "DFRobot_LCD.h"

//setting RGB colors of lcd screen
const int colorR = 255;
const int colorG = 0;
const int colorB = 0;

//16 characters and 2 lines of show
DFRobot_LCD lcd(16,2);

//Setting motor pins
int in1 = 0; //in1
int in2 = 1; //in2
int en1 = 2; //en1
int in3 = 3; //in3
int in4 = 4;//in4
int en2 = 5 ;//en2

//Setting ldr and led pins
const int ledPin = 6;
const int ldrPin = A0;

//Setting trigger,echo and buzzer pin
int trigger_pin = 7;
int echo_pin = 8;
int buzzer_pin = 9;
int Time;
int distance;

//Forward , backward  and stop led pins
int led1 = 10;
int led2 = 11;
int led3 = 12;



void setup() {
  //Initialize lcd
  initialize_lcd();

  //Set motor pins to output
  setMotorPinsToOutput();

  //Setting led and ldr pins to output
  settingLedLdrPins();

  //Setting ultrasonic sensor and buzzer
  initiateObstacleSensor();
}

void loop() {
  // put your main code here, to run repeatedly:
  setLcdCursor("Group 3","Robocob Loaded..");

  //Detect darkness
  detectDarkness();

  //Sense obstacles and buzz sound
  obstacleSensor();

  //Move motor forward
  moveMotorForward();

  //Move motor backward
  moveMotorBackward();

  //turn left
  turnLeft();

  //turn right
  turnRight();
  
  //Stop motor
  stopMotor();
}

//This function initializes lcd
void initialize_lcd(){
  //initialize lcd
  lcd.init();

  //set RGB colours of screen
  lcd.setRGB(colorR, colorG, colorB);

  
}

void setLcdCursor(String data_1, String data_2){
  // set the cursor to column 0, line 1
  lcd.setCursor(0,0);

  //Print message unto screen
  lcd.print(data_1);
  delay(500);
  
  //clear message
  lcd.clear();
  
  //print message unto screen
  lcd.print(data_2);
  delay(500);
  
  //clear message
  lcd.clear();
}

void setMotorPinsToOutput(){
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(en1, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(en2, OUTPUT);
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
}

void moveMotorForward(){
  // Set motors to maximum speed
  // For PWM maximum possible values are 0 to 255
  analogWrite(en1, 100);
  analogWrite(en2, 100);

  // Turn on motor A & B
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  //Turn green led on and yellow led on);
  digitalWrite(led1,HIGH);
  digitalWrite(led2,LOW);
  digitalWrite(led3,LOW);

  //Display moving forward
  setLcdCursor("Forward","Forward");
  delay(100);
}

void moveMotorBackward(){
  analogWrite(en1, 100);
  analogWrite(en2, 100);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  //Off green led and On yellow led
  digitalWrite(led1,LOW);
  digitalWrite(led3,LOW);
  digitalWrite(led2,HIGH);
  
  
  //Display moving backward
  setLcdCursor("Backward","Backward");
  delay(1000);
}

void turnLeft(){
   analogWrite(en1, HIGH);//ENABLING LEFT
  analogWrite(en2, HIGH);//ENABLING RIGHT
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  //Display moving backward
  setLcdCursor("Turning","Left");
  delay(1000);
}

void turnRight(){
   analogWrite(en1, HIGH);//ENABLING LEFT
  analogWrite(en2, HIGH);//ENABLING RIGHT
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  //Display moving backward
  setLcdCursor("Turning","Right");
  delay(1000);
}



void stopMotor(){
  analogWrite(en1, 100);
  analogWrite(en2, 100);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

  //Turn on red led
  digitalWrite(led1,LOW);
  digitalWrite(led2,LOW);
  digitalWrite(led3,HIGH);
  
  //Display stop
  setLcdCursor("Stop","Stop");
}

void settingLedLdrPins(){
  pinMode(ledPin, OUTPUT);
  pinMode(ldrPin, INPUT);
}

void detectDarkness(){
  int ldrStatus = analogRead(ldrPin);

  if (ldrStatus <= 200) {
      //Switch On led
      delay(500);
      switchOnLed();
      
  } else {
    //Switch Off led
    switchOffLed();
  }
}

void switchOnLed(){
  digitalWrite(ledPin, HIGH);
}

void switchOffLed(){
  digitalWrite(ledPin, LOW);
}

void initiateObstacleSensor(){
   pinMode (trigger_pin, OUTPUT); 
   pinMode (echo_pin, INPUT);
   pinMode (buzzer_pin, OUTPUT);
}

void obstacleSensor(){
  digitalWrite (trigger_pin, HIGH);
  delayMicroseconds (10);
  digitalWrite (trigger_pin, LOW);
  Time = pulseIn (echo_pin, HIGH);
  distance = (Time * 0.034) / 2;

  if (distance <= 10) 
        {       
        digitalWrite (buzzer_pin, HIGH);
        delay (500);
        }
  else {
        digitalWrite (buzzer_pin, LOW);
        delay (500);        
  } 
}
/*
Andreas Bastian, OpenSLS 2013
 Arduino code for execution on a slaved Arduino Uno as a temporary
 means for controlling both the laser and the powder management
 hardware.
 
 */

//define pins for powder distributor, pistons (Z), and laser PWM and EN
#define D_STEP_PIN 2
#define D_DIR_PIN 3
//#define D_EN_PIN -1

#define Z_STEP_PIN 4
#define Z_DIR_PIN 5
//#define Z_EN_PIN -1

#define LASER_EN_PIN 8
#define LASER_PWM_PIN 9
#define LASER_READ_PIN A0

#define LAYER_CHANGE_PIN 12
 
 
#include <pins.h>
#include <SoftwareSerial.h>
SoftwareSerial portOne(1,2);

boolean doLayerChange = false;
int i = 0;
void setup()
{
  Serial.begin(9600);
  //portOne.begin(9600);
  pinMode(D_STEP_PIN, OUTPUT);
  pinMode(D_DIR_PIN, OUTPUT);
  pinMode(Z_STEP_PIN, OUTPUT);
  pinMode(Z_DIR_PIN, OUTPUT);
  pinMode(LASER_PWM_PIN, OUTPUT);
  pinMode(LASER_EN_PIN, OUTPUT);
  pinMode(LAYER_CHANGE_PIN, INPUT);
  pinMode(LASER_READ_PIN, INPUT);
}

void loop()
{
  i++;
  analogWrite(LASER_PWM_PIN, i);
  int val = 0;
  for(int j = 0; j<255; j++)
  {
      val = analogRead(LASER_READ_PIN);
  }
  val = val/255;
  Serial.println(val);
  if(i == 255)
  {
   i=0; 
  }
  doLayerChange = digitalRead(LAYER_CHANGE_PIN); //is it time to do a layer change?
  if((LAYER_CHANGE_PIN == 1) && (doLayerChange == true))
  {
    laserOff();
    
    doLayerChange != doLayerChange;//only do one layer
    
  }//end if
  
  
}//end loop()


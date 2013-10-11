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
int testOutput = 11;

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
  pinMode(testOutput, OUTPUT);
}

void loop()
{

  i++;
  analogWrite(testOutput, 40);//pretend to be the RAMBo
  
  //read RAMBo PWM, resend as a 5V signal from LASER_PWM_PIN:
  int readVal = getPWMval(LASER_READ_PIN);//get PWM signal from RAMBo
  //Serial.print("Read value: ");
  //Serial.println(readVal);
  analogWrite(LASER_PWM_PIN, readVal); //send PWM signal
  
  Serial.print("i = ");
  Serial.print(i);
  Serial.print(", reading pin, ");

  if(i > 254)
  {
    i = 0; 
  }

  //  doLayerChange = digitalRead(LAYER_CHANGE_PIN); //is it time to do a layer change?
  //  if((LAYER_CHANGE_PIN == 1) && (doLayerChange == true))
  //  {
  //    laserOff();
  //    
  //    doLayerChange != doLayerChange;//only do one layer
  //    
  //  }//end if


}//end loop()



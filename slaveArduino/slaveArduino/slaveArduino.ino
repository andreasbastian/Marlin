/*
Andreas Bastian, OpenSLS 2013
 Arduino code for execution on a slaved Arduino Uno as a temporary
 means for controlling both the laser and the powder management
 hardware.
 
 */

//define pins for powder distributor, pistons (Z), and laser PWM and EN
int D_STEP_PIN = 2;
int D_DIR_PIN = 3;
int D_EN_PIN = -1;

int Z_STEP_PIN = 4;
int Z_DIR_PIN = 5;
int Z_EN_PIN = -1;

int LASER_EN_PIN = 8;
int LASER_PWM_PIN = 9;
int RAMBO_LSR_PWM_PIN = A0;
int RAMBO_LSR_EN_PIN = 10;

int LAYER_CHANGE_PIN = 12;


#include <pins.h>
#include <SoftwareSerial.h>
#include <A4988_stepper.h>
#include "Arduino.h"

A4988_stepper z();//(Z_STEP_PIN, Z_DIR_PIN, Z_EN_PIN, 3200, 0.25);//z-axis
//A4988_stepper d;//distributor


boolean doLayerChange = false;
int i = 0;
int testOutput = 11;

void setup()
{
  
  
  Serial.begin(9600);
  //portOne.begin(9600);
//  pinMode(D_STEP_PIN, OUTPUT);
//  pinMode(D_DIR_PIN, OUTPUT);
//  pinMode(Z_STEP_PIN, OUTPUT);
//  pinMode(Z_DIR_PIN, OUTPUT);
//  pinMode(LASER_PWM_PIN, OUTPUT);
//  pinMode(LASER_EN_PIN, OUTPUT);
//  pinMode(LAYER_CHANGE_PIN, INPUT);
//  pinMode(RAMBO_LSR_PWM_PIN, INPUT);
//  pinMode(RAMBO_LSR_EN_PIN, INPUT);

  pinMode(testOutput, OUTPUT);
}

void loop()
{
  int readVal = getPWMval(RAMBO_LSR_PWM_PIN);//get PWM signal from RAMBo
  Serial.println(readVal);//sanity check
  analogWrite(LASER_PWM_PIN, readVal); //send PWM signal

  //  doLayerChange = digitalRead(LAYER_CHANGE_PIN); //is it time to do a layer change?
  //  if((LAYER_CHANGE_PIN == 1) && (doLayerChange == true))
  //  {
  //    laserOff();
  //    
  //    doLayerChange != doLayerChange;//only do one layer
  //    
  //  }//end if


}//end loop()

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
void newLayer()
{
  
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////


/*
class A4988_stepper
{
public: 
  A4988_stepper(int stepPin, int dirPin, int enPin, int steps_per_mm, float velocity);
  void setSpeed(float newSpeed);
  void moveDist(float dist, float velocity);
  void moveDist(float dist);

private:
  int _sp;
  int _dp;
  int _ep;
  int _spmm;
  float _v;
  int stepDelay;
  void STEP();
  void setDir(float dist);
};
*/

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
/*
A4988_stepper::A4988_stepper(int stepPin, int dirPin, int enPin, int steps_per_mm, float defaultVelocity)
{
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enPin, OUTPUT);

  _sp = stepPin;
  _dp = dirPin;
  _ep = enPin;
  _spmm = steps_per_mm;
  _v = defaultVelocity;
  stepDelay = 1/(steps_per_mm*defaultVelocity);

}

//change speed
void A4988_stepper::setSpeed(float velocity)
{
  _v = velocity;
}

//move a distance at a velocity
void A4988_stepper::moveDist(float dist, float velocity)
{
  stepDelay = 1/(_spmm*velocity);
  int numSteps = _spmm*dist;
  setDir(dist);
  while(numSteps != 0)
  {
    numSteps--;
    STEP();
  }
}

//move motor with last used velocity
void A4988_stepper::moveDist(float dist)
{
  int numSteps = _spmm*dist;
  setDir(dist);
  while(numSteps != 0)
  {
    numSteps--;
    STEP();
  }
}

//just a simple func to set motor direction based on sign of target distance
void A4988_stepper::setDir(float dist)
{
  if(dist < 0)
  {
    digitalWrite(_dp, HIGH); 
  }
  else
  {
    digitalWrite(_dp, LOW);
  }
}

//take a single step
void A4988_stepper::STEP()
{
  digitalWrite(_sp, HIGH);
  delayMicroseconds(stepDelay/2);
  digitalWrite(_sp, LOW);
  delayMicroseconds(stepDelay/2); 
}
*/

/*
Andreas Bastian, OpenSLS 2013
 Arduino code for execution on a slaved Arduino Uno as a temporary
 means for controlling both the laser and the powder management
 hardware.
 
 */

//define pins for powder distributor, pistons (Z), and laser PWM and EN
int D_STEP_PIN = 4;
int D_DIR_PIN = 5;
int D_EN_PIN = 7;

int Z_STEP_PIN = 2;
int Z_DIR_PIN = 3;
int Z_EN_PIN = 6;

//int LASER_EN_PIN = 8;
//int LASER_PWM_PIN = 9;
//int RAMBO_LSR_PWM_PIN = A0;
//int RAMBO_LSR_EN_PIN = 10;

int LAYER_CHANGE_PIN = A0;


#include <pins.h>
#include <SoftwareSerial.h>
//#include "A4988_stepper.h"
#include "Arduino.h"





class A4988_stepper
{
public: 
  A4988_stepper(int stepPin, int dirPin, int enPin, int steps_per_mm, float velocity);
  void setSpeed(float newSpeed);
  void moveDist(float dist, float velocity);
  void moveDist(float dist);
  void enable();
  void disable();

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
  stepDelay = 1000000/(steps_per_mm*defaultVelocity);

}

//change speed
void A4988_stepper::setSpeed(float velocity)
{
  _v = velocity;
}


//enable
void A4988_stepper::enable()
{
  digitalWrite(_ep, LOW);
}

//disable
void A4988_stepper::disable()
{
  digitalWrite(_ep, HIGH);
}

//move a distance at a velocity
void A4988_stepper::moveDist(float dist, float velocity)
{
  stepDelay = 1000000/(_spmm*velocity);
  //1 million microseconds/second divided by [steps/mm*mm/s]=microsceonds

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
  int numSteps = _spmm*abs(dist);
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










A4988_stepper z(Z_STEP_PIN, Z_DIR_PIN, Z_EN_PIN, 3200, 0.25);//z-axis
A4988_stepper d(D_STEP_PIN, D_DIR_PIN, D_EN_PIN, 80, 30);//distributor

boolean doABarrelRoll = false;
int i = 0;
int LED = 13;

void setup()
{

  Serial.begin(9600);


  pinMode(LED, OUTPUT);
  pinMode(LAYER_CHANGE_PIN, INPUT);
  d.disable();
  z.enable();
}

void loop()
{
  /*
  int readVal = getPWMval(RAMBO_LSR_PWM_PIN);//get PWM signal from RAMBo
   Serial.println(readVal);//sanity check
   analogWrite(LASER_PWM_PIN, readVal); //send PWM signal
   */
  //Serial.println(analogRead(LAYER_CHANGE_PIN));
  doABarrelRoll = checkLayerPin(LAYER_CHANGE_PIN); //is it time to do a layer change?
  if(doABarrelRoll == true)
  {

    digitalWrite(LED,HIGH);
    //GO GO GO!! Roll that barrel!
    newLayer(0.5);
    doABarrelRoll != doABarrelRoll;//only do one layer
    digitalWrite(LED,LOW);

  }//end if


}//end loop()

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////


void newLayer(float layerHeight)
{
  //increment z by layer height
  //distribute powder
  //analogWrite(LASER_PWM_PIN, 0); //make sure that laser is off
  
  z.moveDist(layerHeight); //decrement z by a layer height and increment feed by 3xlyrHt
  d.enable();
  d.moveDist(270); //distribute powder
  d.moveDist(-270); //return distributor to cubby
  d.disable();

}

boolean checkLayerPin(int layerPin)
{
  //Serial.println(analogRead(layerPin));
  if(analogRead(layerPin) > 210)
  {
    return true;
  } 
  else
  {
    return false;
  }
}


/*

 
 
 
 
 
 
 
 //move a distance at a velocity
 void moveDist(int _sp, int _dp, float dist, float velocity, float _spmm)
 {
 int stepDelay = 1/(_spmm*velocity);
 int numSteps = _spmm*dist;
 setDir(, dist);
 while(numSteps != 0)
 {
 numSteps--;
 STEP();
 }
 }
 
 
 //just a simple func to set motor direction based on sign of target distance
 void setDir(int _dp, float dist)
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
 void STEP(int _sp, float stepDelay)
 {
 digitalWrite(_sp, HIGH);
 delayMicroseconds(stepDelay/2);
 digitalWrite(_sp, LOW);
 delayMicroseconds(stepDelay/2); 
 }
 
 
 
 */




//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////




/*
Andreas Bastian, OpenSLS 2013
 Arduino code for execution on a slaved Arduino Uno as a temporary
 means for controlling both the laser and the powder management
 hardware.
 
 */

//define pins for powder distributor, pistons (Z), and laser PWM and EN
int D_DIR_PIN = 2;
int D_STEP_PIN = 3;
int D_EN_PIN = 4;

int Z_DIR_PIN = 5;
int Z_STEP_PIN = 6;
int Z_EN_PIN = 7;

int F_DIR_PIN = 8;
int F_STEP_PIN = 9;
int F_EN_PIN = 10;

//int LASER_EN_PIN = 8;
//int LASER_PWM_PIN = 9;
//int RAMBO_LSR_PWM_PIN = A0;
//int RAMBO_LSR_EN_PIN = 10;

int LAYER_CHANGE_PIN = A0;


//#include <pins.h>
#include <math.h>
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

  int numSteps = _spmm*fabs(dist);
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
  int numSteps = _spmm*fabs(dist);
  //Serial.print("dist = ");
  //Serial.println(fabs(dist));
  //Serial.print("steps = ");
  //Serial.println(numSteps);
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










A4988_stepper z(Z_STEP_PIN, Z_DIR_PIN, Z_EN_PIN, 3200/1.25, 0.25);//z-axis
A4988_stepper d(D_STEP_PIN, D_DIR_PIN, D_EN_PIN, 80, 30);//distributor
A4988_stepper f(F_STEP_PIN, F_DIR_PIN, F_EN_PIN, 3200/3, 0.25);//feed piston

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

    newLayer(0.1);
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




  analogWrite(LASER_PWM_PIN, 0); //make sure that laser is off
  f.moveDist(layerHeight*1.3);//increment feed by k*layer height
  z.moveDist(layerHeight); //decrement z by a layer height
  d.enable();
  d.moveDist(270); //distribute powder
  d.moveDist(-270); //return distributor to cubby
  d.disable();

}

boolean checkLayerPin(int layerPin)
{


  //Serial.println(analogRead(layerPin));
  if(analogRead(layerPin) > 310)
  {
    //layerPin is high, but make sure that it's not noise:
    //make sure that it stays high for 400ms (value determined by watching noise
    //signals on the o-scope)
    int now = millis();
    int later;

    if(analogRead(layerPin) > 310)
    {
      //suuuuuuuuuper hacky implementation. But it works.
      int wait = 400;
      while(wait != 0)
      {
        wait--;
        delay(1);
        if(analogRead(layerPin) < 310)
        {
          return false; 
        }

      }
      //check again:
      if(analogRead(layerPin > 310))
      {
        return true;
      } 
    }
    /* //though I think is cleaner implementation, it doesn't
    //seem to catch two successive pulses and still misfires 
    //when the RAMBO resets.
    while(analogRead(layerPin) > 310)
     {
     //measure duration of high signal
     later = millis(); 
     }
     if(later-now >= 400)
     {
     return true;
     }
     */
  } 
  else
  {
    return false;
  }
}

float fabs(float val)
{
  if(val < 0)
  {
    return -1*val;
  }
  else
  {
    return val;
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









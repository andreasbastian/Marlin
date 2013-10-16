/*
Super basic stepper motor lib for modular motor control with the A4988 driver from Pololu

Andreas Bastian 
October 2013

*/


#include "Arduino.h"
#include "A4988_stepper.h"

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
/*
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

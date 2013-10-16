/*
A4988_stepper.h
 
 Super basic stepper motor lib for modular motor control with the A4988 driver from Pololu
 
 Andreas Bastian 
 October 2013
 
 */

#ifndef A4988_stepper.h
#define A4988_stepper.h

#include "Arduino.h"

class A4988_stepper
{
public: 
  A4988_stepper(int stepPin, int dirPin, int enPin, int steps_per_mm, float velocity);
  //void setSpeed(float newSpeed);
  //void moveDist(float dist, float velocity);
  //void moveDist(float dist);

private:
  int _sp;
  int _dp;
  int _ep;
  int _spmm;
  float _v;
  //int stepDelay;
  //void STEP();
  //void setDir(float dist);
};
#endif


#include <pins.h>
#define LASER_EN_PIN 8
#define LASER_PWM_PIN 9

void laserOn()
{
  digitalWrite(LASER_EN_PIN,LOW);
}

void laserOff()
{
  digitalWrite(LASER_EN_PIN, HIGH);
}

void laze(int laserPWM)
{
  laserOn();
  digitalWrite(LASER_PWM_PIN, laserPWM);
}

int getPWMval(int pwmInput)
{
  //need precision, so use microseconds.  Make sure there isn't overflow though
  unsigned long cycleStart;
  unsigned long cycleEnd;
  unsigned long cycleHigh;
  unsigned long cycleLow;
  unsigned long maxDiff = 1000000;//check for overflow using big value (1 sec)
  while(digitalRead(pwmInput == LOW))
  {
    if(digitalRead(pwmInput) == HIGH)//catch the leading edge of the PWM signal
    {
      cycleStart = micros();
      while(digitalRead(pwmInput) == HIGH)
      {
       cycleEnd = micros(); 
      }
      cycleHigh = cycleEnd-cycleStart; //duration of high signal
      
    } 
  }

}


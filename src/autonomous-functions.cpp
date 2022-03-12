#include "vex.h"
#include "autonomous-functions.h"
#include "driving-functions.h"

using namespace vex;
using namespace std;

//Timeout function: time to do command until motor stops
void setMotorTimeout(int timeSeconds){
    leftWheels.setTimeout(timeSeconds, sec);
    rightWheels.setTimeout(timeSeconds,sec);
}

//Drive distance with specific distance
void moveForward(float distanceCM, int speedPCT, int timeSec){
  setMotorTimeout(timeSec);

  leftWheels.rotateFor(directionType::fwd, double (distanceCM/31.9), rotationUnits::rev, double (speedPCT), velocityUnits::pct,false);
  rightWheels.rotateFor(directionType::fwd, double (distanceCM/31.9), rotationUnits::rev, double (speedPCT), velocityUnits::pct,true);

  setMotorTimeout(0);
}
//Drive forward with flex input (turning right based off front side)(*if rightWheel distance bigger)
void flexMvmtR(float distanceLeft, float distanceRight, int speedPCT, int timeSec){
  setMotorTimeout(timeSec);

  leftWheels.rotateFor(directionType::fwd, double(distanceLeft/31.9), rotationUnits::rev, double(speedPCT), velocityUnits::pct, false);
  rightWheels.rotateFor(directionType::fwd, double(distanceRight/31.9), rotationUnits::rev, double(speedPCT), velocityUnits::pct, true);

  setMotorTimeout(0);
}
//Drive Foward with flex input (turning left based off front side)(*if leftWheel distance bigger)
void flexMvmtL(float distanceLeft, float distanceRight, int speedPCT, int timeSec){
  setMotorTimeout(timeSec);

  rightWheels.rotateFor(directionType::fwd, double(distanceRight/31.9), rotationUnits::rev, double(speedPCT), velocityUnits::pct, false);
  leftWheels.rotateFor(directionType::fwd, double(distanceLeft/31.9), rotationUnits::rev, double(speedPCT), velocityUnits::pct, true);
}



//Turn Clockwise
void turnClockwise(float degree, int speedPCT, int timeSec){
  setMotorTimeout(timeSec);

  leftWheels.rotateFor(directionType::fwd, double (degree/31.9), rotationUnits::rev, double (speedPCT), velocityUnits::pct,false);
  rightWheels.rotateFor(directionType::rev, double (degree/31.9), rotationUnits::rev, double (speedPCT), velocityUnits::pct,true);

  setMotorTimeout(0);
}

//Move lift
void liftAuton(float degree, int speedPCT, int timeSec){
  setMotorTimeout(timeSec);

  lift.rotateFor(directionType::fwd, double (degree/31.9), rotationUnits::rev, double (speedPCT), velocityUnits::pct,false);

  setMotorTimeout(0);
}

//Move back lift
void bLiftAuton(float amt_of_rotation, int timeSec)
//void bLiftAuton(double degree, int speedPCT, int timeSec)
{
  setMotorTimeout(timeSec);
  bLift.spinToPosition(float (amt_of_rotation), rotationUnits::rev);
  //bLift.rotateFor(directionType::fwd, double (degree/31.9), rotationUnits::rev, double (speedPCT), velocityUnits::pct,true);

  setMotorTimeout(0);
}

void bLiftAuton2(double degree, int speedPCT, int timeSec)
{
  setMotorTimeout(timeSec);
  //bLift.spinToPosition(float (amt_of_rotation), rotationUnits::rev);
  bLift.rotateFor(directionType::fwd, double (degree/31.9), rotationUnits::rev, double (speedPCT), velocityUnits::pct,true);

  setMotorTimeout(0);
}

//Belt
void beltControl(double time = 45, double speedPCT = 89)
{
  Belt.spinFor(directionType::fwd, double (1), timeUnits::sec, double (speedPCT), velocityUnits::pct);
  while(time>0)
  {
    if(Belt.velocity(velocityUnits::pct) == 0)
    {
      Belt.spinFor(directionType::rev, double (1), timeUnits::sec, double (speedPCT), velocityUnits::pct);
      
    }
    else
    {
      Belt.spinFor(directionType::fwd, double (1), timeUnits::sec, double (speedPCT), velocityUnits::pct);
      
    }
    time--;
  }
}
bool loweronce = true;
void dirtyBeltControl(float rev, int speedPCT, int timeout){ 
  setMotorTimeout(timeout);

  Belt.rotateFor(directionType::fwd, double (rev), rotationUnits::rev, double (speedPCT), velocityUnits::pct, false);  
  wait(250, timeUnits::msec);
  if(Belt.velocity(velocityUnits::pct) != 0){
    Belt.rotateFor(directionType::fwd, double (rev), rotationUnits::rev, double (speedPCT), velocityUnits::pct, false); 
  }
  else
  {
    if(loweronce){
    bLiftAuton(0.17, 1);
    loweronce = !loweronce;
    }
    Belt.rotateFor(directionType::rev, double (1), rotationUnits::rev, double (speedPCT), velocityUnits::pct, false);  
    wait(500, timeUnits::msec);
    Belt.rotateFor(directionType::fwd, double (rev), rotationUnits::rev, double (speedPCT), velocityUnits::pct, false);
  }

  setMotorTimeout(0);
}
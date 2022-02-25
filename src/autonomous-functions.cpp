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
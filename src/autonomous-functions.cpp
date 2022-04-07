#include "vex.h"
#include "autonomous-functions.h"
#include "driving-functions.h"
#include "visionSensor.h"

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

  leftWheels.rotateFor(directionType::fwd, double(distanceCM/25.9), rotationUnits::rev, double(speedPCT), velocityUnits::pct, false);
  rightWheels.rotateFor(directionType::fwd, double(distanceCM/25.9), rotationUnits::rev, double(speedPCT), velocityUnits::pct, true);

  setMotorTimeout(0);
}
//Drive forward with flex input (turning right based off front side)(*if rightWheel distance bigger)
void flexMvmtR(float distanceLeft, float distanceRight, int speedPCT, int timeSec){
  setMotorTimeout(timeSec);

  leftWheels.rotateFor(directionType::fwd, double(distanceLeft/25.9), rotationUnits::rev, double(speedPCT), velocityUnits::pct, false);
  rightWheels.rotateFor(directionType::fwd, double(distanceRight/25.9), rotationUnits::rev, double(speedPCT), velocityUnits::pct, true);

  setMotorTimeout(0);
}
//Drive Foward with flex input (turning left based off front side)(*if leftWheel distance bigger)
void flexMvmtL(float distanceLeft, float distanceRight, int speedPCT, int timeSec){
  setMotorTimeout(timeSec);

  rightWheels.rotateFor(directionType::fwd, double(distanceRight/25.9), rotationUnits::rev, double(speedPCT), velocityUnits::pct, false);
  leftWheels.rotateFor(directionType::fwd, double(distanceLeft/25.9), rotationUnits::rev, double(speedPCT), velocityUnits::pct, true);
}



//Turn Clockwise
void turnClockwise(float degree, int speedPCT, int timeSec){
  setMotorTimeout(timeSec);

  leftWheels.rotateFor(directionType::fwd, double (degree/25.9), rotationUnits::rev, double (speedPCT), velocityUnits::pct,false);
  rightWheels.rotateFor(directionType::rev, double (degree/25.9), rotationUnits::rev, double (speedPCT), velocityUnits::pct,true);

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
void dirtyBeltControl(double rotations, double speedPCT, int timeout){ 
}

//Inertial Sensors
float inertialAVG(){
  float sum = 0;

  sum = (fabs(inertialLeft.rotation(deg)) + fabs(inertialRight.rotation(deg)));
  sum = sum /2;

  return sum;
}

void inertialTurn(turnType dir, double speed, double degrees, double timeout){
  inertialLeft.setRotation(0, deg);
  inertialRight.setRotation(0, deg);

  if(dir == right){
    while(inertialAVG() < degrees){
      leftWheels.spin(fwd, speed, pct);
      rightWheels.spin(reverse, speed, pct);
      // printf("current turn degree: %2f", inertialAVG());
      // wait(5, msec);
      // printf("avg: %2f\n", ((inertialRight.heading(deg)+inertialLeft.heading(deg)/2)));
    }
    do{
      leftWheels.spin(reverse, 10, pct);
      rightWheels.spin(fwd, 10, pct);
    }while(inertialAVG() > degrees);
  }else if(dir == left){
    while(inertialAVG() < degrees){
      leftWheels.spin(reverse, speed, pct);
      rightWheels.spin(fwd, speed, pct);
      // printf("current turn degree: %2f", inertialAVG());
      // wait(5, msec);
      // printf("avg: %2f\n", ((inertialRight.heading(deg)+inertialLeft.heading(deg)/2)));
    }
    do{
      leftWheels.spin(fwd, 10, pct);
      rightWheels.spin(reverse, 10 , pct);
    }while(inertialAVG() > degrees);
  }
  printf("current turn degree: %2f", inertialAVG());
  wait(5, msec);
  printf("avg: %2f\n", ((inertialRight.heading(deg)+inertialLeft.heading(deg)/2)));
  leftWheels.stop(hold);
  rightWheels.stop(hold);
}


//Vision sensor
void visionSensorTest(string goalColor, double speed){
  int center = 158;
  int OKerror = 50;
  double xScale = 480.0/310;//Scaling the vision sensor range to the V5 Brain Screen
  double yScale = 240.0/212;
  int targetCenter = 0; int x = 0; int y=0; int height =0; int width = 0;
  bool isTrue = true; 
  string Hue = goalColor;

  if(Hue == "Red"){
    while(isTrue){
      Brain.Screen.clearLine();
      Brain.Screen.clearScreen();
      Vision1.takeSnapshot(RED_GOAL);
      if (Vision1.largestObject.exists)
      {
        targetCenter = Vision1.largestObject.centerX;
        x = Vision1.largestObject.originX;
        y = Vision1.largestObject.originY;
        width = Vision1.largestObject.width;
        printf("width: %d\n", width);
        height = Vision1.largestObject.height;
        printf("height: %d\n", height);
        Brain.Screen.print (" X: %d Y: %d Width: %d Height: %d ",x, y, width, height);
        if(Vision1.takeSnapshot(BLUE_GOAL) == Vision1.takeSnapshot(BLUE_GOAL))
        {
          Brain.Screen.setFillColor(color::blue);
        }
        else if(Vision1.takeSnapshot(RED_GOAL) == Vision1.takeSnapshot(RED_GOAL))
        {
          Brain.Screen.setFillColor(color::red);
        }
        Brain.Screen.drawRectangle(x*xScale, y*yScale, width*xScale, height*yScale);
        
        if(targetCenter < (center - OKerror)) //If the object is to the left of center
        {
          //turn right
          rightWheels.spin(fwd, speed, velocityUnits::pct);
          leftWheels.spin(reverse, speed, velocityUnits::pct);
          // rightWheels.spin(directionType::rev, 25, velocityUnits::pct);
          // leftWheels.spin(directionType::fwd, 25, velocityUnits::pct);
        } 
        else if (targetCenter > (center + OKerror)) //If the object is to the right of center
        {
          //turn left
          rightWheels.spin(directionType::rev, speed, velocityUnits::pct);
          leftWheels.spin(directionType::fwd, speed, velocityUnits::pct);
          // rightWheels.spin(directionType::fwd, 25, velocityUnits::pct);
          // leftWheels.spin(directionType::rev, 25, velocityUnits::pct);
        } 
        else //The object is not to the right of center and not to the left of center
        {
          //turn stop
          leftWheels.stop(brakeType::brake);
          rightWheels.stop(brakeType::brake);

          if(width < 263+OKerror && height < 145+OKerror) //(width < 314+OKError) || (height < 145+OKError || height > 145-OKError)
          {
            printf("Attempting to get close enough to goal\n");
            moveForward(-15,25,5);
          }
          else
          {
            printf("Attempt success: goal is close enough\n");
            leftWheels.stop(brakeType::brake);
            rightWheels.stop(brakeType::brake);
            isTrue = false;
          }
        }
      }
      else
      {
        Brain.Screen.print("Vision Sensor: Color Signature Not Found!");
        turnClockwise(15, 15, 3);
      }
    task::sleep(100);
    }
  }else if(Hue == "Blue"){
      while(isTrue){
      Brain.Screen.clearLine();
      Brain.Screen.clearScreen();
      Vision1.takeSnapshot(BLUE_GOAL);
      if (Vision1.largestObject.exists)
      {
        targetCenter = Vision1.largestObject.centerX;
        x = Vision1.largestObject.originX;
        y = Vision1.largestObject.originY;
        width = Vision1.largestObject.width;
        printf("width: %d\n", width);
        height = Vision1.largestObject.height;
        printf("height: %d\n", height);
        Brain.Screen.print (" X: %d Y: %d Width: %d Height: %d ",x, y, width, height);
        if(Vision1.takeSnapshot(RED_GOAL) == Vision1.takeSnapshot(BLUE_GOAL))
        {
          Brain.Screen.setFillColor(color::blue);
        }
        else if(Vision1.takeSnapshot(RED_GOAL) == Vision1.takeSnapshot(RED_GOAL))
        {
          Brain.Screen.setFillColor(color::red);
        }
        Brain.Screen.drawRectangle(x*xScale, y*yScale, width*xScale, height*yScale);
        
        if(targetCenter < (center - OKerror)) //If the object is to the left of center
        {
          //turn right
          rightWheels.spin(directionType::rev, speed, velocityUnits::pct);
          leftWheels.spin(directionType::fwd, speed, velocityUnits::pct);
          // rightWheels.spin(directionType::rev, 25, velocityUnits::pct);
          // leftWheels.spin(directionType::fwd, 25, velocityUnits::pct);
        } 
        else if (targetCenter > (center + OKerror)) //If the object is to the right of center
        {
          //turn left
          rightWheels.spin(directionType::fwd, speed, velocityUnits::pct);
          leftWheels.spin(directionType::rev, speed, velocityUnits::pct);
          // rightWheels.spin(directionType::fwd, 25, velocityUnits::pct);
          // leftWheels.spin(directionType::rev, 25, velocityUnits::pct);
        } 
        else //The object is not to the right of center and not to the left of center
        {
          //turn stop
          leftWheels.stop(brakeType::brake);
          rightWheels.stop(brakeType::brake);

          if(width < 263+OKerror && height < 145+OKerror) //(width < 314+OKError) || (height < 145+OKError || height > 145-OKError)
          {
            printf("Attempting to get close enough to goal\n");
            moveForward(-15,25,5);
          }
          else
          {
            printf("Attempt success: goal is close enough\n");
            leftWheels.stop(brakeType::brake);
            rightWheels.stop(brakeType::brake);
            isTrue = false;
          }
        }
      }
      else
      {
        Brain.Screen.print("Vision Sensor: Color Signature Not Found!");
        turnClockwise(15, 15, 3);
      }
    task::sleep(100);
    }
  }
}

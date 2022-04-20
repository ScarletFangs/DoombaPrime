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

  frontWheels.rotateFor(directionType::fwd, double(distanceCM/25.9), rotationUnits::rev, double(speedPCT), velocityUnits::pct, false);
  backWheels.rotateFor(directionType::fwd, double(distanceCM/25.9), rotationUnits::rev, double(speedPCT), velocityUnits::pct, true);

  setMotorTimeout(0);
}
void moveForwardCoast(float distanceCM, int speedPCT, int timeSec){
  setMotorTimeout(timeSec);

  leftWheels.rotateFor(directionType::fwd, double(distanceCM/25.9), rotationUnits::rev, double(speedPCT), velocityUnits::pct, false);
  rightWheels.rotateFor(directionType::fwd, double(distanceCM/25.9), rotationUnits::rev, double(speedPCT), velocityUnits::pct, true);

  leftWheels.stop(coast);
  rightWheels.stop(coast);
  
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
  printf("bliftPoition: %f", bLift.position(rev));
  //bLift.rotateFor(directionType::fwd, double (degree/31.9), rotationUnits::rev, double (speedPCT), velocityUnits::pct,true);

  setMotorTimeout(0);
}


//Move back lift 2
void bLiftAuton2(float degree, int speedPCT, int timeSec)
//void bLiftAuton(double degree, int speedPCT, int timeSec)
{
  setMotorTimeout(timeSec);
  bLift.rotateFor(directionType::fwd, double (degree/31.9), rotationUnits::rev, double (speedPCT), velocityUnits::pct,true);
  printf("bliftPoition: %f", bLift.position(rev));
  //bLift.rotateFor(directionType::fwd, double (degree/31.9), rotationUnits::rev, double (speedPCT), velocityUnits::pct,true);

  setMotorTimeout(0);
}

void bLiftPOT(string dir, double timeout){
  setMotorTimeout(timeout);

  if(dir == "up"){
    while((angleLiftL.angle(deg) > 75.5)&&(angleLiftR.angle(deg) > 75.5))  //83
    {  
      printf("[up] left:%4.2f   right:%4.2f\n", angleLiftL.angle(deg), angleLiftR.angle(deg));
      bLift.spin(reverse, 50, pct);   
    }
    bLift.stop(hold);
  }else if(dir == "down"){
    while((angleLiftL.angle(deg) < 138 )&&(angleLiftR.angle(deg) < 133))
    {
      printf("[down] left:%4.2f   right:%4.2f\n", angleLiftL.angle(deg), angleLiftR.angle(deg));
      bLift.spin(fwd, 50, pct);   
    }
    bLift.stop(hold);
  }
  setMotorTimeout(0);
}

//Belt
void beltControl(double time = 45, double speedPCT = 95)
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
void dirtyBeltControl(double rotations, double speedPCT, int timeout)
{ 

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
      //printf("current turn degree: %2f", inertialAVG());
      //wait(5, msec);
      //printf("avg: %2f\n", ((inertialRight.heading(deg)+inertialLeft.heading(deg)/2)));
    }
    do{
      leftWheels.spin(reverse, 10, pct);
      rightWheels.spin(fwd, 10, pct);
    }while(inertialAVG() > degrees);
  }else if(dir == left){
    while(inertialAVG() < degrees){
      leftWheels.spin(reverse, speed, pct);
      rightWheels.spin(fwd, speed, pct);
      //printf("current turn degree: %2f", inertialAVG());
      //wait(5, msec);
      //printf("avg: %2f\n", ((inertialRight.heading(deg)+inertialLeft.heading(deg)/2)));
    }
    do{
      leftWheels.spin(fwd, 10, pct);
      rightWheels.spin(reverse, 10 , pct);
    }while(inertialAVG() > degrees);
  }
  leftWheels.stop(hold);
  rightWheels.stop(hold);
}

//Vision sensor
void visionSensorTest(string goalColor, double speed)
{
  int center = 119;//122
  int OKerror = 20;//50
  double xScale = 480.0/310;//Scaling the vision sensor range to the V5 Brain Screen
  double yScale = 240.0/212;
  int targetCenter = 0; int x = 0; int y=0; int height =0; int width = 0;
  bool isTrue = true;
  string Hue = goalColor;

  if(Hue == "Red")
  {
    while(isTrue)
    {
      Brain.Screen.clearLine();
      Brain.Screen.clearScreen();
      Vision1.takeSnapshot(RED_GOAL);
      if (Vision1.largestObject.exists)
      {
        targetCenter = Vision1.largestObject.centerX;
        x = Vision1.largestObject.originX;
        y = Vision1.largestObject.originY;
        width = Vision1.largestObject.width;
        //printf("width: %d\n", width);
        height = Vision1.largestObject.height;
        //printf("height: %d\n", height);
        Brain.Screen.print (" X: %d Y: %d Width: %d Height: %d ",x, y, width, height);
        Brain.Screen.setFillColor(color::red);
        Brain.Screen.drawRectangle(x*xScale, y*yScale, width*xScale, height*yScale);
        
        if(targetCenter < (center - OKerror)) //If the object is to the left of center
        {
          //turn right
          printf("[RED GOAL] The object is too far to the left\n");
            rightWheels.spin(directionType::fwd, speed, velocityUnits::pct);
            leftWheels.spin(directionType::rev, speed, velocityUnits::pct);
        } 
        else if (targetCenter > (center + OKerror)) //If the object is to the right of center
        {
          //turn left
          printf("[RED GOAL] The object is too far to the right\n");
          rightWheels.spin(directionType::rev, speed, velocityUnits::pct);
          leftWheels.spin(directionType::fwd, speed, velocityUnits::pct);
        } 
        else //The object is not to the right of center and not to the left of center
        {
          //turn stop
          leftWheels.stop(brakeType::brake);
          rightWheels.stop(brakeType::brake);

          if(width < 165+OKerror)// && height < 145+OKerror //(width < 314+OKError) || (height < 145+OKError || height > 145-OKError)
          {
            printf("[RED GOAL] Centered. Now attempting to get close enough to goal\n");
            moveForward(-5, 15, 5);
          }
          else
          {
            printf("[RED GOAL] Attempt success: goal is close enough\n");
            leftWheels.stop(brakeType::brake);
            rightWheels.stop(brakeType::brake);
            isTrue = false;
          }
        }
      }
      else
      {
        Brain.Screen.print("Vision Sensor: Color Signature Not Found!");
        turnClockwise(5, 5,5);
      }
      task::sleep(100);
    }
  }
  else if(Hue == "Blue")
  {
      printf("in blue");
      while(isTrue)
      {
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
          Brain.Screen.setFillColor(color::blue);
          Brain.Screen.drawRectangle(x*xScale, y*yScale, width*xScale, height*yScale);
          
          if(targetCenter < (center - OKerror)) //If the object is to the left of center
          {
            //turn right
            printf("[BLUE GOAL] The object is too far to the left\n");
            rightWheels.spin(directionType::fwd, speed, velocityUnits::pct);
            leftWheels.spin(directionType::rev, speed, velocityUnits::pct);
          } 
          else if (targetCenter > (center + OKerror)) //If the object is to the right of center
          {
            //turn left
            printf("[BLUE GOAL] The object is too far to the right\n");
            rightWheels.spin(directionType::rev, speed, velocityUnits::pct);
            leftWheels.spin(directionType::fwd, speed, velocityUnits::pct);
          } 
          else //The object is not to the right of center and not to the left of center
          {
            //turn stop
            leftWheels.stop(brakeType::brake);
            rightWheels.stop(brakeType::brake);

            if(width < 165+OKerror) //&& height < 145+OKerror //(width < 314+OKError) || (height < 145+OKError || height > 145-OKError)
            {
              printf("[BLUE GOAL] Centered. Now attempting to get close enough to goal\n");
              moveForward(-5, 15, 5);
            }
            else
            {
              printf("[BLUE GOAL] Attempt success: goal is close enough\n");
              leftWheels.stop(brakeType::brake);
              rightWheels.stop(brakeType::brake);
              isTrue = false;
            }
          }
        }
        else
        {
          Brain.Screen.print("Vision Sensor: Color Signature Not Found!");
          turnClockwise(5, 5,5);
        }
        task::sleep(100);
    }
  }
  else if(Hue == "Purple")
  {
    printf("in ring");
      while(isTrue)
      {
        Brain.Screen.clearLine();
        Brain.Screen.clearScreen();
        Vision1.takeSnapshot(DONUT);
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
          Brain.Screen.setFillColor(color::purple);
          Brain.Screen.drawRectangle(x*xScale, y*yScale, width*xScale, height*yScale);
          
          if(targetCenter < (center - OKerror)) //If the object is to the left of center
          {
            //turn right
            printf("[DONUT] The object is too far to the left\n");
            rightWheels.spin(directionType::fwd, speed, velocityUnits::pct);
            leftWheels.spin(directionType::rev, speed, velocityUnits::pct);
            // rightWheels.spin(directionType::rev, 25, velocityUnits::pct);
            // leftWheels.spin(directionType::fwd, 25, velocityUnits::pct);
          } 
          else if (targetCenter > (center + OKerror)) //If the object is to the right of center
          {
            //turn left
            printf("[DONUT] The object is too far to the right\n");
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

            if(width < 25+OKerror) //(width < 314+OKError) || (height < 145+OKError || height > 145-OKError)
            {
              printf("[DONUT] Centered. Now attempting to get close enough to ring\n");
              moveForward(-10, 20,5);
            }
            else
            {
              printf("[DONUT] Attempt success: ring is close enough\n");
              leftWheels.stop(brakeType::brake);
              rightWheels.stop(brakeType::brake);
              isTrue = false;
            }
          }
        }
        else
        {
          printf("Vision Sensor: Color Signature Not Found!\n");
          turnClockwise(5, 5, 3);
        }
        task::sleep(100);
    }
  }
}





void printing(int aim){
  int x = 0; int y = 0;
  int center = 0;
  int targetCenter = 0;
  bool runOnce = true;

   while(runOnce){
      switch(aim){
        case 1:
          Vision1.takeSnapshot(RED_GOAL);
          center = 122;
          break;
        case 2:
          Vision1.takeSnapshot(BLUE_GOAL);
          center = 122;
          break;
        case 3:
          Vision1.takeSnapshot(DONUT);
          center = 33;
          break;
      }

      if(Vision1.largestObject.exists){
          targetCenter = Vision1.largestObject.centerX;
          printf("center: %d\n", targetCenter);
          x = Vision1.largestObject.originX;
          //printf("center x: %d\n", Vision1.largestObject.originX);
          y = Vision1.largestObject.originY;
          //printf("center y: %d\n", Vision1.largestObject.originY);
      }
      wait( 10, msec);
   }
}
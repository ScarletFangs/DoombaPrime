#include "vex.h"
#include "routine.h"
#include "autonomous-functions.h"
#include "robot-config.h"
#include "driving-functions.h"
#include "GPS.h"
#include <iostream>
#include <fstream>

using namespace vex;
timer internalTimer;

/* -----------------------------------*/
//GOALSIDE
/* -----------------------------------*/
void goalFrontBlue()
{
  internalTimer.reset();
  //get yellow goal
  latchDown.set(1);
  liftAuton(0, 10, 5);
  moveForward(78, 100, 5);
  latchDown.set(0);
  moveForward(-40, 30, 10000);
  liftAuton(2, 10, 1);
  visionSensorTest("Purple", 5);
  wait(1, sec);

  // //get personal
  //inertialTurn(left, 20, 90, 5);   //NOT WORKING FOR NOW. IT CONTNINUES TO SPIN NON STOP
  turnClockwise(-15, 15, 5); //perfect is 15
  moveForward(15, 10, 1);
  bLiftAuton2(28, 50, 1); //down
  visionSensorTest("Blue", 5);
  moveForward(-20, 20, 1);
  bLiftAuton2(-30, 50, 1);  //up
  moveForward(20, 10, 1); //uncomment this
  do{
    Belt.spin(fwd, 95, pct);
    // moveForward(-10, 15, 1);
    // moveForward(-10, 15, 1);
  }while(internalTimer > 30000);
}

void goalFrontRed()
{
  internalTimer.reset();
  //get yellow goal
  latchDown.set(1);
  liftAuton(0, 10, 5);
  moveForward(78, 100, 5);
  latchDown.set(0);
  moveForward(-40, 30, 10000);
  liftAuton(2, 10, 1);
  visionSensorTest("Purple", 5);
  wait(1, sec);

  // //get personal
  //inertialTurn(left, 20, 90, 5);   //NOT WORKING FOR NOW. IT CONTNINUES TO SPIN NON STOP
  turnClockwise(-15, 15, 5); //perfect is 15
  moveForward(15, 10, 1);
  bLiftAuton2(28, 50, 1); //down
  visionSensorTest("Red", 5);
  moveForward(-20, 20, 1);
  bLiftAuton2(-30, 50, 1);  //up
  moveForward(20, 10, 1); //uncomment this
  do{
    Belt.spin(fwd, 95, pct);
    // moveForward(-10, 15, 1);
    // moveForward(-10, 15, 1);
  }while(internalTimer > 30000);
}

/* -----------------------------------*/
//RAMPSIDE
/* -----------------------------------*/
void rampFrontRed(){
  internalTimer.reset();
  //get yellow goal
  latchDown.set(1);
  liftAuton(0, 10, 5);
  moveForward(76, 100, 5);
  latchDown.set(0);
  //moveForward(-110, 100, 10000); //initially we just move backward hard code

  //newly added. allign using vision sensor
  moveForward(-40, 30, 10000);    //-40, 30, 10000
  liftAuton(2, 10, 1);
  visionSensorTest("Purple", 15);
  wait(1, sec);

  // //get personal
  inertialTurn(left, 15, 90, 5);
  //turnClockwise(-15, 15, 5); //perfect is 15
  moveForward(10, 10, 1);
  bLiftAuton2(28, 50, 1); //down
  visionSensorTest("Red", 10);
  moveForward(-7, 10, 1);
  bLiftAuton2(-30.2, 50, 1);  //up
  moveForward(20, 10, 1);
  inertialTurn(right, 15, 25, 1);
  do{
    Belt.spin(fwd, 90, pct);
    moveForward(50, 15, 1);
    wait(1, sec);
    moveForward(-40, 15, 1);
  }while((internalTimer > 30000) && (internalTimer < 45000));

}
void rampFrontBlue(){
  internalTimer.reset();
  //get yellow goal
  latchDown.set(1);
  liftAuton(0, 10, 5);
  moveForward(76, 100, 5);
  latchDown.set(0);
  //moveForward(-110, 100, 10000); //initially we just move backward hard code

  //newly added. allign using vision sensor
  moveForward(-40, 30, 10000);
  liftAuton(2, 10, 1);
  visionSensorTest("Purple", 10);
  wait(1, sec);

  // //get personal
  //inertialTurn(left, 30, 80, 5); //NOT WORKING FOR NOW. IT CONTNINUES TO SPIN NON STOP
  turnClockwise(-15, 15, 5); //perfect is 15
  moveForward(10, 10, 1);
  bLiftAuton2(28, 50, 1); //down
  visionSensorTest("Blue", 5);
  moveForward(-15, 10, 1);
  bLiftAuton2(-28, 50, 1);  //up   -30.2
  moveForward(20, 10, 1);
  inertialTurn(right, 15, 65, 1);
  Belt.spin(fwd, 90, pct);
  moveForward(30, 20, 1);   //good speed 15
  do{
    wait(1, sec);
    moveForward(-40, 20, 1);
    wait(1, sec);
    moveForward(40, 20, 1);
  }while((internalTimer > 30000) && (internalTimer < 45000));
}

/* -----------------------------------*/
//OTHERS
/* -----------------------------------*/
void rampSafe(){
  internalTimer.reset();

  bLiftAuton(1, 1);
  moveForward(-40, 20, 5);
  bLiftAuton(0.35, 1);
  moveForward(20, 10, 2);
  do{
    Belt.spin(fwd, 89, pct);
  }while(internalTimer.time() > 5000);
}

void sensorTest(){
  bLiftAuton2(28, 50, 1);
  wait(1, sec);
  bLiftAuton2(-30, 50, 1);
}
void skillsAuton(){
  // //1push then grab yellow to other side
  // latchDown.set(1);   //open
  // //moveForward(200, 40, 10);
  // DriveToTargetXY(0, -970, 47, 100); //DriveToTargetXY(0, -970, 47, 50);     //0, -970, 19, 50
  // latchDown.set(0);   //close
  // moveForward(5, 35, 1);
  // liftAuton(2, 10, 1);
  // printf("1:DONE\n");

  // //2position for grabbing goal off ramp
  // DriveToTargetXY(635, -1270, 10, 55);       //635,-1270,13,65
  // ImprovedDriveToHeading(240, 10, 6, 20);  //238
  // wait(5, msec);
  // printf("2:DONE\n");

  // //3drive and pick up goal off ramp and move
  // bLiftAuton(1.25, 1);        //bLiftAuton(-33, 50, 2);
  // moveForward(-160, 35, 5);   //-125, 25, 1
  // bLiftAuton(0.5, 1);     //bLiftAuton(-21.5, 30, 5);
  // moveForward(75, 25, 1);
  // printf("3:DONE\n");
  
  // //4 drive to personal square
  // ImprovedDriveToHeading(300, 5, 3, 50);  //300, 5, 3, 50
  // DriveToTargetXY(-200, -850, 19, 50);
  // ImprovedDriveToHeading(90, 4, 3, 50);   //300, 5, 3, 50
  // printf("4:DONE\n");
  
  //5go back to start scoring rings
  //dirtyBeltControl(10, 89, 1);
  //moveForward(-120, 10, 10);    //initial go back
  liftAuton(-5, 10, 1);
  lift.stop(coast);
  bLiftAuton(1.23, 1);
  wait(1, msec);
  bLiftAuton(0.5, 1);
  moveForward(-50, 10, 2);
  dirtyBeltControl(10, 89, 1);
  moveForward(-40, 10, 2);
  dirtyBeltControl(10, 89, 1);
  printf("5:DONE\n");

  //6   //field lifted, attempt code at ocmpeittion tmr
  bLiftAuton(1.23, 1);
  moveForward(125, 15, 1);
  bLiftAuton(1.10, 1);
  printf("yes\n");
  DriveToTargetXY(-850, -600, 10, 30);
  printf("no\n");
  ImprovedDriveToHeading(0, 5, 3, 20);
  printf("yes\n");
  moveForward(-150, 20, 3);
  bLiftAuton(0.5, 1);    
  moveForward(70, 10, 1);
  printf("6:DONE\n");

  //7
  ImprovedDriveToHeading(270, 5, 3, 20);
  moveForward(-250, 50, 1);

}


#include "vex.h"
#include "routine.h"
#include "autonomous-functions.h"
#include "robot-config.h"
#include "driving-functions.h"
#include "GPS.h"
#include <iostream>
#include <fstream>

using namespace vex;

timer routineTimer;
//latchDown.set(1) - pneumatic open
//bLiftAuton (1.25, 2) - down       (0.5, 2) - up
void rampFront(){
  routineTimer.reset();
  latchDown.set(1);

  //get yellow goal in fro  nt
  moveForward(180, 100, 5);  
  //moveForward(-200, 100, 5);
}

void skillsAuton(){
  // //1push then grab yellow to other side
  latchDown.set(1);   //open
  //moveForward(200, 40, 10);
  DriveToTargetXY(0, -970, 47, 100); //DriveToTargetXY(0, -970, 47, 50);     //0, -970, 19, 50
  latchDown.set(0);   //close
  moveForward(5, 35, 1);
  liftAuton(2, 10, 1);
  printf("1:DONE\n");

  // //2position for grabbing goal off ramp
  DriveToTargetXY(635, -1290, 10, 55);   //635, -1270, 10, 55    //635,-1270,13,65
  ImprovedDriveToHeading(240, 10, 6, 20);  //238
  wait(5, msec);
  printf("2:DONE\n");

  // //3drive and pick up goal off ramp and move
  bLiftAuton(1.25, 1);        //bLiftAuton(-33, 50, 2);
  moveForward(-160, 35, 5);   //-125, 25, 1
  bLiftAuton(0.5, 1);     //bLiftAuton(-21.5, 30, 5);
  moveForward(75, 25, 1);
  printf("3:DONE\n");
  
  // //4 drive to personal square
  ImprovedDriveToHeading(300, 5, 3, 50);  //300, 5, 3, 50
  DriveToTargetXY(-200, -850, 19, 50);
  ImprovedDriveToHeading(90, 4, 3, 50);   //300, 5, 3, 50
  printf("4:DONE\n");
  
  //5go back to start scoring rings
  dirtyBeltControl(10, 89, 1);
  // moveForward(-120, 10, 10);    //initial go back
  // liftAuton(-0.5, 10, 1);
  // lift.stop(coast);
  // bLiftAuton(1.23, 1);
  // wait(1, msec);
  // bLiftAuton(0.5, 1);
  moveForward(-50, 10, 2);
  dirtyBeltControl(10, 89, 1);
  moveForward(-40, 10, 2);
  dirtyBeltControl(10, 89, 1);
  printf("5:DONE\n");

  //6   //field lifted, attempt code at ocmpeittion tmr
  bLiftAuton(1.23, 1);
  moveForward(125, 15, 1);
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


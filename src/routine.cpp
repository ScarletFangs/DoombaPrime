#include "vex.h"
#include "routine.h"
#include "autonomous-functions.h"
#include "robot-config.h"
#include "driving-functions.h"
#include "GPS.h"
#include <iostream>
#include <fstream>

using namespace vex;
using namespace std;

vex::thread beltThread(beltControl);

void otherSideTallGoalBLUE(){
  latchDown.set(1);
  bLiftAuton(31, 50, 5);
  moveForward(-43, 20, 5);
  bLiftAuton(-21.2, 30, 5);
  dirtyBeltControl(1000, 89);

  moveForward(40, 10, 5);
  turnClockwise(30, 20, 5);
  dirtyBeltControl(45, 89);
  moveForward(20, 10, 5);
  turnClockwise(30, 20, 5);
  moveForward(20, 10, 5);

  DriveToTargetXY(600, -900, 7, 65);
  DriveToTargetXY(0, -900, 7, 65);
  moveForward(15, 20, 5);
  latchDown.set(0);

  ImprovedDriveToHeading(180, 10, 3, 50);
  moveForward(10, 20, 5);
  ImprovedDriveToHeading(270, 10, 3, 50);

  moveForward(-150, 60, 50);
}
void otherSideTallGoalRED(){
  latchDown.set(1);
  bLiftAuton(31, 50, 5);
  moveForward(-43, 20, 5);
  bLiftAuton(-21.2, 30, 5);
  dirtyBeltControl(1000, 89);

  moveForward(40, 10, 5);
  turnClockwise(30, 20, 5);
  dirtyBeltControl(45, 89);
  moveForward(20, 10, 5);
  turnClockwise(30, 20, 5);
  moveForward(20, 10, 5);

  DriveToTargetXY(-600, 900, 7, 65);
  DriveToTargetXY(0, 900, 7, 65);
  moveForward(15, 20, 5);
  latchDown.set(0);

  ImprovedDriveToHeading(0, 10, 3, 50);
  moveForward(10, 20, 5);
  ImprovedDriveToHeading(90, 10, 3, 50);

  moveForward(-150, 60, 50);
}

void gpsTEST(){
latchDown.set(0);
ImprovedDriveToHeading(182, 1, 20, 10);
wait(1, sec);
ImprovedDriveToHeading(0, 1, 20, 10);
wait(1, sec);
ImprovedDriveToHeading(270, 1, 20, 10);
wait(1, sec);
ImprovedDriveToHeading(90, 1, 20, 10);
}

//BETTER WORK 3/4
void FrontYellowGoalRED(){
  liftAuton(0, 10, 10);     //push lift to bottom
  latchDown.set(1);   //open
  //flexMvmtR(181, 191, 60, 76, 10);    //60,76
  moveForward(181, 70, 10);
  latchDown.set(0);   //close
  moveForward(-75, 30, 500000000);

  //turn for blue positioning
  //ImprovedDriveToHeading(200, 5, 20, 5);
  DriveToTargetXY(-920, -500, 10, 45);  //920
  wait(1, sec);
  ImprovedDriveToHeading(0, 1, 5, 50); //174 for blue side

  //grab blue
  bLiftAuton(32, 50, 5);
  moveForward(-115, 20, 5);
  bLiftAuton(-21.2, 30, 5);
  dirtyBeltControl(1000, 89);
  DriveToTargetXY(-1060, -1190, 5, 40);
  //turnClockwise(-30, 7, 10);
  ImprovedDriveToHeading(270, 1, 3, 50);   //85 for blue side
  dirtyBeltControl(1000, 89);
  wait(5, msec);

  //move forward 220 but divide distance so we can check if donuts get stuck
  //1st iteration
  moveForward(-44, 7, 10);
  dirtyBeltControl(45, 89); 
  //2nd iteration
  moveForward(-44, 7, 10);
  dirtyBeltControl(45, 89);
  //3rd iteration
  moveForward(-44, 7, 10);
  dirtyBeltControl(45, 89);
  // //4th iteration
  // moveForward(-44, 7, 10);
  // dirtyBeltControl(45, 89);
  // //5th iteration
  // moveForward(-44, 7, 10);
  // dirtyBeltControl(45, 89);
  //total of 220

  //turnClockwise(-110, 7, 10);
  ImprovedDriveToHeading(90, 1, 3, 50);

  // //moving back to collect 9 donuts we can feed. we divide it into chunks
  // //#1
  moveForward(-50, 7, 10);
  dirtyBeltControl(45, 89);
  // //#2
  moveForward(-50, 7, 10);
  dirtyBeltControl(45, 89);
  // //#3
  moveForward(-50, 7, 10);
  dirtyBeltControl(45, 89);
  // //#4
  moveForward(-50, 7, 10);
  dirtyBeltControl(45, 89);
  //   // //#5
  // moveForward(-50, 7, 10);
  // dirtyBeltControl(45, 89);
   
  while(1)
  {
    moveForward(70, 7, 10);
    dirtyBeltControl(45, 89);
    moveForward(-70, 7, 10);  //forward
    dirtyBeltControl(45, 89);
  }
}

void FrontYellowGoalBLUE(){
  liftAuton(0, 10, 10);     //push lift to bottom
  latchDown.set(1);   //open
  //flexMvmtR(181, 191, 60, 76, 10);    //60,76
  moveForward(181, 70, 10);
  latchDown.set(0);   //close
  moveForward(-75, 30, 500000000);

  //turn for blue positioning
  //ImprovedDriveToHeading(200, 5, 20, 5);
  DriveToTargetXY(920, 500, 10, 45);  //920
  wait(1, sec);
  ImprovedDriveToHeading(180, 1, 3, 50); //174 for blue side

  //grab blue
  bLiftAuton(32, 50, 5);
  moveForward(-115, 20, 5);
  bLiftAuton(-21.2, 30, 5);
  dirtyBeltControl(1000, 89);
  DriveToTargetXY(1060, 1190, 5, 40);
  //turnClockwise(-30, 7, 10);
  ImprovedDriveToHeading(90, 1, 3, 50);   //85 for blue side
  dirtyBeltControl(1000, 89);
  wait(5, msec);

  //move forward 220 but divide distance so we can check if donuts get stuck
  //1st iteration
  moveForward(-44, 7, 10);
  dirtyBeltControl(45, 89); 
  //2nd iteration
  moveForward(-44, 7, 10);
  dirtyBeltControl(45, 89);
  //3rd iteration
  moveForward(-44, 7, 10);
  dirtyBeltControl(45, 89);
  // //4th iteration
  // moveForward(-44, 7, 10);
  // dirtyBeltControl(45, 89);
  // //5th iteration
  // moveForward(-44, 7, 10);
  // dirtyBeltControl(45, 89);
  //total of 220

  //turnClockwise(-110, 7, 10);
  ImprovedDriveToHeading(270, 1, 3, 50);

  // //moving back to collect 9 donuts we can feed. we divide it into chunks
  // //#1
  moveForward(-50, 7, 10);
  dirtyBeltControl(45, 89);
  // //#2
  moveForward(-50, 7, 10);
  dirtyBeltControl(45, 89);
  // //#3
  moveForward(-50, 7, 10);
  dirtyBeltControl(45, 89);
  // //#4
  moveForward(-50, 7, 10);
  dirtyBeltControl(45, 89);
  //   // //#5
  // moveForward(-50, 7, 10);
  // dirtyBeltControl(45, 89);
   
  while(1)
  {
    moveForward(70, 7, 10);
    dirtyBeltControl(45, 89);
    moveForward(-70, 7, 10);  //forward
    dirtyBeltControl(45, 89);
  }
}
void dirtyBlueGoalSide()
{
  liftAuton(0, 10, 10);     //push lift to bottom
  latchDown.set(1);           //open
  bLiftAuton(32.5, 50, 5); 
  wait(1,sec);
  moveForward(-75, 25, 10);
  bLiftAuton(-21.5, 30, 5); //goal ready for rings
  dirtyBeltControl(1000, 89);
  turnClockwise(-42, 7, 10);
  dirtyBeltControl(1000, 89);
  moveForward(-56, 7, 10); //positioning
  dirtyBeltControl(1000, 89);
  turnClockwise(40, 7, 10);
  dirtyBeltControl(1000, 89);

  //move forward 220 but divide distance so we can check if donuts get stuck
  //1st iteration
  moveForward(-44, 7, 10);
  dirtyBeltControl(45, 89); 
  //2nd iteration
  moveForward(-44, 7, 10);
  dirtyBeltControl(45, 89);
  //3rd iteration
  moveForward(-44, 7, 10);
  dirtyBeltControl(45, 89);
  //4th iteration
  moveForward(-44, 7, 10);
  dirtyBeltControl(45, 89);
  //5th iteration
  moveForward(-44, 7, 10);
  dirtyBeltControl(45, 89);
  //total of 220

  turnClockwise(-60, 7, 10);

  // //moving back to collect 9 donuts we can feed. we divide it into chunks
  // //#1
  moveForward(-50, 7, 10);
  dirtyBeltControl(45, 89);
  // //#2
  moveForward(-50, 7, 10);
  dirtyBeltControl(45, 89);
  // //#3
  moveForward(-50, 7, 10);
  dirtyBeltControl(45, 89);
  // //#4
  moveForward(-50, 7, 10);
  dirtyBeltControl(45, 89);
  // //fifth move forward 50 to get to our end so we can feed donuts
  moveForward(-50, 7, 10);
  dirtyBeltControl(45, 89);
  
  while(1)
  {
    moveForward(70, 7, 10);
    dirtyBeltControl(45, 89);
    moveForward(-70, 7, 10);  //forward
    dirtyBeltControl(45, 89);
  }
}

void skillsAuton(){
  //1push then grab yellow to other side
  latchDown.set(1);   //open
  //moveForward(200, 40, 10);
  DriveToTargetXY(0, -970, 47, 50);     //0, -970, 19, 50
  latchDown.set(0);   //close
  moveForward(5, 20, 3);
  liftAuton(2, 10, 5);
  // moveForward(30, 10, 3);
  // turnClockwise(35, 20, 3);   //35,30,3
  // moveForward(20, 19, 3);
  printf("1:DONE\n");

  //2position for grabbing goal off ramp
  //liftAuton(70, 20, 5);
  DriveToTargetXY(635, -1300, 9, 60);       //635, -1270
  ImprovedDriveToHeading(238, 20, 3, 50);  //246
  wait(5, msec);
  printf("2:DONE\n");

  //3drive and pick up goal off ramp and move
  bLiftAuton(42, 50, 2); 
  moveForward(-120, 25, 2);
  bLiftAuton(-32, 30, 2);     //-25 good
  moveForward(75, 35, 2);
  printf("3:DONE\n");
  
  //4drive to feed donuts into red
  ImprovedDriveToHeading(300, 5, 3, 50);
  DriveToTargetXY(-200, -850, 19, 50);
  ImprovedDriveToHeading(90, 5, 3, 50);

  //5go back to start scoring rings
  dirtyBeltControl(100, 89);
  moveForward(-120, 10, 10);    //initial go back
  dirtyBeltControl(45, 89);
  moveForward(80, 10, 10);
  dirtyBeltControl(45, 89);
  moveForward(-80, 10, 10);
  dirtyBeltControl(45, 89);
  moveForward(80, 10, 10);
  dirtyBeltControl(45, 89);
  moveForward(-80, 10, 10);
  dirtyBeltControl(45, 89);
}


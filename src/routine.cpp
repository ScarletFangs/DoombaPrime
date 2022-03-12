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
  bLiftAuton(1.25, 2);  //comes down //previous before modification: bLiftAuton(31, 50, 5);
  moveForward(-43, 20, 5);
  bLiftAuton(0.5, 2); //comes up //previous before modification: bLiftAuton(-21.2, 30, 5);
  dirtyBeltControl(1000, 89, 1);

  moveForward(40, 10, 5);
  turnClockwise(30, 20, 5);
  dirtyBeltControl(45, 89, 1);
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
  bLiftAuton(1.25, 2);  //comes down //previous before modification: bLiftAuton(31, 50, 5);
  moveForward(-43, 20, 5);
  bLiftAuton(0.5, 2); //comes up //previous before modification: bLiftAuton(-21.2, 30, 5);
  dirtyBeltControl(1000, 89, 1);

  moveForward(40, 10, 5);
  turnClockwise(30, 20, 5);
  dirtyBeltControl(45, 89, 1);
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
  bLiftAuton(1.25, 2);  //comes down //previous before modification: bLiftAuton(32, 50, 5);
  moveForward(-115, 20, 5);
  bLiftAuton(0.5, 2); //comes up //previous before modification: bLiftAuton(-21.2, 30, 5);
  dirtyBeltControl(1000, 89, 1);
  DriveToTargetXY(-1060, -1190, 5, 40);
  //turnClockwise(-30, 7, 10);
  ImprovedDriveToHeading(270, 5, 3, 50);   //85 for blue side
  dirtyBeltControl(1000, 89, 1);
  wait(5, msec);

  //move forward 220 but divide distance so we can check if donuts get stuck
  //1st iteration
  moveForward(-44, 7, 10);
  dirtyBeltControl(45, 89, 1); 
  //2nd iteration
  moveForward(-44, 7, 10);
  dirtyBeltControl(45, 89, 1);
  //3rd iteration
  moveForward(-44, 7, 10);
  dirtyBeltControl(45, 89, 1);
  // //4th iteration
  // moveForward(-44, 7, 10);
  // dirtyBeltControl(45, 89, 1);
  // //5th iteration
  // moveForward(-44, 7, 10);
  // dirtyBeltControl(45, 89, 1);
  //total of 220

  //turnClockwise(-110, 7, 10);
  ImprovedDriveToHeading(90, 5, 3, 50);

  // //moving back to collect 9 donuts we can feed. we divide it into chunks
  // //#1
  moveForward(-50, 7, 10);
  dirtyBeltControl(45, 89, 1);
  // //#2
  moveForward(-50, 7, 10);
  dirtyBeltControl(45, 89, 1);
  // //#3
  moveForward(-50, 7, 10);
  dirtyBeltControl(45, 89, 1);
  // //#4
  moveForward(-50, 7, 10);
  dirtyBeltControl(45, 89, 1);
  //   // //#5
  // moveForward(-50, 7, 10);
  // dirtyBeltControl(45, 89, 1);
   
  while(1)
  {
    moveForward(70, 7, 10);
    dirtyBeltControl(45, 89, 1);
    moveForward(-70, 7, 10);  //forward
    dirtyBeltControl(45, 89, 1);
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
  ImprovedDriveToHeading(180, 5, 3, 50); //174 for blue side

  //grab blue
  bLiftAuton(1.25, 2);  //comes down //previous before modification: bLiftAuton(32, 50, 5);
  moveForward(-115, 20, 5);
  bLiftAuton(0.5, 2); //comes up //previous before modification: bLiftAuton(-21.2, 30, 5);
  dirtyBeltControl(1000, 89, 1);
  DriveToTargetXY(1060, 1190, 5, 40);
  //turnClockwise(-30, 7, 10);
  ImprovedDriveToHeading(90, 5, 3, 50);   //85 for blue side
  dirtyBeltControl(1000, 89, 1);
  wait(5, msec);

  //move forward 220 but divide distance so we can check if donuts get stuck
  //1st iteration
  moveForward(-44, 7, 10);
  dirtyBeltControl(45, 89, 1); 
  //2nd iteration
  moveForward(-44, 7, 10);
  dirtyBeltControl(45, 89, 1);
  //3rd iteration
  moveForward(-44, 7, 10);
  dirtyBeltControl(45, 89, 1);
  // //4th iteration
  // moveForward(-44, 7, 10);
  // dirtyBeltControl(45, 89);
  // //5th iteration
  // moveForward(-44, 7, 10);
  // dirtyBeltControl(45, 89);
  //total of 220

  //turnClockwise(-110, 7, 10);
  ImprovedDriveToHeading(270, 5, 3, 50);

  // //moving back to collect 9 donuts we can feed. we divide it into chunks
  // //#1
  moveForward(-50, 7, 10);
  dirtyBeltControl(45, 89, 1);
  // //#2
  moveForward(-50, 7, 10);
  dirtyBeltControl(45, 89, 1);
  // //#3
  moveForward(-50, 7, 10);
  dirtyBeltControl(45, 89, 1);
  // //#4
  moveForward(-50, 7, 10);
  dirtyBeltControl(45, 89, 1);
  //   // //#5
  // moveForward(-50, 7, 10);
  // dirtyBeltControl(45, 89, 1);
   
  while(1)
  {
    moveForward(70, 7, 10);
    dirtyBeltControl(45, 89, 1);
    moveForward(-70, 7, 10);  //forward
    dirtyBeltControl(45, 89, 1);
  }
}
void dirtyBlueGoalSide()
{
  liftAuton(0, 10, 10);     //push lift to bottom
  latchDown.set(1);           //open
  bLiftAuton(1.25, 2);  //comes down //previous before modification: bLiftAuton(32.5, 50, 5); 
  wait(1,sec);
  moveForward(-75, 25, 10);
  bLiftAuton(0.5, 2); //comes up //previous before modification: bLiftAuton(-21.5, 30, 5); //goal ready for rings
  dirtyBeltControl(1000, 89, 1);
  turnClockwise(-42, 7, 10);
  dirtyBeltControl(1000, 89, 1);
  moveForward(-56, 7, 10); //positioning
  dirtyBeltControl(1000, 89, 1);
  turnClockwise(40, 7, 10);
  dirtyBeltControl(1000, 89, 1);

  //move forward 220 but divide distance so we can check if donuts get stuck
  //1st iteration
  moveForward(-44, 7, 10);
  dirtyBeltControl(45, 89, 1); 
  //2nd iteration
  moveForward(-44, 7, 10);
  dirtyBeltControl(45, 89, 1);
  //3rd iteration
  moveForward(-44, 7, 10);
  dirtyBeltControl(45, 89, 1);
  //4th iteration
  moveForward(-44, 7, 10);
  dirtyBeltControl(45, 89, 1);
  //5th iteration
  moveForward(-44, 7, 10);
  dirtyBeltControl(45, 89, 1);
  //total of 220

  turnClockwise(-60, 7, 10);

  // //moving back to collect 9 donuts we can feed. we divide it into chunks
  // //#1
  moveForward(-50, 7, 10);
  dirtyBeltControl(45, 89, 1);
  // //#2
  moveForward(-50, 7, 10);
  dirtyBeltControl(45, 89, 1);
  // //#3
  moveForward(-50, 7, 10);
  dirtyBeltControl(45, 89, 1);
  // //#4
  moveForward(-50, 7, 10);
  dirtyBeltControl(45, 89, 1);
  // //fifth move forward 50 to get to our end so we can feed donuts
  moveForward(-50, 7, 10);
  dirtyBeltControl(45, 89, 1);
  
  while(1)
  {
    moveForward(70, 7, 10);
    dirtyBeltControl(45, 89, 1);
    moveForward(-70, 7, 10);  //forward
    dirtyBeltControl(45, 89, 1);
  }
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
  //dirtyBeltControl(10, 89, 1);
  moveForward(-40, 10, 2);
  //dirtyBeltControl(10, 89, 1);
  printf("5:DONE\n");

  //6
  bLiftAuton(1.23, 1);
  moveForward(100, 10, 1);
  bLiftAuton(1.10, 1);
  printf("yes\n");
  DriveToTargetXY(-850, -600, 10, 30);
  printf("no\n");
  ImprovedDriveToHeading(0, 5, 3, 20);
  printf("yes\n");
  moveForward(-100, 10, 1);
  bLiftAuton(0.5, 1);    
  moveForward(70, 10, 1);
  printf("6:DONE\n");

  //7
  ImprovedDriveToHeading(270, 5, 3, 20);
  moveForward(-250, 50, 1);

}


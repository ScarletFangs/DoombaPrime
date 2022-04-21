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

/* -----------------------------------
  LOCATION: RED GOAL-SIDE

  AUTON DESCRIPTION:
  -Grab Red Alliance Goal from Triangle Line
  -Collect Ring
  -Grab Yellow
 -----------------------------------*/
void donutRedGoal()
{
  internalTimer.reset();
}



/* -----------------------------------
  LOCATION: RED GOAL-SIDE

  AUTON DESCRIPTION:
  -Grab Red Alliance Goal from Triangle Line
  -Collect Ring
  -Grab Yellow
 -----------------------------------*/
void donutBlueGoal()
{
  internalTimer.reset();
}


/* -----------------------------------
  LOCATION: RED RAMP-SIDE

  AUTON DESCRIPTION:
  -Grab Red Alliance Goal from Ramp
  -Collect Ring
  -Grab Yellow
 -----------------------------------*/
void donutRedRamp()
{
  internalTimer.reset();

//positioning
  moveForward(15, 15, 1);
  turnClockwise(-10, 15, 5);

//Grabbing Goal
  bLiftPOT("down", 1);
  visionSensorTest("Red", 5);
  moveForward(-20, 20, 1);
  bLiftPOT("up", 2);

//Collecting Ring
  moveForward(20, 10, 1);
  inertialTurn(right, 15, 30, 1);
  Belt.spin(fwd, 90, pct);
  moveForward(25, 20, 1);  
  do
  {
    wait(500, msec);
    moveForward(-32, 20, 1);
    wait(500, msec);
    moveForward(32, 20, 1); 
  } while(internalTimer < 30000);

//Grab Yellow
  inertialTurn(right, 15, 15, 1);
  latchDown.set(1); //open
  liftAuton(0, 10, 5);
  moveForward(60, 30, 5); //78, 98, 5
  latchDown.set(0); //close latchdown
  liftAuton(2, 10, 1);
  moveForward(-70, 60, 10000);
}


/* -----------------------------------
  LOCATION: BLUE RAMP-SIDE

  AUTON DESCRIPTION:
  -Grab Blue Alliance Goal from Ramp
  -Collect Ring
  -Grab Yellow
 -----------------------------------*/
void donutBlueRamp()
{
  internalTimer.reset();

//positioning
  moveForward(15, 15, 1);
  turnClockwise(-10, 15, 5);

//Grabbing Goal
  bLiftPOT("down", 1);
  visionSensorTest("Blue", 5);
  moveForward(-20, 20, 1);
  bLiftPOT("up", 2);

//Collecting Ring
  moveForward(20, 10, 1);
  inertialTurn(right, 15, 30, 1);
  Belt.spin(fwd, 90, pct);
  moveForward(25, 20, 1);  
  do
  {
    wait(500, msec);
    moveForward(-32, 20, 1);
    wait(500, msec);
    moveForward(32, 20, 1); 
  } while(internalTimer < 30000);

//Grab Yellow
  inertialTurn(right, 15, 15, 1);
  latchDown.set(1); //open
  liftAuton(0, 10, 5);
  moveForward(60, 30, 5); //78, 98, 5
  latchDown.set(0); //close latchdown
  liftAuton(2, 10, 1);
  moveForward(-70, 60, 10000);
}



/* -----------------------------------
  LOCATION: BLUE GOAL-SIDE

  AUTON DESCRIPTION:
  -Go for Yellow first
  -Grab Blue Alliance Goal from Triangle Line
  -Collect Ring
 -----------------------------------*/
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

  //get personal
  //inertialTurn(left, 20, 90, 5); //NOT WORKING FOR NOW. IT CONTNINUES TO SPIN NON STOP
  turnClockwise(-15, 15, 5);
  moveForward(15, 10, 1);

  //NEW BACKLIFT DOWN BELOW
  bLiftPOT("down", 1);

  visionSensorTest("Blue", 5);
  moveForward(-20, 20, 1);

  //NEW BACKLIFT UP BELOW
  bLiftPOT("up", 2);


  moveForward(20, 10, 1);
  do{
    Belt.spin(fwd, 95, pct);
    // moveForward(-10, 15, 1);
    // moveForward(-10, 15, 1);
  }while(internalTimer > 30000);
}


/* -----------------------------------
  LOCATION: RED GOAL-SIDE

  AUTON DESCRIPTION:
  -Go for Yellow first
  -Grab Red Alliance Goal from Triangle Line
  -Collect Ring

 -----------------------------------*/
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

  //get personal
  //inertialTurn(left, 20, 90, 5); //NOT WORKING FOR NOW. IT CONTNINUES TO SPIN NON STOP
  turnClockwise(-15, 15, 5);
  moveForward(15, 10, 1);

  //NEW BACKLIFT DOWN
  bLiftPOT("down", 1);

  visionSensorTest("Red", 5);
  moveForward(-20, 20, 1);

  //NEW BACKLIFT UP
  bLiftPOT("up", 2); 

  moveForward(20, 10, 1); 
  do{
    Belt.spin(fwd, 95, pct);
    // moveForward(-10, 15, 1);
    // moveForward(-10, 15, 1);
  }while(internalTimer > 30000);
}


/* -----------------------------------
  LOCATION: RED RAMP-SIDE

  AUTON DESCRIPTION:
  -Go for Yellow first
  -Grab Red Alliance Goal from Ramp
  -Collect Ring
 -----------------------------------*/
void rampFrontRed()
{
  internalTimer.reset();
  //get yellow goal
  latchDown.set(1);
  liftAuton(0, 10, 5);
  moveForward(75, 85, 5); //78, 98, 5
  latchDown.set(0);

  moveForward(-40, 30, 10000);
  liftAuton(2, 10, 1);
  visionSensorTest("Purple", 10);
  wait(1, sec);

  //get personal
  //inertialTurn(left, 15, 90, 5); NOT WORKING FOR NOW
  turnClockwise(-15, 15, 5);
  moveForward(10, 10, 1);

  //OLD BACKLIFT: bLiftAuton2(33, 50, 1); //down 
  //NEW BACKLIFT DOWN BELOW
  bLiftPOT("down", 1);


  visionSensorTest("Red", 5);
  moveForward(-15, 10, 1);


  //OLD BACKLIFT: bLiftAuton2(-31, 50, 1);  //up //-32.5
  //NEW BACKLIFT UP BELOW
  bLiftPOT("up", 2);

  moveForward(20, 10, 1);
  inertialTurn(right, 15, 30, 1);
  Belt.spin(fwd, 90, pct);
  moveForward(25, 20, 1);  
  do
  {
    wait(500, msec);
    moveForward(-35, 20, 1);
    wait(500, msec);
    moveForward(35, 20, 1); 
  } while((internalTimer > 30000) && (internalTimer < 45000));
}  


/* -----------------------------------
  LOCATION: Blue RAMP-SIDE

  AUTON DESCRIPTION:
  -Go for Yellow first
  -Grab Blue Alliance Goal from Ramp
  -Collect Ring
 -----------------------------------*/
void rampFrontBlue()
{
  internalTimer.reset();
  //get yellow goal
  latchDown.set(1);
  liftAuton(0, 10, 5);
  moveForward(75, 85, 5); //78, 98, 5
  latchDown.set(0);

  moveForward(-40, 30, 10000);
  liftAuton(2, 10, 1);
  visionSensorTest("Purple", 10);
  wait(1, sec);



  //get personal
  //inertialTurn(left, 30, 80, 5); //NOT WORKING FOR NOW. IT CONTNINUES TO SPIN NON STOP
  turnClockwise(-15, 15, 1);
  moveForward(10, 10, 1);

  //OLD BACKLIFT: bLiftAuton2(33, 50, 1); //down
  //NEW BACKLIFT DOWN BELOW
  bLiftPOT("down", 1);
  wait(2, sec);


  visionSensorTest("Blue", 5);
  moveForward(-15, 10, 1);


  //OLD BACKLIFT: bLiftAuton2(-33, 50, 1);  //up //-32.5  -30.2
  //NEW BACKLIFT UP BELOW
  bLiftPOT("up", 2);
  wait(2,sec);  


  moveForward(20, 10, 1);
  inertialTurn(right, 15, 30, 1);
  Belt.spin(fwd, 90, pct);
  moveForward(25, 20, 1);
  do
  {
    wait(500, msec);
    moveForward(-35, 20, 1); 
    wait(500, msec);
    moveForward(35, 20, 1);
  }
  while((internalTimer > 30000) && (internalTimer < 45000));
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
  internalTimer.reset();
  
  if(internalTimer > 500){
    printf("left: %f\n", angleLiftL.angle(deg));
    printf("right: %f\n", angleLiftR.angle(deg));
    internalTimer.reset();
  }
}
void skillsAuton(){
  
  //1push then grab yellow to other side
  latchDown.set(1);   //open
  //moveForward(200, 40, 10);
  DriveToTargetXY(0, -970, 47, 100); //0, 970, 47, 100
  latchDown.set(0);   //close
  moveForward(5, 35, 1);
  liftAuton(2, 10, 1);
  printf("1:DONE\n");

  //2position for grabbing goal off ramp
  DriveToTargetXY(635, -1270, 20, 55);       //635,-1270,47,55
  ImprovedDriveToHeading(240, 10, 6, 20);  //238
  wait(5, msec);
  printf("2:DONE\n");

  //3drive and pick up goal off ramp and move
  bLiftPOT("down", 1);
  //moveForward(-100, 40, 1);   //-125, 25, 1
  visionSensorMORE("Red", true, left, 10, 10, 10, 180);  //150
  moveForward(-5, 15, 1);
  bLiftPOT("up", 2);
  moveForward(75, 25, 1);
  printf("3:DONE\n");
  
  //4 drive to personal square
  ImprovedDriveToHeading(300, 5, 3, 50);  //300, 5, 3, 50
  DriveToTargetXY(-200, -850, 30, 50);
  ImprovedDriveToHeading(88, 4, 3, 50);   //300, 5, 3, 50
  printf("4:DONE\n");
  
  //5go back to start scoring rings
  lift.stop(coast);
  Belt.spin(fwd, 100, pct);
  moveForward(-75, 30, 10);    //initial go back
  wait(5, msec);
  moveForward(50, 15, 1);
  wait(5, msec);
  moveForward(-50, 15, 1);

  printf("5:DONE\n");

  // //6   //field lifted, attempt code at ocmpeittion tmr
  // bLiftAuton(1.23, 1);
  // moveForward(125, 15, 1);
  // bLiftAuton(1.10, 1);
  // printf("yes\n");
  // DriveToTargetXY(-850, -600, 10, 30);
  // printf("no\n");
  // ImprovedDriveToHeading(0, 5, 3, 20);
  // printf("yes\n");
  // moveForward(-150, 20, 3);
  // bLiftAuton(0.5, 1);    
  // moveForward(70, 10, 1);
  // printf("6:DONE\n");

  // //7
  // ImprovedDriveToHeading(270, 5, 3, 20);
  // moveForward(-250, 50, 1);

}


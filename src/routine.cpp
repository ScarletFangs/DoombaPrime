#include "vex.h"
#include "routine.h"
#include "autonomous-functions.h"
#include "robot-config.h"
#include "driving-functions.h"
#include "GPS.h"

using namespace vex;
using namespace std;

void blueGoalSide(){
  liftAuton(0, 10, 10);     //push lift to bottom
  latchDown.set(1);           //open
  bLiftAuton(32.5, 50, 5); 
  wait(2,sec);
  moveForward(-75, 25, 10);
  bLiftAuton(-22, 30, 5); 
  beltControl(50, 89);
  turnClockwise(-42, 7, 10);
  moveForward(-45, 7, 10);
  turnClockwise(42, 7, 10);
  moveForward(-140, 10, 10);

  


  // moveForward(165, 100, 10); 
  // latchDown.set(0);           //close
  // liftAuton(0.5, 10, 10);
  // moveForward(-20, 100, 10); 
  // DriveToTargetXY(900,  900, 30, 120);
  
  //DriveToHeading(180, 25, 3);
  // bLiftAuton(33, 30, 5); 
  // wait(1,sec);
  //moveForward(-20, 35, 10);
  //bLiftAuton(120, 30, 5);    //drop the back lift. preparing to scoop
  //moveForward(150, 20, 10);

  // //grab blue go other side
  // DriveToTargetXY(900, 1330, 25, 85);
  // //DriveToHeading(-10, 27, 3);
  // moveForward(25, 20, 10);
  // wait(1, sec);
  // latchDown.set(0);

  // //back to other side
  // DriveToTargetXY(930, -600, 32, 65);
  // wait(1, sec);
  // DriveToHeading(180, 25, 3); //turn
  // latchDown.set(1);
  // moveForward(-10, 10, 10);

  // //middle
  // DriveToTargetXY(900, 0, 32, 65);
  // wait(1, sec);
  // DriveToHeading(259, 25, 3);
  // DriveToTargetXY(0, 0, 32, 65);
  // latchDown.set(0);
  // DriveToTargetXY(900, 0, 32, 65);
}

void tallGoal(){
  latchDown.set(1);
  moveForward(114, 100, 5);
  latchDown.set(0);
  moveForward(-115, 100, 5);
  liftAuton(1, 10, 10);
  turnClockwise(31, 50, 5);
}

void aimatCornerGPS(){
  liftAuton(0, 10, 10);     //push lift to bottom
  latchDown.set(1);           //open
  moveForward(100, 100, 10); 
  latchDown.set(0);
  liftAuton(0.5, 10, 10);
  moveForward(-20, 55, 10);

  //gps to align to middle of ramp
  DriveToTargetXY(570, 75, 32, 65);
  Drivetrain.stop();
  wait(1, sec);
  DriveToHeading(91, 25, 3);      //93 almos work      

  liftAuton(240, 30, 5);
  wait(1, sec);
  moveForward(55, 25, 10);
  //liftAuton(-3, 10, 10);
  //wait(1,sec);
  latchDown.set(1);

  moveForward(-25, 10, 10);
  wait(1, sec);
  liftAuton(-125, 10, 10);
  DriveToHeading(0, 25, 10);

  //go for blue 
  DriveToTargetXY(900, 1330, 25, 85);
  //DriveToHeading(-10, 27, 3);
  moveForward(25, 20, 10);
  wait(1, sec);
  latchDown.set(0);

  //back to other side
  DriveToTargetXY(930, -600, 32, 65);
  wait(1, sec);
  DriveToHeading(180, 25, 3); //turn
  latchDown.set(1);

  //middle
  DriveToTargetXY(900, 0, 32, 65);
  wait(1, sec);
  DriveToHeading(259, 25, 3);
  moveForward(60, 40, 10);
  latchDown.set(0);
  moveForward(-60, 40, 10);
}




//Grab middle goal
void rampSide(){
  liftAuton(0, 10, 10);     //push lift to bottom
  latchDown.set(1);           //open
  moveForward(155, 55, 10);     
  latchDown.set(0);
  moveForward(-142, 55, 10);
  turnClockwise(-40, 20, 10);
  latchDown.set(1);
  moveForward(-15, 20, 10);
  turnClockwise(40, 20, 10);
}



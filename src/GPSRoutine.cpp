#include "vex.h"
#include "routine.h"
#include "autonomous-functions.h"
#include "robot-config.h"
#include "driving-functions.h"
#include "GPS.h"

using namespace vex;
using namespace std;

void score130points(){
  //2
  DriveToTargetXY(700, -1400, 27, 65);    
  Drivetrain.stop();
  // wait(1, sec);                               

  //3
  DriveToTargetXY(790, -1000, 25, 65);
  Drivetrain.stop();
  //wait(1, sec);

  //4
  DriveToTargetXY(-710, -1000, 32, 65);
  Drivetrain.stop();
  //wait(1, sec);  
  
  //5
  DriveToTargetXY(-650, 0, 25, 65);
  Drivetrain.stop();
  //wait(1, sec);

  //6
  DriveToTargetXY(730, 0, 25, 65);
  Drivetrain.stop();
  //wait(1, sec);

  //7
  DriveToTargetXY(1350, 1650, 30, 65);
  Drivetrain.stop();
  //wait(1, sec);

  //8
  DriveToTargetXY(-700, 1550, 25, 65);
  Drivetrain.stop();
  //wait(1, sec);

  //9
  DriveToTargetXY(-230, 1100, 30, 65);
  Drivetrain.stop();
  //wait(1, sec);

  //10
  DriveToTargetXY(530, 400, 32, 65);
  Drivetrain.stop();
  //wait(1, sec);

  //11
  DriveToTargetXY(500, -1050, 32, 65);
  Drivetrain.stop();
  //wait(1, sec);

  //12
  DriveToTargetXY(1670, -1000, 25, 65);
  Drivetrain.stop();
  //wait(1, sec);

  DriveToHeading(0, 25, 3);
  moveForward(70, 70, 10);

  //Print the ending position of the robot
}
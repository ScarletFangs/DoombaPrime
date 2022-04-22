/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\Sirena K                                         */
/*    Created:      Thu Dec 30 2021                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "robot-config.h"
#include "driving-functions.h"
#include "autonomous-functions.h"
#include "routine.h"
//-----NEW-----
#include "customMenu.h"
// #include "GPS.h"
// #include "GPSRoutine.h"
// #include "visionSensor.h"
//-------------
//#include "autonSkills.h"

using namespace vex;
competition Competition;

// // Without Menu
// void userControl(){
//   while(1){
//     tankDrive();
//     liftControl();
//     liftToggle();
//     bLiftManual();
//     beltControl();
//     changespeed();
//     //potbLift();
//     printf("right: %4.3f   |", angleLiftR.angle(deg));
//     printf("left: %4.3f\n", angleLiftL.angle(deg));
//   }
// }


// void Autonomous(){
//   //goalTest();
//   //printing(2);
//   //donutBlueGoal();
//   //donutRedGoal();
//   //donutRedRamp();
//   //rampFrontBlue();
//   //rampFrontRed();
//   //sensorTest();
//   // //rampSafe();
//   //skillsAuton();
//   //goalFrontBlue();


//   //bLiftPOT("down", 1);
//   // wait(2, sec);
//   // printf("1\n");
//   // moveForward(-25, 15, 1);
//   // printf("2\n");
//   // wait(2, sec);
//   // bLiftPOT("up", 2);
//   // wait(2,sec);
//   // printf("3\n");

//   // //Belt.spin(fwd, 90, pct); //does not allow simultaneous task

//   // beltControl(45,95); //Nate is gonna attempt to use this

//   // while(yes)
//   // {
//   //   printf("im in the whileloop"); //does not print. never entered while loop
//   //   moveForward(-30, 20, 1);
//   //   wait(500, sec);
//   //   moveForward(30, 20, 1); //50, 20, 1
//   // }
// }

//---Menu---
int tempStatus = 0;
void menuSetup(){
  menuCONFIG();
  notificationHUD("Robot: OK");
}
void Autonomous(){
  if(getValues(AUTON_COLOR)== BLUE){
    if(getValues(AUTON_TYPE) == GOALSIDE){
      //regular goalside
      goalFrontBlue();
    }else if(getValues(AUTON_TYPE) == RAMPSIDE){
      //regular rampside
      rampFrontBlue();
    }else if(getValues(AUTON_TYPE) == RING_RAMP){
      //score ring first then yellow goal, rampsie
      donutBlueRamp();
    }else if(getValues(AUTON_TYPE) == RING_GOAL){
      //score rings first then yellow goal, goalside
      donutBlueGoal();
    }else if(getValues(AUTON_TYPE) == SKILLS){
      //skills
      skillsAuton();
    }

    notificationHUD("Auton: Done");
  }
  else if(getValues(AUTON_COLOR) == RED){
    if(getValues(AUTON_TYPE) == GOALSIDE){
      //regular goalside
      goalFrontRed();
    }else if(getValues(AUTON_TYPE) == RAMPSIDE){
      //regular rampside
      rampFrontRed();
    }else if(getValues(AUTON_TYPE) == RING_RAMP){
      //score ring first then yellow goal, rampsie
      donutRedRamp();
    }else if(getValues(AUTON_TYPE) == RING_GOAL){
      //score rings first then yellow goal, goalside
      donutRedGoal();
    }else if(getValues(AUTON_TYPE) == SKILLS){
      //skills
      skillsAuton();
    }
    notificationHUD("Auton: Done");
  }
}
  void userControl(){
    Brain.Screen.clearScreen(green);
    while(1){
      if(getValues(AUTON_DRIVE) == ARCADE){
        arcadeDrive();
        liftToggle();
        liftControl();
        beltControl();
        bLiftManual();
        changespeed();
      }else if(getValues(AUTON_DRIVE) == TANK){
        tankDrive();
        liftControl();
        liftToggle();
        bLiftManual();
        beltControl();
        changespeed();
      }
    }
}

void pre_auton (void){
  menuCONFIG();
  notificationHUD("Robot: OK");
}


int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  pre_auton();

  Competition.drivercontrol(userControl);
  Competition.autonomous(Autonomous);



  while(1){
    if(tempStatus != currStatus()){
      statusHUD();
      tempStatus = currStatus();
    }
  }
  
}

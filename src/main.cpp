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

// Without Menu
void userControl(){
  while(1){
    tankDrive();
    liftControl();
    liftToggle();
    //bLiftManual();
    beltControl();
    changespeed();
    potbLift();
    // printf("right: %4.3f   |", angleLiftR.angle(deg));
    // printf("left: %4.3f\n", angleLiftL.angle(deg));
  }
}


void Autonomous(){
  //goalTest();
  //printing(2);
  //rampFrontBlue();
  //rampFrontRed();
  // sensorTest();
  // //rampSafe();
  bLiftPOT("down", 1);
  wait(2, sec);
  printf("1\n");
  moveForward(-25, 15, 1);
  printf("2\n");
  wait(2, sec);
  bLiftPOT("up", 2);
  wait(2,sec);
  printf("3\n");
  Belt.spin(fwd, 90, pct);
}

// //---Menu---
// int tempStatus = 0;
// void menuSetup(){
//   menuCONFIG();
//   notificationHUD("Robot: OK");
// }
// void Autonomous(){
//   if(getValues(AUTON_COLOR)== BLUE){
//     if(getValues(AUTON_TYPE) == GOALSIDE){
//       goalFrontBlue();
//       printf("goal side auton");
//     }else if(getValues(AUTON_TYPE) == RAMPSIDE){
//       rampFrontBlue();
//       printf("ramp side auton");
//     }else if(getValues(AUTON_TYPE) == SKILLS){
//       //skillsAuton();
//       printf("skills");
//     }
//     notificationHUD("Auton: Done");
//   }
//   else if(getValues(AUTON_COLOR) == RED){
//     if(getValues(AUTON_TYPE) == GOALSIDE){
//       goalFrontRed();
//       printf("REDgoal side auton");
//     }else if(getValues(AUTON_TYPE) == RAMPSIDE){
//       rampFrontRed();
//       printf("ramp side auton");
//     }else if(getValues(AUTON_TYPE) == SKILLS){
//       //skillsAuton();
//       printf("skills");
//     }
//     notificationHUD("Auton: Done");
//   }
// }
//   void userControl(){
//     Brain.Screen.clearScreen(green);
//     while(1){
//       if(getValues(AUTON_DRIVE) == ARCADE){
//         arcadeDrive();
//         liftToggle();
//         liftControl();
//         beltControl();
//         // bLiftControl();
//       }else if(getValues(AUTON_DRIVE) == TANK){
//         tankDrive();
//         liftControl();
//         liftToggle();
//         bLiftManual();
//         beltControl();
//         changespeed();
//       }
//     }
// }

// void pre_auton (void){
//   menuCONFIG();
//   notificationHUD("Robot: OK");
// }


int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  //pre_auton();

  Competition.drivercontrol(userControl);
  Competition.autonomous(Autonomous);



  // while(1){
  //   if(tempStatus != currStatus()){
  //     statusHUD();
  //     tempStatus = currStatus();
  //   }
  // }
  
}

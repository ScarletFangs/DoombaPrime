#include "vex.h"
#include "robot-config.h"
using namespace vex;

// A global instance of brain used for printing to the V5 brain screen
//PORT2 BAD?
brain Brain;

controller controller1(primary);
controller controller2(partner);

//Driving motors
motor left1(PORT12, ratio18_1, false);
motor left2(PORT20, ratio18_1, false); 
motor left3(PORT1, ratio18_1, false); //front motor left

motor right1(PORT10, ratio18_1, true);
motor right2(PORT11, ratio18_1, true); 
motor right3(PORT6, ratio18_1, true); //front motor right

//Motor Groups
motor_group leftWheels(left1, left2, left3);
motor_group rightWheels(right1, right2, right3);
motor_group frontWheels(left2, right2, left3);
motor_group backWheels(left1, right1, right3);

//4 Bar motor
motor liftL1(PORT3, ratio36_1, false);
motor liftL2(PORT5, ratio36_1, false);
motor liftR1(PORT8, ratio36_1, true);
motor liftR2(PORT7, ratio36_1, true);

motor_group lift(liftL1, liftL2, liftR1, liftR2);

//Pneumatic
digital_out latchDown = digital_out(Brain.ThreeWirePort.A);

//GPS
gps DrivetrainGPS = gps(PORT9, -190, -20, mm, -90); //port, x, y, units, angle
smartdrive Drivetrain = smartdrive(leftWheels, rightWheels, DrivetrainGPS, 319.19, 320, 40, mm, 1);
long map(long x, long in_min, long in_max, long out_min, long out_max)
 {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

//Inertial Sensor
inertial inertialLeft = inertial(PORT9);
inertial inertialRight = inertial(PORT19);


//Belt
motor Belt(PORT18, ratio18_1, false);

//Back Lift
motor bLift1(PORT15, ratio36_1, true);
motor bLift2(PORT16, ratio36_1, false);
motor_group bLift(bLift1, bLift2);

//potentiometer
pot angleLiftR = pot(Brain.ThreeWirePort.H);
pot angleLiftL = pot(Brain.ThreeWirePort.G);

void vexcodeInit(void) {
  Brain.setTimer(0, msec);
  Brain.Screen.print("Device initialization...");
  Brain.Screen.setCursor(2, 1);
  // calibrate the drivetrain GPS
  wait(200, msec);
  DrivetrainGPS.calibrate();
  Brain.Screen.print("Calibrating GPS for Drivetrain");
  // wait for the GPS calibration process to finish
  while (DrivetrainGPS.isCalibrating()) {
    wait(25, msec);
  }

  //Set Drivetrain Velocity
  Drivetrain.setHeading(DrivetrainGPS.heading(), degrees);

  // reset the screen now that the calibration is complete
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1,1);
  wait(50, msec);
  Brain.Screen.clearScreen();
}
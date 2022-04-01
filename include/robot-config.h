#ifndef ROBOT_CONFIG
#define ROBOT_CONFIG
using namespace vex;

extern brain Brain;

//Controller
extern controller controller1;
extern controller controller2;  

//Driving motor
extern motor left1;
extern motor left2;
extern motor left3;
extern motor left4;

extern motor right1;
extern motor right2;
extern motor right3;
extern motor right4;

//Driving Motor Groups
extern smartdrive Drivetrain;
extern motor_group leftWheels;
extern motor_group rightWheels;

//4 Bar motor
extern motor liftL1;
extern motor liftL2;
extern motor liftR1;
extern motor liftR2;

//Bar Motor Group
extern motor_group lift;

//Pneumatic 
extern digital_out latchDown;

//GPS
extern gps DrivetrainGPS;

//Inertial sensor
extern inertial inertialLeft;
extern inertial inertialRight;

//Belt
extern motor Belt;

//Back Lift
extern motor bLift1;
extern motor bLift2;
extern motor_group bLift;


void vexcodeInit(void);
long map(long x, long in_min, long in_max, long out_min, long out_max);

#endif
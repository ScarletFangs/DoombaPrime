#ifndef AUTONOMOUS_FUNCTOINS
#define AUTONOMOUS_FUNCTIONS


//Timeout function: time to do command until motor stops
void setMotorTimeout(int timeSeconds);

//Drive distance with specific distance
void moveForward(float distanceCM, int speedPCT, int timeSec);
void moveForwardCoast(float distanceCM, int speedPCT, int timeSec);
//Input sides individually (turning right)
void flexMvmtR(float distanceLeft, float distanceRight, int speedPCTL, int speedPCTR, int timeSec);
//Input sides individually (turning left)
void flexMvmtL(float, float, int, int);

//Turn Clockwise
void turnClockwise(float degree, int speedPCT, int timeSec);

//Move lift
void liftAuton(float, int, int);

//Move back lift
void bLiftAuton(double, int);
void bLiftAuton2(float degree, int speedPCT, int timeSec);
void bLiftPOT(std::string, double);

//Belt
void beltControl(double, double);

void dirtyBeltControl(float, double, int);

//inertial sensors
float inertialAVG();
void inertialTurn(vex::turnType dir, double speed, double degrees, double timeout);

//Vision sensor
void visionSensorTest(std::string goalColor, double);
void visionSensorMORE(std::string goalColor, bool pursuit, vex::turnType dir, double turnSpeed, double pursuitSpeed, double pursuitDistance, int targetWidth);

void printing(int);
#endif
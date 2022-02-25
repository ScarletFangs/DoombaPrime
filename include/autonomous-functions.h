#ifndef AUTONOMOUS_FUNCTIONS
#define AUTONOMOUS_FUNCTIONS

//Timeout function: time to do command until motor stops
void setMotorTimeout(int timeSeconds);

//Drive distance with specific distance
void moveForward(float distanceCM, int speedPCT, int timeSec);

//Input sides individually (turning right)
void flexMvmtR(float distanceLeft, float distanceRight, int speedPCT, int timeSec);
//Input sides individually (turning left)
void flexMvmtL(float, float, int, int);

//Turn Clockwise
void turnClockwise(float degree, int speedPCT, int timeSec);

//Move lift
void liftAuton(float, int, int);


#endif
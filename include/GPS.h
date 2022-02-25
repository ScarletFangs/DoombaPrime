
#ifndef GPS_SENSOR
#define GPS_SENSOR

float FindTurnAngle(float endx, float endy);

float FindDriveDistance(float endx, float endy);

void printPosition(int x, int y);

void DriveToTargetXY(int x, int y, int base_speed, int GPS_DriveDistance_Threshold);

void DriveToHeading(int TargetHeading,int base_speed, int precision);

void GPSDataToSD(int PrintTurnError, int PrintErrorIntegral, int DriveDistance, int PrintDerivativeError);

void ImprovedDriveToHeading(int TargetHeading,int base_speed, int precision, int Iter);

void DriveToTargetXY_2(int x, int y, int base_speed, int GPS_DriveDistance_Threshold);


#endif
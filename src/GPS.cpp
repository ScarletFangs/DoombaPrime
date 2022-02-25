#include "GPS.h"
#include "vex.h"
#include "robot-config.h"
#include <iostream>
#include <fstream>

#define GPS_DISTANCE_THRESHOLD 20
#define GPS_DEGREE_THRESHOLD 2
#define GPS_HEADING_DEBUG false
#define GPS_DEBUG false
#define KP 0.2
std::ofstream myFile;

using namespace vex;

float FindTurnAngle(float endx, float endy){
  // Store the current position of the robot
    float startingX = DrivetrainGPS.xPosition(mm);
    float startingY = DrivetrainGPS.yPosition(mm);

    // Store the target ending position of the robot
    float endingX = endx;
    float endingY = endy;

    // Implement atan2 to calculate the heading that the robot needs to
    // turn to in order to drive towards the ending position
    float turnAngle = atan((endingX - startingX) / (endingY - startingY)) * 180 / M_PI;
    if (endingY - startingY < 0) 
      turnAngle = turnAngle + 180;

    return turnAngle;
}

float FindDriveDistance(float endx, float endy){
  // Store the current position of the robot
  float startingX = DrivetrainGPS.xPosition(mm);
  float startingY = DrivetrainGPS.yPosition(mm);

  // Store the target ending position of the robot
  float endingX = endx;
  float endingY = endy;

  // Calculate the drive distance needed, then drive towards the target position
  return sqrt(((endingX - startingX) * (endingX - startingX)) + ((endingY - startingY) * (endingY - startingY)));
}

void printPosition(int x, int y) {
  // Print GPS position values to the V5 Brain
  Brain.Screen.print("X: %.2f", DrivetrainGPS.xPosition(mm));
  Brain.Screen.print("  Y: %.2f", DrivetrainGPS.yPosition(mm));
  Brain.Screen.print("  Distance: %.2f",FindDriveDistance(x,y));
  Brain.Screen.newLine();

  // Print GPS position values to theTerminal
  printf("X: %.2f", DrivetrainGPS.xPosition(mm));
  printf("  Y: %.2f", DrivetrainGPS.yPosition(mm));
  printf("  Distance: %.2f\n",FindDriveDistance(x,y));

}

void DriveToTargetXY(int x, int y, int base_speed, int GPS_DriveDistance_Threshold){
  //Initialize variables
  int TurnAngle = FindTurnAngle(x,y);
  int CurrentHeading = DrivetrainGPS.heading();
  int TurnError = (CurrentHeading - TurnAngle);
  int DriveVelocity = 0;
  int ErrorIntegral = 0;
  float ErrorDerivative = 0;
  int PreviousError = 0;
  int DistanceTOSpeed = 0;
  int InitialDriveDistance = FindDriveDistance(x,y);
  int CurrentDriveDistance = InitialDriveDistance;
  float dT = 100/1000; // [msec] Sampling time. Assume constant time equal to the delay in the while loop

  DriveToHeading(TurnAngle, 0, 10);

  while( (CurrentDriveDistance > GPS_DriveDistance_Threshold) ){

  // Turn the robot to face the ending position
  TurnAngle = FindTurnAngle(x,y);
  CurrentHeading = DrivetrainGPS.heading();
  CurrentDriveDistance = FindDriveDistance(x, y);
  TurnError = (CurrentHeading - TurnAngle);

  //change Turn direction if turn error is beyond 180*
  if(abs( TurnError ) > 180){
    TurnError = -(360-abs(TurnError));
  } 

  //Find the integral of the error
  ErrorIntegral += TurnError;
  
  //Find the derivative of the error
  ErrorDerivative = float(TurnError - PreviousError) / dT;

  //Apply Proportional Control to TurnError
  DriveVelocity = int((0.4*TurnError) + int(0*ErrorIntegral) + int(0*ErrorDerivative)); //* CurrentDriveDistance * .0015);

  //Calculate distance to speed with Map function
  DistanceTOSpeed = map(CurrentDriveDistance, 0, InitialDriveDistance, 0, base_speed);
  
  //Apply power to the motors
  rightWheels.spin(fwd, base_speed + DriveVelocity ,pct);
  leftWheels.spin(fwd, base_speed - DriveVelocity ,pct);
  
  
  //Remember the turnerror and set it as the value for Previous Error 
  PreviousError = TurnError;

  //Print out function values to debug the system
  if(GPS_DEBUG){
    printf("\n Current Heading: %i | Drive Distane: %i | Turn Error: %i | Drive Velocity: %i | integral Distance Error: %i", CurrentHeading,CurrentDriveDistance,TurnError, DriveVelocity, ErrorIntegral);
    GPSDataToSD(TurnError, ErrorIntegral, FindDriveDistance(x, y), ErrorDerivative);
  }

  //Must have a delay so that the integral term does not add up too fast. 
  wait(50, msec);
  }
  
  //Close File used in debugging
  myFile.close();
  //stop the drivetrain motors
  Drivetrain.stop();
}

void DriveToHeading(int TargetHeading,int base_speed, int precision){
  int CurrentHeading =  DrivetrainGPS.heading();
  int HeadingError = TargetHeading - CurrentHeading;
  int DriveVelocity = 0;
  int IntegralError = 0;
  int DerivativeError = 0;
  int PreviousHeadingError = 0;


  while( abs(HeadingError) > precision ){

    // Get measurements from GPS Sensor
    CurrentHeading = DrivetrainGPS.heading();
    HeadingError = TargetHeading - CurrentHeading;

    

    //Change Turn Direction if graeter than 180*
    if ( abs(HeadingError) > 180){
      HeadingError = (360 - abs(HeadingError));
    }

    //Integral Term
    IntegralError += HeadingError;
    //Find Derivative of error
    DerivativeError = HeadingError - PreviousHeadingError;

    //Add Proportional Control
    DriveVelocity = int((KP * HeadingError) + int(0.002*IntegralError) - int(0.2* DerivativeError));
    //  printf("\n Proportional Error: %f | Integral Error: %f | Derivative Error: %f | Drive Velocity: %i ", (KP * HeadingError),(0.004*IntegralError),(0.2* DerivativeError), DriveVelocity);

    //Apply Power to the wheels
    rightWheels.spin(fwd, -base_speed - DriveVelocity, pct);
    leftWheels.spin(fwd, base_speed + DriveVelocity, pct);

    

    PreviousHeadingError = HeadingError;

    //For Debugging
    if (GPS_HEADING_DEBUG){
      // printf("\n Current Heading: %i | Target Heading: %i | Heading Error: %i | Drive Velocity: %i ", CurrentHeading,TargetHeading,HeadingError, DriveVelocity);
      // GPSDataToSD(HeadingError, 0, 0, 0);
    }

    //Delay
    wait(20, msec);

  }

  //Stop the drivetrain motors from moving
  Drivetrain.stop();

}

void ImprovedDriveToHeading(int TargetHeading,int base_speed, int precision, int Iter){

  // Get measurements from GPS Sensor
  int CurrentHeading = DrivetrainGPS.heading();
  int HeadingError = TargetHeading - CurrentHeading;
  int Iterations = 0;
  
  // Orient the drivetrain's heading with the GPS heading
  Drivetrain.stop(hold);
  while( abs(HeadingError) > 3 && Iterations < Iter){
  DriveToHeading(TargetHeading, base_speed, precision);
  Drivetrain.stop();
  wait(100, msec);
  CurrentHeading = DrivetrainGPS.heading();
  HeadingError = TargetHeading - CurrentHeading;
  Iterations += 1;
  printf("\nIteration: %i | Target Heading: %i | Heading Error: %i ", Iterations, TargetHeading, HeadingError);

  }

}

void GPSDataToSD(int PrintTurnError, int PrintErrorIntegral, int DriveDistance, int PrintDerivativeError){
  
  if (Brain.SDcard.isInserted()){
    //open the file. otherwise create the text file. 
    myFile.open("GPS-Data.txt", std::ostream::app);

    if(myFile.is_open()){
      
      //ouput the variables in CSV format and graph the response
      myFile << Brain.timer(msec) << "," << PrintTurnError << "," << PrintErrorIntegral << "," << DriveDistance << "," << PrintDerivativeError << "\r\n";
      myFile.close();

    } else {
      Brain.Screen.clearScreen();
      Brain.Screen.setCursor(5, 0);
      Brain.Screen.print("File Could Not Open");
    }


  } else {
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(5, 0);
    Brain.Screen.print("SD card Could Not Open");
  }

}

void DriveToTargetXY_2(int x, int y, int base_speed, int GPS_DriveDistance_Threshold){
 //Initialize variables
  int TurnAngle = FindTurnAngle(x,y);
  int CurrentHeading = DrivetrainGPS.heading();
  int TurnError = (CurrentHeading - TurnAngle);
  int DriveVelocity = 0;
  int ErrorIntegral = 0;
  float ErrorDerivative = 0;
  int PreviousError = 0;
  int DistanceTOSpeed = 0;
  int InitialDriveDistance = FindDriveDistance(x,y);
  int CurrentDriveDistance = InitialDriveDistance;
  float dT = 100/1000; // [msec] Sampling time. Assume constant time equal to the delay in the while loop

  DriveToHeading(TurnAngle, 0, 10);

  while( (CurrentDriveDistance > GPS_DriveDistance_Threshold) ){

  // Turn the robot to face the ending position
  TurnAngle = FindTurnAngle(x,y);
  CurrentHeading = DrivetrainGPS.heading();
  CurrentDriveDistance = FindDriveDistance(x, y);
  TurnError = (CurrentHeading - TurnAngle);

  //change Turn direction if turn error is beyond 180*
  if(abs( TurnError ) > 180){
    TurnError = -(360-abs(TurnError));
  } 

  //Find the integral of the error
  ErrorIntegral += TurnError;
  
  //Find the derivative of the error
  ErrorDerivative = float(TurnError - PreviousError) / dT;

  //Apply Proportional Control to TurnError
  DriveVelocity = int((0.4*TurnError) + int(0.0000*ErrorIntegral) + int(0*ErrorDerivative)); //* CurrentDriveDistance * .0015);

  //Calculate distance to speed with Map function
  DistanceTOSpeed = map(CurrentDriveDistance, 0, InitialDriveDistance, 0, base_speed);
  
  //Apply power to the motors
  rightWheels.spin(fwd, DistanceTOSpeed + DriveVelocity ,pct);
  leftWheels.spin(fwd, DistanceTOSpeed - DriveVelocity ,pct);
  
  
  //Remember the turnerror and set it as the value for Previous Error 
  PreviousError = TurnError;

  //Print out function values to debug the system
  if(GPS_DEBUG){
    printf("\n Current Heading: %i | Drive Distane: %i | Turn Error: %i | Drive Velocity: %i | integral Distance Error: %i", CurrentHeading,CurrentDriveDistance,TurnError, DriveVelocity, ErrorIntegral);
    GPSDataToSD(TurnError, ErrorIntegral, FindDriveDistance(x, y), ErrorDerivative);
  }

  //Must have a delay so that the integral term does not add up too fast. 
  wait(50, msec);
  }
  
  //Close File used in debugging
  myFile.close();
  //stop the drivetrain motors
  Drivetrain.stop();
}
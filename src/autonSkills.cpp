#include "vex.h"
#include "autonSkills.h"
#include "autonomous-functions.h"
#include "robot-config.h"
#include "driving-functions.h"

using namespace vex;
using namespace std;

void autonProgram(){
  liftAuton(0, 10, 10);     //push lift to bottom
  latchDown.set(1);           //open
  moveForward(210, 55, 10);     
  latchDown.set(0);
  turnClockwise(-30, 20, 10);
  moveForward(80, 55, 10);

  //dropping yellow goal
  liftAuton(120, 50, 5); 
  turnClockwise(12, 15, 10);     //turns left
  moveForward(20, 20, 10);
  latchDown.set(1);
  moveForward(-40, 30, 10);

  //grabbing personal
  turnClockwise(-14, 20, 10);     
  moveForward(36, 25, 10);
  latchDown.set(0);
  moveForward(-75, 30, 10);

  //position for ramp, moving and lifting lift
  turnClockwise(-46, 20, 5);     
  liftAuton(120, 50, 5);       
  moveForward(50, 20, 5);

  //PLAN B FORCE IN
  turnClockwise(-17.5, 15, 5);   //-18,15,10
  moveForward(15, 10, 5);
  latchDown.set(1);
}
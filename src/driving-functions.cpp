#include "vex.h"
#include "driving-functions.h"

//Drive
void tankDrive(){
  if(abs(controller1.Axis3.value())>5||abs(controller1.Axis2.value())){
    leftWheels.spin(fwd, controller1.Axis3.value(), pct);
    rightWheels.spin(fwd, controller1.Axis2.value(),pct);
  }else{
    leftWheels.stop(coast);
    rightWheels.stop(coast);
  }
}

void arcadeDrive(){
  if(abs(controller1.Axis3.value())>5||abs(controller1.Axis1.value())){
    leftWheels.spin(fwd,controller1.Axis3.value()*0.38+controller1.Axis1.value()*0.2,pct);
    rightWheels.spin(fwd, controller1.Axis3.value()*0.36-controller1.Axis1.value()*0.2,pct);
  }else{
    leftWheels.stop(coast);
    rightWheels.stop(coast);
  }
}

bool brakes = false;
bool brakeStopper = false;
vex::brakeType changeBrake(){
  if(controller1.ButtonUp.pressing()){
    if(!brakeStopper){
      brakes = !brakes;
      brakeStopper = true;
    }
  }else{
    brakeStopper = false;
  }

  if(brakes){
    return hold;
  }else{
    return coast;
  }
  wait(20, msec);
}


//4 Bar
void liftControl(){
  if(controller1.ButtonR1.pressing()){
    lift.spin(fwd, 55.0, pct);
  }else if(controller1.ButtonR2.pressing()){
    lift.spin(reverse, 30.0, pct);
  }else{
    lift.stop(hold);
  }
}

//Latch
bool toggle = false;
bool stopper = false;
void liftToggle(){
  if(toggle){
    latchDown.set(1);
  }else{
    latchDown.set(0);
  }

  if(controller1.ButtonA.pressing()){
    if(!stopper){
      toggle = !toggle;
      stopper = true;
    }
  }else{
    stopper = false;
  }
  wait(20,msec);
} 

//Belt
bool belttoggle = false;
bool beltstopper = false;
void beltControl(){
  if(controller1.ButtonL1.pressing()){
    if(!beltstopper){
      belttoggle = !belttoggle;
      beltstopper = true;
    }
  }else{
    beltstopper = false;
  }

  if(belttoggle){
    Belt.spin(fwd, 89, pct);
  }else{
    Belt.stop(coast);
  }
  if(controller1.ButtonL2.pressing()){
    Belt.spin(reverse, 89, pct);
  }
}

//Back lift
bool lifttoggle = false;
bool liftstopper = false;
bool initialdown = false;
float bliftdegree = 0.5;
//code to drop down a little if gets blocked like auton
bool justdownonce = false;
void bLiftControl(){
  if(controller1.ButtonX.pressing()){
    printf("FIRST\n");
    initialdown =  true;
  }
  if(initialdown){
  if(lifttoggle){
    printf("SECOND\n");
    bLift.spinToPosition(bliftdegree, rev);  //0.22, rev
    printf("motor1 torque: %f\n", bLift1.torque());  
    printf("motor2 torque: %f\n", bLift2.torque());     
    bLift.stop(hold);
    
  }else{
    printf("THIRD\n");
    bLift.spinToPosition(1.25, rev);  //0.91,rev   
    bLift.stop(hold);
  }
  if(controller1.ButtonB.pressing()){
    bliftdegree = bliftdegree + 0.1;
  }

  printf("motor1 torque: %f\n", bLift1.torque());  
  printf("motor2 torque: %f\n", bLift2.torque());  


  if(controller1.ButtonX.pressing()){
    if(!stopper){
      lifttoggle = !lifttoggle;
      liftstopper = true;
    }
  }else{
    liftstopper = false;
  }
  wait(20,msec);
  }
} 
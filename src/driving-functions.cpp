#include "vex.h"
#include "driving-functions.h"

//Drive
void tankDrive(){
  if(abs(controller1.Axis3.value())>5||abs(controller1.Axis2.value())){
    leftWheels.spin(fwd, controller1.Axis3.value()*1.4, pct);
    rightWheels.spin(fwd, controller1.Axis2.value()*1.4,pct);
  }else{
    leftWheels.stop(hold);
    rightWheels.stop(hold);
  }
}

void arcadeDrive(){
  if(abs(controller1.Axis3.value())>5||abs(controller1.Axis1.value())){
    leftWheels.spin(fwd,controller1.Axis3.value()*0.4+controller1.Axis1.value()*0.55,pct);
    rightWheels.spin(fwd, controller1.Axis3.value()*0.4-controller1.Axis1.value()*0.55,pct);
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
bool justonce = false;
void bLiftControl(){
  if(controller1.ButtonX.pressing()){
    justonce = true;
  }
  if(justonce){
  if(lifttoggle){
    bLift.spinToPosition(0.36, rev);
    bLift.stop(hold);
  }else{
    bLift.spinToPosition(1.09, rev);    //1.10
    bLift.stop(hold);
  }

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
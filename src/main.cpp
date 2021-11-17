/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;
brain Brain;
controller Control=controller(primary);

motor MotorL1=motor(PORT1,ratio18_1,false);
motor MotorL2=motor(PORT2,ratio18_1,true);
motor MotorL3=motor(PORT3,ratio18_1,false);
motor_group MotoresL=motor_group(MotorL1,MotorL2,MotorL3);

motor MotorR1=motor(PORT4,ratio18_1,true);
motor MotorR2=motor(PORT5,ratio18_1,false);
motor MotorR3=motor(PORT6,ratio18_1,true);
motor_group MotoresR=motor_group(MotorR1,MotorR2,MotorR3);

inertial SensorInethial=inertial(PORT12);

smartdrive Drivetrain=smartdrive(MotoresL,MotoresR,SensorInethial, 319.19 , 368.3 , 406.4 , mm , 1 );

motor CenterWhell1=motor(PORT7,ratio18_1,true);
motor CenterWhell2=motor(PORT8,ratio18_1,false);
motor_group CenterWhells=motor_group(CenterWhell1,CenterWhell2);

motor Brazo=motor(PORT11,ratio36_1,false);
motor Garra=motor(PORT9,ratio18_1,true);

motor BrazoL=motor(PORT11,ratio36_1,true);
motor BrazoR=motor(PORT20,ratio36_1,false);

pneumatics ValveL1=pneumatics(Brain.ThreeWirePort.A);
pneumatics ValveL2=pneumatics(Brain.ThreeWirePort.B);
pneumatics ValveR1=pneumatics(Brain.ThreeWirePort.C);
pneumatics ValveR2=pneumatics(Brain.ThreeWirePort.D);

void BaseSetUp(int v, int t){
  MotoresL.setVelocity(v, percent);
  MotoresL.setMaxTorque(t,percent);
  MotoresL.setStopping(hold);

  MotoresR.setVelocity(v, percent);
  MotoresR.setMaxTorque(t,percent);
  MotoresR.setStopping(hold);
}

void DriveSetUp(int v, int r){
  Drivetrain.setTurnVelocity(r, percent);
  Drivetrain.setDriveVelocity(v, percent);
  Drivetrain.setStopping(hold);
}

void CenterWhellsSetUp(int v, int t){
  CenterWhells.setVelocity(v, percent);
  CenterWhells.setMaxTorque(t, percent);
}

void BrazosSetUp(int v, int t){
  BrazoL.setVelocity(v, percent);
  BrazoL.setMaxTorque(t,percent);
  BrazoL.setStopping(hold);

  BrazoR.setVelocity(v, percent);
  BrazoR.setMaxTorque(t,percent);
  BrazoR.setStopping(hold);
}

void ManoSetup(int v, int t){
  Brazo.setVelocity(v, percent);
  Brazo.setMaxTorque(t,percent);
  Brazo.setStopping(hold);

  Garra.setVelocity(v, percent);
  Garra.setMaxTorque(t,percent);
  Garra.setStopping(hold);
}


// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void gradostest(){
  Drivetrain.driveFor(forward,1,inches);
  Control.Screen.print(MotoresR.rotation(deg));
}

void Multitasktest(int BD){
  int Romprecilcos=0;
  while(1){
    if(MotoresL.rotation(degrees)<BD&&MotoresR.rotation(degrees)<BD){
      Drivetrain.drive(forward);
    }else{
      Drivetrain.stop();
      Romprecilcos=Romprecilcos+1;
    }
  }
}

void autonomous(void) {
  // ..........................................................................
  gradostest();
  // ..........................................................................
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void MovL(){
  MotoresL.spin(forward,Control.Axis3.value(),percent);
}

void MovR(){
  MotoresR.spin(forward,Control.Axis2.value(),percent);
}

void CenterwhellsMov(){
  if(Control.ButtonLeft.pressing()){
    CenterWhells.spin(forward);
  }else if(Control.ButtonRight.pressing()){
    CenterWhells.spin(reverse);
  }else {
    CenterWhells.stop(coast);
  }
}

void BrazoLMov(){
  if(Control.ButtonL1.pressing()){
    BrazoL.spin(forward);
  }else if(Control.ButtonL2.pressing()){
    BrazoL.spin(reverse);
  }else{
    BrazoL.stop();
  }
}

void BrazoRMov(){
  if(Control.ButtonR1.pressing()){
    BrazoR.spin(forward);
  }else if(Control.ButtonR2.pressing()){
    BrazoR.spin(reverse);
  }else{
    BrazoR.stop();
  }
}

void ManoMov(){
  if(Control.ButtonX.pressing()){
    Brazo.spin(forward);
  }else if(Control.ButtonB.pressing()){
    Brazo.spin(reverse);
  }else{
    Brazo.stop();
  }
}

void GarraMov(){
  if(Control.ButtonY.pressing()){
    Garra.spin(forward);
  }else if(Control.ButtonA.pressing()){
    Garra.spin(reverse);
  }else{
    Garra.stop();
  }
}

void GanchosCerrojo(){
  bool Piston1=false,Piston2=false;
  if(Control.ButtonUp.pressing()&&Piston1==false){
    ValveL1.set(true);
    ValveL2.set(false);
    Piston1=true;
    Control.Screen.print("PistonL On");
    Control.Screen.newLine();
    Control.rumble(".");
    //task::sleep(1000);
    wait(800, msec);
  }if(Control.ButtonUp.pressing()&&Piston1==true){
      ValveL1.set(false);
      ValveL2.set(true);
      Piston1=false;
      Control.Screen.print("PistonL OFF");
      Control.Screen.newLine();
      Control.rumble(".");
      //task::sleep(1000);
      wait(800, msec);
  }

  if(Control.ButtonDown.pressing()&&Piston2==false){
    ValveR1.set(true);
    ValveR2.set(false);
    Piston2=true;
    Control.Screen.print("PistonR OFF");
    Control.Screen.newLine();
    Control.rumble(".");
    //task::sleep(1000);
    wait(800, msec);
  }if(Control.ButtonDown.pressing()&&Piston2==true) {
    ValveR1.set(false);
    ValveR2.set(true);
    Piston2=false;
    Control.Screen.print("PistonR OFF");
    Control.Screen.newLine();
    Control.rumble(".");
    //task::sleep(1000);
    wait(800, msec);
  }
}

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.
    BaseSetUp(100, 100);
    CenterWhellsSetUp(100, 100);
    BrazosSetUp(100, 100);
    ManoSetup(100, 100);
    
    MovL();
    MovR();
    CenterwhellsMov();

    BrazoLMov();
    BrazoRMov();
    GanchosCerrojo();

    ManoMov();
    GarraMov();
    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}

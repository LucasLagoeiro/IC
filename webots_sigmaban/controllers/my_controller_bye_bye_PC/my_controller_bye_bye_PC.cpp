// File:          my_controller_bye_bye.cpp
// Date:
// Description:
// Author:
// Modifications:

// You may need to add webots include files such as
// <webots/DistanceSensor.hpp>, <webots/Motor.hpp>, etc.
// and/or to add some other includes
#include <webots/Robot.hpp>
#include <webots/Motor.hpp>
#include <webots/PositionSensor.hpp>

#define TIME_STEP 64

// All the webots classes are defined in the "webots" namespace
using namespace webots;

// This is the main program of your controller.
// It creates an instance of your Robot instance, launches its
// function(s) and destroys it at the end of the execution.
// Note that only one instance of Robot should be created in
// a controller program.
// The arguments of the main function can be specified by the
// "controllerArgs" field of the Robot node
int main(int argc, char **argv) {
  // create the Robot instance.
  Robot *robot = new Robot();


  // You should insert a getDevice-like function in order to get the
  // instance of a device of the robot. Something like:
  Motor *motorRightShoulderPitch = robot->getMotor("right_shoulder_pitch");
  Motor *motorRightShoulderRoll = robot->getMotor("right_shoulder_roll");
  Motor *motorRightElbow= robot->getMotor("right_elbow");
  
  Motor *motorLeftShoulderPitch = robot->getMotor("left_shoulder_pitch");
  Motor *motorLeftElbow= robot->getMotor("left_elbow");
  
  Motor *motorRightHipPitch= robot->getMotor("right_hip_pitch");
  Motor *motorLeftHipPitch= robot->getMotor("left_hip_pitch");
  Motor *motorRightKnee= robot->getMotor("right_knee");
  Motor *motorLeftKnee= robot->getMotor("left_knee");
  
  motorRightHipPitch->setVelocity(0.3);
  motorLeftHipPitch->setVelocity(0.3);
  motorRightKnee->setVelocity(0.1);
  motorLeftKnee->setVelocity(0.1);
  
  PositionSensor *ps_elbowR = robot->getPositionSensor("right_elbow_sensor");
  ps_elbowR->enable(TIME_STEP);

  // Main loop:
  // - perform simulation steps until Webots is stopping the controller
  while (robot->step(TIME_STEP) != -1) {
    // Read the sensors:
    // Enter here functions to read sensor data, like:
    

    // Process sensor data here.

    // Enter here functions to send actuator commands, like:
    motorRightShoulderPitch->setPosition(-1.35);
    motorRightShoulderRoll->setPosition(-1.55);
    
    motorLeftElbow->setPosition(-1.5);
    motorLeftShoulderPitch->setPosition(0.3);
    
    motorRightHipPitch->setPosition(0.3);
    motorLeftHipPitch->setPosition(-0.3);        
    motorRightKnee->setPosition(0.5);
    motorLeftKnee->setPosition(0.5);
    
    //motorRightElbow->setPosition(-1);
  
    int val = ps_elbowR->getValue();
    if (val == 0){
       motorRightElbow->setPosition(-2);}
    else if (val == -2){
       motorRightElbow->setPosition(-1);}
       
     std::cout << val << "\n";
       //motorRightElbow->setPosition(-2);
  };

  // Enter here exit cleanup code.

  delete robot;
  return 0;
}

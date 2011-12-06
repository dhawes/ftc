#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S1,     ,                    sensorI2CMuxController)
#pragma config(Motor,  motorA,          motorA,        tmotorNormal, openLoop)
#pragma config(Motor,  motorB,          motorB,        tmotorNormal, openLoop)
#pragma config(Motor,  motorC,          motorC,        tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C1_1,     right,         tmotorNormal, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motorE,        tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     left,          tmotorNormal, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     intake,        tmotorNormal, openLoop)
#pragma config(Servo,  srvo_S1_C3_1,    grab,     tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    servo2,     tServoStandard)
#pragma config(Servo,  srvo_S1_C3_4,    hopper,     tServoStandard)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/* $Id: L-Cliff.c 59 2011-02-06 03:01:05Z 4105 $ */

//#define MOVE

#include "Autonomous.c"
#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.

/**
 * Starting on the left, drive over the cliff.
 */
task main()
{
  initializeRobot();

  // Wait for the beginning of autonomous phase.
  //waitForStart();

  // go forward
  motor[right] = 100;
  motor[left]  = 100;
  wait1Msec(3000);
  motor[right] = 0;
  motor[left]  = 0;

  wait1Msec(200);

  // turn right
  motor[right] = 100;
  motor[left]  = -100;
  wait1Msec(2000);
  motor[right] = 0;
  motor[left]  = 0;

  wait1Msec(200);

  motor[intake] = -100;

  // go to corner
  motor[right] = 100;
  motor[left]  = 100;
  wait1Msec(6000);
  motor[right] = 0;
  motor[left]  = 0;
}
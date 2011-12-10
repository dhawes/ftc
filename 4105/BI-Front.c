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
#pragma config(Servo,  srvo_S1_C3_4,    hopper,     tServoStandard)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/* $Id: L-Cliff.c 59 2011-02-06 03:01:05Z 4105 $ */

#define MOVE_TIMED
#define TURN_RIGHT_TIMED

#include "Autonomous.c"
#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.

/**
 * Starting on blue on the inside, drive to the front parking area.
 */
task main()
{
  initializeRobot();

  // Wait for the beginning of autonomous phase.
  waitForStart();

  // go forward
  moveTimed(MOTOR_FULL, MOVE_OFF_RAMP_TIME);
  wait1Msec(200);

  // turn right
  turnRightTimed(MOTOR_FULL, RIGHT_TURN_TIME);
  wait1Msec(200);

  // move forward
  moveTimed(MOTOR_FULL, MOVE_TO_BBALL_TIME);
  wait1Msec(200);

  // slight right
  turnRightTimed(MOTOR_FULL, SLIGHT_RIGHT_TIME);
  wait1Msec(200);

  motor[intake] = -MOTOR_FULL;

  // go to the front parking zone
  moveTimed(MOTOR_FULL, MOVE_TO_CORNER_TIME);
}

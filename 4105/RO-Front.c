#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S1,     ,                    sensorI2CMuxController)
#pragma config(Motor,  motorA,          green,        tmotorNormal, openLoop)
#pragma config(Motor,  motorB,          yellow,        tmotorNormal, openLoop)
#pragma config(Motor,  motorC,          red,        tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C1_1,     right,         tmotorNormal, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     whacker,        tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     left,          tmotorNormal, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     intake,        tmotorNormal, openLoop)
#pragma config(Servo,  srvo_S1_C3_1,    grab,     tServoStandard)
#pragma config(Servo,  srvo_S1_C3_3,    hopper1,     tServoStandard)
#pragma config(Servo,  srvo_S1_C3_4,    hopper2,     tServoStandard)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/* $Id$ */

#define MOVE_TIMED
#define TURN_LEFT_TIMED

#include "Autonomous.c"
#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.

/**
 * Starting on red on the outside, drive to the front parking area.
 */
task main()
{
  initializeRobot();

  // Wait for the beginning of autonomous phase.
  waitForStart();

  StartTask(prettyLights);

  // go forward
  moveTimed(MOTOR_FULL, MOVE_OFF_RAMP_TIME);
  wait1Msec(200);

  // turn left
  turnLeftTimed(MOTOR_FULL, LEFT_TURN_TIME);
  wait1Msec(200);

  // move forward
  moveTimed(MOTOR_FULL, MOVE_TO_BBALL_TIME * 2);
  wait1Msec(200);

  // slight left
  turnLeftTimed(MOTOR_FULL, SLIGHT_LEFT_TIME);
  wait1Msec(200);

  motor[intake] = -MOTOR_FULL;

  // go to the front parking zone
  moveTimed(MOTOR_FULL, MOVE_TO_CORNER_TIME);
}

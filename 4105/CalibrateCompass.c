#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S2,     HTAC,                sensorLowSpeed)
#pragma config(Sensor, S3,     HTMC,                sensorLowSpeed)
#pragma config(Motor,  motorA,          motorA,        tmotorNormal, openLoop)
#pragma config(Motor,  motorB,          motorB,        tmotorNormal, openLoop)
#pragma config(Motor,  motorC,          motorC,        tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C1_1,     motorD,        tmotorNormal, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motorE,        tmotorNormal, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     goalGrab,        tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     wheelieBar,    tmotorNormal, openLoop)
#pragma config(Servo,  srvo_S1_C3_3,    goalArm,              tServoStandard)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/* $Id$ */

#define COMPASS
#define RIGHT_COMPASS_TURN
#define LEFT_COMPASS_TURN

#include "Autonomous.c"
#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.

/**
 * Calibrate the compass.
 */
task main()
{
  initializeRobot();

  HTMCstartCal(HTMC);

  // move a little more than 360 degrees in more than 20 seconds
  motor[motorD] = 10;
  motor[motorE] = 10;
  wait1Msec(22000);
  motor[motorD] = 0;
  motor[motorE] = 0;

  HTMCstopCal(HTMC);

  HTMCsetTarget(HTMC);

  leftCompassTurn(-90, 25, 500);
  wait1Msec(200);
  rightCompassTurn(0, 25, 500);
  wait1Msec(200);
  leftCompassTurn(-45, 25, 500);
  wait1Msec(200);
  rightCompassTurn(0, 25, 500);
  wait1Msec(200);
}

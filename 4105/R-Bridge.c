#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S2,     HTAC,                sensorLowSpeed)
#pragma config(Motor,  motorA,          motorA,        tmotorNormal, openLoop)
#pragma config(Motor,  motorB,          motorB,        tmotorNormal, openLoop)
#pragma config(Motor,  motorC,          motorC,        tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C1_1,     motorD,        tmotorNormal, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motorE,        tmotorNormal, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     intake,        tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     wheelieBar,    tmotorNormal, openLoop)
#pragma config(Servo,  srvo_S1_C3_1,    goalCapture1,         tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    goalCapture2,         tServoStandard)
#pragma config(Servo,  srvo_S1_C3_3,    goalArm,              tServoStandard)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/* $Id$ */

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.
#include "Autonomous.c"

/**
 * Starting on the right side, traverse the bridge.
 */
task main()
{
  initializeRobot();

  // Wait for the beginning of autonomous phase.
  waitForStart();

  leftHalfTurn();
  wait1Msec(200);

  move(R_BRIDGE_APPROACH, 30);
  wait1Msec(200);

  leftHalfTurn();
  wait1Msec(200);

  leftTurn();
  wait1Msec(200);

  motor[motorD] = -30;
  wait1Msec(R_BRIDGE_ADJUST_TIME);
  motor[motorD] = 0;
  nMotorEncoder[motorE] = 0;
  nMotorEncoder[motorD] = 0;

  move(R_BRIDGE_ADJUST, -30);
  wait1Msec(200);

  /* wheelie bar */
  wheelieBarDown();
  wait1Msec(300);

  move(BR_GET_ON, -30);
  wait1Msec(200);

  wheelieBarUp();
  wait1Msec(200);

  move(BR_GO_OVER, -30);
  wait1Msec(200);

  wait1Msec(30000);
}

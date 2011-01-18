#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S2,     HTAC,                sensorLowSpeed)
#pragma config(Motor,  motorA,          motorA,        tmotorNormal, openLoop)
#pragma config(Motor,  motorB,          motorB,        tmotorNormal, openLoop)
#pragma config(Motor,  motorC,          motorC,        tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C1_1,     motorD,        tmotorNormal, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motorE,        tmotorNormal, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     intake,        tmotorNormal, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     wheelieBar,    tmotorNormal, openLoop)
#pragma config(Servo,  srvo_S1_C3_1,    goalCapture1,          tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    goalCapture2,          tServoStandard)
#pragma config(Servo,  srvo_S1_C3_3,    goalArm,              tServoStandard)

/* $Id$ */

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.
#include "Autonomous.c"

/**
 *
 */
task main()
{
  initializeRobot();

  waitForStart(); // Wait for the beginning of autonomous phase.

  nMotorEncoder[motorE] = 0;  //clear the TETRIX encoders in motors D and E
  nMotorEncoder[motorD] = 0;

  leftQuarterTurn();
  wait1Msec(200);

  move(1900, 30);
  wait1Msec(200);

  leftQuarterTurn();
  wait1Msec(200);

  leftTurn();
  wait1Msec(200);

  motor[motorD] = -30;
  wait1Msec(400);
  motor[motorD] = 0;
  nMotorEncoder[motorE] = 0;
  nMotorEncoder[motorD] = 0;

  move(300, -30);
  wait1Msec(200);

  /* wheelie bar */
  wheelieBarDown();
  wait1Msec(300);

  move(600, -30);
  wait1Msec(60);

  wheelieBarUp();
  wait1Msec(200);

  move(4800, -30);
  wait1Msec(200);

  wheelieBarUp();
  wait1Msec(600);
}

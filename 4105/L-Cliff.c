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

#include "Autonomous.c"
#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.

/**
 *
 */
task main()
{
  initializeRobot();

  waitForStart(); // Wait for the beginning of autonomous phase.

  // 1 rotation is about 2', 1440 on the encoder
  move(7000, 50);
  wait1Msec(600);
}
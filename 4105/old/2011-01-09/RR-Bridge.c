#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Motor,  motorA,          motorA,        tmotorNormal, openLoop)
#pragma config(Motor,  motorB,          motorB,        tmotorNormal, openLoop)
#pragma config(Motor,  motorC,          motorC,        tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C1_1,     motorD,        tmotorNormal, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motorE,        tmotorNormal, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     intake,        tmotorNormal, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     wheelieBar,    tmotorNormal, openLoop)
#pragma config(Servo,  srvo_S1_C3_3,    goalArm,              tServoStandard)
#pragma config(Servo,  srvo_S1_C3_1,    goalCapture1,          tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    goalCapture2,          tServoStandard)

/* RR-Bridge.c */

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

  motor[motorE] = 0; //turn both motors off
  motor[motorD] = 0;

  wait1Msec(1000);

  leftTurn();
  wait1Msec(600);

  move(2000, 30);
  wait1Msec(600);

  rightTurn();
  wait1Msec(600);

  move(4000, 30);
  wait1Msec(600);

  /* wheelie bar */
  wheelieBarDown();
  wheelieBarUp();

  move(4000, 30);
  wait1Msec(600);
}

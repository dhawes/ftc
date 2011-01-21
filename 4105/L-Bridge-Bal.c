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
 *
 */
task main()
{
  initializeRobot();

  /*
  while(true)
  {
    HTACreadAllAxes(HTAC, xAxis, yAxis, zAxis);
    wait1Msec(200);
  }
  //*/

  HTACreadAllAxes(HTAC, xAxis, yAxis, zAxis);

  // Wait for the beginning of autonomous phase.
  waitForStart();

  ClearTimer(T1);

  HTACreadAllAxes(HTAC, xLevel, yAxis, zAxis);

  motor[motorB] = 0;
  motor[motorC] = 0;

  StartTask(balanceLEDIndicate);

  rightQuarterTurn();
  wait1Msec(200);

  move(1900, 30);
  wait1Msec(200);

  rightQuarterTurn();
  wait1Msec(200);

  rightTurn();
  wait1Msec(200);

  //moveRight(120, -30);
  motor[motorE] = -30;
  wait1Msec(400);
  motor[motorE] = 0;
  nMotorEncoder[motorE] = 0;
  nMotorEncoder[motorD] = 0;

  move(250, -30);
  wait1Msec(200);

  /* wheelie bar */
  wheelieBarDown();
  wait1Msec(300);

  move(600, -30);
  wait1Msec(200);

  /*
  if(!onBridge())
  {
    retryBridgeApproach();
  }
  */

  wheelieBarUp();
  wait1Msec(200);

  move(1600, -30);
  wait1Msec(1000);

  //bridgeBalance();
  bridgeBalanceStabilize();

  // could not balance, move off of bridge
  move(2700, -30);

  wait1Msec(30000);
}

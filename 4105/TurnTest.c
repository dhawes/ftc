#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S2,     HTAC,                sensorLowSpeed)
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

/* R-Bridge */

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.
#include "Autonomous.c"

int encD;
int encE;

/**
 *
 */
task main()
{
  initializeRobot();

  //waitForStart(); // Wait for the beginning of autonomous phase.

  nMotorEncoder[motorE] = 0;  //clear the TETRIX encoders in motors D and E
  nMotorEncoder[motorD] = 0;

  motor[motorE] = 0; //turn both motors off
  motor[motorD] = 0;
  motor[wheelieBar] = 0;
  //wheelieBarUp();

  wait1Msec(200);

  /*
  leftQuarterTurn();
  wait1Msec(200);

  rightQuarterTurn();
  wait1Msec(200);
  */

  /*
  motor[motorD] = 25;
  while(true)
  {
    encD = nMotorEncoder[motorD];
    encE = nMotorEncoder[motorE];
  }
  wait1Msec(10000);
  return;
  //*/

  /*
  nMotorEncoder[motorE] = 0;
  nMotorEncoder[motorD] = 0;
  while (abs(nMotorEncoder[motorE]) < LEFT_TURN_ENCODER)
  {
    //motor[motorE] = TURN_SPEED * -1;
    motor[motorE] = TURN_SPEED;
  }
  motor[motorE] = 0;
  motor[motorD] = 0;
  nMotorEncoder[motorE] = 0;
  nMotorEncoder[motorD] = 0;

  nMotorEncoder[motorE] = 0;
  nMotorEncoder[motorD] = 0;
  while (abs(nMotorEncoder[motorD]) < LEFT_TURN_ENCODER)
  {
    //motor[motorE] = TURN_SPEED * -1;
    motor[motorD] = TURN_SPEED;
  }
  motor[motorE] = 0;
  motor[motorD] = 0;
  nMotorEncoder[motorE] = 0;
  nMotorEncoder[motorD] = 0;

  wait1Msec(10000);

  return;
  */

  /*
  rightTurn();
  wait1Msec(1000);

  leftTurn();
  wait1Msec(1000);
  */
  leftTurn();
  wait1Msec(1000);

  rightTurn();
  wait1Msec(1000);

  return;

  rightHalfTurn();
  wait1Msec(1000);

  leftHalfTurn();
  wait1Msec(1000);

  leftHalfTurn();
  wait1Msec(1000);

  rightHalfTurn();
  wait1Msec(200);
}
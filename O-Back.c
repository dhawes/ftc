#pragma config(Hubs,  S1, HTServo,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Sensor, S2,     HTIRS2,         sensorI2CCustom)
#pragma config(Sensor, S3,     HTGYRO,         sensorAnalogInactive)
#pragma config(Sensor, S4,     SONAR,         sensorSONAR)
#pragma config(Motor,  motorA,          green,         tmotorNormal, openLoop)
#pragma config(Motor,  motorB,          yellow,        tmotorNormal, openLoop)
#pragma config(Motor,  motorC,          red,           tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     ballArm,       tmotorNormal, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     clawArm,          tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     intake,        tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     spool,         tmotorNormal, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C4_1,     right,          tmotorNormal, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C4_2,     left,         tmotorNormal, openLoop, encoder)
#pragma config(Servo,  srvo_S1_C1_1,    clawRelease,                 tServoStandard)
#pragma config(Servo,  srvo_S1_C1_2,    armRelease,               tServoStandard)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/* $Id$ */

#define GYRO
#define MOVE_GYRO
#define MOVE_TIMED

#include "Autonomous.h"

/**
 * Starting on the outside, drive to the back parking area.
 */
task main()
{
  initializeRobot();

  // Wait for the beginning of autonomous phase.
  waitForStart();

  StartTask(prettyLights);

  // go to the back parking area
  if(useGyro)
  {
    moveGyro(MOTOR_FULL, MOVE_TO_BACK_TIME);
  }
  else
  {
    moveTimed(MOTOR_FULL, MOVE_TO_BACK_TIME);
  }
}

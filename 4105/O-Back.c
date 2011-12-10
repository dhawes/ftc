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
#pragma config(Servo,  srvo_S1_C3_4,    hopper,     tServoStandard)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/* $Id$ */

#define MOVE_TIMED

#include "Autonomous.c"
#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.

/**
 * Starting on the outside, drive to the back parking area.
 */
task main()
{
  initializeRobot();

  // Wait for the beginning of autonomous phase.
  waitForStart();

  motor[green]  = LED_OFF;
  motor[yellow] = LED_OFF;
  motor[red]    = LED_OFF;

  // go to the back parking area
  moveTimed(MOTOR_FULL, MOVE_TO_BACK_TIME);
}

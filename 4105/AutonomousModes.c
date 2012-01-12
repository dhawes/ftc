#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S2,     HTGYRO,              sensorAnalogInactive)
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

#define ALL_USER_INPUT
#define GYRO
#define MOVE_GYRO
#define RIGHT_GYRO_TURN
#define LEFT_GYRO_TURN
#define MOVE_TIMED
#define TURN_RIGHT_TIMED
#define TURN_LEFT_TIMED

#include "Autonomous.c"
#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.

/**
 * Autonomous modes depending on user input.
 */
task main()
{
  initializeRobot();

  // Wait for the beginning of autonomous phase.
  waitForStart();

  StartTask(prettyLights);

  if(startPause)
  {
    wait1Msec(10000);
  }

  // go forward
  if(useGyro)
  {
    moveGyro(MOTOR_FULL, MOVE_OFF_RAMP_TIME);
  }
  else
  {
    moveTimed(MOTOR_FULL, MOVE_OFF_RAMP_TIME);
    wait1Msec(200);
  }

  if(startColor == START_RED)
  {
    // turn left
    if(useGyro)
    {
      leftGyroTurn(-90, MOTOR_FULL);
    }
	  else
	  {
	    turnLeftTimed(MOTOR_FULL, startPosition == START_INSIDE ? LEFT_TURN_TIME : LEFT_OUTSIDE_TURN_TIME);
	    wait1Msec(200);
	  }
	}
	else
	{
	  // turn right
    if(useGyro)
    {
      rightGyroTurn(90, MOTOR_FULL);
    }
	  else
	  {
	    turnRightTimed(MOTOR_FULL, startPosition == START_INSIDE ? RIGHT_TURN_TIME : RIGHT_OUTSIDE_TURN_TIME);
	    wait1Msec(200);
	  }
	}

  // move forward
  if(useGyro)
  {
    moveGyro(MOTOR_FULL, startPosition == START_INSIDE ? MOVE_TO_BBALL_TIME : MOVE_OUTSIDE_TO_BBALL_TIME);
  }
  else
  {
    moveTimed(MOTOR_FULL, startPosition == START_INSIDE ? MOVE_TO_BBALL_TIME : MOVE_OUTSIDE_TO_BBALL_TIME);
    wait1Msec(200);
  }

  if(startColor == START_RED)
  {
	  // slight left
	  if(useGyro)
	  {
	    leftGyroTurn(-105, MOTOR_FULL);
	  }
	  else
	  {
	    turnLeftTimed(MOTOR_FULL, startPosition == START_INSIDE ? SLIGHT_LEFT_TIME: SLIGHT_OUTSIDE_LEFT_TIME);
	    wait1Msec(200);
	  }
	}
	else
	{
	  // slight right
	  if(useGyro)
	  {
	    rightGyroTurn(105, MOTOR_FULL);
	  }
	  else
	  {
	    turnRightTimed(MOTOR_FULL, startPosition == START_INSIDE ? SLIGHT_RIGHT_TIME: SLIGHT_OUTSIDE_RIGHT_TIME);
	    wait1Msec(200);
	  }
	}

  motor[intake] = MOTOR_FULL;

  // go to the front parking zone
  if(useGyro)
  {
    moveGyro(MOTOR_FULL, MOVE_TO_CORNER_TIME);
  }
  else
  {
    moveTimed(MOTOR_FULL, MOVE_TO_CORNER_TIME);
  }
}

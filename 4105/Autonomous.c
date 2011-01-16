/* Autonomous.c */
#include "HTAC-driver.h"

/* Function prototypes */
void initializeRobot();
void rightTurn();
void leftTurn();
void rightQuarterTurn();
void leftQuarterTurn();
void move(int distance, int speed);
void batonLoader();
void bridgeBalance();

/* Common defines */
#define LEFT_TURN_ENCODER    750
#define RIGHT_TURN_ENCODER   750
#define TURN_SPEED           25
#define INTAKE_SPEED         -30
#define RIGHT_180_ENCODER    1550
#define WHEELIE_BAR_SPEED    30
#define WHEELIE_BAR_TIME     400
#define ACCELEROMETER_LEVEL  -13
#define ACCELEROMETER_X_UP   -47
#define ACCELEROMETER_X_DOWN 19
#define ACCELEROMETER_THRESH 5
#define BALANCE_WAIT_TIME    1400
#define BALANCE_ABORT_TIME   3500

/* Accelerometer globals */
int xAxis = 0, yAxis = 0, zAxis = 0;

/**
 * Initialize robot.
 */
void initializeRobot()
{
  // Place code here to sinitialize servos to starting positions.
  // Sensors are automatically configured and setup by ROBOTC. They may need a brief time to stabilize.
  //servo[wheelieBar1] = 0;
  //servo[wheelieBar2] = 0;
  //bFloatDuringInactiveMotorPWM = false;
  motor[motorA] = 100;
  motor[motorB] = 100;
  motor[motorC] = 100;
  servo[goalCapture1] = 35;
  servo[goalCapture2] = 200;
  servo[goalArm] = 68;

  return;
}

/**
 * Make a right turn.
 */
void rightTurn()
{
  nMotorEncoder[motorE] = 0;
  nMotorEncoder[motorD] = 0;
  while (abs(nMotorEncoder[motorE]) < RIGHT_TURN_ENCODER ||
         abs(nMotorEncoder[motorD]) < RIGHT_TURN_ENCODER)
  {
    motor[motorE] = TURN_SPEED;
    motor[motorD] = TURN_SPEED * -1;
  }
  motor[motorE] = 0;
  motor[motorD] = 0;
  nMotorEncoder[motorE] = 0;
  nMotorEncoder[motorD] = 0;
}

/**
 * Make a left turn.
 */
void leftTurn()
{
  nMotorEncoder[motorE] = 0;
  nMotorEncoder[motorD] = 0;
  while (abs(nMotorEncoder[motorD]) < LEFT_TURN_ENCODER ||
         abs(nMotorEncoder[motorE]) < LEFT_TURN_ENCODER)
  {
    motor[motorE] = TURN_SPEED * -1;
    motor[motorD] = TURN_SPEED;
  }
  motor[motorE] = 0;
  motor[motorD] = 0;
  nMotorEncoder[motorE] = 0;
  nMotorEncoder[motorD] = 0;
}

/**
 * Move the provided distance at the provided motor speed.
 *
 * distance -- the distance in encoder counts
 * speed    -- the motor speed (positive == forwards, negative == reverse
 */
void move(int distance, int speed)
{
  while (abs(nMotorEncoder[motorD]) < distance ||
         abs(nMotorEncoder[motorE]) < distance)
  {
    motor[motorE] = speed;
    motor[motorD] = speed;
  }
  motor[motorE] = 0;
  motor[motorD] = 0;
  nMotorEncoder[motorE] = 0;
  nMotorEncoder[motorD] = 0;
}

/**
 * Move the provided distance at the provided motor speed.
 *
 * distance -- the distance in encoder counts
 * speed    -- the motor speed (positive == forwards, negative == reverse
 */
void moveRight(int distance, int speed)
{
  while (abs(nMotorEncoder[motorD]) < distance ||
         abs(nMotorEncoder[motorE]) < distance)
  {
    motor[motorD] = speed;
    motor[motorE] = 0;
    //motor[motorE] = speed * -1;
  }
  motor[motorE] = 0;
  motor[motorD] = 0;
  nMotorEncoder[motorE] = 0;
  nMotorEncoder[motorD] = 0;
}

/**
 * Put the wheelie bar down.
 */
void wheelieBarDown()
{
  motor[wheelieBar] = WHEELIE_BAR_SPEED;
  wait1Msec(WHEELIE_BAR_TIME);
}

/**
 * Put the wheelie bar up.
 */
void wheelieBarUp()
{
  motor[wheelieBar] = WHEELIE_BAR_SPEED * -1;
  wait1Msec(WHEELIE_BAR_TIME);
}

/**
 * Make a left quarter turn.
 */
void leftQuarterTurn()
{
  nMotorEncoder[motorE] = 0;
  nMotorEncoder[motorD] = 0;
  while (abs(nMotorEncoder[motorD]) < LEFT_TURN_ENCODER / 2 ||
         abs(nMotorEncoder[motorE]) < LEFT_TURN_ENCODER / 2)
  {
    motor[motorE] = TURN_SPEED * -1;
    motor[motorD] = TURN_SPEED;
  }
  motor[motorE] = 0;
  motor[motorD] = 0;
  nMotorEncoder[motorE] = 0;
  nMotorEncoder[motorD] = 0;
}

/**
 * Make a right quarter turn.
 */
void rightQuarterTurn()
{
  nMotorEncoder[motorE] = 0;
  nMotorEncoder[motorD] = 0;
  while (abs(nMotorEncoder[motorD]) < RIGHT_TURN_ENCODER / 2 ||
         abs(nMotorEncoder[motorE]) < RIGHT_TURN_ENCODER / 2)
  {
    motor[motorE] = TURN_SPEED;
    motor[motorD] = TURN_SPEED * -1;
  }
  motor[motorE] = 0;
  motor[motorD] = 0;
  nMotorEncoder[motorE] = 0;
  nMotorEncoder[motorD] = 0;
}

/**
 * Run the baton loader for 5 seconds.
 */
void batonLoader()
{
  // baton (re)loader
  motor[intake] = INTAKE_SPEED;
  wait1Msec(5000);
  motor[intake] = 0;
}

/**
 * Use the accelerometer sensor to balance on the bridge.
 */
void bridgeBalance()
{
  while(HTACreadAllAxes(HTAC, xAxis, yAxis, zAxis))
  {
	  if(xAxis < ACCELEROMETER_LEVEL - ACCELEROMETER_THRESH)
	  {
	    if(time10[T1] > BALANCE_ABORT_TIME)
	    {
	      break;
	    }
	    move(50, -25);
	    wait1Msec(500);
	  }
	  else if(xAxis > ACCELEROMETER_LEVEL + ACCELEROMETER_THRESH)
	  {
	    if(time10[T1] > BALANCE_ABORT_TIME)
	    {
	      break;
	    }
	    move(50, 25);
	    wait1Msec(500);
	  }
	  wait1Msec(BALANCE_WAIT_TIME);
	}
}

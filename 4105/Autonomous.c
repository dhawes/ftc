/* $Id$ */
#include "HTAC-driver.h"

/* Function prototypes */
void initializeRobot();
void rightTurn();
void leftTurn();
void rightQuarterTurn();
void leftQuarterTurn();
void move(int distance, int speed);
void moveTimed(int distance, int speed, int time);
void wheelieBarUp();
void wheelieBarDown();
void batonLoader();
void bridgeBalance();
void bridgeBalanceStabilize();
void balanceStabilize();
bool onBridge();
void retryBridgeApproach();

/* Common defines */
#define LEFT_TURN_ENCODER    200
#define RIGHT_TURN_ENCODER   200
#define TURN_SPEED           25
#define INTAKE_SPEED         -30
#define RIGHT_180_ENCODER    1550
#define WHEELIE_BAR_SPEED    30
#define WHEELIE_BAR_TIME     400
#define ACCELEROMETER_LEVEL  -13
#define ACCELEROMETER_X_UP   -47
#define ACCELEROMETER_X_DOWN 19
#define ACCELEROMETER_THRESH 10
#define BRIDGE_THRESH        5
#define BALANCE_WAIT_TIME    1400
#define BALANCE_ABORT_TIME   3500

/* Bridge approach defines */
/* Left */
#define L_BRIDGE_APPROACH    525
#define L_BRIDGE_ADJUST_TIME 300
#define L_BRIDGE_ADJUST      100
/* Right */
#define R_BRIDGE_APPROACH    525
#define R_BRIDGE_ADJUST_TIME 300
#define R_BRIDGE_ADJUST      100

/* Accelerometer globals */
int xAxis = 0, yAxis = 0, zAxis = 0, xLevel = 0;

/**
 * Initialize robot.
 */
void initializeRobot()
{
  motor[motorA] = 100;
  motor[motorB] = 100;
  motor[motorC] = 100;
  motor[motorD] = 0;
  motor[motorE] = 0;
  wheelieBarUp();
  motor[wheelieBar] = 0;
  motor[intake] = 0;
  servo[goalCapture1] = 35;
  servo[goalCapture2] = 200;
  servo[goalArm] = 54;

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
  nMotorEncoder[motorE] = 0;
  nMotorEncoder[motorD] = 0;
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
 * time     -- the time in 10ms intervals to quit
 */
void moveTimed(int distance, int speed, int time)
{
  ClearTimer(T2);
  nMotorEncoder[motorE] = 0;
  nMotorEncoder[motorD] = 0;
  while (abs(nMotorEncoder[motorD]) < distance ||
         abs(nMotorEncoder[motorE]) < distance)
  {
    motor[motorE] = speed;
    motor[motorD] = speed;
    if(time10[T2] > time)
	  {
	    break;
	  }
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
  wait1Msec(WHEELIE_BAR_TIME * 2);
  motor[wheelieBar] = 0;
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

/**
 * Use the accelerometer sensor to balance on the bridge.
 */
void bridgeBalanceStabilize()
{
  while(HTACreadAllAxes(HTAC, xAxis, yAxis, zAxis))
  {
	  if(xAxis < xLevel - ACCELEROMETER_THRESH)
	  {
	    if(time10[T1] > BALANCE_ABORT_TIME)
	    {
	      break;
	    }
	    move(50, -25);
	  }
	  else if(xAxis > xLevel + ACCELEROMETER_THRESH)
	  {
	    if(time10[T1] > BALANCE_ABORT_TIME)
	    {
	      break;
	    }
	    move(50, 25);
	  }
	  motor[motorB] = 100;
	  balanceStabilize();
	  motor[motorB] = 0;
	}
}

/**
 * Wait for accelerometer readings to stabilize.
 */
void balanceStabilize()
{
  bool stable = false;
  int stableCount = 0;
  int x, y, z;
  HTACreadAllAxes(HTAC, xAxis, yAxis, zAxis);
  //while(!stable)
  while(stableCount < 2)
  {
    wait1Msec(400);
    HTACreadAllAxes(HTAC, x, y, z);
    if((x <= 0 && xAxis <= 0) ||
       (x >= 0 && xAxis >= 0))
    {
      int diff = abs(x) - abs(xAxis); // have to use variable because of compiler issue
      if(abs(diff) < ACCELEROMETER_THRESH)
      {
        stable = true;
        stableCount++;
      }
      else
      {
        stableCount = 0;
      }
    }
    else
    {
      if(abs(x - xAxis) < ACCELEROMETER_THRESH)
      {
        stable = true;
        stableCount++;
      }
      else
      {
        stableCount = 0;
      }
    }
    HTACreadAllAxes(HTAC, xAxis, yAxis, zAxis);
  }
}

/**
 * Use the accelerometer to determine if we are on the bridge.
 */
bool onBridge()
{
  bool ret = false;
  HTACreadAllAxes(HTAC, xAxis, yAxis, zAxis);
  if(xAxis < xLevel - BRIDGE_THRESH ||
     xAxis > xLevel + BRIDGE_THRESH)
  {
    // accleromter reading indicates we are on the bridge
    ret = true;
  }
  return ret;
}

/**
 * Try to get on the bridge again.
 */
void retryBridgeApproach()
{
  wheelieBarUp();
  moveTimed(200, 30, 200);
  wheelieBarDown();
  moveTimed(1000, -30, 200);
  wait1Msec(200);
  if(!onBridge())
  {
    wheelieBarUp();
    moveTimed(200, 30, 200);
    wheelieBarDown();
    moveTimed(1000, -30, 200);
  }
}

/**
 * Indicate with the LEDs whether the robot is balanced.
 */
task balanceLEDIndicate()
{
  while(true)
  {
    if(xAxis < xLevel - ACCELEROMETER_THRESH ||
       xAxis > xLevel + ACCELEROMETER_THRESH)
	  {
	    motor[motorA] = 0;
	    motor[motorC] = 100;
	  }
	  else
	  {
	    motor[motorA] = 100;
	    motor[motorC] = 0;
	  }
	  wait1Msec(500);
  }
}

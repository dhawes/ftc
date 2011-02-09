/* $Id$ */
#ifdef BRIDGE_BALANCE
#include "HTAC-driver.h"
#endif /* BRIDGE_BALANCE */
#ifdef COMPASS
#include "HTMC-driver.h"
#endif /* COMPASS */

/* Common defines */
#define LEFT_TURN_ENCODER    205
#define RIGHT_TURN_ENCODER   217
#define TURN_SPEED           25
#define WHEELIE_BAR_SPEED    55
#define WHEELIE_BAR_TIME     400
#define ACCELEROMETER_THRESH 10
#define BRIDGE_THRESH        5
#define BALANCE_ABORT_TIME   3500
#define BALANCE_ENCODER_CNT  15

/* Bridge approach defines */
/* Left */
#define L_BRIDGE_APPROACH    650
#define L_BRIDGE_ADJUST_TIME 325
#define L_BRIDGE_ADJUST      50
/* Right */
#define R_BRIDGE_APPROACH    675
#define R_BRIDGE_ADJUST_TIME 050
#define R_BRIDGE_ADJUST      50
/* Common */
#define BR_GET_ON            200
#define BR_TO_CENTER         400
#define BR_MOVE_OFF          900
#define BR_GO_OVER           1600

#ifdef BRIDGE_BALANCE
/* Accelerometer globals */
int xAxis = 0, yAxis = 0, zAxis = 0, xLevel = 0;
#endif /* BRIDGE_BALANCE */

#ifdef COMPASS
int initialHeading = 0;
#endif /* COMPASS */

/**
 * Initialize robot.
 */
void initializeRobot()
{
  /* PID control */
  /*
  nMotorPIDSpeedCtrl[motorD] = mtrSpeedReg;  // mtrNoReg for off
  nMotorPIDSpeedCtrl[motorE] = mtrSpeedReg;
  nPidUpdateInterval = 25;
  nMaxRegulatedSpeed12V = 1000;
  */

  motor[motorA] = 100;
  motor[motorB] = 100;
  motor[motorC] = 100;
  motor[motorD] = 0;
  motor[motorE] = 0;
  //wheelieBarUp();
  motor[wheelieBar] = 0;
  motor[goalGrab] = 0;
  servo[goalArm] = 54;

  return;
}

#ifdef RIGHT_TURN
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
#endif /* RIGHT_TURN */

#ifdef LEFT_TURN
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
#endif /* LEFT_TURN */

#ifdef RIGHT_COMPASS_TURN
/**
 * Turn to the right to the relative heading, stopping if we go over the time.
 *
 * heading  -- the relative heading to move to
 * speed    -- the motor speed (positive == forwards, negative == reverse
 * time     -- the time in 10ms intervals to quit
 */
void rightCompassTurn(int heading, int speed, int time)
{
  ClearTimer(T2);
  int relativeHeading = HTMCreadRelativeHeading(HTMC);
  while(relativeHeading != heading)
  {
    motor[motorE] = speed;
    motor[motorD] = speed * -1;
    if(time10[T2] > time)
	  {
	    break;
	  }
	  relativeHeading = HTMCreadRelativeHeading(HTMC);
  }
  motor[motorE] = 0;
  motor[motorD] = 0;
}
#endif /* RIGHT_COMPASS_TURN */

#ifdef LEFT_COMPASS_TURN
/**
 * Turn to the left to the relative heading, stopping if we go over the time.
 *
 * heading  -- the relative heading to move to
 * speed    -- the motor speed (positive == forwards, negative == reverse
 * time     -- the time in 10ms intervals to quit
 */
void leftCompassTurn(int heading, int speed, int time)
{
  ClearTimer(T2);
  int relativeHeading = HTMCreadRelativeHeading(HTMC);
  while(relativeHeading != heading)
  {
    motor[motorE] = speed * -1;
    motor[motorD] = speed;
    if(time10[T2] > time)
	  {
	    break;
	  }
	  relativeHeading = HTMCreadRelativeHeading(HTMC);
  }
  motor[motorE] = 0;
  motor[motorD] = 0;
}
#endif /* LEFT_COMPASS_TURN */

#ifdef MOVE
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
#endif /* MOVE */

#ifdef MOVE_TIMED
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
#endif /* MOVE_TIMED */

#ifdef MOVE_RIGHT
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
#endif /* MOVE_RIGHT */

#ifdef WHEELIE_BAR
/**
 * Put the wheelie bar down.
 */
void wheelieBarDown()
{
  motor[wheelieBar] = -WHEELIE_BAR_SPEED;
  wait1Msec(WHEELIE_BAR_TIME);
}


/**
 * Put the wheelie bar up.
 */
void wheelieBarUp()
{
  motor[wheelieBar] = WHEELIE_BAR_SPEED;
  wait1Msec(WHEELIE_BAR_TIME * 2);
  motor[wheelieBar] = 0;
}
#endif /* WHEELIE_BAR */

#ifdef LEFT_HALF_TURN
/**
 * Make a left half turn.
 */
void leftHalfTurn()
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
#endif /* LEFT_HALF_TURN */

#ifdef RIGHT_HALF_TURN
/**
 * Make a right half turn.
 */
void rightHalfTurn()
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
#endif /* RIGHT_HALF_TURN */

#ifdef BRIDGE_BALANCE
/**
 * Wait for accelerometer readings to stabilize.
 */
void balanceStabilize()
{
  int stableCount = 0;
  int x, y, z;
  HTACreadAllAxes(HTAC, xAxis, yAxis, zAxis);
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
	    move(BALANCE_ENCODER_CNT, -25);
	  }
	  else if(xAxis > xLevel + ACCELEROMETER_THRESH)
	  {
	    if(time10[T1] > BALANCE_ABORT_TIME)
	    {
	      break;
	    }
	    move(BALANCE_ENCODER_CNT, 25);
	  }
	  motor[motorB] = 100;
	  balanceStabilize();
	  motor[motorB] = 0;
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
#endif /* BRIDGE_BALANCE */

#ifdef ON_BRIDGE
/**
 * Use the accelerometer to determine if we are on the bridge.
 */
bool onBridge()
{
  bool ret = false;
  HTACreadAllAxes(HTAC, xAxis, yAxis, zAxis);
  if(xAxis < xLevel - ACCELEROMETER_THRESH ||
     xAxis > xLevel + ACCELEROMETER_THRESH)
  {
    // accleromter reading indicates we are on the bridge
    ret = true;
  }
  return ret;
}
#endif /* ON_BRIDGE */

#ifdef RETRY_BRIDGE_APPROACH
/**
 * Try to get on the bridge again.
 */
void retryBridgeApproach()
{
  wheelieBarUp();
  moveTimed(50, 30, 200);
  wheelieBarDown();
  moveTimed(200, -30, 200);
  wait1Msec(200);
  while(!onBridge())
  {
    wheelieBarUp();
    moveTimed(50, 30, 200);
    wheelieBarDown();
    moveTimed(200, -30, 200);
    wait1Msec(200);
  }
}
#endif /* RETRY_BRIDGE_APPROACH */

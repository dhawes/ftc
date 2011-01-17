/* Autonomous.c */

#include "Autonomous.h"

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
  servo[goalCapture1] = 220;
  servo[goalCapture2] = 50;
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
 * Put the wheelie bar down.
 */
void wheelieBarDown()
{
  motor[wheelieBar] = WHEELIE_BAR_SPEED * -1;
  wait1Msec(WHEELIE_BAR_TIME);
}

/**
 * Put the wheelie bar up.
 */
void wheelieBarUp()
{
  motor[wheelieBar] = WHEELIE_BAR_SPEED;
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

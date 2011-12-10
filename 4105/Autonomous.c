/* $Id$ */

/* Common defines */
#define LEFT_TURN_ENCODER    205
#define RIGHT_TURN_ENCODER   217
#define TURN_SPEED           25
#define GRAB_START 20
#define GRAB_OPEN  100
#define HOPPER_OPEN  180
#define HOPPER_CLOSED  255
#define MOTOR_OFF 0
#define MOTOR_FULL 100

/* Movement defines */
#define MOVE_OFF_RAMP_TIME  1700
#define RIGHT_TURN_TIME     1500
#define LEFT_TURN_TIME      1500
#define MOVE_TO_BBALL_TIME  1000
#define SLIGHT_RIGHT_TIME   500
#define SLIGHT_LEFT_TIME    500
#define MOVE_TO_CORNER_TIME 5650
#define MOVE_TO_WALL_TIME   1000
#define MOVE_TO_BACK_TIME   6000

/**
 * Initialize robot.
 */
void initializeRobot()
{
  motor[right] = MOTOR_OFF;
  motor[left] = MOTOR_OFF;
  motor[intake] = MOTOR_OFF;
  servo[grab] = GRAB_START;
  servo[hopper] = HOPPER_CLOSED;

  return;
}

#ifdef RIGHT_TURN
/**
 * Make a right turn.
 */
void rightTurn()
{
  nMotorEncoder[right] = 0;
  nMotorEncoder[left] = 0;
  while (abs(nMotorEncoder[right]) < RIGHT_TURN_ENCODER ||
         abs(nMotorEncoder[left]) < RIGHT_TURN_ENCODER)
  {
    motor[right] = TURN_SPEED;
    motor[left] = TURN_SPEED * -1;
  }
  motor[right] = 0;
  motor[left] = 0;
  nMotorEncoder[right] = 0;
  nMotorEncoder[left] = 0;
}
#endif /* RIGHT_TURN */

#ifdef LEFT_TURN
/**
 * Make a left turn.
 */
void leftTurn()
{
  nMotorEncoder[right] = 0;
  nMotorEncoder[left] = 0;
  while (abs(nMotorEncoder[left]) < LEFT_TURN_ENCODER ||
         abs(nMotorEncoder[right]) < LEFT_TURN_ENCODER)
  {
    motor[right] = TURN_SPEED * -1;
    motor[left] = TURN_SPEED;
  }
  motor[right] = 0;
  motor[left] = 0;
  nMotorEncoder[right] = 0;
  nMotorEncoder[left] = 0;
}
#endif /* LEFT_TURN */

#ifdef MOVE
/**
 * Move the provided distance at the provided motor speed.
 *
 * distance -- the distance in encoder counts
 * speed    -- the motor speed (positive == forwards, negative == reverse
 */
void move(int distance, int speed)
{
  nMotorEncoder[right] = 0;
  nMotorEncoder[left] = 0;
  while (abs(nMotorEncoder[left]) < distance ||
         abs(nMotorEncoder[right]) < distance)
  {
    motor[right] = speed;
    motor[left] = speed;
  }
  motor[right] = MOTOR_OFF;
  motor[left] = MOTOR_OFF;
  nMotorEncoder[right] = 0;
  nMotorEncoder[left] = 0;
}
#endif /* MOVE */

#ifdef MOVE_TIMED
/**
 * Move at the provided motor speed for the provided time.
 *
 * speed    -- the motor speed (positive == forwards, negative == reverse
 * time     -- the time in ms
 */
void moveTimed(int speed, int time)
{
    motor[right] = speed;
    motor[left]  = speed;
    wait1Msec(time);
    motor[right] = MOTOR_OFF;
    motor[left]  = MOTOR_OFF;
}
#endif /* MOVE_TIMED */

#ifdef TURN_RIGHT_TIMED
/**
 * Turn right at the provided motor speed for the provided time.
 *
 * speed    -- the motor speed (positive == forwards, negative == reverse
 * time     -- the time in ms
 */
void turnRightTimed(int speed, int time)
{
    motor[right] = -speed;
    motor[left]  = speed;
    wait1Msec(time);
    motor[right] = MOTOR_OFF;
    motor[left]  = MOTOR_OFF;
}
#endif /* TURN_RIGHT_TIMED */

#ifdef TURN_LEFT_TIMED
/**
 * Turn left at the provided motor speed for the provided time.
 *
 * speed    -- the motor speed (positive == forwards, negative == reverse
 * time     -- the time in ms
 */
void turnLeftTimed(int speed, int time)
{
    motor[right] = speed;
    motor[left]  = -speed;
    wait1Msec(time);
    motor[right] = MOTOR_OFF;
    motor[left]  = MOTOR_OFF;
}
#endif /* TURN_LEFT_TIMED */

/* $Id$ */

/* Common defines */
#define LEFT_TURN_ENCODER    205
#define RIGHT_TURN_ENCODER   217
#define TURN_SPEED           25
#define GRAB_START 20
#define GRAB_OPEN  100
#define MOTOR_OFF 0
#define MOTOR_FULL 100
#define LED_ON 100
#define LED_OFF 0
#define HOPPER1_OPEN   75
#define HOPPER1_CLOSED 10
#define HOPPER2_OPEN   180
#define HOPPER2_CLOSED 255

/* Movement defines */
#define MOVE_OFF_RAMP_TIME         1800
#define RIGHT_TURN_TIME            1500
#define LEFT_TURN_TIME             1800
#define MOVE_TO_BBALL_TIME         1000
#define SLIGHT_RIGHT_TIME          750
#define SLIGHT_LEFT_TIME           800
#define MOVE_TO_CORNER_TIME        5000
#define MOVE_TO_WALL_TIME          1000
#define MOVE_TO_BACK_TIME          6000
/* Outside modes */
#define LEFT_OUTSIDE_TURN_TIME     1800
#define RIGHT_OUTSIDE_TURN_TIME    1700
#define MOVE_OUTSIDE_TO_BBALL_TIME 2125
#define SLIGHT_OUTSIDE_RIGHT_TIME  500
#define SLIGHT_OUTSIDE_LEFT_TIME   750

/**
 * Initialize robot.
 */
void initializeRobot()
{
  motor[right]   = MOTOR_OFF;
  motor[left]    = MOTOR_OFF;
  motor[intake]  = MOTOR_OFF;
  motor[whacker] = MOTOR_OFF;
  servo[grab]    = GRAB_START;
  servo[hopper1] = HOPPER1_CLOSED;
  servo[hopper2] = HOPPER2_CLOSED;
  motor[green]   = LED_ON;
  motor[yellow]  = LED_ON;
  motor[red]     = LED_ON;

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

task prettyLights()
{
  while(true)
  {
    motor[green] = LED_ON;
    wait1Msec(200);
    motor[green] = LED_OFF;
    motor[yellow] = LED_ON;
    wait1Msec(200);
    motor[yellow] = LED_OFF;
    motor[red] = LED_ON;
    wait1Msec(200);
    motor[red] = LED_OFF;
    motor[yellow] = LED_ON;
    wait1Msec(200);
    motor[yellow] = LED_OFF;
    motor[green] = LED_ON;
  }
}

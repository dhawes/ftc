/* $Id$ */
#ifdef GYRO
#include "HTGYRO-driver.h"
task getHeading();
#endif /* GYRO */

/* Common defines */
#define LEFT_TURN_ENCODER   205
#define RIGHT_TURN_ENCODER  217
#define TURN_SPEED          25
#define MOTOR_OFF           0
#define MOTOR_HALF          50
#define MOTOR_FULL          100
#define LED_ON              100
#define LED_OFF             0
#define ARM_RELEASE_OPEN    120
#define ARM_RELEASE_CLOSED  255
#define CLAW_RELEASE_OPEN   186
#define CLAW_RELEASE_CLOSED 131

/* Movement defines */
#define MOVE_OFF_RAMP_TIME         1700
#define RIGHT_TURN_TIME            1500
#define LEFT_TURN_TIME             1800
#define MOVE_TO_BBALL_TIME         1000
#define SLIGHT_RIGHT_TIME          350
#define SLIGHT_LEFT_TIME           500
#define MOVE_TO_CORNER_TIME        5500
#define MOVE_TO_WALL_TIME          1000
#define MOVE_TO_BACK_TIME          6000
/* Outside modes */
#define LEFT_OUTSIDE_TURN_TIME     1600
#define RIGHT_OUTSIDE_TURN_TIME    1700
#define MOVE_OUTSIDE_TO_BBALL_TIME 2125
#define SLIGHT_OUTSIDE_RIGHT_TIME  500
#define SLIGHT_OUTSIDE_LEFT_TIME   750

/* user input globals */
bool useGyro = false;
#ifdef ALL_USER_INPUT
#define START_RED     "Red"
#define START_BLUE    "Blue"
#define START_INSIDE  "Inside"
#define START_OUTSIDE "Outside"
#define PARK_BACK     "Back"
#define PARK_FRONT    "Front"
string startColor;
string startPosition;
bool startPause = false;
string robotPark;
string bBallPark;
#endif /* ALL_USER_INPUT */
//bool useIRSeeker = false;

void getUserInput()
{
#ifdef ALL_USER_INPUT
  nxtDisplayCenteredTextLine(0, "Red or Blue?");
  nxtDisplayCenteredTextLine(7, "Red        Blue");
  while(true)
  {
    if(nNxtButtonPressed == 2)
    {
      startColor = START_RED;
      nxtDisplayCenteredTextLine(0, "Red");
      break;
    }
    else if(nNxtButtonPressed == 1)
    {
      startColor = START_BLUE;
      nxtDisplayCenteredTextLine(0, "Blue");
      break;
    }
  }
  PlaySound(soundBlip);
  wait1Msec(1000);
  nxtDisplayCenteredTextLine(1, "Inside or Outside?");
  nxtDisplayCenteredTextLine(7, "Inside  Outside");
  while(true)
  {
    if(nNxtButtonPressed == 2)
    {
      startPosition = START_INSIDE;
      nxtDisplayCenteredTextLine(1, "Inside");
      break;
    }
    else if(nNxtButtonPressed == 1)
    {
      startPosition = START_OUTSIDE;
      nxtDisplayCenteredTextLine(1, "Outside");
      break;
    }
  }
  PlaySound(soundBlip);
  wait1Msec(1000);
  nxtDisplayCenteredTextLine(2, "Wait 10 Seconds?");
  nxtDisplayCenteredTextLine(7, "Yes          No");
  while(true)
  {
    if(nNxtButtonPressed == 2)
    {
      startPause = true;
      nxtDisplayCenteredTextLine(2, "10s Wait: Yes");
      break;
    }
    else if(nNxtButtonPressed == 1)
    {
      startPause = false;
      nxtDisplayCenteredTextLine(2, "10s Wait: No");
      break;
    }
  }
  nxtDisplayTextLine(7, "");
  PlaySound(soundBlip);
  wait1Msec(1000);
#endif /* ALL_USER_INPUT */
#ifdef GYRO
  nxtDisplayCenteredTextLine(4, "Gyro?");
  nxtDisplayCenteredTextLine(7, "Yes          No");
  while(true)
  {
    if(nNxtButtonPressed == 2)
    {
      useGyro = true;
      nxtDisplayCenteredTextLine(4, "Gyro: Yes");
      break;
    }
    else if(nNxtButtonPressed == 1)
    {
      useGyro = false;
      nxtDisplayCenteredTextLine(4, "Gyro: No");
      break;
    }
  }
  nxtDisplayTextLine(7, "");
  PlaySound(soundBlip);
#endif /* GYRO */
#ifdef PARK_MODES
  wait1Msec(1000);
  nxtDisplayCenteredTextLine(5, "Ball Park?");
  nxtDisplayCenteredTextLine(7, "Front      Back");
  while(true)
  {
    if(nNxtButtonPressed == 2)
    {
      bBallPark = PARK_FRONT;
      nxtDisplayCenteredTextLine(5, "Ball Park: Front");
      break;
    }
    else if(nNxtButtonPressed == 1)
    {
      bBallPark = PARK_BACK;
      nxtDisplayCenteredTextLine(5, "Ball Park: Back");
      break;
    }
  }
  nxtDisplayTextLine(7, "");
  PlaySound(soundBlip);
  wait1Msec(1000);
  if(bBallPark == PARK_BACK)
  {
	  nxtDisplayCenteredTextLine(6, "Robot Park?");
	  nxtDisplayCenteredTextLine(7, "Front      Back");
	  while(true)
	  {
	    if(nNxtButtonPressed == 2)
	    {
	      robotPark = PARK_FRONT;
	      nxtDisplayCenteredTextLine(6, "Bot Park: Front");
	      break;
	    }
	    else if(nNxtButtonPressed == 1)
	    {
	      robotPark = PARK_BACK;
	      nxtDisplayCenteredTextLine(6, "Bot Park: Back");
	      break;
	    }
	  }
	  nxtDisplayTextLine(7, "");
	  PlaySound(soundBlip);
	}
#endif /* PARK_MODES */

    string sayings[] = {"* Tally ho! *",
                        "* Geronimo! *",
                        "* Bansai! *",
                        "* Kamikazee! *",
                        "* Charge! *",
                        "* Ballin! *",
                        "* For Demacia! *",
                        "* Banana Pancakes *",
                        "* You Broke Me :(",
                        "You Look Ravishing",
                        "Radishes & Shining",
                        "Dont cross streams!",
                        "Break them",
                        "Well Then"};
	  //nxtDisplayCenteredTextLine(7, "* Tally ho! *");
	  nxtDisplayCenteredTextLine(7, sayings[rand() % 14]);
}

/**
 * Initialize robot.
 */
void initializeRobot()
{
  getUserInput();

#ifdef GYRO
  if(useGyro)
  {
    wait1Msec(2000);
    StartTask(getHeading);
  }
#endif /* GYRO */

  motor[green] =  LED_ON;
  motor[yellow] = LED_ON;
  motor[red] =    LED_ON;
  motor[right] =   MOTOR_OFF;
  motor[clawArm] = MOTOR_OFF;
  motor[left] =    MOTOR_OFF;
  motor[ballArm] = MOTOR_OFF;
  motor[spool] =   MOTOR_OFF;
  motor[intake] =  MOTOR_OFF;
  servoChangeRate[armRelease] = 50;
  servoTarget[armRelease] =  ARM_RELEASE_CLOSED;
  servoChangeRate[armRelease] = 10;
  servoTarget[clawRelease] = CLAW_RELEASE_CLOSED;
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
  }
}

#ifdef GYRO

#define RATE_THRESH 3
#define MOVE_THRESH 10
#define RIGHT_TURN_THRESH 0
#define LEFT_TURN_THRESH 2

float currHeading = 0;

// Task to keep track of the current heading using the HT Gyro
task getHeading ()
{
  float delTime = 0;
  float prevHeading = 0;
  float curRate = 0;

  HTGYROstartCal(HTGYRO);
  PlaySound(soundBeepBeep);
  while(true)
  {
    time1[T1] = 0;
    curRate = HTGYROreadRot(HTGYRO);
    if (abs(curRate) > RATE_THRESH)
    {
      //hogCPU();
      prevHeading = currHeading;
      currHeading = prevHeading + curRate * delTime;
      //if (currHeading >= 360) currHeading -= 360;
      //else if (currHeading < 0) currHeading += 360;
      //releaseCPU();
    }
    /*
    nxtDisplayTextLine(1, "curr: %f", currHeading);
    nxtDisplayTextLine(2, "prev: %f", prevHeading);
    nxtDisplayTextLine(3, "delTime: %f", delTime);
    nxtDisplayTextLine(4, "curRate: %f", curRate);
    */
    wait1Msec(5);
    delTime = ((float)time1[T1]) / 1000;
  }
}

#ifdef LEFT_GYRO_TURN
/**
 * Make a left turn to a heading.
 */
void leftGyroTurn(float heading, int speed)
{
  while(currHeading > heading + LEFT_TURN_THRESH)
  {
    motor[right] = speed;
    motor[left] = -speed;
  }
  motor[right] = MOTOR_OFF;
  motor[left] = MOTOR_OFF;
}
#endif /* LEFT_GYRO_TURN */

#ifdef RIGHT_GYRO_TURN
/**
 * Make a right turn to a heading.
 */
void rightGyroTurn(float heading, int speed)
{
  while(currHeading < heading - RIGHT_TURN_THRESH)
  {
    motor[right] = -speed;
    motor[left] = speed;
  }
  motor[right] = MOTOR_OFF;
  motor[left] = MOTOR_OFF;
}
#endif /* RIGHT_GYRO_TURN */

#ifdef MOVE_GYRO
void moveGyro(int speed, int time)
{
  float oHeading = currHeading;
  time1[T2] = 0;
  while(time1[T2] < time)
  {
    // drifting left
    if(currHeading < oHeading)
    {
        motor[right] = speed - MOVE_THRESH;
        motor[left] = speed;
    }
    // drifting right
    else if(currHeading > oHeading)
    {
        motor[right] = speed;
        motor[left] = speed - MOVE_THRESH;
    }
    else
    {
        motor[right] = speed;
        motor[left] = speed;
    }
    wait1Msec(10);
  }
  motor[right] = MOTOR_OFF;
  motor[left] = MOTOR_OFF;
}
#endif /* MOVE_GYRO */
#endif /* GYRO */

#ifdef IR_SEEKER
#include "HTIRS2-driver.h"

int getIRDirection()
{
  int dir = HTIRS2readACDir(HTIRS2);
  //nxtDisplayTextLine(1, "direction: %d", dir);
  return dir;
}

void turnToIRBeacon(int speed)
{
  int dir = getIRDirection();

  while(true)
  {
    if(dir == 0)
    {
      // no reading
      break;
    }
    else if(dir == 5)
    {
      break;
    }
    else if(dir > 5 && dir > 0)
    {
      // left of beacon
      motor[right] = -speed;
      motor[left] = speed;
    }
    else if(dir < 5 && dir > 0)
    {
      // right of beacon
      motor[right] = speed;
      motor[left] = -speed;
    }
    wait1Msec(100);
    dir = getIRDirection();
  }
  motor[left] = MOTOR_OFF;
  motor[right] = MOTOR_OFF;
}
#endif /* IR_SEEKER */


#ifdef BALL_GRAB
task BallGrab()
{
  wait1Msec(1000);
  motor[ballArm] = -MOTOR_FULL;
  wait1Msec(450);
  motor[ballArm] = MOTOR_OFF;
  return;
}
#endif /* BALL_GRAB */

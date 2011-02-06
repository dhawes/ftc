#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Motor,  motorA,          motorA,        tmotorNormal, openLoop)
#pragma config(Motor,  motorB,          motorB,        tmotorNormal, openLoop)
#pragma config(Motor,  motorC,          motorC,        tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C1_1,     motorD,        tmotorNormal, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motorE,        tmotorNormal, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     goalGrab,        tmotorNormal, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     wheelieBar,    tmotorNormal, openLoop)
#pragma config(Servo,  srvo_S1_C3_3,    goalArm,              tServoStandard)

/* $Id$ */

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.

#define GOAL_ARM_CLOSED 54
#define GOAL_ARM_OPEN 0
#define SERVO_CHANGE_RATE 10
#define LED_ON 100
#define LED_OFF 0
#define JOYSTICK_THRESHOLD 10
#define GOAL_GRAB_POWER 100
#define WHEELIE_BAR_POWER 50
#define MOTOR_OFF 0

/**
 * Initialize the robot.
 */
void initializeRobot()
{
  bFloatDuringInactiveMotorPWM = false;
  motor[motorA] = LED_ON;
  motor[motorB] = LED_ON;
  motor[motorC] = LED_ON;
  motor[motorD] = MOTOR_OFF;
  motor[motorE] = MOTOR_OFF;
  motor[wheelieBar] = MOTOR_OFF;
  motor[goalGrab] = MOTOR_OFF;
  servo[goalArm] = GOAL_ARM_CLOSED;

  return;
}

/**
 *
 */
task main()
{
  initializeRobot(); // init

  waitForStart();   // wait for start of tele-op phase

  while(true)
  {
    getJoystickSettings(joystick);

    if(joy1Btn(8))
    {
      // only allow 20% power
      motor[motorD] = joystick.joy1_y2 * .2;
      motor[motorE] = joystick.joy1_y1 * .2;
      motor[motorA] = LED_OFF;
      motor[motorB] = LED_OFF;
      motor[motorC] = LED_ON;
    }
    else if(joy1Btn(6))
    {
      // only allow 40% power
      motor[motorD] = joystick.joy1_y2 * .4;
      motor[motorE] = joystick.joy1_y1 * .4;
      motor[motorA] = LED_OFF;
      motor[motorB] = LED_ON;
      motor[motorC] = LED_OFF;
    }
    else
    {
      // 100% power
      motor[motorD] = joystick.joy1_y2;
      motor[motorE] = joystick.joy1_y1;
      motor[motorA] = LED_ON;
      motor[motorB] = LED_OFF;
      motor[motorC] = LED_OFF;
    }

    // figure out how to calibrate joystick so we don't have to check a threshold
    if(joystick.joy2_y2 > JOYSTICK_THRESHOLD)
    {
      motor[goalGrab] = -GOAL_GRAB_POWER;
    }
    else if(joystick.joy2_y2 < -JOYSTICK_THRESHOLD)
    {
      motor[goalGrab] = GOAL_GRAB_POWER;
    }
    else
    {
      motor[goalGrab] = MOTOR_OFF;
    }

    // wheelie bar up/down
    if(joystick.joy2_y1 > JOYSTICK_THRESHOLD)
    {
      motor[wheelieBar] = WHEELIE_BAR_POWER;
    }
    else if(joystick.joy2_y1 < -JOYSTICK_THRESHOLD)
    {
      motor[wheelieBar] = -WHEELIE_BAR_POWER;
    }
    else
    {
      motor[wheelieBar] = MOTOR_OFF;
    }

    // baton dumper
    if(joy2Btn(2))
    {
      // if joystick button 2 (controller 2) is pressed then servo motor 2 will "open"
      servo[goalArm] = GOAL_ARM_OPEN;
    }
    else
    {
      //if no buttons are pressed, then the servos will do nothing or go back automatically
      servo[goalArm] = GOAL_ARM_CLOSED;
    }
  }
}

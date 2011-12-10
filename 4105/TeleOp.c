#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S1,     ,                    sensorI2CMuxController)
#pragma config(Motor,  motorA,          motorA,        tmotorNormal, openLoop)
#pragma config(Motor,  motorB,          motorB,        tmotorNormal, openLoop)
#pragma config(Motor,  motorC,          motorC,        tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C1_1,     right,         tmotorNormal, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     whacker,        tmotorNormal, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     left,          tmotorNormal, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     intake,        tmotorNormal, openLoop)
#pragma config(Servo,  srvo_S1_C3_1,    grab,                 tServoStandard)
#pragma config(Servo,  srvo_S1_C3_4,    hopper,               tServoStandard)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/* $Id$ */

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.

#define SERVO_CHANGE_RATE 10
#define LED_ON 100
#define LED_OFF 0
#define JOYSTICK_THRESHOLD 10
#define INTAKE_POWER 100
#define MOTOR_OFF 0
#define GRAB_START 20
#define GRAB_OPEN  100
#define HOPPER_OPEN  180
#define HOPPER_CLOSED  255

/**
 * Initialize the robot.
 */
void initializeRobot()
{
  bFloatDuringInactiveMotorPWM = false;
  /*
  motor[motorA] = LED_ON;
  motor[motorB] = LED_ON;
  motor[motorC] = LED_ON;
  */
  motor[right] = MOTOR_OFF;
  motor[left] = MOTOR_OFF;
  motor[intake] = MOTOR_OFF;
  motor[whacker] = MOTOR_OFF;
  servo[grab] = GRAB_START;
  servo[hopper] = HOPPER_CLOSED;

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

    // 100% power
    motor[right] = joystick.joy1_y2;
    motor[left]= joystick.joy1_y1;
    /*
    motor[motorA] = LED_ON;
    motor[motorB] = LED_OFF;
    motor[motorC] = LED_OFF;
    */

    if(abs(joystick.joy2_y1) > JOYSTICK_THRESHOLD)
    {
      motor[whacker] = joystick.joy2_y1;
    }
    else
    {
      motor[whacker] = MOTOR_OFF;
    }
    // intake
    if(joy2Btn(2))
    {
      motor[intake] = INTAKE_POWER;
    }
    else if(joy2Btn(1))
    {
      motor[intake] = -INTAKE_POWER;
    }
    else
    {
      motor[intake] = MOTOR_OFF;
    }

    if(joy1Btn(6))
    {
      servo[grab] = GRAB_START;
    }
    else if(joy1Btn(8))
    {
      servo[grab] = GRAB_OPEN;
    }

    if(joy2Btn(6))
    {
      servo[hopper] = HOPPER_OPEN;
    }
    else
    {
      servo[hopper] = HOPPER_CLOSED;
    }
  }
}

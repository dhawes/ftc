#pragma config(Hubs,  S1, HTServo,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Sensor, S2,     HTGYRO,              sensorAnalogInactive)
#pragma config(Sensor, S3,     HTIRS2,              sensorI2CCustom)
#pragma config(Motor,  motorA,          green,        tmotorNormal, openLoop)
#pragma config(Motor,  motorB,          yellow,        tmotorNormal, openLoop)
#pragma config(Motor,  motorC,          red,        tmotorNormal, openLoop)
#pragma config(Servo,  srvo_S1_C1_1,    clawRelease,                 tServoStandard)
#pragma config(Servo,  srvo_S1_C1_2,    armRelease,                 tServoStandard)
#pragma config(Motor,  mtr_S1_C2_1,     right,          tmotorNormal, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     clawArm,          tmotorNormal, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     left,          tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     ballArm,          tmotorNormal, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C4_1,     spool,          tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C4_2,     intake,          tmotorNormal, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/* $Id$ */

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.

#define SERVO_CHANGE_RATE 10
#define LED_ON 100
#define LED_OFF 0
#define JOYSTICK_THRESHOLD 10
#define INTAKE_POWER 100
#define MOTOR_OFF 0
#define MOTOR_FULL 100
#define SPOOL_SPEED 50
#define GRAB_START 20
#define GRAB_OPEN  100
#define ARM_RELEASE_OPEN    120
#define ARM_RELEASE_CLOSED  255
#define CLAW_RELEASE_OPEN   186
#define CLAW_RELEASE_CLOSED 131
#define CLAW_SPEED 100

/**
 * Initialize the robot.
 */
void initializeRobot()
{
  bFloatDuringInactiveMotorPWM = false;
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

  return;
}

/**
 *
 */
task main()
{
  bool armReleaseOpen = false;

  initializeRobot(); // init

  waitForStart();   // wait for start of tele-op phase

  motor[green]  = LED_OFF;
  motor[yellow] = LED_OFF;
  motor[red]    = LED_OFF;

  while(true)
  {
    getJoystickSettings(joystick);

    // 100% power
    motor[left] = joystick.joy1_y1;
    motor[right]= joystick.joy1_y2;

    if(abs(joystick.joy2_y1) > JOYSTICK_THRESHOLD)
    {
      motor[ballArm] = joystick.joy2_y1;
    }
    else
    {
      motor[ballArm] = MOTOR_OFF;
    }
    // intake
    if(joy2Btn(2))
    {
      motor[intake] = INTAKE_POWER;
      motor[green]  = LED_OFF;
      motor[red]    = LED_ON;
    }
    else if(joy2Btn(1))
    {
      motor[intake] = -INTAKE_POWER;
      motor[green]  = LED_ON;
      motor[red]    = LED_OFF;
    }
    else
    {
      motor[intake] = MOTOR_OFF;
      motor[green]  = LED_OFF;
      motor[red]    = LED_OFF;
    }

    if(joy2Btn(4) && joy2Btn(5))
    {
      servo[clawRelease] = CLAW_RELEASE_OPEN;
    }
    else
    {
      servo[clawRelease] = CLAW_RELEASE_CLOSED;
    }

    if(joy2Btn(3) && joy2Btn(5))
    {
      servo[armRelease] = ARM_RELEASE_OPEN;
      armReleaseOpen = true;
    }
    else if(!armReleaseOpen)
    {
      servo[armRelease] = ARM_RELEASE_CLOSED;
    }

    if(joy2Btn(6))
    {
      motor[spool] = SPOOL_SPEED;
    }
    else if(joy2Btn(8))
    {
      motor[spool] = -SPOOL_SPEED;
    }
    else
    {
      motor[spool] = MOTOR_OFF;
    }

    if(abs(joystick.joy2_y2) > JOYSTICK_THRESHOLD)
    {
      if(joystick.joy2_y2 > 0)
      {
        motor[clawArm] = 20;
      }
      else
      {
        motor[clawArm] = -CLAW_SPEED;
      }
    }
    else
    {
      motor[clawArm] = MOTOR_OFF;
    }

    /*
    if(joy1Btn(6))
    {
      servo[grab] = GRAB_START;
      motor[yellow] = LED_OFF;
    }
    else if(joy1Btn(8))
    {
      servo[grab] = GRAB_OPEN;
      motor[yellow] = LED_ON;
    }

    if(joy2Btn(6))
    {
      servo[hopper1] = HOPPER1_OPEN;
      servo[hopper2] = HOPPER2_OPEN;
    }
    else
    {
      servo[hopper1] = HOPPER1_CLOSED;
      servo[hopper2] = HOPPER2_CLOSED;
    }
    */
  }
}

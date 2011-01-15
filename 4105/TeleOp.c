#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Motor,  motorA,          motorA,        tmotorNormal, openLoop)
#pragma config(Motor,  motorB,          motorB,        tmotorNormal, openLoop)
#pragma config(Motor,  motorC,          motorC,        tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C1_1,     motorD,        tmotorNormal, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motorE,        tmotorNormal, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     intake,        tmotorNormal, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     wheelieBar,    tmotorNormal, openLoop)
#pragma config(Servo,  srvo_S1_C3_1,    goalCapture1,          tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    goalCapture2,          tServoStandard)
#pragma config(Servo,  srvo_S1_C3_3,    goalArm,              tServoStandard)


#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.

#define GOAL_CAPTURE_1_UP 220
#define GOAL_CAPTURE_2_UP 50
#define GOAL_CAPTURE_1_DOWN 80
#define GOAL_CAPTURE_2_DOWN 250
#define GOAL_CAPTURE_INCREMENT 2
#define GOAL_ARM_CLOSED 68
#define GOAL_ARM_OPEN 0
#define SERVO_CHANGE_RATE 10
#define LED_ON 100
#define LED_OFF 0
#define JOYSTICK_THRESHOLD 10
#define INTAKE_POWER 30
#define WHEELIE_BAR_POWER 30
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
  servo[goalArm] = GOAL_ARM_CLOSED;
  servoChangeRate[goalCapture1] = SERVO_CHANGE_RATE;
  servoChangeRate[goalCapture2] = SERVO_CHANGE_RATE;
  servo[goalCapture1] = GOAL_CAPTURE_1_UP;
  servo[goalCapture2] = GOAL_CAPTURE_2_UP;

  return;
}

/**
 *
 */
task main()
{
  int sv1 = GOAL_CAPTURE_1_UP;
  int sv2 = GOAL_CAPTURE_2_UP;

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
      // only allow 30% power
      motor[motorD] = joystick.joy1_y2 * .3;
      motor[motorE] = joystick.joy1_y1 * .3;
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
      motor[intake] = INTAKE_POWER;
    }
    else if(joystick.joy2_y2 < -JOYSTICK_THRESHOLD)
    {
      motor[intake] = -INTAKE_POWER;
    }
    else
    {
      motor[intake] = MOTOR_OFF;
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

    // goal capture arm
    if(joystick.joy2_TopHat == 0)
    {
      sv1 = GOAL_CAPTURE_1_UP;
      sv2 = GOAL_CAPTURE_2_UP;
      servo[goalCapture1] = sv1;
      servo[goalCapture2] = sv2;
    }
    else if(joystick.joy2_TopHat == 4)
    {
      if(sv1 > GOAL_CAPTURE_1_DOWN)
      {
        sv1 -= GOAL_CAPTURE_INCREMENT;
        sv2 += GOAL_CAPTURE_INCREMENT;
        servo[goalCapture1] = sv1;
        servo[goalCapture2] = sv2;
      }
    }
    else
    {
      servo[goalCapture1] = sv1;
      servo[goalCapture2] = sv2;
    }
  }
}

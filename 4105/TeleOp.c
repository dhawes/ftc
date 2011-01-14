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
//#pragma config(Servo,  srvo_S1_C3_3,    goalArm,              tServoStandard)


#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.

/**
 * Initialize the robot.
 */
void initializeRobot()
{
  bFloatDuringInactiveMotorPWM = false;
  motor[motorA] = 100;
  motor[motorB] = 100;
  motor[motorC] = 100;
  //servo[goalArm] = 68;
  servoChangeRate[goalCapture1] = 10;
  servoChangeRate[goalCapture2] = 10;
  servo[goalCapture1] = 220;
  servo[goalCapture2] = 50;


  return;
}

/**
 *
 */
task main()
{
  bool wheelieBarDown = false;
  initializeRobot();
  waitForStart();   // wait for start of tele-op phase

  while(true)
  {
    getJoystickSettings(joystick);

    if(joy1Btn(8))
    {
      // only allow 20% power
      motor[motorD] = joystick.joy1_y2 * .2;
      motor[motorE] = joystick.joy1_y1 * .2;
      motor[motorA] = 0;
      motor[motorB] = 0;
      motor[motorC] = 100;
    }
    else if(joy1Btn(6))
    {
      // only allow 30% power
      motor[motorD] = joystick.joy1_y2 * .3;
      motor[motorE] = joystick.joy1_y1 * .3;
      motor[motorA] = 0;
      motor[motorB] = 100;
      motor[motorC] = 0;
    }
    else
    {
      // 100% power
      motor[motorD] = joystick.joy1_y2;
      motor[motorE] = joystick.joy1_y1;
      motor[motorA] = 100;
      motor[motorB] = 0;
      motor[motorC] = 0;
    }

    // figure out how to calibrate joystick so we don't have to check a threshold
    if(joystick.joy2_y2 > 10)
    {
      motor[intake] = 30;
    }
    else if(joystick.joy2_y2 < -10)
    {
      motor[intake] = -30;
    }
    else
    {
      motor[intake] = 0;
    }

    // wheelie bar up/down
    if(joystick.joy2_y1 > 10)
    {
      motor[wheelieBar] = 30;
    }
    else if(joystick.joy2_y1 < -10)
    {
      motor[wheelieBar] = -30;
    }
    else
    {
      motor[wheelieBar] = 0;
    }

    if(joy2Btn(2))
    {
      // if joystick button 2 (controller 2) is pressed then servo motor 2 will "open"
      //servo[goalArm] = 0;
    }
    else
    {
      //if no buttons are pressed, then the servos will do nothing or go back automatically
      //servo[goalArm] = 68;
      /*
      servo[wheelieBar1] = 0;
      servo[wheelieBar2] = 0;
      */
    }
    if(joystick.joy2_TopHat == 0)
    {
      servo[goalCapture1] = 220;
      servo[goalCapture2] = 50;
    }
    else if(joystick.joy2_TopHat == 4)
    {
      int sv1 = ServoValue[goalCapture1];
      int sv2 = ServoValue[goalCapture2];
      if(sv1 > 80)
      {
        servo[goalCapture1] = sv1 - 2;
        servo[goalCapture2] = sv2 + 2;
      }
    }
  }
}

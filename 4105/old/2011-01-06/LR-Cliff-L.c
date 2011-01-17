/* LR-Cliff-L.c */

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.
#include "Autonomous.c"

/**
 *
 */
task main()
{
  initializeRobot();

  waitForStart(); // Wait for the beginning of autonomous phase.

  nMotorEncoder[motorE] = 0;  //clear the TETRIX encoders in motors D and E
  nMotorEncoder[motorD] = 0;

  motor[motorE] = 0; //turn both motors off
  motor[motorD] = 0;

  wait1Msec(1000);

  // 1 rotation is about 2', 1440 on the encoder
  move(7000, 50);
  wait1Msec(600);

  leftTurn();
  wait1Msec(600);

  batonLoader();
}
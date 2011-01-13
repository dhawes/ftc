/* Autonomous.h */

/* Function prototypes */
void initializeRobot();
void rightTurn();
void leftTurn();
void rightQuarterTurn();
void leftQuarterTurn();
void move(int distance, int speed);
void batonLoader();

/* Common defines */

#define LEFT_TURN_ENCODER  750
#define RIGHT_TURN_ENCODER 750
#define TURN_SPEED         25
#define INTAKE_SPEED       -30
#define RIGHT_180_ENCODER  1550
#define WHEELIE_BAR_SPEED  30
#define WHEELIE_BAR_TIME   200

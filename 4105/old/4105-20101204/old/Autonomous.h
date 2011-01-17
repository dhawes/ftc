/* Common autonomous prototypes and defines */

#define LEFT_TURN_ENCODER  750
#define RIGHT_TURN_ENCODER 750
#define TURN_SPEED         25
#define RIGHT_180_ENCODER  1550

void rightTurn();
void leftTurn();
void rightQuarterTurn();
void leftQuarterTurn();
void turnInPlaceRight();
void move(int distance, int speed);
void batonLoader();

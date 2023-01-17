#include "pinout.h"

#define SPR     200          // Motor steps per revolution
#define RSPR    2000         // Rotator steps per revolution
#define SDELAY  5          // Delay between HIGH/LOW

void test_move() 
{
  for (int i = 0; i < SPR; i++) {
    // These four lines result in 1 step:
    digitalWrite(STP, HIGH);
    delayMicroseconds(SDELAY);
    digitalWrite(STP, LOW);
    delay(1);
  }

  // Change rotation to clockwise
  digitalWrite(DIR, HIGH);

  for (int i = 0; i < SPR; i++) {
    digitalWrite(STP, HIGH);
    delayMicroseconds(SDELAY);
    digitalWrite(STP, LOW);
    delay(1);
  }

  // Change rotation to counterclockwise
  delay(50);
  digitalWrite(DIR, LOW);
}
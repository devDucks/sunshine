#include "pinout.h"

# define SPR 200

void test_move() 
{
    for (int i = 0; i < SPR; i++) {
    // These four lines result in 1 step:
      digitalWrite(STP, HIGH);
      delayMicroseconds(1000);
      digitalWrite(STP, LOW);
      delayMicroseconds(1000);
  }
}
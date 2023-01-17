#ifndef parsing_h
#define parsing_h

#include "pinout.h"
#include "version.h"
#include "movement.h"

#define CMD_MAX_LENGTH 9

char version[6] = {58, 86, VER_MAJ, VER_MIN, VER_PAT, 35};

void parse_command(char cmd[])
{
  int i = 1;

  // If the command doesn't start with : it's either malformed
  // or not parsed correctly
  if (cmd[0] != ':') {
    Serial.write(":E1#");
    return;
  }

  // Find the position of #
  for (i; i < CMD_MAX_LENGTH; i++) {
    if (cmd[i] == '#') {
      break;
    }
  }

  if (i == CMD_MAX_LENGTH && cmd[i] != '#') {
    Serial.write(":E2#");
    return;
  }

  switch (cmd[1]) {
    // Case 'P'
    case 80:
      Serial.write(":OK#");
      break;
    // Case 'T'
    case 84:
      test_move();
      Serial.write(":OK#");
      break;
    // Case 'V'
    case 86:
      Serial.write(version);
      break;
    // Case 'D'
    case 68:
      switch (cmd[2]) {
        // Case '0'
        case 48:
          digitalWrite(DIR, LOW);
          Serial.write(":OK#");
          break;
        // Case '1'
        case 49:
          digitalWrite(DIR, HIGH);
          Serial.write(":OK#");
          break;
        // Case 'R'
        case 82:
          int val = digitalRead(DIR);
          if (val == 0) {
            Serial.write(":D0#");
          } else {
            Serial.write(":D1#");
          }
          break;
        // Errors
        default:
          Serial.write(":E4#");
          break;
      }
      break;
    // Case 'M'
    case 77:
      switch (cmd[2]) {
        // Case 'R'
        case 82:
          Serial.write(":MR#");
          break;
        // Case 'L'
        case 76:
          Serial.write(":ML#");
          break;
      }
      break;
    // Errors
    default:
      Serial.write(":E3#");
      break;
  }
}
#endif

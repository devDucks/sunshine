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

  if (cmd[1] == 'P') {
    Serial.write(":OK#");
    return;
  }

  if (cmd[1] == 'T') {
    test_move();
    return;
  }

  if (cmd[1] == 'D') {
    if (cmd[2] == '0') {
      digitalWrite(DIR, LOW);
      return;
    }

    if (cmd[2] == '1') {
      digitalWrite(DIR, HIGH);
      return;
    }

    if (cmd[2] == 'R') {
      int val = digitalRead(DIR);
      if (val == 0) {
        Serial.write(":D0#");
      } else {
        Serial.write(":D1#");
      }
      return;
    }
  }

  if (cmd[1] == 'M') {
    if (cmd[2] == 'R') {
      Serial.write(":MR#");
      return;
    }

    if (cmd[2] == 'L') {
      Serial.write(":ML#");
      return;
    }
  }

  if (cmd[1] == 'V') {
    Serial.write(version);
    return;
  }

  Serial.write(":E3#");
}

#endif

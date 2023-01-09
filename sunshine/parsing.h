#ifndef parsing_h
#define parsing_h

#include "version.h"

#define CMD_MAX_LENGTH 9

char version[6] = {58, 86, VER_MAJ, VER_MIN, VER_PAT, 35};

void parse_command(char cmd[])
{
  int i = 1;

  Serial.print("The command is ");
  Serial.println(cmd[1]);

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
  }

  if (cmd[1] == 'M') {
    if (cmd[2] == 'R') {
      Serial.write(":MR#");
    }

    if (cmd[2] == 'L') {
      Serial.write(":ML#");
    }
  }

  if (cmd[1] == 'V') {
    Serial.write(version);
  }
}

#endif
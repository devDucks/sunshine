#include "parsing.h"


char tempByte;  // for incoming serial data
int eoc = 0;
int idx = 0;

char cmdBuf[CMD_MAX_LENGTH];

void setup() {
  Serial.begin(9600);
}

void loop() {
  // send data only when you receive data:
  if (!Serial.available()) {
    delay(500);
  } else {
    while (Serial.available() && !eoc) {
      tempByte = Serial.read();
      if (tempByte != "#" && tempByte != ":") {
        cmdBuf[idx++] = tempByte;

        if (idx >= CMD_MAX_LENGTH) {
          idx = CMD_MAX_LENGTH - 1;
        }
      } else {
        if (tempByte == "#") {
          eoc = 1;
        }
      }
    }
    
    parse_command(cmdBuf);

    // Reset index and command buffer for next reading
    memset(cmdBuf, 0, CMD_MAX_LENGTH);
    idx = 0;
  }
  delay(1000);
}

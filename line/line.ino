#include <Servo.h>
// Used in Body / Runner

#include "Body.h"
#include "Pins.h"

// Configuration
const Pins pins_paulie = {{3, 4, 5, 6, 7}, 8, {13, 12}, {10, 9}};
const Pins& pins = pins_paulie;

enum Mode { WAIT, FORWARD, LEFT, RIGHT, LEFT_STRONG, RIGHT_STRONG };
Mode mode = WAIT;

Body body;

void setup() {
  Serial.begin(9600);
  
  body.init(pins);
  body.run(0, 0);
}

void loop() {
  // Set mode  
  if (mode == WAIT && body.button_pressed()) {
    mode = FORWARD;
  }
  
  if (mode != WAIT) {
    mode = FORWARD;
    if (body.sensor_l() && !body.sensor_r()) {
      if (body.sensor_c()) {
        mode = LEFT;
      } else {
        mode = LEFT_STRONG;
      }
    }
    if (body.sensor_r() && !body.sensor_l()) {
      if (body.sensor_c()) {
        mode = RIGHT;
      } else {
        mode = RIGHT_STRONG;
      }
    }
  }
  
  // Execute mode
  switch (mode) {
    case WAIT:
      Serial.println("WAIT");
      body.run(0, 0);
      body.light(true, true);
      break;
    case FORWARD:
      Serial.println("FORWARD");
      body.run(90, 90);
      body.light(false, false);
      break;
    case LEFT:
      Serial.println("LEFT");
      body.run(0, 90);
      body.light(true, false);
      break;
    case RIGHT:
      Serial.println("RIGHT");
      body.run(90, 0);
      body.light(false, true);
      break;
    case LEFT_STRONG:
      Serial.println("LEFT_STRONG");
      body.run(-90, 90);
      body.light(true, false);
      break;
    case RIGHT_STRONG:
      Serial.println("RIGHT_STRONG");
      body.run(90, -90);
      body.light(false, true);
      break;
  }
}

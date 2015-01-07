#include <Servo.h>
// Used in Body / Runner

#include "Body.h"
#include "Pins.h"

// Configuration
const Pins pins_paulie = {{3, 4, 5, 6, 7}, 8, {13, 12}, {10, 9}};
const Pins& pins = pins_paulie;

enum Mode { WAIT, FORWARD, LEFT, RIGHT, LEFT_STRONG, RIGHT_STRONG };
Mode mode = WAIT;

enum ModeFollow { FOLLOW_CENTER, FOLLOW_LEFT, FOLLOW_RIGHT };
ModeFollow mode_follow = FOLLOW_CENTER;
const unsigned long follow_delay = 1000;
unsigned long follow_center_time = 0;

Body body;

void setup() {
  Serial.begin(9600);
  
  body.init(pins);
  body.run(0, 0);
}

void loop() {
  const unsigned long time = millis();
  
  // Set mode_follow
  if (body.sensor_ll() && !body.sensor_rr() && mode_follow == FOLLOW_CENTER) {
    mode_follow = FOLLOW_LEFT;
    follow_center_time = time + follow_delay;
  }
  if (body.sensor_rr() && !body.sensor_ll() && mode_follow == FOLLOW_CENTER) {
    mode_follow = FOLLOW_RIGHT;
    follow_center_time = time + follow_delay;
  }
  if (time >= follow_center_time) {
    mode_follow = FOLLOW_CENTER;
  }
  
  // Set move mode
  const boolean l = body.sensor_l();
  const boolean c = body.sensor_c();
  const boolean r = body.sensor_r();
  
  if (l && mode_follow == FOLLOW_LEFT) {
    mode = LEFT;
  }
  if (r && mode_follow == FOLLOW_RIGHT) {
    mode = RIGHT;
  }
  if (c && !l && !r) {
    mode = FORWARD;
  }
  if (l && !r && !c) {
    mode = LEFT_STRONG;
  }
  if (r && !l && !c) {
    mode = RIGHT_STRONG;
  }
  if (c && l && !r && mode_follow == FOLLOW_RIGHT) {
    mode = FORWARD;
  }
  if (c && r && !l && mode_follow == FOLLOW_LEFT) {
    mode = FORWARD;
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
      break;
    case LEFT:
      Serial.println("LEFT");
      body.run(0, 90);
      break;
    case RIGHT:
      Serial.println("RIGHT");
      body.run(90, 0);
      break;
    case LEFT_STRONG:
      Serial.println("LEFT_STRONG");
      body.run(-90, 90);
      break;
    case RIGHT_STRONG:
      Serial.println("RIGHT_STRONG");
      body.run(90, -90);
      break;
  }
  
  if (mode != WAIT) {
    switch (mode_follow) {
      case FOLLOW_CENTER:
        body.light(false, false);
        break;
      case FOLLOW_LEFT:
        body.light(true, false);
        break;
      case FOLLOW_RIGHT:
        body.light(false, true);
        break;
    }
  }
}

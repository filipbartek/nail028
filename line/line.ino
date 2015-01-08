#include <limits.h>
// ULONG_MAX

#include <Servo.h>
// Used in Body / Runner

#include "Body.h"
#include "Pins.h"

// Configuration
// Pins: {sensor[5], button, servo[2], diod[2]}
const Pins pins_paulie = {{3, 4, 5, 6, 7}, 8, {13, 12}, {10, 9}};
const Pins& pins = pins_paulie;

const long velocity = 90;

// Mode of movement - low level
enum Mode { WAIT, FORWARD, LEFT, RIGHT, LEFT_STRONG, RIGHT_STRONG };
// WAIT: Wait for button press
Mode mode = WAIT;

// Mode of line following - high level
enum ModeFollow { FOLLOW_CENTER, FOLLOW_LEFT, FOLLOW_RIGHT };
ModeFollow mode_follow = FOLLOW_CENTER;
const unsigned long follow_delay = 1000;
unsigned long follow_center_time = ULONG_MAX; // Auxiliary - timer

Body body;

// Realize starting behavior
boolean starting = true; // Wait for button press once we reach starting line
boolean start_mark = false; // We're on the starting line right now

void setup() {
  Serial.begin(9600);
  
  body.init(pins);
  body.run(0, 0);
}

void loop() {
  const unsigned long time = millis();
  
  // Process marks (sensors ll and rr)
  
  // Starting behavior
  if (body.sensor_ll() && body.sensor_rr()) {
    if (!start_mark) {
      // We've just reached the start mark
      // (Only executed once in each lap)
      start_mark = true;
      if (starting) {
        mode = WAIT;
      }
    }
  } else {
    start_mark = false;
  }
  
  // Follow mode updates
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
    follow_center_time = ULONG_MAX;
  }
  
  // Register button press
  if (mode == WAIT && body.button_pressed()) {
    mode = FORWARD;
    if (start_mark) {
      starting = false;
    }
  }
  
  // Shorten names of sensor states
  const boolean l = body.sensor_l();
  const boolean c = body.sensor_c();
  const boolean r = body.sensor_r();
  
  // Works like magic!
  if (mode != WAIT) {
    if (l) {
      // May change to turning left
      if (!r && !c) {
        mode = LEFT_STRONG;
      } else if (mode_follow == FOLLOW_LEFT) {
        mode = LEFT;
      }
    }
    if (r) {
      // May change to turning right
      if (!l && !c) {
        mode = RIGHT_STRONG;
      } else if (mode_follow == FOLLOW_RIGHT) {
        mode = RIGHT;
      }
    }
    if (c) {
      // May change to going straight ahead
      if (!l && !r) {
        mode = FORWARD;
      }
      if (l && !r && mode_follow == FOLLOW_RIGHT) {
        mode = FORWARD;
      }
      if (r && !l && mode_follow == FOLLOW_LEFT) {
        mode = FORWARD;
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
      body.run(velocity, velocity);
      break;
    case LEFT:
      Serial.println("LEFT");
      body.run(0, velocity);
      break;
    case RIGHT:
      Serial.println("RIGHT");
      body.run(velocity, 0);
      break;
    case LEFT_STRONG:
      Serial.println("LEFT_STRONG");
      body.run(-velocity, velocity);
      break;
    case RIGHT_STRONG:
      Serial.println("RIGHT_STRONG");
      body.run(velocity, -velocity);
      break;
  }
  
  // Indicate follow mode using diods
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

#include <limits.h>
// ULONG_MAX

#include <Servo.h>
// Used in Body / Runner

#include "Body.h"
#include "Pins.h"
#include "update_mode.h"

// Configuration
// Pins: {sensor[5], button, servo[2], diod[2]}
const Pins pins_paulie = {{3, 4, 5, 6, 7}, 8, {13, 12}, {10, 9}};
const Pins& pins = pins_paulie;

const long velocity = 90;

Mode mode = WAIT;

ModeFollow mode_follow = FOLLOW_CENTER;

ModeFollow follow_next_mode = FOLLOW_CENTER;
unsigned long follow_next_time = ULONG_MAX;
const unsigned long follow_attack = 200;
const unsigned long follow_release = 2000;

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
  if (body.sensor_ll() && body.sensor_rr() && (body.sensor_l() + body.sensor_r() + body.sensor_c()) == 1) {
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
  if (time >= follow_next_time) {
    mode_follow = follow_next_mode;
    if (mode_follow != FOLLOW_CENTER) {
      follow_next_mode = FOLLOW_CENTER;
      follow_next_time = time + follow_release;
    } else {
      follow_next_time = ULONG_MAX;
    }
  }
  if (body.sensor_ll() && !body.sensor_rr() && mode_follow == FOLLOW_CENTER && follow_next_time == ULONG_MAX) {
    follow_next_mode = FOLLOW_LEFT;
    follow_next_time = time + follow_attack;
  }
  if (body.sensor_rr() && !body.sensor_ll() && mode_follow == FOLLOW_CENTER && follow_next_time == ULONG_MAX) {
    follow_next_mode = FOLLOW_RIGHT;
    follow_next_time = time + follow_attack;
  }
  
  // Register button press
  if (mode == WAIT && body.button_pressed()) {
    mode = FORWARD;
    if (start_mark) {
      starting = false;
      // Prevent the start mark from changing the follow mode
      follow_next_mode = FOLLOW_CENTER;
      follow_next_time = time + 200;
    }
  }
  
  update_mode(mode, mode_follow, body);
  
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
      body.run(-5, velocity);
      break;
    case RIGHT_STRONG:
      Serial.println("RIGHT_STRONG");
      body.run(velocity, -5);
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

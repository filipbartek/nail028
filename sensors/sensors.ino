#include <Servo.h>
// Used in Runner.h

#include "Behavior.h"
#include "Runner.h"

// Misa:
// sensors: 7 11 9 10 8
// button: 6

// Marketka:
// sensors: 8 11 9 10 7
// button: 6

struct SensorPins {
  int ll;
  int l;
  int c;
  int r;
  int rr;
};

const int sensor_l_pin = 11;
const int sensor_r_pin = 10;
const int sensor_c_pin = 9;
const int sensor_ll_pin = 8;
const int sensor_rr_pin = 7;
// 0: light returns; white surface
// 1: light gets lost; black surface

SensorPins sensor_pins;

const int button_pin = 6;

// Mode:
boolean wait_for_button = true;
boolean dir = true;
boolean after_junction = false;
// true: right
// false: left

int val_button_prev = 1;

boolean turn_l_prev = false;
boolean turn_r_prev = false;

Runner runner;

void setup() {
  // Initialize debug output channel
  Serial.begin(9600);
  
  runner.init(13, 12);
  // Left servo (13): 0: back, 180: forward
  // Right servo (12): 180: back, 0: forward
  runner.run(0, 0);
  
  pinMode(button_pin, INPUT_PULLUP);
  
  sensor_pins.l = 11;
  sensor_pins.r = 10;
  sensor_pins.c = 9;
  sensor_pins.ll = 7;
  sensor_pins.rr = 8;
  
  pinMode(sensor_pins.l, INPUT);
  pinMode(sensor_pins.r, INPUT);
  pinMode(sensor_pins.c, INPUT);
  pinMode(sensor_pins.ll, INPUT);
  pinMode(sensor_pins.rr, INPUT);
}

enum FollowMode { CENTER, LEFT, RIGHT };
FollowMode follow_mode = CENTER;

BehaviorFollowCenter behavior_follow_center(runner);
BehaviorFollowLeft behavior_follow_left(runner);
BehaviorFollowRight behavior_follow_right(runner);
Behavior * behavior = &behavior_follow_center;

boolean turn_left_prev = false;
boolean turn_right_prev = false;

const unsigned long delay_center = 1000;
unsigned long time_center = 0;

void loop() {
  const int val_ll = digitalRead(sensor_pins.ll);
  const int val_rr = digitalRead(sensor_pins.rr);
  
  if (val_ll && !val_rr && follow_mode == CENTER) {
    follow_mode = LEFT;
    time_center = millis() + delay_center;
  }
  if (val_rr && !val_ll && follow_mode == CENTER) {
    follow_mode = RIGHT;
    time_center = millis() + delay_center;
  }
  
  if (time_center != 0 && millis() > time_center) {
    follow_mode = CENTER;
    time_center = 0;
  }
  
  switch (follow_mode) {
    case CENTER:
      behavior = &behavior_follow_center;
      break;
    case LEFT:
      behavior = &behavior_follow_left;
      break;
    case RIGHT:
      behavior = &behavior_follow_right;
      break;
  }

  const int val_l = digitalRead(sensor_pins.l);
  const int val_c = digitalRead(sensor_pins.c);
  const int val_r = digitalRead(sensor_pins.r);
  behavior->tick(val_l, val_c, val_r);
}


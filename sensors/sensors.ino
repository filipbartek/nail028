#include <Servo.h>
// Used in "Runner.h"

#include "Runner.h"

const int sensor_l_pin = 11;
const int sensor_r_pin = 10;
const int sensor_c_pin = 9;
// 0: light returns; white surface
// 1: light gets lost; black surface

const int servo_l_pin = 13;
const int servo_r_pin = 12;

const int button_pin = 8;

boolean dir = true;
// true: right
// false: left

int val_button_prev = 1;

// TODO: Check if possible.
Runner runner(servo_l_pin, servo_r_pin);

void setup() {
  // Initialize debug output channel
  Serial.begin(9600);
  
  pinMode(sensor_l_pin, INPUT);
  pinMode(sensor_r_pin, INPUT);
  pinMode(sensor_c_pin, INPUT);
  
  pinMode(button_pin, INPUT_PULLUP);
}

void loop() {
  int val_l = digitalRead(sensor_l_pin);
  int val_r = digitalRead(sensor_r_pin);
  int val_c = digitalRead(sensor_c_pin);
  
  if (val_c && !val_l && !val_r) {
    runner.go_forward();
  }
  if (!val_l && val_r) {
    if (val_c) {
      if (!dir) {
        runner.go_forward();
      } else {
        runner.go_right_weak();
      }
    } else {
      runner.go_right_strong();
    }
  }
  if (!val_r && val_l) {
    if (val_c) {
      if (dir) {
        runner.go_forward();
      } else {
        runner.go_left_weak();
      }
    } else {
      runner.go_left_strong();
    }
  }
  if (val_l && val_r) {
    // choose by `dir`
    if (dir) {
      runner.go_right_weak();
    } else {
      runner.go_left_weak();
    }
  }
  if (!val_l && !val_c && !val_r) {
    runner.go_back();
  }
  
  int val_button = digitalRead(button_pin);
  // 0: pressed
  // 1: released
  
  // Flip `dir` if button was pressed in this frame.
  if (!val_button && val_button_prev) {
    // The button was pressed just now
    dir = !dir;
  }
  val_button_prev = val_button;
  
  Serial.println(dir);
  
  //delay(1);
}


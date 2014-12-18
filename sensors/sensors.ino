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

// Paulie:
// sensors: 3 4 5 6 7
// button: 8
// diods: 9 10

struct SensorPins {
  int ll;
  int l;
  int c;
  int r;
  int rr;
};

// 0: light returns; white surface
// 1: light gets lost; black surface

const int diod_l = 10;
const int diod_r = 9;

SensorPins sensor_pins;

const int button_pin = 8;

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
  
  sensor_pins.ll = 3;
  sensor_pins.l = 4;
  sensor_pins.c = 5;
  sensor_pins.r = 6;
  sensor_pins.rr = 7;
  
  pinMode(sensor_pins.ll, INPUT);
  pinMode(sensor_pins.l, INPUT);
  pinMode(sensor_pins.c, INPUT);
  pinMode(sensor_pins.r, INPUT);
  pinMode(sensor_pins.rr, INPUT);
  
  pinMode(diod_l, OUTPUT);
  pinMode(diod_r, OUTPUT);

  digitalWrite(diod_l, HIGH);
  digitalWrite(diod_r, HIGH);
}

enum FollowMode { WAIT, CENTER, LEFT, RIGHT };
FollowMode follow_mode = WAIT;

BehaviorNull behavior_null(runner);
BehaviorFollowCenter behavior_follow_center(runner);
BehaviorFollowLeft behavior_follow_left(runner);
BehaviorFollowRight behavior_follow_right(runner);
Behavior * behavior = &behavior_null;

boolean turn_left_prev = false;
boolean turn_right_prev = false;

const unsigned long delay_center = 1000;
unsigned long time_center = 0;

void loop() {
  const int val_ll = digitalRead(sensor_pins.ll);
  const int val_rr = digitalRead(sensor_pins.rr);
  
  const boolean ll_black = val_ll == 0;
  const boolean rr_black = val_rr == 0;
  
  const int val_button = digitalRead(button_pin);
  // 0: pressed
  // 1: released
  
  const boolean button_pressed = val_button == 0;
  
  unsigned long time = millis();
  
  if (follow_mode == WAIT && button_pressed) {
    follow_mode = CENTER;
    digitalWrite(diod_l, HIGH);
    digitalWrite(diod_r, HIGH);
  }
  
  if (ll_black && !rr_black && follow_mode == CENTER) {
    follow_mode = LEFT;
    digitalWrite(diod_l, HIGH);
    digitalWrite(diod_r, LOW);
    time_center = time + delay_center;
  }
  if (rr_black && !ll_black && follow_mode == CENTER) {
    follow_mode = RIGHT;
    digitalWrite(diod_r, HIGH);
    digitalWrite(diod_l, LOW);
    time_center = time + delay_center;
  }
  
  if (time_center != 0 && time > time_center) {
    follow_mode = CENTER;
    digitalWrite(diod_l, HIGH);
    digitalWrite(diod_r, HIGH);
    time_center = 0;
  }
  
  switch (follow_mode) {
    case WAIT:
      behavior = &behavior_null;
      break;
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
  
  const boolean l_black = val_l == 0;
  const boolean c_black = val_c == 0;
  const boolean r_black = val_r == 0;
  
  behavior->tick(l_black, c_black, r_black);
}


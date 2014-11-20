#include <Servo.h>
// Servo

Servo servo_l; // 0: back, 180: forward
Servo servo_r; // 180: back, 0: forward

const int sensor_l_pin = 11;
const int sensor_r_pin = 10;
const int sensor_c_pin = 9;
// 0: light returns; white surface
// 1: light gets lost; black surface

const int button_pin = 8;

boolean dir = true;
// true: right
// false: left

int val_button_prev = 1;

void setup() {
  // Initialize debug output channel
  Serial.begin(9600);
  
  servo_l.attach(13);
  servo_r.attach(12);
  servo_l.write(90);
  servo_r.write(90);
  
  pinMode(sensor_l_pin, INPUT);
  pinMode(sensor_r_pin, INPUT);
  pinMode(sensor_c_pin, INPUT);
  
  pinMode(button_pin, INPUT_PULLUP);
}

// left, right:
// 0: stop
// 90: full forward
// -90: full back
void run(long left, long right) {
  long power_l = map(left, -90, 90, 0, 180);
  long power_r = map(right, -90, 90, 180, 0);
  servo_l.write(power_l);
  servo_r.write(power_r);
}

void loop() {
  const int val_l = digitalRead(sensor_l_pin);
  const int val_r = digitalRead(sensor_r_pin);
  const int val_c = digitalRead(sensor_c_pin);
  // default: go back slowly
  long left = -5;
  long right = -5;
  if (val_c && !val_l && !val_r) {
    // go forward
    left = 90;
    right = 90;
  }
  if (!val_l && val_r) {
    // go right
    left = 90;
    if (val_c) {
      if (!dir) {
        // forward
        right = 90;
      } else {
        // right weak
        right = 0;
      }
    } else {
      // right strong
      right = -90;
    }
  }
  if (!val_r && val_l) {
    // go left
    right = 90;
    if (val_c) {
      if (dir) {
        // forward
        left = 90;
      } else {
        // left weak
        left = 0;
      }
    } else {
      // left strong
      left = -90;
    }
  }
  if (val_l && val_r) {
    // choose by `dir`
    if (dir) {
      // go right weak
      left = 90;
      right = 0;
    } else {
      // go left weak
      right = 90;
      left = 0;
    }
  }
  run(left, right);
  
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


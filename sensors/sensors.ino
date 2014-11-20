#include <Servo.h>
// Servo

Servo servo_l; // 0: back, 180: forward
Servo servo_r; // 180: back, 0: forward
 
// sensors: 7 11 9 10 8
// button: 6

const int sensor_l_pin = 11;
const int sensor_r_pin = 10;
const int sensor_c_pin = 9;
const int sensor_ll_pin = 7;
const int sensor_rr_pin = 8;
// 0: light returns; white surface
// 1: light gets lost; black surface

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
  const int val_ll = digitalRead(sensor_ll_pin);
  const int val_rr = digitalRead(sensor_rr_pin);
  
  const boolean turn_l = val_ll && !val_rr;
  const boolean turn_r = val_rr && !val_ll;
  
  if (turn_l && !turn_l_prev) {
    // TODO: Consider considering dir here.
    if (after_junction) {
      after_junction = false;
    } else {
      dir = false;
      after_junction = true;
    }
  }
  
  if (turn_r && !turn_r_prev) {
    if (after_junction) {
      after_junction = false;
    } else {
      dir = true;
      after_junction = true;
    }
  }
  
  turn_l_prev = turn_l;
  turn_r_prev = turn_r;
  
  // TODO: Implement dir oblivious mode for period after `after_junction` is set to false.
  // (?)
  
  if (val_ll && val_rr && !wait_for_button) {
    wait_for_button = true;
    run(0, 0);
  }
  
  if (wait_for_button) {
    // Wait
    
    const int val_button = digitalRead(button_pin);
    // 0: pressed
    // 1: released
    
    if (!val_button) {
      // Button pressed
      // Wait is over
      wait_for_button = false;
      after_junction = false;
      // TODO: Add timeout
    }
  }
  if (!wait_for_button) {
    // Run
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
  }
  
  Serial.println(dir);
}


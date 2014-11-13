#ifndef RUNNER_H
#define RUNNER_H

#include <Arduino.h>
// map

#include <Servo.h>
// Servo

class Runner {
  private:
  Servo servo_l; // 0: back, 180: forward
  Servo servo_r; // 180: back, 0: forward
  
  const long power_forward;
  const long power_back;
  const long power_stop;
  const long power_back_strong;
  
  void go_side_weak(const boolean& side_right) {
    go(power_stop, power_forward, side_right);
  }
  
  void go_side_strong(const boolean& side_right) {
    go(power_back_strong, power_forward, side_right);
  }
  
  public:
  Runner(const int& servo_l_pin, const int& servo_r_pin,
         const long& power_forward = 90,
         const long& power_back = -5,
         const long& power_stop = 0,
         const long& power_back_strong = -90);
  
  // left, right:
  // 0: stop
  // 90: full forward
  // -90: full back
  void go(const long& left, const long& right,
          const boolean& flip = false);
  
  void go_back() {
    go(power_back, power_back);
  }
  
  void go_forward() {
    go(power_forward, power_forward);
  }
  
  void go_left_weak() {
    go_side_weak(false);
  }
  
  void go_left_strong() {
    go_side_strong(false);
  }
  
  void go_right_weak() {
    go_side_weak(true);
  }
  
  void go_right_strong() {
    go_side_strong(true);
  }
};

#endif // RUNNER_H


#ifndef RUNNER_H
#define RUNNER_H

#include <Arduino.h>

#include <Servo.h>
// Servo

class Runner {
private:
  Servo servo_l;
  Servo servo_r;
public:
  void init(const int& servo_l_pin, const int& servo_r_pin) {
    servo_l.attach(servo_l_pin);
    servo_r.attach(servo_r_pin);
  }
  
  // left, right:
  // 0: stop
  // 90: full forward
  // -90: full back
  void run(const long& l, const long& r) {
    const long power_l = map(l, -90, 90, 0, 180);
    const long power_r = map(r, -90, 90, 180, 0);
    servo_l.write(power_l);
    servo_r.write(power_r);
  }
};

#endif // RUNNER_H


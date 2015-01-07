#ifndef RUNNER_H
#define RUNNER_H

#include <Servo.h>

class Runner {
private:
  Servo servo_l;
  Servo servo_r;
public:
  void init(const int& servo_l_pin, const int& servo_r_pin);
  
  // left, right:
  // 0: stop
  // 90: full forward
  // -90: full back
  void run(const long& l, const long& r);
};

#endif // RUNNER_H

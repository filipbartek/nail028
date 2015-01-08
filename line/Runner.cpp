#include "Runner.h"

#include <Arduino.h>
// map

void
Runner::init(const int& servo_l_pin, const int& servo_r_pin) {
  servo_l.attach(servo_l_pin);
  servo_r.attach(servo_r_pin);
}

void
Runner::run(const long& l, const long& r) {
  servo_l.write(map(l, -90, 90, 0, 180));
  servo_r.write(map(r, -90, 90, 180, 0));
}

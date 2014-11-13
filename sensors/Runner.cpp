#include "Runner.h"

static void flip_vals(long& left, long& right) {
  long aux = left;
  left = right;
  right = aux;
}

Runner::Runner(const int& servo_l_pin, const int& servo_r_pin,
               const long& power_forward,
               const long& power_back,
               const long& power_stop,
               const long& power_back_strong)
: power_forward(power_forward), power_back(power_back),
  power_stop(power_stop), power_back_strong(power_back_strong)
{
  servo_l.attach(servo_l_pin);
  servo_r.attach(servo_r_pin);
  // Stop the servos
  servo_l.write(90);
  servo_r.write(90);
}

void
Runner::go(const long& left, const long& right,
           const boolean& flip) {
  long power_l = map(left, -90, 90, 0, 180);
  long power_r = map(right, -90, 90, 180, 0);
  if (flip) {
    flip_vals(power_l, power_r);
  }
  servo_l.write(power_l);
  servo_r.write(power_r);
}


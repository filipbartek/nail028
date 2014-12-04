#ifndef BEHAVIOR_H
#define BEHAVIOR_H

#include "Runner.h"

struct SensorPins {
  int ll;
  int l;
  int c;
  int r;
  int rr;
};

class Behavior {
public:
  Behavior(const SensorPins& sensor_pins, const int& button_pin, Runner& runner)
    : sensor_pins(sensor_pins), button_pin(button_pin), runner(runner) {}
  void tick() = 0;
private:
  const SensorPins& sensor_pins;
  const int& button_pin;
  Runner& runner;
};

class BehaviorNull: public Behavior {
  void tick() {}
};

class BehaviorFollowLine: public Behavior {
  void tick() {
    const int val_l = digitalRead(sensor_pins.l);
    const int val_c = digitalRead(sensor_pins.c);
    const int val_r = digitalRead(sensor_pins.r);
  }
};

#endif // BEHAVIOR_H


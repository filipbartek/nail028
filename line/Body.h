#ifndef BODY_H
#define BODY_H

#include <Arduino.h>
// boolean

#include "Pins.h"
#include "Runner.h"

class Body {
public:
  void init(const Pins& pins);
  void run(const long& l, const long& r);
  void light(const boolean& l, const boolean& r);
  boolean button_pressed();
  
  // Return true iff sensor detects a line
  boolean sensor_l();
  boolean sensor_c();
  boolean sensor_r();
private:
  Pins pins;
  Runner runner;
};

#endif // BODY_H

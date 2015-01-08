#ifndef BODY_H
#define BODY_H

#include <Arduino.h>
// boolean

#include "Pins.h"
#include "Runner.h"

// Represents body of the robot - sensors and actuators
class Body {
public:
  void init(const Pins& pins);
  
  void run(const long& l, const long& r);
  void light(const boolean& l, const boolean& r);
  
  // Returns true iff button is pressed
  boolean button_pressed();
  
  // Return true iff sensor detects a line
  boolean sensor_l();
  boolean sensor_c();
  boolean sensor_r();
  boolean sensor_ll();
  boolean sensor_rr();
private:
  Pins pins;
  Runner runner;
};

#endif // BODY_H

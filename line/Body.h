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
  void light(const boolean& l, const boolean& r) const;
  
  // Returns true iff button is pressed
  boolean button_pressed() const;
  
  // Return true iff sensor detects a line
  boolean sensor_l() const;
  boolean sensor_c() const;
  boolean sensor_r() const;
  boolean sensor_ll() const;
  boolean sensor_rr() const;
private:
  Pins pins;
  Runner runner;
};

#endif // BODY_H

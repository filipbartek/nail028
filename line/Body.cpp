#include "Body.h"

#include <Arduino.h>
// INPUT, OUTPUT, INPUT_PULLUP, HIGH

void
Body::init(const Pins& pins) {
  this->pins = pins;
  
  // sensor
  pinMode(pins.sensor.ll, INPUT);
  pinMode(pins.sensor.l, INPUT);
  pinMode(pins.sensor.c, INPUT);
  pinMode(pins.sensor.r, INPUT);
  pinMode(pins.sensor.rr, INPUT);
  
  // button
  pinMode(pins.button, INPUT_PULLUP);
  
  // diod
  pinMode(pins.diod.l, OUTPUT);
  pinMode(pins.diod.r, OUTPUT);
  digitalWrite(pins.diod.l, HIGH);
  digitalWrite(pins.diod.r, HIGH);
  
  // servo / runner
  runner.init(pins.servo.l, pins.servo.r);
}

void
Body::run(const long& l, const long& r) {
  runner.run(l, r);
}

void
Body::light(const boolean& l, const boolean& r) const {
  digitalWrite(pins.diod.l, l ? HIGH : LOW);
  digitalWrite(pins.diod.r, r ? HIGH : LOW);
}

boolean
Body::button_pressed() const {
  return digitalRead(pins.button) == 0;
}

boolean
Body::sensor_l() const {
  return digitalRead(pins.sensor.l) == 0;
}

boolean
Body::sensor_c() const {
  return digitalRead(pins.sensor.c) == 0;
}

boolean
Body::sensor_r() const {
  return digitalRead(pins.sensor.r) == 0;
}

boolean
Body::sensor_ll() const {
  return digitalRead(pins.sensor.ll) == 0;
}

boolean
Body::sensor_rr() const {
  return digitalRead(pins.sensor.rr) == 0;
}

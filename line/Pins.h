#ifndef PINS_H
#define PINS_H

struct SensorPins {
  int ll;
  int l;
  int c;
  int r;
  int rr;
};

struct ServoPins {
  int l;
  int r;
};

struct DiodPins {
  int l;
  int r;
};

struct Pins {
  SensorPins sensor;
  int button;
  ServoPins servo;
  DiodPins diod;
};

#endif // PINS_H

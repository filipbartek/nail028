// Configuration
const int pins_input[] = {3, 4, 5, 6, 7};
const int pins_input_pullup[] = {8};
const int pins_output[] = {9, 10};
const int delay_ms = 500;

// Deduced values
const size_t pins_input_n = sizeof(pins_input) / sizeof(int);
const size_t pins_input_pullup_n = sizeof(pins_input_pullup) / sizeof(int);
const size_t pins_output_n = sizeof(pins_output) / sizeof(int);

// mode type is int, as defined in Arduino.h
void set_mode(const int * const pins, const size_t& n, const int& mode) {
  for (int i = 0; i < n; ++i) {
    const int& pin = pins[i];
    pinMode(pin, mode);
  }
}

void print_ints(const int * const ints, const size_t& n) {
  for (int i = 0; i < n; ++i) {
    const int& pin = ints[i];
    if (i > 0) {
      Serial.print(" ");
    }
    Serial.print(pin);
  }
  Serial.println();
}

void print_vals(const int * const pins, const size_t& n) {
  for (int i = 0; i < n; ++i) {
    const int& pin = pins[i];
    const int val = digitalRead(pin);
    if (i > 0) {
      Serial.print(" ");
    }
    Serial.print(val);
  }
  Serial.println();
}

void setup() {
  Serial.begin(9600);
  
  set_mode(pins_input, pins_input_n, INPUT);
  set_mode(pins_input_pullup, pins_input_pullup_n, INPUT_PULLUP);
  set_mode(pins_output, pins_output_n, OUTPUT);
  
  Serial.println("pins_input:");
  print_ints(pins_input, pins_input_n);
  
  Serial.println("pins_input_pullup:");
  print_ints(pins_input_pullup, pins_input_pullup_n);
  
  Serial.println("pins_output:");
  print_ints(pins_output, pins_output_n);
}

void loop() {
  print_vals(pins_input, pins_input_n);
  print_vals(pins_input_pullup, pins_input_pullup_n);
  
  const int output_value = (millis() / 1000) % 2; // TODO: Use constants HIGH and LOW
  
  const int * const pins = pins_output;
  const size_t& n = pins_output_n;
  for (int i = 0; i < n; ++i) {
    const int& pin = pins[i];
    digitalWrite(pin, output_value);
  }
  
  delay(delay_ms);
}

A line following robot using Boe-Bot and Arduino

## Course
This project is a part of the course
[NAIL028 Úvod do robotiky](https://is.cuni.cz/studium/predmety/index.php?do=predmet&kod=NAIL028) (winter 2014)
on [Charles University](http://cuni.cz/) in Prague.

* [Home page](http://ulita.ms.mff.cuni.cz/pub/predn/nail028/)
* [SIS page](https://is.cuni.cz/studium/predmety/index.php?do=predmet&kod=NAIL028)

## Hardware
* [Boe-Bot](http://www.parallax.com/product/boe-bot-robot)
    * a pair of wheels powered by a pair of servo motors
* [Arduino Uno](http://arduino.cc/en/Main/arduinoBoardUno)
    * [ATmega328](http://www.atmel.com/devices/atmega328.aspx)
* an array of sensors

### Sensors
#### 5
```
      red  black
||||| |    |
76543 5V   GND
```

#### 3
Each sensor has three wires:
* brown: ground
* yellow: power (5V)
* green or white: output

## Arduino
* [Home page](http://arduino.cc/)
* [Reference](http://arduino.cc/en/Reference)
    * [Servo](http://arduino.cc/en/Reference/Servo)

## Interface between the robot and a computer
Serial port `/dev/ttyACM0`

Use `putty` to listen for the messages from the robot.

## Sage
[Sage Math Cloud project](https://cloud.sagemath.com/projects/f18cd484-a3f3-4c7d-a485-4c8f09c8b652/files/)

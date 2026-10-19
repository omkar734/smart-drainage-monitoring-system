Smart Drainage Overflow Monitoring and Early Warning System

Project Overview

This project is an Arduino Nano-based prototype that monitors water levels using an HC-SR04 ultrasonic sensor. A 16×2 I2C LCD displays the estimated water-level percentage and status. An LED and buzzer provide warnings when configured thresholds are reached.

The prototype demonstrates how embedded programming can be used for water-level monitoring and overflow warnings.

Features

- Measures distance using an HC-SR04 ultrasonic sensor.
- Calculates estimated water-level percentage.
- Displays water level and status on a 16×2 I2C LCD.
- Turns on an LED at the warning threshold.
- Activates a buzzer at the danger threshold.
- Displays sensor readings through the Serial Monitor.

Components Used

- Arduino Nano
- HC-SR04 ultrasonic sensor
- 16×2 I2C LCD
- LED
- 220Ω or 330Ω LED resistor
- Compatible buzzer
- Jumper wires and breadboard

Pin Connections

Component| Arduino Nano
HC-SR04 TRIG| D11
HC-SR04 ECHO| D12
LCD SDA| A4
LCD SCL| A5
LCD VCC| 5V
LCD GND| GND
LED anode through resistor| D8
Buzzer positive| D7
Buzzer negative| GND

All components share a common ground.

Operating Logic

- NORMAL: Water level below 60%.
- WARNING: Water level from 60% to below 80%; LED ON.
- DANGER: Water level at or above 80%; LED and buzzer ON.

These are configurable prototype thresholds.

Water-Level Calculation

The estimated water level is calculated using:

Water Level (%) = ((H - D) / H) × 100

Where:

- H is the calibrated distance from the sensor to the container bottom when empty.
- D is the measured distance from the sensor to the water surface.

The current prototype uses a calibrated empty distance of approximately 10.3 cm. This value should be adjusted if the mounting height changes.

Software and Concepts

- Arduino C/C++
- GPIO control
- Ultrasonic sensor interfacing
- I2C communication
- Conditional statements
- Timing and pulse measurement
- Serial debugging

How to Run

1. Open "drainage_monitor.ino" in Arduino IDE.
2. Install a compatible LiquidCrystal_I2C library.
3. Select Arduino Nano and the correct COM port.
4. Check all wiring before powering the circuit.
5. Upload the sketch.
6. Open the Serial Monitor at 9600 baud.
7. Observe the LCD, LED, and buzzer while testing different water levels.

Limitations

This is an educational prototype for simulated drainage water-level monitoring. It is not a certified safety system and does not independently detect physical drainage blockages.

Author

Built as a hands-on Embedded Systems learning project using Arduino Nano.

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int trigPin = 11;
const int echoPin = 12;
const int ledPin = 8;
const int buzzerPin = 7;

const float height = 10.3;  // Calibrated empty distance in cm

long duration;
float distance;
float level;

void setup()
{
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(ledPin, OUTPUT);
    pinMode(buzzerPin, OUTPUT);

    Serial.begin(9600);

    lcd.init();
    lcd.backlight();

    digitalWrite(ledPin, LOW);
    digitalWrite(buzzerPin, LOW);

    lcd.setCursor(0, 0);
    lcd.print("DRAIN MONITOR");
    lcd.setCursor(0, 1);
    lcd.print("Starting...");
    delay(1500);
    lcd.clear();
}

void loop()
{
    // Send ultrasonic trigger pulse
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Measure echo duration
    duration = pulseIn(echoPin, HIGH, 30000);

    if (duration == 0)
    {
        digitalWrite(ledPin, LOW);
        digitalWrite(buzzerPin, LOW);

        lcd.setCursor(0, 0);
        lcd.print("Sensor Error    ");
        lcd.setCursor(0, 1);
        lcd.print("Check sensor    ");

        Serial.println("No echo detected");
    }
    else
    {
        // Calculate distance in centimetres
        distance = duration * 0.0343 / 2;

        // Calculate water-level percentage
        level = (height - distance) / height * 100;

        if (level < 0)
            level = 0;

        if (level > 100)
            level = 100;

        // Display water level
        lcd.setCursor(0, 0);
        lcd.print("Water Level: ");
        lcd.print(level, 0);
        lcd.print("%   ");

        // Normal, warning and danger states
        if (level >= 80)
        {
            lcd.setCursor(0, 1);
            lcd.print("Status: DANGER  ");

            digitalWrite(ledPin, HIGH);
            digitalWrite(buzzerPin, HIGH);
        }
        else if (level >= 60)
        {
            lcd.setCursor(0, 1);
            lcd.print("Status: WARNING ");

            digitalWrite(ledPin, HIGH);
            digitalWrite(buzzerPin, LOW);
        }
        else
        {
            lcd.setCursor(0, 1);
            lcd.print("Status: NORMAL  ");

            digitalWrite(ledPin, LOW);
            digitalWrite(buzzerPin, LOW);
        }

        // Display readings in Serial Monitor
        Serial.print("Distance: ");
        Serial.print(distance, 1);
        Serial.print(" cm | Water Level: ");
        Serial.print(level, 1);
        Serial.println("%");
    }

    delay(300);
}

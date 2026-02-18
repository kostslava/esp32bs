// include libraries
#include <Adafruit_SH110X.h>
#include <Adafruit_GFX.h>

// ultrasonic sensor pins
#define trig 15
#define echo 16

// oled screen
#define sda 9
#define scl 10

Adafruit_SH1106G display = Adafruit_SH1106G(128, 64, &Wire);

void setup() {
  //define output pins for sensor
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  //define pins for display
  Wire.begin(sda, scl);
  display.begin(0x3c);

  //start serial monitor
  Serial.begin(115200);
}

void loop() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  int distance = pulseIn(echo, HIGH) / 58;
  display.clearDisplay();
  display.setCursor(20, 10);
  display.setTextColor(SH110X_WHITE);
  display.setTextSize(1);
  display.print("Distance: ");
  display.print(distance);
  display.println(" cm");

  if (distance <= 5) {
    display.setCursor(10, 30);
    display.setTextSize(2);
    display.print("TOO CLOSE");
  }

  display.display();
  delay(100);
}

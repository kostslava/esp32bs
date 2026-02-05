#include <Adafruit_NeoPixel.h>

#define upled 7
#define leftled 6
#define midled 5
#define rightled 4
#define lowled 8

#define sw 12
#define vry 11
#define vrx 10


void setup() {
  Serial.begin(115200);  // Start serial, do this once
  pinMode(upled, OUTPUT);
  pinMode(leftled, OUTPUT);
  pinMode(midled, OUTPUT);
  pinMode(rightled, OUTPUT);
  pinMode(lowled, OUTPUT);
  pinMode(sw, INPUT_PULLUP);

}


void loop() {
  int vrx_amt = analogRead(vrx);
  int vry_amt = analogRead(vry);

  if (vrx_amt <= 50) {digitalWrite(leftled, HIGH);}
  else {digitalWrite(leftled, LOW);}

  if (vrx_amt >= 4090) {digitalWrite(rightled, HIGH);}
  else {digitalWrite(rightled, LOW);}

  if (vry_amt <= 50) {digitalWrite(upled, HIGH);}
  else {digitalWrite(upled, LOW);}

  if (vry_amt >= 4090) {digitalWrite(lowled, HIGH);}
  else {digitalWrite(lowled, LOW);}

  if (digitalRead(sw) == LOW) {digitalWrite(midled, HIGH);}
  else {digitalWrite(midled, LOW);}
  delay(10);  // Add at end of loop()
}



#include <Adafruit_NeoPixel.h>

#define l1 8
#define l2 18
#define l3 17
#define l4 16
#define l5 15
#define l6 7
#define l7 6
#define l8 5
#define l9 4

#define sw 12
#define vry 11
#define vrx 10


void setup() {
  Serial.begin(115200);  // Start serial, do this once
  pinMode(l1, OUTPUT);
  pinMode(l2, OUTPUT);
  pinMode(l3, OUTPUT);
  pinMode(l4, OUTPUT);
  pinMode(l5, OUTPUT);
  pinMode(l6, OUTPUT);
  pinMode(l7, OUTPUT);
  pinMode(l8, OUTPUT);
  pinMode(l9, OUTPUT);
  pinMode(sw, INPUT_PULLUP);

}


void loop() {
  int vrx_amt = analogRead(vrx);
  int vry_amt = analogRead(vry);

    digitalWrite(l1, LOW);
    digitalWrite(l2, LOW);
    digitalWrite(l3, LOW);
    digitalWrite(l4, LOW);
    digitalWrite(l5, LOW);
    digitalWrite(l6, LOW);
    digitalWrite(l7, LOW);
    digitalWrite(l8, LOW);
    digitalWrite(l9, LOW);
  
  if (vrx_amt >= 100) {
    digitalWrite(l1, HIGH);
  }

  if (vrx_amt >= 500) {
    digitalWrite(l2, HIGH);
  }

  if (vrx_amt >= 1000) {
    digitalWrite(l3, HIGH);
  }

  if (vrx_amt >= 1500) {
    digitalWrite(l4, HIGH);
  }

  if (vrx_amt >= 2000) {
    digitalWrite(l5, HIGH);
  }

  if (vrx_amt >= 2500) {
    digitalWrite(l6, HIGH);
  }

  if (vrx_amt >= 3000) {
    digitalWrite(l7, HIGH);
  }

  if (vrx_amt >= 3500) {
    digitalWrite(l8, HIGH);
  }

  if (vrx_amt >= 4000) {
    digitalWrite(l9, HIGH);
  }
  delay(10);  // Add at end of loop()
}



#include <ESP32Servo.h>

#define servoPinElbow 9
#define servoPin360 10
#define servoPinArm 11
#define servoPinHand 12

Servo servoElbow;
Servo servo360;
Servo servoArm;
Servo servoHand;

void setup() {
  Serial.begin(115200);

  // Set frequency for both servos
  servoElbow.setPeriodHertz(50);
  servo360.setPeriodHertz(50);
  servoArm.setPeriodHertz(50);
  servoHand.setPeriodHertz(50);

  // Attach 180° servo on pin 14
  int channel1 = servoElbow.attach(servoPinElbow, 500, 2400);
  int channel2 = servo360.attach(servoPin360);
  int channel3 = servoArm.attach(servoPinArm, 500, 2400);
  int channel4 = servoHand.attach(servoPinHand, 500, 2400);
}

void loop() {
  // Sweep 180° servo from 0 to 180
  for (int i = 7; i <= 11; i++) {
    Serial.print("Angle: ");
    Serial.println(i * 10);
    servoElbow.write(i * 10);
    servo360.write(88.5);
    servoArm.write(i * 10);
    servoHand.write(i * 10);
    delay(500);
  }

  for (int i = 11; i >= 7; i--) {
    Serial.print("Angle: ");
    Serial.println(i * 10);
    servoElbow.write(i * 10);
    servo360.write(98.5);
    servoArm.write(i * 10);
    servoHand.write(i * 10);
    delay(500);
  }
}

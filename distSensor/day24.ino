// include libraries
#include <Adafruit_SH110X.h>
#include <Adafruit_GFX.h>

// ultrasonic sensor pins
#define trig 15
#define echo 16

// oled screen
#define sda 9
#define scl 10

// buttons
#define scrollBtn 6

//define the display
Adafruit_SH1106G display = Adafruit_SH1106G(128, 64, &Wire);

//define variables
bool curScrollBtnState = HIGH;
bool lastScrollBtnState = HIGH;
int mathRate = 58; //58 for cm, 148 for inches
int distance = 0; //define distance

String mathType = "cm";

void setup() {
  //define output pins for sensor
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  //define pins for display
  Wire.begin(sda, scl);
  display.begin(0x3c);

  //define pins for buttons
  pinMode(scrollBtn, INPUT_PULLUP);

  //start serial monitor
  Serial.begin(115200);
}

void loop() {
  //run button check
  buttonStateCheck();

  //run sensor thing
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  distance = pulseIn(echo, HIGH) / mathRate;

  //display changes
  display.clearDisplay();
  display.setCursor(20, 10);
  display.setTextColor(SH110X_WHITE);
  display.setTextSize(1);
  display.print("Distance: ");
  display.print(distance);
  display.print(" ");
  display.println(mathType);

  if (distance <= 290 / mathRate) {
    display.setCursor(10, 30);
    display.setTextSize(2);
    display.print("TOO CLOSE");
  }

  display.display();
  delay(100);
  buttonStateReset();
}

void buttonStateCheck() {
  curScrollBtnState = digitalRead(scrollBtn);
  if (curScrollBtnState == LOW && lastScrollBtnState == HIGH) {
    if (mathRate == 58) {
      mathType = "in";
      mathRate = 148;
    } else {
      mathType = "cm";
      mathRate = 58;
    }
  }
}

void buttonStateReset() {
  lastScrollBtnState = curScrollBtnState;
}

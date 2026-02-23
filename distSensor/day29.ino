// include libraries
#include <Adafruit_SH110X.h>
#include <Adafruit_GFX.h>
#include <Adafruit_AHTX0.h>

// ultrasonic sensor pins
#define trig 15
#define echo 16

// oled screen
#define sda 9
#define scl 10

// buttons
#define scrollBtn 6
#define backBtn 7

//define the display
Adafruit_SH1106G display = Adafruit_SH1106G(128, 64, &Wire);

//define the aht sensor
Adafruit_AHTX0 aht;

//define variables
bool curScrollBtnState = HIGH;
bool lastScrollBtnState = HIGH;
bool curBackBtnState = HIGH;
bool lastBackBtnState = HIGH;
int appState = 0;
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
  
  //define aht sensor
  aht.begin(); 

  //define pins for buttons
  pinMode(scrollBtn, INPUT_PULLUP);
  pinMode(backBtn, INPUT_PULLUP);

  //start serial monitor
  Serial.begin(115200);
}

void loop() {
  curScrollBtnState = digitalRead(scrollBtn);
  if (curScrollBtnState == LOW && lastScrollBtnState == HIGH) {
    if (appState == 0) {
      appState = 1;
    }
    else if (appState == 1) {
      appState = 0;
    }
  }

  if (appState == 0) {
    distMesure();
  } 
  if (appState == 1) {
    tempMesure();
  }
  buttonStateReset();

}

void distMesure() {
  //run button check
  mesureTypeCheck();

  //run sensor thing
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  distance = pulseIn(echo, HIGH) / mathRate;

  //display updates
  display.clearDisplay();
  display.setCursor(20, 7);
  display.setTextColor(SH110X_WHITE);
  display.setTextSize(1);
  display.print("Distance: ");
  display.print(distance);
  display.print(" ");
  display.println(mathType);
  display.drawRect(0, 0, 128, 64, SH110X_WHITE);

  if (distance <= 290 / mathRate) {
    display.setCursor(11, 25);
    display.setTextSize(2);
    display.print("TOO CLOSE");
  }

  display.display();
  delay(100);
}

void tempMesure() {
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp); // populate temp and humidity objects with fresh data

  display.clearDisplay();
  display.drawRect(0, 0, 128, 64, SH110X_WHITE);

  display.setTextColor(SH110X_WHITE);
  display.setTextWrap(false);
  display.setCursor(13, 7);
  display.print("Temperature: ");
  display.print(temp.temperature, 1);
  display.print("C");

  display.setCursor(22, 18);
  display.print("Humidity: ");
  display.print(humidity.relative_humidity, 1);
  display.print("%");

  display.display();
  delay(100);
}

void mesureTypeCheck() {
  curBackBtnState = digitalRead(backBtn);
  if (curBackBtnState == LOW && lastBackBtnState == HIGH) {
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
  lastBackBtnState = curBackBtnState;
}

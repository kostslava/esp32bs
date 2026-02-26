// include libraries
#include <Adafruit_SH110X.h>
#include <Adafruit_GFX.h>
#include <Adafruit_AHTX0.h>
#include <Org_01.h>

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

// thermometer | 18x18 
const unsigned char tempMap [] PROGMEM = {
	0x00, 0x00, 0x80, 0x00, 0x39, 0x40, 0x00, 0x40, 0x80, 0x38, 0x40, 0x00, 0x44, 0x40, 0x00, 0x44, 
	0x40, 0x00, 0x46, 0x38, 0x00, 0x54, 0x00, 0x00, 0x56, 0x00, 0x00, 0x54, 0x00, 0x00, 0x56, 0x00, 
	0x00, 0x54, 0x00, 0x00, 0x56, 0x00, 0x00, 0x92, 0x00, 0x00, 0xba, 0x00, 0x00, 0x82, 0x00, 0x00, 
	0x44, 0x00, 0x00, 0x38, 0x00, 0x00
};

// humidity | 16x12 
const unsigned char humidMap [] PROGMEM = {
	0x08, 0x11, 0x14, 0x02, 0x2e, 0x04, 0x2e, 0x08, 0x5f, 0x11, 0x5f, 0x00, 0xbf, 0x80, 0xff, 0x80, 
	0xff, 0x80, 0x7f, 0x00, 0x7f, 0x00, 0x3e, 0x00
};

// ruler | 19x6 
const unsigned char rulerMap [] PROGMEM = {
	0xff, 0xff, 0xe0, 0x80, 0x00, 0x20, 0x80, 0x00, 0x20, 0x81, 0x01, 0x20, 0x91, 0x11, 0x20, 0xff, 
	0xff, 0xe0
};



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
  display.setTextColor(1);
  display.setTextSize(1);
  display.setTextWrap(false);
  display.setFont(&Org_01);
  display.setCursor(40, 25);
  display.print("Distance: ");
  display.print(distance);
  display.print(" ");
  display.println(mathType);
  display.drawRect(0, 0, 128, 64, SH110X_WHITE);

  if (distance <= 290 / mathRate) {
    display.setTextSize(2);
    display.setCursor(11, 41);
    display.print("TOO CLOSE");
  }

  display.drawBitmap(15, 20, rulerMap, 19, 6, 1);

  display.display();
  delay(100);
}

void tempMesure() {
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp); // populate temp and humidity objects with fresh data

  mesureTypeCheck();
  display.clearDisplay();
  display.drawRect(0, 0, 128, 64, 1);

  display.setTextColor(1);
  display.setTextWrap(false);
  display.setFont(&Org_01);
  display.setCursor(48, 20);
  display.setTextSize(1);
  display.print("Temp: ");
  if (mathType == "in") {display.print((temp.temperature * 1.8 + 32), 1); display.print("F");} 
  else {display.print(temp.temperature, 1); display.print("C");}

  display.setCursor(41, 44);
  display.print("Humidity: ");
  display.print(humidity.relative_humidity, 1);
  display.print("%");

  display.drawBitmap(26, 8, tempMap, 18, 18, 1);
  display.drawBitmap(20, 36, humidMap, 16, 12, 1);

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

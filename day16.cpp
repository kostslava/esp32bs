#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>

#define TFT_CS 13
#define TFT_DC 18
#define TFT_RST 17
#define TFT_SCLK 15
#define TFT_MOSI 16
#define TFT_BL 14
#define touchPin 7
#define VRx 6
#define VRy 5
#define SW 4

Adafruit_ST7789 tft(TFT_CS, TFT_DC, TFT_RST);

const int xMid = 1950;
const int yMid = 1950;

int xCursor = 20;
int yCursor = 20;
int xIn = 0;
int yIn = 0;
int xDiff = 0;
int yDiff = 0;

void setup() {
  Serial.begin(115200);  // Start serial, do this once
  pinMode(touchPin, INPUT);
  SPI.begin(TFT_SCLK, -1, TFT_MOSI, TFT_CS); //start spi with tft
  ledcAttach(TFT_BL, 5000, 8);
  ledcWrite(TFT_BL, 100);
  tft.init(240, 240);
  tft.setRotation(0);
  tft.fillScreen(ST77XX_BLACK);
}

void loop() {
  cursorLocationUpdate(5);
  //touchpin detection
  bool curTouchState = digitalRead(touchPin);

  if (curTouchState == HIGH) {
    //lets say i check the state of the click, and if it clicked in a certain area it will open smth WHILE the rest of the animation is playing
    for (int i = 0; i < 4 ; i++) {
      cursorLocationUpdate(5 - i);
    }
    for (int i = 0; i < 4 ; i++) {
      cursorLocationUpdate(1 + i);
    }
    for (int i = 0; i < 3; i++) {
      cursorLocationUpdate(5 + (i * 3));
    }
    for (int i = 0; i < 5; i++) {
      cursorLocationUpdate(11 - (i * 2));
    }
  }
}

void cursorLocationUpdate(int radius) {
  //calculate joystick location
  xIn = analogRead(VRx);
  yIn = analogRead(VRy);
  xDiff = xMid - xIn;
  yDiff = yMid - yIn;

  //check if cursor will go out of screen for x
  if (xDiff > 100 || xDiff < -100) {
    xCursor = xCursor - ((xDiff / 15) / 18); //change location

    if (xCursor > 230 || xCursor < 10) { //if location bad go back
      xCursor = xCursor + ((xDiff / 15) / 18);
    }
  }

  //check if cursor will go out of screen for y
  if (yDiff > 100 || yDiff < -100) {
    yCursor = yCursor - ((yDiff / 15) / 18); //change location

    if (yCursor > 230 || yCursor < 10) { //if location bad go back
      yCursor = yCursor + ((yDiff / 15) / 18);
    } 
  }

  //draw the cursor
  tft.drawCircle(xCursor, yCursor, radius, ST77XX_WHITE);

  //last cursor erased after a little bit of time
  delay(20);
  tft.drawCircle(xCursor, yCursor, radius, ST77XX_BLACK);
  
}

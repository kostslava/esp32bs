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

enum WindowState {STATE_HOME, STATE_SETTINGS, STATE_BROWSER, STATE_GAME};

Adafruit_ST7789 tft(TFT_CS, TFT_DC, TFT_RST);
WindowState currentWindowState = STATE_HOME;

const int xMid = 1950;
const int yMid = 1950;

const int APP_COUNT = 9;
const int appX[APP_COUNT] = {10,  90, 170, 10,  90, 170, 10,  90, 170};
const int appY[APP_COUNT] = {10,  10,  10, 90,  90,  90, 170, 170, 170};
const int appW[APP_COUNT] = {60,  60,  60, 60,  60,  60,  60,  60,  60};
const int appH[APP_COUNT] = {60,  60,  60, 60,  60,  60,  60,  60,  60};
const uint16_t appColor[APP_COUNT] = {ST77XX_RED, ST77XX_BLUE, ST77XX_MAGENTA, ST77XX_RED, ST77XX_BLUE, ST77XX_MAGENTA, ST77XX_RED, ST77XX_BLUE, ST77XX_MAGENTA};
bool appNeedSet[APP_COUNT] = {true, true, true, true, true, true, true, true, true};
bool appHover[APP_COUNT] = {false, false, false, false, false, false, false, false, false};

int xCursor = 20;
int yCursor = 20;
int xIn = 0;
int yIn = 0;
int xDiff = 0;
int yDiff = 0;
int cursorRadius = 5;

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
  checkWindowState();
  cursorLocationUpdate(cursorRadius);
  checkTouchBtn();
}

void checkTouchBtn() {
  bool curTouchState = digitalRead(touchPin);
  if (curTouchState == HIGH) {
    for (int i = 0; i < 4 ; i++) {
      cursorAnimUpdate(cursorRadius - i);
    }
    for (int i = 0; i < 4 ; i++) {
      cursorAnimUpdate(cursorRadius - 4 + i);
    }
    for (int i = 0; i < 3; i++) {
      cursorAnimUpdate(cursorRadius + (i * 3));
    }
    for (int i = 0; i < 5; i++) {
      cursorAnimUpdate(cursorRadius + 6 - (i * 2));
    }
  }
}

void cursorLocationUpdate(int radius) {
  //calculate joystick location
  xIn = analogRead(VRx);
  yIn = analogRead(VRy);
  xDiff = xMid - xIn;
  yDiff = yMid - yIn;

  calculateBorders();

  //draw the cursor
  tft.drawCircle(xCursor, yCursor, radius, ST77XX_WHITE);

  //last cursor erased after a little bit of time
  delay(20);
  tft.drawCircle(xCursor, yCursor, radius, ST77XX_BLACK);
}

void cursorAnimUpdate(int radius) {
  //draw the cursor
  tft.drawCircle(xCursor, yCursor, radius, ST77XX_WHITE);

  //last cursor erased after a little bit of time
  delay(20);
  tft.drawCircle(xCursor, yCursor, radius, ST77XX_BLACK);
}

void checkAppHover() {
  for (int i = 0; i < 9; i++) {
    if (appHover[i] == true) {
      if (xCursor < appX[i] || xCursor > appX[i] + appW[i] || yCursor < appY[i] || yCursor > appY[i] + appH[i]) {
        tft.drawRect(appX[i] - 3, appY[i] - 3, appW[i] + 6, appH[i] + 6, ST77XX_BLACK);
        tft.drawRect(appX[i] - 2, appY[i] - 2, appW[i] + 4, appH[i] + 4, ST77XX_BLACK);
        tft.drawRect(appX[i] - 1, appY[i] - 1, appW[i] + 2, appH[i] + 2, ST77XX_BLACK);
        appHover[i] = false;
        appNeedSet[i] = true;
      }
    }

    if (xCursor > appX[i] - 5 && xCursor < appX[i] + appW[i] + 5 && yCursor > appY[i] - 5 && yCursor < appY[i] + appH[i] + 5) {
      appNeedSet[i] = true;
    }

    if (xCursor > appX[i] && xCursor < appX[i] + appW[i] && yCursor > appY[i] && yCursor < appY[i] + appH[i]) {
      appHover[i] = true;
    }
  }
}

void calculateBorders() {
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
}

void checkWindowState() {
  if (currentWindowState == STATE_HOME) {
    displayHome();
  } 
}

void displayHome() {
  checkAppHover();
  for (int i = 0; i < 9; i++) {
    if (appNeedSet[i] == true) {
      if (appHover[i] == true) {
        tft.fillRect(appX[i] - 3, appY[i] - 3, appW[i] + 6, appH[i] + 6, appColor[i]);
      } else {
        tft.fillRect(appX[i], appY[i], appW[i], appH[i], appColor[i]);
        appNeedSet[i] = false;
      }
    }
  }
}

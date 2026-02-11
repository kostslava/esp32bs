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
void (*appDrawFuncs[APP_COUNT])(int, int, int, int, bool);
void (*appOpen[APP_COUNT])(int, int);

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
  appDrawFuncs[0] = drawSettings;
  appDrawFuncs[1] = drawGoon;
  appDrawFuncs[2] = drawGoon;
  appDrawFuncs[3] = drawGoon;
  appDrawFuncs[4] = drawGoon;
  appDrawFuncs[5] = drawGoon;
  appDrawFuncs[6] = drawGoon;
  appDrawFuncs[7] = drawGoon;
  appDrawFuncs[8] = drawGoon;

  appOpen[0] = openSettings;
  appOpen[1] = openSettings;
  appOpen[2] = openSettings;
  appOpen[3] = openSettings;
  appOpen[4] = openSettings;
  appOpen[5] = openSettings;
  appOpen[6] = openSettings;
  appOpen[7] = openSettings;
  appOpen[8] = openSettings;
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
    if (currentWindowState == STATE_HOME) {
      for (int i = 0; i < 9; i++) {
        if (appHover[i] == true) {
          appOpen[i](xCursor, yCursor);
        }  
      }
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

  if (currentWindowState == STATE_SETTINGS) {
    displaySettings();
  }
}

void displayHome() {
  checkAppHover();
  for (int i = 0; i < 9; i++) {
    if (appNeedSet[i] == true) {
      appDrawFuncs[i](appX[i], appY[i], appW[i], appH[i], appHover[i]);
      appNeedSet[i] = false;
    }
  }
}

void displaySettings() {
  tft.fillRect(10, 10, 220, 220, ST77XX_BLUE);
  tft.fillCircle(110, 110, 10, ST77XX_CYAN);

}

void drawSettings(int x, int y, int w, int h, bool hovered) {
  if (hovered == true) {
    w = w + 6;
    h = h + 6;
    x = x - 3;
    y = y - 3;
  }
  tft.fillRect(x, y, w, h, ST77XX_BLUE);
  tft.fillCircle(x + w / 2, y + h / 2, h / 6, ST77XX_CYAN);
}
void drawGoon(int x, int y, int w, int h, bool hovered) {
  if (hovered == true) {
    w = w + 6;
    h = h + 6;
    x = x - 3;
    y = y - 3;
  }
  tft.fillRect(x, y, w, h, ST77XX_RED);
  tft.fillCircle(x + w / 2, y + h / 2, h / 6, ST77XX_BLUE);
}
void drawStore(int x, int y, int w, int h, bool hovered);

void openSettings(int x, int y) {
  for (int i = 0; i < 10; i++) {
    tft.fillCircle(x, y, i * 15, ST77XX_BLUE);
    delay(35);
  }
  tft.fillScreen(ST77XX_BLUE);
  for (int i = 0; i < 10; i++) {
    tft.fillCircle(x, y, i * 15, ST77XX_BLACK);
    delay(35);
  }
  tft.fillScreen(ST77XX_BLACK);
  currentWindowState = STATE_SETTINGS;
}

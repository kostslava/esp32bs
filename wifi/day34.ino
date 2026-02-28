#include <WiFi.h>
#include <WebServer.h>
#include <Adafruit_SH110X.h>
#include <Adafruit_GFX.h>

// oled screen
#define sda 9
#define scl 10

//create the constants
const char* ssid = "wifi name";
const char* password = "wifi password";

//define the display
Adafruit_SH1106G display = Adafruit_SH1106G(128, 64, &Wire);

//start webserver listening on port 80
WebServer server(80);

void handleRoot();

void setup() {
  //start serial monitor
  Serial.begin(115200);

  //begin connection to wifi
  WiFi.begin(ssid, password);

  //define pins for display
  Wire.begin(sda, scl);
  display.begin(0x3c);

  // loop connecting until connected
  while (WiFi.status() != WL_CONNECTED) {
    display.clearDisplay();
    display.setTextColor(1);
    display.setCursor(0, 0);
    display.println("Connecting");
    display.display();
    delay(500);
  }

  //define 
  server.on("/", handleRoot);
  server.begin();

  //say that its connected and what the ip is. 
  display.clearDisplay();
  display.setTextColor(1);
  display.setCursor(0, 0);
  display.println("=====================");
  display.println("      Connected!");
  display.println("=====================");
  display.print("Link at: ");
  display.println(WiFi.localIP());
  display.display();
  delay(500);
}

void loop() {
  server.handleClient();
}

void handleRoot() {
  server.send(200, "text/html",#include <WiFi.h>
#include <WebServer.h>
#include <Adafruit_SH110X.h>
#include <Adafruit_GFX.h>

// oled screen
#define sda 9
#define scl 10

//create the constants
const char* ssid = "RISC-V";
const char* password = "l1Nux0wnzyoU";

//define the display
Adafruit_SH1106G display = Adafruit_SH1106G(128, 64, &Wire);

//start webserver listening on port 80
WebServer server(80);

void handleRoot();

void setup() {
  //start serial monitor
  Serial.begin(115200);

  //begin connection to wifi
  WiFi.begin(ssid, password);

  //define pins for display
  Wire.begin(sda, scl);
  display.begin(0x3c);

  // loop connecting until connected
  while (WiFi.status() != WL_CONNECTED) {
    display.clearDisplay();
    display.setTextColor(1);
    display.setCursor(0, 0);
    display.println("Connecting");
    display.display();
    delay(500);
  }

  //define 
  server.on("/", handleRoot);
  server.begin();

  //say that its connected and what the ip is. 
  display.clearDisplay();
  display.setTextColor(1);
  display.setCursor(0, 0);
  display.println("=====================");
  display.println("      Connected!");
  display.println("=====================");
  display.print("Link at: ");
  display.println(WiFi.localIP());
  display.display();
  delay(500);
}

void loop() {
  server.handleClient();
}

void handleRoot() {
  server.send(200, "text/html", "<!DOCTYPE html><html lang=\"en\"><head><title>testing page</title><style>body {font-family: Arial, sans-serif;background-color: #f0f0f0;display: flex;justify-content: center;align-items: center;height: 100vh;margin: 0;}</style></head><body><h1>Testing Page</h1></body></html>");
  display.clearDisplay();
  display.setCursor(10, 10);
  display.println("Device connected!");
  display.display();
  rgbLedWrite(RGB_BUILTIN, 0, RGB_BRIGHTNESS, 0);  // Green
  delay(300);
  digitalWrite(RGB_BUILTIN, LOW);
  delay(300);
  rgbLedWrite(RGB_BUILTIN, 0, RGB_BRIGHTNESS, 0);  // Green
  delay(300);
  digitalWrite(RGB_BUILTIN, LOW);
  delay(300);
  rgbLedWrite(RGB_BUILTIN, 0, RGB_BRIGHTNESS, 0);  // Green
  delay(700);
  digitalWrite(RGB_BUILTIN, LOW);  // Turn the RGB LED off
} "<!DOCTYPE html><html lang=\"en\"><head><title>testing page</title><style>body {font-family: Arial, sans-serif;background-color: #f0f0f0;display: flex;justify-content: center;align-items: center;height: 100vh;margin: 0;}</style></head><body><h1>Testing Page</h1></body></html>");
  display.clearDisplay();
  display.setCursor(10, 10);
  display.println("Device connected!");
  display.display();
  rgbLedWrite(RGB_BUILTIN, 0, RGB_BRIGHTNESS, 0);  // Green
  delay(300);
  digitalWrite(RGB_BUILTIN, LOW);
  delay(300);
  rgbLedWrite(RGB_BUILTIN, 0, RGB_BRIGHTNESS, 0);  // Green
  delay(300);
  digitalWrite(RGB_BUILTIN, LOW);
  delay(300);
  rgbLedWrite(RGB_BUILTIN, 0, RGB_BRIGHTNESS, 0);  // Green
  delay(700);
  digitalWrite(RGB_BUILTIN, LOW);  // Turn the RGB LED off
}

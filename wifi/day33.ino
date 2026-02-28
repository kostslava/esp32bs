#include <WiFi.h>
#include <WebServer.h>

//create the constants
const char* ssid = "RISC-V";
const char* password = "l1Nux0wnzyoU";

//start webserver listening on port 80
WebServer server(80);

void handleRoot();

void setup() {
  //start serial monitor
  Serial.begin(115200);

  //begin connection to wifi
  WiFi.begin(ssid, password);

  Serial.print("\n\n\n\n\n\n\n\n\n\n");

  // loop connecting until connected
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Connecting..");
    delay(500);
  }

  server.on("/", handleRoot);

  server.begin();

  //say that its connected and what the ip is. 
  Serial.println("===========================");
  Serial.println("\tConnected!");
  Serial.println("===========================");
  Serial.print("Link at: ");
  Serial.println(WiFi.localIP());
  delay(500);
}

void loop() {
  server.handleClient();
}

void handleRoot() {
  server.send(200, "text/html", "<!DOCTYPE html><html lang=\"en\"><head><title>testing page</title><style>body {font-family: Arial, sans-serif;background-color: #f0f0f0;display: flex;justify-content: center;align-items: center;height: 100vh;margin: 0;}</style></head><body><h1>Testing Page</h1></body></html>");
  Serial.println("Device connected!");
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

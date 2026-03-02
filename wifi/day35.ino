#include <WiFi.h>
#include <WebServer.h>
#include <Adafruit_SH110X.h>
#include <Adafruit_GFX.h>
#include <Adafruit_AHTX0.h>

// oled screen
#define sda 9
#define scl 10

//create the constants
const char* ssid = "RISC-V";
const char* password = "l1Nux0wnzyoU";

//define the display and sensors
Adafruit_SH1106G display = Adafruit_SH1106G(128, 64, &Wire);
Adafruit_AHTX0 aht;

//start webserver listening on port 80
WebServer server(80);

void handleRoot();
void getData();

void setup() {
  //start serial monitor
  Serial.begin(115200);

  //begin connection to wifi
  WiFi.begin(ssid, password);

  //define pins for display and sensors
  Wire.begin(sda, scl);
  display.begin(0x3c);
  aht.begin();

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
  server.on("/data", getData);
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
  String html = "<!DOCTYPE html>";
  html += "<html lang=\"en\">";
  html += "<head>";
  html += "    <meta charset=\"UTF-8\">";
  html += "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
  html += "    <title>testing page</title>";
  html += "    <style>";
  html += "        body {";
  html += "            font-family: Arial, sans-serif;";
  html += "            background-color: #f0f0f0;";
  html += "            text-align: center ;";
  html += "            height: 100vh;";
  html += "            margin: 0;";
  html += "        }";
  html += "    </style>";
  html += "</head>";
  html += "<body>";
  html += "    <h1>goon tracker</h1>";
  html += "    <p>temperature: <span id=\"tempValue\">0</span>C</p>";
  html += "    <p>humidity: <span id=\"humidityValue\">0</span>%</p>";
  html += "</body>";
  html += "<script>";
  html += "    function placeData() {";
  html += "        fetch('/data')";
  html += "            .then(response => response.text())";
  html += "            .then(data => {";
  html += "                const values = data.split(',');";
  html += "                document.getElementById('tempValue').textContent = parseFloat(values[0]).toFixed(1);";
  html += "                document.getElementById('humidityValue').textContent = parseFloat(values[1]).toFixed(1);";
  html += "            })";
  html += "    }";
  html += "    setInterval(placeData, 300);";
  html += "</script>";
  html += "</html>";


  server.send(200, "text/html", html);
  display.clearDisplay();
  display.setCursor(10, 10);
  display.println("Device connected!");
  display.display();
  rgbLedWrite(RGB_BUILTIN, 0, RGB_BRIGHTNESS, 0);  // Green
  delay(300);
  digitalWrite(RGB_BUILTIN, LOW);  // Turn the RGB LED off
}

void getData() {
  // populate temp and humidity objects with fresh data
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp); 

  //create the big info string
  String info = String(temp.temperature, 1);
  info += ",";
  info += String(humidity.relative_humidity, 1);

  //send that string to the site
  server.send(200, "text/plain", info);
}

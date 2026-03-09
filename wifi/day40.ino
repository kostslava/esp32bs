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
  html += "<meta charset=\"UTF-8\">";
  html += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
  html += "<title>tracker server</title>";
  html += "<style>";
  html += "body {";
  html += "font-family: Arial, sans-serif;";
  html += "background-color: #f0f0f0;";
  html += "text-align: center;";
  html += "height: 100vh;";
  html += "margin: 0;";
  html += "}";
  html += ".infoBox {";
  html += "background-color: #fff;";
  html += "border: 1px solid #ccc;";
  html += "border-radius: 10px;";
  html += "padding: 20px;";
  html += "margin: 20px auto;";
  html += "width: 200px;";
  html += "box-shadow: 0 2px 5px rgba(0, 0, 0, 0.1);";
  html += "}";
  html += ".controlBtn {";
  html += "background-color: #007BFF;";
  html += "font-size: 20px;";
  html += "color: white;";
  html += "border: none;";
  html += "border-radius: 25px;";
  html += "padding: 10px 20px;";
  html += "margin: 10px;";
  html += "cursor: pointer;";
  html += "}";
  html += ".refreshBtn {";
  html += "background-color: #68b83a;";
  html += "font-size: 20px;";
  html += "color: white;";
  html += "border: none;";
  html += "border-radius: 25px;";
  html += "padding: 10px 20px;";
  html += "padding-top: 17px;";
  html += "margin: 10px;";
  html += "cursor: pointer;";
  html += "}";
  html += "</style>";
  html += "</head>";
  html += "<body>";
  html += "<h1>tracker server</h1>";
  html += "<div class=\"infoBoxDiv\">";
  html += "<p class=\"infoBox\" id=\"tempBox\">temperature: <span id=\"tempValue\">0</span>C</p>";
  html += "<p class=\"infoBox\" id=\"humidityBox\">humidity: <span id=\"humidityValue\">0</span>%</p>";
  html += "</div>";
  html += "<div class=\"controlsDiv\">";
  html += "<div class=\"controlsButtonsDiv\">";
  html += "<button class=\"controlBtn\" id=\"lastBtn\" onclick=\"changeData(-1)\">←</button>";
  html += "<button class=\"controlBtn\" id=\"nextBtn\" onclick=\"changeData(1)\">→</button>";
  html += "</div>";
  html += "<div class=\"refreshRateDiv\">";
  html += "<button class=\"refreshBtn\" id=\"refreshRateBtn\" onclick=\"setRefreshRate()\">🗘 Refresh Rate</button>";
  html += "</div>";
  html += "</div>";
  html += "<script>";
  html += "let refreshRate = 1000;";
  html += "let refreshInterval;";
  html += "let currentBox = 0;";
  html += "function setRefreshRate() {";
  html += "const userInput = prompt(\"Enter refresh rate in milliseconds:\", refreshRate);";
  html += "if (userInput !== null) {";
  html += "refreshRate = parseInt(userInput);";
  html += "clearInterval(refreshInterval);";
  html += "refreshInterval = setInterval(placeData, refreshRate);";
  html += "}";
  html += "}";
  html += "function placeData() {";
  html += "fetch('/data')";
  html += ".then(response => response.text())";
  html += ".then(data => {";
  html += "const values = data.split(',');";
  html += "document.getElementById('tempValue').textContent = parseFloat(values[0]).toFixed(1);";
  html += "document.getElementById('humidityValue').textContent = parseFloat(values[1]).toFixed(1);";
  html += "})";
  html += "}";
  html += "function changeData(direction) {";
  html += "currentBox += direction;";
  html += "if (currentBox < 0) currentBox = 1;";
  html += "if (currentBox > 1) currentBox = 0;";
  html += "const tempBox = document.getElementById('tempBox');";
  html += "const humidityBox = document.getElementById('humidityBox');";
  html += "if (currentBox === 0) {";
  html += "tempBox.style.display = 'block';";
  html += "humidityBox.style.display = 'none';";
  html += "} else {";
  html += "tempBox.style.display = 'none';";
  html += "humidityBox.style.display = 'block';";
  html += "}";
  html += "}";
  html += "changeData(0);";
  html += "placeData();";
  html += "refreshInterval = setInterval(placeData, refreshRate);";
  html += "</script>";
  html += "</body>";
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

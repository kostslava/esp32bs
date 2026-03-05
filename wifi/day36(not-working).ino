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
  html += "<title>testing page</title>";
  html += "<style>";
  html += "@import url('https://fonts.googleapis.com/css2?family=Inter:wght@400;500;600;700&display=swap');";
  html += "* { box-sizing: border-box; margin: 0; padding: 0; }";
  html += "body { font-family: 'Inter', sans-serif; min-height: 100vh; display: flex; flex-direction: column; align-items: center; justify-content: center; background: #111; color: #fff; padding: 1.5rem; }";
  html += "h1 { font-size: 1rem; font-weight: 500; letter-spacing: 0.2em; text-transform: uppercase; color: #666; margin-bottom: 2.5rem; }";
  html += ".slider-wrapper { display: flex; align-items: center; gap: 1.25rem; width: 100%; max-width: 480px; }";
  html += ".arrow-btn { flex-shrink: 0; width: 42px; height: 42px; border-radius: 50%; border: 1px solid #2a2a2a; background: #1a1a1a; color: #888; font-size: 1rem; cursor: pointer; display: flex; align-items: center; justify-content: center; transition: background 0.2s, color 0.2s, border-color 0.2s; user-select: none; }";
  html += ".arrow-btn:hover { background: #222; border-color: #444; color: #fff; }";
  html += ".arrow-btn:active { background: #2a2a2a; }";
  html += ".card-viewport { flex: 1; overflow: hidden; border-radius: 20px; }";
  html += ".card-track { display: flex; transition: transform 0.4s cubic-bezier(0.4, 0, 0.2, 1); }";
  html += ".card { min-width: 100%; background: #1a1a1a; border: 1px solid #2a2a2a; border-radius: 20px; padding: 2.5rem 2rem; text-align: center; }";
  html += ".card-label { font-size: 0.7rem; text-transform: uppercase; letter-spacing: 0.18em; color: #555; margin-bottom: 1rem; font-weight: 600; }";
  html += ".card-value { font-size: clamp(3.5rem, 14vw, 5rem); font-weight: 700; color: #fff; line-height: 1; letter-spacing: -0.02em; }";
  html += ".card-unit { font-size: 1rem; color: #444; margin-top: 0.5rem; font-weight: 500; }";
  html += ".dots { display: flex; gap: 6px; margin-top: 1.75rem; }";
  html += ".dot { width: 6px; height: 6px; border-radius: 50%; background: #333; transition: background 0.3s, transform 0.3s; cursor: pointer; }";
  html += ".dot.active { background: #fff; transform: scale(1.3); }";
  html += "</style>";
  html += "</head>";
  html += "<body>";
  html += "<h1>goon tracker</h1>";
  html += "<div class=\"slider-wrapper\">";
  html += "<button class=\"arrow-btn\" id=\"prevBtn\">&#8592;</button>";
  html += "<div class=\"card-viewport\">";
  html += "<div class=\"card-track\" id=\"cardTrack\">";
  html += "<div class=\"card\">";
  html += "<div class=\"card-label\">Temperature</div>";
  html += "<div class=\"card-value\"><span id=\"tempValue\">0</span></div>";
  html += "<div class=\"card-unit\">&#176;C</div>";
  html += "</div>";
  html += "<div class=\"card\">";
  html += "<div class=\"card-label\">Humidity</div>";
  html += "<div class=\"card-value\"><span id=\"humidityValue\">0</span></div>";
  html += "<div class=\"card-unit\">%</div>";
  html += "</div>";
  html += "</div>";
  html += "</div>";
  html += "<button class=\"arrow-btn\" id=\"nextBtn\">&#8594;</button>";
  html += "</div>";
  html += "<div class=\"dots\">";
  html += "<div class=\"dot active\" data-index=\"0\"></div>";
  html += "<div class=\"dot\" data-index=\"1\"></div>";
  html += "</div>";
  html += "<script src=\"/app.js\"></script>";  // <-- JS is separate
  html += "</body>";
  html += "</html>";

  server.send(200, "text/html", html);
}

void handleJS() {
  String js = "";
  js += "var track = document.getElementById('cardTrack');";
  js += "var dots = document.querySelectorAll('.dot');";
  js += "var current = 0;";
  js += "var total = 2;";
  js += "function goTo(index) {";
  js += "current = (index + total) % total;";
  js += "track.style.transform = 'translateX(-' + (current * 100) + '%)';";
  js += "dots.forEach(function(d) { d.classList.toggle('active', parseInt(d.dataset.index) === current); });";
  js += "}";
  js += "document.getElementById('prevBtn').addEventListener('click', function() { goTo(current - 1); });";
  js += "document.getElementById('nextBtn').addEventListener('click', function() { goTo(current + 1); });";
  js += "dots.forEach(function(d) { d.addEventListener('click', function() { goTo(parseInt(d.dataset.index)); }); });";
  js += "function placeData() {";
  js += "fetch('/data').then(function(r) { return r.text(); }).then(function(data) {";
  js += "var v = data.split(',');";
  js += "document.getElementById('tempValue').textContent = parseFloat(v[0]).toFixed(1);";
  js += "document.getElementById('humidityValue').textContent = parseFloat(v[1]).toFixed(1);";
  js += "});";
  js += "}";
  js += "placeData();";
  js += "setInterval(placeData, 300);";

  server.send(200, "application/javascript", js);
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

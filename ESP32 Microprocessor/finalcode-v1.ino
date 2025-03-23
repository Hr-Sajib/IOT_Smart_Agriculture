#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"
#include <Wire.h>
#include <BH1750.h>
#include "time.h"

#define DHTPIN 4 
#define SOIL_MOISTURE_PIN 34 
#define DHTTYPE DHT11   

// Initialize 
DHT dht(DHTPIN, DHTTYPE);
BH1750 lightMeter(0x23);

#define MAX_MOISTURE 2450  
#define MIN_MOISTURE 4095 

const char* ssid = "DeadNet";
const char* password = "00000000";

Google Apps Script URL
const char* url = "https://script.google.com/macros/s/AKfycbySlDI837cht27Mv2WRzzwceEbDAq7SNW9WId8encQefomvMlVGTaUWGpYTtSt37zgV8A/exec";

NTP server for time
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 6 * 3600;   // Time offset in seconds (Bangladesh: GMT+6)
const int   daylightOffset_sec = 0;     // No daylight saving

void setup() {
  Serial.begin(115200);
  Serial.println("Initializing sensors");

  dht.begin();

  Wire.begin(21, 22); // SDA = 21, SCL = 22
  if (lightMeter.begin()) {
    Serial.println("BH1750 initialized");
  } else {
    Serial.println("Error initializing BH1750");
  }

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Initialize time using NTP
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
}

void loop() {
  delay(1000);

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Adjust
  float correctedHumidity = humidity - 19;

  // Read soil moisture level from AO pin
  int soilMoistureValue = analogRead(SOIL_MOISTURE_PIN);
  float moisturePercentage = (float)(soilMoistureValue - MIN_MOISTURE) / (MAX_MOISTURE - MIN_MOISTURE) * 100;
  moisturePercentage = constrain(moisturePercentage, 0, 100);

  float lightIntensity = lightMeter.readLightLevel();

  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    return;
  }
  char currentDate[20];
  char currentTime[10];
  strftime(currentDate, sizeof(currentDate), "%Y-%m-%d", &timeinfo);
  strftime(currentTime, sizeof(currentTime), "%H:%M:%S", &timeinfo);

  Serial.print("Humidity: ");
  Serial.print(correctedHumidity);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C\t");
  Serial.print("Soil Moisture Level: ");
  Serial.print(moisturePercentage);
  Serial.print(" %\t");
  Serial.print("Light Intensity: ");
  Serial.print(lightIntensity);
  Serial.println(" lx");
  Serial.print("Date: ");
  Serial.println(currentDate);
  Serial.print("Time: ");
  Serial.println(currentTime);

  // Send data to Sheets
  sendDataToGoogleSheets(currentDate, currentTime, temperature, correctedHumidity, lightIntensity, moisturePercentage);
}

void sendDataToGoogleSheets(const char* date, const char* time, float temperature, float humidity, float light, float moisture) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(url);

    http.setTimeout(5000);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    String postData = "date=" + String(date) + "&time=" + String(time) + "&temperature=" + String(temperature) +
                      "&humidity=" + String(humidity) + "&light=" + String(light) + "&moisture=" + String(moisture);

    int httpResponseCode = http.POST(postData);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(httpResponseCode);
      Serial.println(response);
    } else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  } else {
    Serial.println("WiFi Disconnected");
  }
}

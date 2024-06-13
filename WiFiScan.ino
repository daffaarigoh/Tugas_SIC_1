#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>

#define DHTPIN 18       // Pin output data sensor DHT11
#define DHTTYPE DHT11   // Jenis sensor DHT yang digunakan
#define MQ135PIN 34     // Pin input data sensor MQ135

DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "Sukses Bersama";
const char* password = "berjuang3";
const char* serverName = "http://192.168.1.44:5000/"; // Ganti dengan alamat IP server Python

void setup() {
  Serial.begin(115200);
  dht.begin();
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();
    float airQuality = analogRead(MQ135PIN);

    if (isnan(temperature) || isnan(humidity) || isnan(airQuality)) {
      Serial.println("Failed to read from sensors!");
      return;
    }

    HTTPClient http;
    http.begin(serverName);
    http.addHeader("Content-Type", "application/json");

    String postData = "{\"temperature\":" + String(temperature, 2) + ", \"humidity\":" + String(humidity, 2) + ", \"air_quality\":" + String(airQuality) + "}";

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
    Serial.println("Error in WiFi connection");
  }

  delay(4000);
}

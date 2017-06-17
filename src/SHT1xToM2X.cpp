/*
  SHT11toM2x.cpp
  A sketch for sending temperature and humidity data from SHT1x to AT&T M2X
  Copyright (c) 2017 Jun Kimura All right reserved.
*/


#if defined ESP32
#include <WiFi.h>
#elif defined ESP8266
#include <ESP8266WiFi.h>
#endif

#include <SHT1x.h>

#define ESP8266_PLATFORM
//#include <M2XStreamClient/M2XStreamClient.h>
#include <M2XStreamClient.h>

// WiFi setttings
const char* ssid = "Your AP's SSID";
const char* password = "Your AP's password";

// m2x settings
const char* m2xKey = "Your m2x access key"; // Your M2X access key
const char* deviceId = "Your device id"; // Device you want to push to
const char* streamNameTemp = "Your stream id for temparature"; // Stream you want to push to
const char* streamNameHum = "Your stream id for humidity"; // Stream you want to push to
WiFiClient client;
M2XStreamClient m2xClient(&client, m2xKey);

// SHT1x settings
#define dataPin  13
#define clockPin 12
SHT1x sht1x(dataPin, clockPin);

#define SENSE_INTERVAL 60000

void setup() {
    Serial.begin(115200);
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void loop() {
  // Read values from the sensor
  float temp_c  = sht1x.readTemperatureC();
  float humidity = sht1x.readHumidity();

  // Print the values to the serial port
  Serial.print("Temperature: ");
  Serial.print(temp_c, DEC);
  Serial.print("C. Humidity: ");
  Serial.print(humidity);
  Serial.println("%");

  int response = m2xClient.updateStreamValue(deviceId, streamNameTemp, temp_c);
  Serial.print("M2x client response code: ");
  Serial.println(response);
  response = m2xClient.updateStreamValue(deviceId, streamNameHum, humidity);
  Serial.print("M2x client response code: ");
  Serial.println(response);

  delay(SENSE_INTERVAL);
}

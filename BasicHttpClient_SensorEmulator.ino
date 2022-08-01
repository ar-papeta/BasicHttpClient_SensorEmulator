/**
 * BasicHTTPClient.ino
 *
 *  Created on: 24.05.2015
 *
 */
#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>

#include "NtpHelper.h"
#include "SerialHelper.h"
#include "SensorDataModel.h"

const char* ssid = "Dima_EXT";
const char* password = "PapamamA";

void setup()
{
    InitSerial();

    WiFi.begin(ssid, password);
    // wait for WiFi connection
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    InitNtp();
}

void loop()
{
    HTTPClient http;

    http.begin("https://sensor-jwt.herokuapp.com/api/sensorsdata/SEN_B5_G4__1234512345"); //HTTP

    USE_SERIAL.print("\n\n\t\t[HTTP] POST\n");
    // start connection and send HTTP header
    http.addHeader("api_key", "_ba66f?b4b&d14=6");
    http.addHeader("Content-Type", "application/json");
    int httpCode = http.POST(SerializeNewRandomData());
    if(httpCode != 200){
      ESP.restart();
    }
    // httpCode will be negative on error
    if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        USE_SERIAL.printf("\n\n\t[HTTP] POST code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK) {
            String payload = http.getString();
            USE_SERIAL.println(payload);
            USE_SERIAL.println("\n\n");
        }
    }
    else {
        USE_SERIAL.printf("\n\t[HTTP] POST failed, error: %s\n\n\n\n", http.errorToString(httpCode).c_str());
    }
    http.end();

    delay(30000);
}

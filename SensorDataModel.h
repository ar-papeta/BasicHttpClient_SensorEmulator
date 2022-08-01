#pragma once
#include "NtpHelper.h"
DynamicJsonDocument sensor_json(1024);

float GetNextRandomValue(int minLimit, int maxLimit);

typedef struct {
    String Type;
    float Value;
} SensorMeasurement;

typedef struct {
    SensorMeasurement Measurements[2];
    String Time;
} SensorData;

String SerializeNewRandomData()
{
    sensor_json["time"] = GetDateTimeNow();
    sensor_json["measurements"][0]["type"] = "Current, ampere";
    sensor_json["measurements"][0]["value"] = GetNextRandomValue(0, 10);
    sensor_json["measurements"][1]["type"] = "Voltage, volt";
    sensor_json["measurements"][1]["value"] = GetNextRandomValue(210, 240);
    sensor_json["measurements"][2]["type"] = "Pressure, pascal";
    sensor_json["measurements"][2]["value"] = GetNextRandomValue(101325, 1013250);
    String str_json = "";
    serializeJsonPretty(sensor_json, str_json);
    serializeJsonPretty(sensor_json, Serial);
    return str_json;
}

float GetNextRandomValue(int minLimit, int maxLimit)
{
    int randomInt = random(minLimit, maxLimit); // a random integer from minLimit to maxLimit
    float randomDecimal = random(0, 100) / 100.0; // a random decimal number from 0.00 to 0.99
    return (float)(randomInt + randomDecimal);
}

#pragma once

#include <NTPClient.h>
#include <WiFiUdp.h>

//Prototypes
int AddHours(int hours);

// Define NTP Client to get time
WiFiUDP ntpUDP;

//add +3 hours (10800 sec) offset for current timezone
NTPClient timeClient(ntpUDP, AddHours(+3));

void InitNtp()
{
    timeClient.begin();
}

String GetDateTimeNow()
{
    while (!timeClient.update()) {
        timeClient.forceUpdate();
    }
    String timeNow = timeClient.getFormattedDate();
    while(!timeNow){
      timeClient.end();
      timeClient.begin();
      timeNow = timeClient.getFormattedDate();
      Serial.println("reinit time!");
      delay(1000);
    }
    // The formattedDate comes with the following format:
    // 2022-07-09T16:00:13Z
    return timeNow;
}

int AddHours(int hours)
{
    return hours * 60 * 60;
}

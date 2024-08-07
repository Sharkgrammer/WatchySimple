#include "simple.h"

#define DARKMODE false

const uint8_t BATTERY_SEGMENT_WIDTH = 7;
const uint8_t BATTERY_SEGMENT_HEIGHT = 11;
const uint8_t BATTERY_SEGMENT_SPACING = 9;
const uint8_t WEATHER_ICON_WIDTH = 48;
const uint8_t WEATHER_ICON_HEIGHT = 32;


void WatchySimple::drawWatchFace() {
    display.fillScreen(DARKMODE ? GxEPD_BLACK : GxEPD_WHITE);
    display.setTextColor(DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);

    drawTime();
    drawDate();
    drawSteps();
    drawBattery();
}

void WatchySimple::drawTime() {
    display.setFont(&DSEG7_Classic_Bold_53);
    String time = "";

    int displayHour
    if (HOUR_12_24 == 12) {
        displayHour = ((currentTime.Hour + 11) % 12) + 1;
    }
    else {
        displayHour = currentTime.Hour;
    }

    if (displayHour < 10) {
        time += "0";
    }

    time += displayHour;
    time += ":";

    if (currentTime.Minute < 10) {
        time += "0";
    }

    time += currentTime.Minute;

    int16_t  x1, y1;
    uint16_t w, h;
    display.getTextBounds(time, 5, 126, &x1, &y1, &w, &h);

    if (w == 152) {
        display.setCursor(-5, 126);
    }
    else {
        display.setCursor(5, 126);
    }

    display.println(time);
}

void WatchySimple::drawDate() {
    display.setFont(&Seven_Segment10pt7b);

    int16_t  x1, y1;
    uint16_t w, h;

    String dayOfWeek = dayStr(currentTime.Wday);
    display.getTextBounds(dayOfWeek, 5, 85, &x1, &y1, &w, &h);
    if (currentTime.Wday == 4) {
        w = w - 5;
    }

    display.setCursor(100 - (w / 2), 30);
    display.print(dayOfWeek);

    // Day
    display.setFont(&DSEG7_Classic_Bold_25);

    String date = "";
    date += currentTime.Day;

    switch (currentTime.Day) {
        case 1:
            date += "ST";
            break;
        case 2:
            date += "ND";
            break;
        case 3:
            date += "RD";
            break;
        default:
            date += "TH";
            break;
    }

    date += " ";
    date += monthShortStr(currentTime.Month);

    display.getTextBounds(date, 50, 65, &x1, &y1, &w, &h);

    display.setCursor(100 - (w / 2), 65);
    display.println(date);

}

void WatchySimple::drawSteps() {
    // reset step counter at midnight
    if (currentTime.Hour == 0 && currentTime.Minute == 0) {
        sensor.resetStepCounter();
    }
    uint32_t stepCount = sensor.getCounter();
    display.drawBitmap(10, 165, steps, 19, 23, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    display.setCursor(35, 190);
    display.println(stepCount);
}

void WatchySimple::drawBattery() {
    display.drawBitmap(158, 165 + 2, battery, 37, 21, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    display.fillRect(163, 170 + 2, 27, BATTERY_SEGMENT_HEIGHT, DARKMODE ? GxEPD_BLACK : GxEPD_WHITE);//clear battery segments

    int8_t batteryLevel = 0;
    float VBAT = getBatteryVoltage();

    if (VBAT > 4.0) {
        batteryLevel = 3;
    }
    else if (VBAT > 3.6 && VBAT <= 4.0) {
        batteryLevel = 2;
    }
    else if (VBAT > 3.20 && VBAT <= 3.6) {
        batteryLevel = 1;
    }
    else if (VBAT <= 3.20) {
        batteryLevel = 0;
    }

    for (int8_t batterySegments = 0; batterySegments < batteryLevel; batterySegments++) {
        display.fillRect(163 + (batterySegments * BATTERY_SEGMENT_SPACING), 170 + 2, BATTERY_SEGMENT_WIDTH, BATTERY_SEGMENT_HEIGHT, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    }
}


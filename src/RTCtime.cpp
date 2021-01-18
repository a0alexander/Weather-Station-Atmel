



#include <Arduino.h>
#include<Wire.h>
#include <mainHead.h>


#include "RTClib.h"

RTC_DS1307 RTC;

void setupRTC ()

{

// Serial.begin(9600);

// Wire.begin();

// RTC.begin(); // load the time from your computer.

if (! RTC.isrunning())

{

Serial.println("RTC is NOT running!");// This will reflect the time that your sketch was compiled

// RTC.adjust(DateTime(__DATE__, __TIME__));

}

}

void getRTCTime ()

{

// DateTime now = RTC.now();

// Serial.print(now.month(), DEC);

// Serial.print('/');

// Serial.print(now.day(), DEC);

// Serial.print('/');

// Serial.print(now.year(), DEC);

// Serial.print(' ');

// Serial.print(now.hour(), DEC);

// Serial.print(':');

// Serial.print(now.minute(), DEC);

// Serial.print(':');

// Serial.print(now.second(), DEC);

// Serial.println();

// delay(1000);

}












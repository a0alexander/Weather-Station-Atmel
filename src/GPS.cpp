


#include <Arduino.h>
#include <mainHead.h>
#include <TinyGPS++.h>


TinyGPSPlus gps;

bool gpsInit1 = false;
int16_t hours, minutes, seconds;

void drawGPSInterface(){

if(!gpsInit1){initGPS();gpsInit1=true;}



if(Serial2.available()){

  // Serial.write(Serial2.read());
if(gps.encode(Serial2.read()))


if(gps.date.isValid()){
Serial.println(gps.time.hour());
hours = gps.time.hour();
minutes = gps.time.minute();
seconds = gps.time.second();
drawTime(hours,minutes,seconds);

}

}

}



void initGPS(){
Serial3.end();

// drawTime();
Serial2.begin(9600);
Serial.println("gps initialized");


}


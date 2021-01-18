

#include <Arduino.h>
#include <mainHead.h>
#include<Wire.h>
#include <TinyGPS++.h>

#include "DHT.h"
extern TinyGPSPlus gps;


char *humidValue;

extern DHT dht;

 extern MCUFRIEND_kbv tft;

extern bool isDrawn;

 void setupMisc(){

    drawTime(0,0,0);

    if (isDrawn){
  return;
}
//   Serial.begin(9600);
  Wire.begin();
clearDisplay();
 
//   Serial.println(F("BH1750 Test"));
   placeText("Dew Point",0.5,0.3);
   placeText("Altitude",0.5,0.6);
//    placeText("C",0.8,0.6);

isDrawn = true;

}
static unsigned long last_misc_update = 0;
unsigned long misc_refresh_current=0 ;


void displayMisc(){

    misc_refresh_current = millis();

 if(misc_refresh_current- last_misc_update <1000){

                         return ;

        }
        last_misc_update=misc_refresh_current;

    dht.begin();

float H = dht.readHumidity();
float T = dht.readTemperature(false);
 float dew = calculateDewPoint(T, H);
//  float dew = (T - (100 - H) / 5);



   humidValue= float2String(dew,7,1,"C");


changeFontSize(LARGE);
if(!isnan(dew)){
   placeText(humidValue,0.5,0.45);

}
changeFontSize(SMALL);


// drawLightMeter(lux);

displayAltitude();

}

float a=17.27;
float b = 237.7;



float calculateDewPoint(float T, float H){

    float abt = (a*T)/(b+T);

    float numer = b*(abt+log(H/100));
    float denom = a-(abt+log(H/100));

    return numer/denom;



}

char *altitude;
uint8_t checksum;

void displayAltitude(){

    if(Serial2.available()){

  // Serial.write(Serial2.read());
if(gps.encode(Serial2.read())){

if(gps.altitude.isValid()){
//    placeText(altitude,0.5,0.6);
   altitude =  float2String(gps.altitude.meters(),7,1,"m");
checksum=1;
}
else{
    altitude=  float2String(528,7,1,"m");
checksum=0;

}



changeFontSize(LARGE);

   placeText(altitude,0.5,0.75);


changeFontSize(SMALL);



}


    }

    if(!isdigit(checksum)){
 altitude=  float2String(528,7,1,"m");

        changeFontSize(LARGE);
   placeText(altitude,0.5,0.75);
changeFontSize(SMALL);
    }


}








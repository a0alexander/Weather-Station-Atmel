


#include <Arduino.h>
#include <mainHead.h>
#include <TinyGPS++.h>
// #include<Wire.h>


TinyGPSPlus gps;

bool gpsInit1 = false;
double lat, lng;
char latString[15];
char lngString[15];
static unsigned long last_gps_update = 0;
unsigned long gps_refresh_time ;
 extern MCUFRIEND_kbv tft;
 
 uint8_t gpsOnCheck;

void drawGPSInterface(){

if(!gpsInit1){initGPS();Serial2.begin(9600); gpsInit1=true;}



if(Serial2.available()){

  // Serial.write(Serial2.read());
if(gps.encode(Serial2.read()))


lat = gps.location.lat();
lng = gps.location.lng();




 
  gps_refresh_time = millis();

 if (gps_refresh_time - last_gps_update > 1000)
 {

    if(gps.location.isValid()){
      lat = gps.location.lat();
      lng = gps.location.lng();
gpsOnCheck = 1;
    }else{
            lat = 7.849583;
          lng = 80.584838;
          
    }




strcpy(latString, float2String(lat,3,4," deg"));
strcpy(lngString, float2String(lng,3,4," deg"));
      // dtostrf(lat, 15, 4, latString);
      // dtostrf(lng, 15, 4, lngString);

      placeText("Latitude", 0.5,0.3);
      placeText(latString, 0.5,0.4);

      drawHoriLine(0.5,0.5,0.51,0xffff);

      placeText("Longitude", 0.5,0.6);
      placeText(lngString, 0.5,0.7);

last_gps_update = gps_refresh_time;
 }



    
  //  tft.setFont(&FreeMonoBold9pt7b);

}

if(!isdigit(gpsOnCheck)){
     lat = 7.849583;
          lng = 80.584838;
      placeText("Latitude", 0.5,0.3);
        
    // placeText(float2String(lat,3,4," deg"), 0.5,0.3);
      // placeText(float2String(lat,3,4," deg"), 0.5,0.4);
      placeText("Position Fixing..", 0.5,0.4);


      drawHoriLine(0.5,0.5,0.51,0xffff);
      placeText("Longitude", 0.5,0.6);

     
      // placeText(float2String(lng,3,4," deg"), 0.5,0.7);
      placeText("Position Fixing..", 0.5,0.7);


}

}



void initGPS(){
Serial3.end();

// drawTime();
Serial2.begin(9600);
Serial.println("gps initialized");


}






#include <Arduino.h>
#include<Wire.h>
#include <mainHead.h>
#include <BH1750.h>



extern MCUFRIEND_kbv tft;
char *luxValue;

BH1750 lightMeter;
extern bool isDrawn;

void setupLux(){

    if (isDrawn){
  return;
}
  Serial.begin(9600);
  Wire.begin();
  lightMeter.begin();
//   Serial.println(F("BH1750 Test"));
   placeText("Light Intensity",0.5,0.3);
   placeText("lx",0.8,0.6);

isDrawn = true;

}

static unsigned long last_lux_update = 0;
unsigned long lux_refresh_current=0 ;

void getLuminosity() {

    drawBlinker(5,0.95,0.07,rgbto565(200,0,0),500);
    lux_refresh_current = millis();

        if(lux_refresh_current- last_lux_update >1000){

            displayLux();
            last_lux_update = lux_refresh_current;

        }



}

void displayLux(){
  float lux = lightMeter.readLightLevel();
  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" lux");

   luxValue= float2String(lux,7,1,"");


changeFontSize(LARGE);
   placeText(luxValue,0.5,0.5);
changeFontSize(SMALL);


drawLightMeter(lux);

}

uint8_t lowerBound = 1;
uint16_t defUpper = 1000;
uint16_t upperBound = defUpper;
int maxBoxes = 15;
float boxWidth;
float spaceWidth = 0.008;
float totWidth ;
float boxHeight = 0.1;
int linearInter;
uint8_t changeTracker=64;

void drawLightMeter(float fluxVal){

    if(fluxVal>upperBound){
        upperBound=upperBound+500;

    }else if(fluxVal<defUpper){
        upperBound=defUpper;

    }

linearInter = (fluxVal/upperBound)*maxBoxes;
    // Serial.println(linearInter);

    if(linearInter==changeTracker){return;}

    changeTracker=linearInter;
    for(int i =0;i<maxBoxes;i++){
   totWidth = 0.9/maxBoxes;
        boxWidth = totWidth -spaceWidth*2;

        if(i<=linearInter){

        drawRectangle(0.1+i*totWidth,0.8,boxWidth,boxHeight,0xffff,true);

                }
                else{
        drawRectangle(0.1+i*totWidth,0.8,boxWidth,boxHeight,0x0000,true);
        drawLineRectangle(0.1+i*totWidth,0.8,boxWidth,boxHeight,0xffff,true);

                }           
    }

// drawRectangle(0.1,0.8,0.05,0.1,0xffff,true);


}
























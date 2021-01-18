



#include <Arduino.h>
#include <mainHead.h>

#include <MCUFRIEND_kbv.h>

// enum FontSize{XSMALL,SMALL, MEDIUM,LARGE};
// enum FontSize{XSMALL,SMALL, MEDIUM,LARGE};


extern MCUFRIEND_kbv tft;

int aqiSensor = A14;
//byte aqiPower = 22;

int8_t avgAQI[50] = {};
int8_t currentIdx = 0;
int8_t arrayLength = 0;
int prevAvg = 0;
int aqi= 0;
extern bool isDrawn; 
uint16_t defBlinkRate = 700;
uint16_t blinkRate = defBlinkRate;

//REMOVE MULTIPLIERS


void initAqi() {
  // put your setup code here, to run once:
// Serial.begin(9600);

if(isDrawn){return;}

placeText("CO Level",0.5,0.3);
pinMode(aqiSensor,INPUT);
arrayLength = sizeof(avgAQI)/sizeof(avgAQI[0]);
isDrawn =true;
aqi= 0;
}

void readAirQuality() {
  // put your main code here, to run repeatedly:

drawBlinker(5,0.9,0.1,rgbto565(255,0,0),500);


aqi= averageVal();
    drawNotifierRect(aqi);


if(prevAvg!=aqi){

    char aqiChar[5];

    sprintf(aqiChar, "%02d", abs(aqi));

    changeFontSize(LARGE);
    placeText(aqiChar, 0.5, 0.55);
    changeFontSize(SMALL);
    placeText("ppm", 0.5, 0.65);

    
    // drawCircleRing(0.5,0.6,0.3,5,1,20);
    drawCircleColorRing(0.5,0.6,0.3,5,1,20,aqi);
}
prevAvg=aqi;
 

}


int averageVal(){

    avgAQI[currentIdx] = analogRead(aqiSensor);
    currentIdx++;

    if(currentIdx>(arrayLength - 1)){
      currentIdx = 0;
    }

    int sum = 0;
    for(int i =0; i<(arrayLength); i++){

      sum += avgAQI[i];
      
      
      }

    int avg = sum/arrayLength;

    // tft.print(avg);


    

    return avg;
//    Serial.print(avg);
//    Serial.print('\t');
//    Serial.print(currentIdx);
//    Serial.print('\t');
//    Serial.print(analogRead(aqiSensor));
//    Serial.println(' ');


  
}


extern int displayHeight, displayWidth;


void drawCircleColorRing(float xPerc, float yPerc,float bigRadius, float smallRadius, float percFull, int numCircles,int COval){

  float degBetweenCircles = (2*M_PI)/numCircles;
  float radius = bigRadius*240;
  float visibleCircles = 1*numCircles;
  int offsetAngle = 0*(M_PI/180);

  float x0 = xPerc*displayWidth;
  float y0 = yPerc*displayHeight;




  for (int8_t i = 0; i < (int)numCircles; i++)
  {
    float xAng = radius*cos(i*degBetweenCircles+offsetAngle)+ x0;
    float yAng = radius*sin(i*degBetweenCircles+offsetAngle)+y0;
    // tft.fillCircle((int)xAng,(int)yAng,smallRadius,0x0000);


if(i<(int)visibleCircles){
    // tft.fillCircle((int)xAng,(int)yAng,smallRadius,0xffff);
// colorCodeCircle((float)i/(float)numCircles,(int)xAng,(int)yAng,5);
setCircleRingColor(COval,(int)xAng,(int)yAng,5);
    // delay(15);
}else{
// tft.fillCircle((int)xAng,(int)yAng,smallRadius,0x0000);

}
// delay(20);

// float val = (float)i/(float)numCircles;




  }
  
  




}


void setCircleRingColor(float perc,int x0, int y0, int r){

  if(perc<=100){
tft.fillCircle(x0,y0,r,rgbto565(0,255,0));
blinkRate =defBlinkRate;
  }
  else if(perc>100 && perc<=400){
tft.fillCircle(x0,y0,r,rgbto565(255,200,00));
blinkRate =500;

    
  }  else if(perc>400 && perc<=800){
// tft.fillCircle(x0,y0,r,rgbto565(255,100,40));
tft.fillCircle(x0,y0,r,rgbto565(255,200,00));
blinkRate =250;

    
  }  else if(perc>6000){
tft.fillCircle(x0,y0,r,rgbto565(255,0,0));
blinkRate =250;
    
  }  
  


}

static unsigned long last_CO_update = 0;
unsigned long CO_refresh_current=0 ;
uint16_t currentColor;
bool isRectDrawn=false;

void drawNotifierRect(int COval){
  CO_refresh_current = millis();


    if(COval<=100){
       currentColor = rgbto565(0,255,0);
  }
  else if(COval>100 && COval<=400){
       currentColor = rgbto565(255,200,00);
    
  }  else if(COval>400 && COval<=800){
// tft.fillCircle(x0,y0,r,rgbto565(255,100,40));
      currentColor =  rgbto565(255,200,00);

    
  }  else if(COval>6000){

  currentColor =  rgbto565(255,0,0);
  }  

  if(CO_refresh_current-last_CO_update>blinkRate){

      if(isRectDrawn){
      drawRectangle(0.5,0.95,1,0.1,0x0000,false);
      // drawLineRectangle(0.5,0.96,1,0.11,currentColor,false);
      isRectDrawn=false;
      }
      else{
      drawRectangle(0.5,0.95,1,0.1,currentColor,false);
      isRectDrawn=true;

      }
      last_CO_update = CO_refresh_current;

  }


}
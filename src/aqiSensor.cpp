



#include <Arduino.h>
#include <mainHead.h>

#include <MCUFRIEND_kbv.h>

// enum FontSize{XSMALL,SMALL, MEDIUM,LARGE};
// enum FontSize{XSMALL,SMALL, MEDIUM,LARGE};


// extern MCUFRIEND_kbv tft;

int aqiSensor = A13;
//byte aqiPower = 22;

int8_t avgAQI[50] = {};
int8_t currentIdx = 0;
int8_t arrayLength = 0;
int prevAvg = 0;
int aqi= 0;
extern bool isDrawn; 

void initAqi() {
  // put your setup code here, to run once:
// Serial.begin(9600);

if(isDrawn){return;}

placeText("Air Q. Index",0.5,0.15);
pinMode(aqiSensor,INPUT);
arrayLength = sizeof(avgAQI)/sizeof(avgAQI[0]);
isDrawn =true;
aqi= 0;
}

void readAirQuality() {
  // put your main code here, to run repeatedly:

drawBlinker(5,0.9,0.1,rgbto565(255,0,0),500);


aqi= averageVal();


if(prevAvg!=aqi){

    char aqiChar[5];

    sprintf(aqiChar, "%0d", abs(aqi));

    changeFontSize(LARGE);
    placeText(aqiChar, 0.5, 0.5);
    changeFontSize(SMALL);

    
    drawCircleRing(0.5,0.5,0.3,5,aqi*0.008,20);
    
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


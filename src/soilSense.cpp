

#include <Arduino.h>
#include <mainHead.h>
#include <sdcard.h>


const int AirValue = 870;   //you need to replace this value with Value_1
const int WaterValue = 600;  //you need to replace this value with Value_2
int soilMoistureValue = 0;
int soilmoisturepercent=0;
extern bool isDrawn; 
byte soilPin = A7;
int minVal = 0;
int maxVal = 0;

int8_t avgSoilMoist[5] = {};
int8_t currentIndx = 0;
int8_t arrayLength_ = sizeof(avgSoilMoist)/sizeof(avgSoilMoist[0]);


void drawSoilSense(){
if(isDrawn){return;}

placeText("Soil Moisture",0.5,0.25);
// placeText("Min: ", 0.2,0.8);
placeText("Max: ",0.25,0.7);
placeText("Avg: ",0.75,0.7);


pinMode(soilPin,INPUT);
drawTime(11,12,53);



isDrawn =true;


}


void readSoilMoisture() {
    drawBlinker(5,0.9,0.1,rgbto565(0,150,200),500);
    // drawTime(0,0,0);


readSoilVal();




}

unsigned long prevTime;
int delayTime =1000;

void readSoilVal(){

    unsigned long currentTime = millis();

    if(currentTime-prevTime>delayTime){

soilMoistureValue = analogRead(soilPin);  
soilmoisturepercent = map(soilMoistureValue, AirValue, WaterValue, 0, 100);
if(soilmoisturepercent>100){soilmoisturepercent=100;}
if(soilmoisturepercent<0){soilmoisturepercent=0;}

    char soilChar[5];


   sprintf(soilChar, "%03d%%", abs(soilmoisturepercent));

    changeFontSize(LARGE);
    placeText(soilChar, 0.5, 0.5);
    changeFontSize(SMALL);
    
    minMax(soilmoisturepercent);


prevTime = currentTime;
    }





}

void minMax(int val){

    char avgChar[5];

        if(val>maxVal){
            maxVal = val;
            
    char maxChar[5];

   sprintf(maxChar, "%03d%%", abs(soilmoisturepercent));

            placeText(maxChar,0.25,0.85);
        }

        int avg = averageSoilVal(val);

   sprintf(avgChar, "%03d%%", abs(avg));
            placeText(avgChar,0.75,0.85);

            // writeToSD(val,avg);




}
// int sum = 0;

int averageSoilVal(int val){

avgSoilMoist[currentIndx] = val;
    
    currentIndx++;

    if(currentIndx>(arrayLength_ - 1)){
      currentIndx = 0;
      
    }
int sum=0;
    
    for(int i =0; i<(arrayLength_); i++){

      sum += avgSoilMoist[i];
      
      
      }

    int avg = sum/arrayLength_;

    return avg;



  
}

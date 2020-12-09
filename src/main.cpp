#include <Arduino.h>






#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 //
#define LCD_RESET A4

#include <SPI.h>          // f.k. for Arduino-1.5.2
//#include "Adafruit_GFX.h"// Hardware-specific library
#include <MCUFRIEND_kbv.h>


#include <Fonts/FreeSans12pt7b.h>
#include<Fonts/weathercons.h>
#include <Fonts/FreeMonoBold12pt7b.h>
#include <Fonts/FreeMonoBold9pt7b.h>
#include <Fonts/FreeMonoBold18pt7b.h>
#include <Fonts/FreeMonoBold24pt7b.h>

#include <SD.h>
#include <SPI.h>
// #include "bme_sensor.cpp"
#include <bme.h>
#include <gprsHead.h>
#include <sdcard.h>
#include <mainHead.h>
 
// MCUFRIEND_kbv tft;
int displayHeight, displayWidth;

MCUFRIEND_kbv tft;

struct textData{
  int16_t  x1, y1;
uint16_t w, h;
  };

// enum FontSize{XSMALL,SMALL, MEDIUM,LARGE};


enum states{HOME, TEMPERATURE,DEF};			//FSM state initialization 
volatile enum states state;								//enumerable initialization 
volatile enum states current_state=DEF;

int8_t btnPin = 19;
int8_t btnPin2 = 18;
int8_t btnPin3 = 43;

bool isDrawn;
uint8_t hh,mm,ss;

void setup() {

  Serial.begin(9600);
    tft.reset();
    tft.begin();
    tft.setRotation(4);
//    uint16_t accent2 = rgbto565(251, 222, 20);//yellow


    displayHeight = tft.height();
    displayWidth = tft.width();



    state = HOME;
    // drawTemperatureSensor();
    
    setupBME();
    setupGPRS();
    pinMode(btnPin, INPUT_PULLUP);
    pinMode(btnPin2, INPUT_PULLUP);
    pinMode(btnPin3, INPUT_PULLUP);
attachInterrupt(digitalPinToInterrupt(btnPin), button1, LOW);
attachInterrupt(digitalPinToInterrupt(btnPin2), button2, LOW);
isDrawn = false;

hh = conv2d(__TIME__);
    mm = conv2d(__TIME__ + 3);
    ss = conv2d(__TIME__ + 6);

}

// int count =0;
 void switchPage(){


    if(current_state==state){
      isDrawn =true;

    }else{
   isDrawn = false;

    }
    
      current_state = state;




 }


void drawHome(){

if(isDrawn){return;}

//   tft.setFont(&FreeMonoBold12pt7b);

  tft.fillScreen(0x0000);

//   tft.setFont(&FreeMonoBold9pt7b);
//   placeText("Monday OCT 14", 0.5, 0.02);

//   tft.setFont(&FreeMonoBold12pt7b);
//   placeText("23:59:29", 0.5, 0.1);

  
while(1){printHome(tft);}
  // h1.definetft(tft);

// 





}

unsigned long timeTrack;
unsigned long lastTime = 1000;
char prevDateString[20];
char dateString[20];


void drawTime(int16_t hour,int16_t mins,int16_t sec){
// int16_t hour,mins,sec;
// char dateString[20];
strcpy(dateString,"10 SEP 2020");
timeTrack = millis();

if(timeTrack-lastTime<1000){return;}

 tft.setFont(&FreeMonoBold9pt7b);
 if(strcmp(dateString,prevDateString)!=0){
  placeText("Thursday SEP 10", 0.5, 0.02);
  strcpy(prevDateString,dateString);

 }

  tft.setFont(&FreeMonoBold12pt7b);

      if (++ss > 59) {
            ss = 0;
            mm++;
            if (mm > 59) {
                mm = 0;
                hh++;
                if (hh > 23) hh = 0;
            }
        }

sprintf(dateString,"%02d:%02d:%02d",hh,mm,ss);
  placeText(dateString, 0.5, 0.1);

lastTime=timeTrack;

}



uint8_t conv2d(const char* p)
{
    uint8_t v = 0;
    if ('0' <= *p && *p <= '9') v = *p - '0';
    return 10 * v + *++p - '0';
}








void drawTemperatureSensor(){

if (isDrawn){
  return;
}

    tft.setFont(&FreeMonoBold12pt7b);

    extern const uint16_t tempIcon3[];
    extern const uint16_t humidIcon[];
    extern const uint16_t baroIcon[];
    extern const uint16_t clockIcon[];
    extern const uint16_t sunIcon[];
    
    uint16_t accent2 = rgbto565(5, 5, 5);//yellow
    uint16_t accent1 = rgbto565(1,23,40);//blue

        tft.fillScreen(0x0000);
    
     tft.setFont(&FreeMonoBold9pt7b);
    placeText("Thursday SEP 14",0.5,0.02);
    
    
    tft.setFont(&FreeMonoBold12pt7b);
    placeText("23:59:29",0.5,0.1);

//    tft.setFont(&FreeMonoBold9pt7b);
//    tft.setTextColor(rgbto565(1,23,40));
//    placeText("Temperature",0.65,0.2);
    
    
    placeIconMasked(sunIcon, 0.15, 0.3,60,rgbto565(255,220,00));
    tft.setFont(&FreeMonoBold24pt7b);
    placeText("25.6C", 0.65,0.3);

    drawHoriLine(0.5,0.45,0.51,0xffff);
    
   tft.setFont(&FreeMonoBold9pt7b);

    float pressX = 0.25;
    float humidX = 0.75;
   
    placeText("Pressure", pressX,0.56);
    placeIcon(baroIcon,pressX,0.7,40 );
    placeText("95.34 kPa", pressX,0.85);
    
    placeText("Humidity", humidX,0.55);
    placeIcon(humidIcon,humidX,0.7,40 );
    placeText("87%", humidX,0.85);

    isDrawn=true;

}











void drawHoriLine(float xPos, float yPos, float len, uint16_t color){

float x = displayWidth*xPos;
float y = displayHeight*yPos;

float x0 = x-(len*displayWidth)/2;
float x1 = x+(len*displayWidth)/2;


tft.drawLine(x0,y,x1,y,color);
  
  
  }




void placeIcon(const uint16_t Icon[],float xPerc, float yPerc, int16_t dims){

  int halfDims = dims/2;
  float yOffset = yPerc*displayHeight - halfDims;
  float xOffset = xPerc*displayWidth - halfDims;

  
  tft.drawRGBBitmap((int16_t)xOffset,(int16_t)yOffset,Icon,dims,dims);
  
  

  
}


void placeIconMasked(const uint16_t Icon[],float xPerc, float yPerc, int16_t dims,int16_t col){

  int halfDims = dims/2;
  float yOffset = yPerc*displayHeight - halfDims;
  float xOffset = xPerc*displayWidth - halfDims;

  
   tft.drawRGBBitmapCustom((int16_t)xOffset,(int16_t)yOffset,Icon,dims,dims,col);

  
  

  
}


void drawRectangle(float xPerc, float yPerc,float wPerc, float hPerc,uint16_t col ,bool rnd){

//  float Xperc,yPerc,w,h;

float xPos = displayWidth*(xPerc)-(displayWidth*wPerc)/2 ;
float yPos = displayHeight*(yPerc)-(displayHeight*hPerc)/2;

float w = wPerc*displayWidth;
float h = hPerc*displayHeight;

if(rnd){
   tft.fillRoundRect((int)xPos,(int)yPos,(int)w,(int)h,20,col);

}
else{
  
   tft.fillRect((int)xPos,(int)yPos,(int)w,(int)h,col);

}
  


  
}


uint16_t rgbto565(uint8_t r, uint8_t g, uint8_t b)
{
  return ((r / 8) << 11) | ((g / 4) << 5) | (b / 8);
}

char* prevText;
void placeText(char* s,float xPerc, float yPerc){

            float xPos = xPerc* displayWidth;
            float yPos = yPerc* displayHeight;
            
            struct textData tmp = getTextData(s, 0,0);
            
            float txtWidth = tmp.w;
            float txtHeight = tmp.h;
            
            //tft.fillRect(tmp.x1,tmp.y1, tmp.w,tmp.h,0x0000);
     tft.setCursor((int)(xPos-(txtWidth/2)),(int)(yPos+(txtHeight/2)));
     tft.fillRect((int)(xPos-(txtWidth/2)),(int)(yPos-(txtHeight/2)),(int)txtWidth+5,(int)txtHeight+5,0x0000);

      
         
     tft.println(s);


              
}






void clearText(char* text, int xPos,int yPos){

//  clearText(prevText,(int)(xPos-(txtWidth/2)),(int)(yPos+(txtHeight/2)));
       tft.setCursor(xPos,yPos);
       tft.setTextColor(0x0000);
       tft.println(text);
       tft.setTextColor(0xFFFF);

}



  struct textData getTextData(String string, int x, int y){

    struct textData txt;
     
    tft.getTextBounds(string, x, y, &txt.x1, &txt.y1, &txt.w, &txt.h);
    
    return txt;
  }

#include <Wire.h>

#include <BMx280I2C.h>

// extern enum homeStates;
// extern homeStates selectionState;

enum homeStates{TEMP,AQI,SOIL,GPS,FIRE,SET,DEF1,INIT};
extern volatile homeStates selectionState;

 bool dataOn=false;

void recordMeasurement(){

  struct bmeData bme = getBMEMeasurement();

delay(100);
drawBlinker(5,0.95,0.07,rgbto565(200,0,0),500);
//

float T = bme.temperature;
float P = bme.pressure;
//char* temp, pres;
//
//Serial.println(temp);
//Serial.println(pres);
tft.setFont(&FreeMonoBold24pt7b);

char tempe[10],pres[10];
memset(tempe,0,10);
memset(pres,0,10);

strncpy(tempe, float2String(T,3,1,"C"),10);
strncpy(pres, float2String(P/1000,4,2," kPa"),10);

//float prese =  float2String(P/1000,3,1," kPa");

if(selectionState==TEMP && !isnan(T)&& T<100){
  placeText(tempe,0.65,0.3);
tft.setFont(&FreeMonoBold9pt7b);
}

if(selectionState==TEMP&& !isnan(P)){
tft.setFont(&FreeMonoBold9pt7b);
  placeText(pres, 0.25,0.85);
Serial.println(tempe);
}

tft.setFont(&FreeMonoBold12pt7b);



if(dataOn==true){
  placeText("DATA ON",0.5,0.9);
  sendDataCloud(T,P);
  drawBlinker(5,0.9,0.1,rgbto565(255,0,222),200);

}

//  sendDataCloud(T,P);
// writeToSD(T,P);
}






void loop() {

  
delay(1000);
drawHome();





}

char charbuf[12];
char charbuf2[12];

char* float2String(float T1,int numLength, int numDeci,char* unit){
memset(charbuf,0,12);
memset(charbuf2,0,12);

dtostrf(T1, numLength, numDeci, charbuf);
sprintf(charbuf2,"%s%s",charbuf,unit);
return charbuf2;



  }

void drawLineRectangle(float xPerc, float yPerc,float wPerc, float hPerc,uint16_t col ,bool rnd){

//  float Xperc,yPerc,w,h;

  float xPos = displayWidth*(xPerc)-(displayWidth*wPerc)/2 ;
  float yPos = displayHeight*(yPerc)-(displayHeight*hPerc)/2;

  float w = wPerc*displayWidth;
float h = hPerc*displayHeight;

if(rnd){
  tft.drawRoundRect((int)xPos,(int)yPos,(int)w,(int)h,20,col);
  

}
else{
  
   tft.drawRect((int)xPos,(int)yPos,(int)w,(int)h,col);


}
  


  
}



void clearDisplay(){
  tft.fillScreen(0x0000);
}




void changeFontSize(FontSize font){

switch(font){

  case XSMALL:tft.setFont(&FreeMonoBold9pt7b) ;break;
  case SMALL:tft.setFont(&FreeMonoBold12pt7b)  ;break;
  case MEDIUM:tft.setFont(&FreeMonoBold18pt7b)  ;break;
  case LARGE:tft.setFont(&FreeMonoBold24pt7b)  ;break;
  default:;break;
}

}

unsigned long previousBlink = 0;
int blinkDuration1 = 500;
uint16_t prevColor=2;
bool isOn=false;

void drawBlinker(int radius, float xPerc, float yPerc,uint16_t color,int blinkDuration ){

float x0 = xPerc*displayWidth;
float y0 = yPerc*displayHeight;

// if(isDrawn){
//   prevColor = tft.readPixel(0,0);
// // tft.print('prev color saved');
// }
// drawTime(0,0,0);
unsigned long blink_Current = millis();

    if((blink_Current - previousBlink) > blinkDuration1){

    if(!isOn){
      

    tft.fillCircle((uint16_t)x0,(uint16_t)y0,radius,color);
    isOn=true;

    }
    else{

tft.fillCircle((uint16_t)x0,(uint16_t)y0,radius,0x0000);
isOn=false;

}
previousBlink = blink_Current;

    }


}





void drawCircleRing(float xPerc, float yPerc,float bigRadius, float smallRadius, float percFull, int numCircles){

  float degBetweenCircles = (2*M_PI)/numCircles;
  float radius = bigRadius*240;
  float visibleCircles = percFull*numCircles;
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
colorCodeCircle((float)i/(float)numCircles,(int)xAng,(int)yAng,5);

    // delay(15);
}else{
tft.fillCircle((int)xAng,(int)yAng,smallRadius,0x0000);

}
// delay(20);

// float val = (float)i/(float)numCircles;




  }
  
  




}


void colorCodeCircle(float perc,int x0, int y0, int r){

  if(perc<=0.1){
tft.fillCircle(x0,y0,r,rgbto565(0,255,0));
  }
  else if(perc>0.1 && perc<=0.2){
tft.fillCircle(x0,y0,r,rgbto565(255,200,00));
    
  }  else if(perc>0.2 && perc<=0.3){
// tft.fillCircle(x0,y0,r,rgbto565(255,100,40));
tft.fillCircle(x0,y0,r,rgbto565(255,200,00));

    
  }  else if(perc>0.3 && perc<=0.4){
tft.fillCircle(x0,y0,r,rgbto565(255,0,0));
    
  }  else if(perc>0.4 && perc<=0.6){
// tft.fillCircle(x0,y0,r,rgbto565(140,40,140));
tft.fillCircle(x0,y0,r,rgbto565(255,0,0));

    
  }  else if(perc>0.6 && perc<=1){
tft.fillCircle(x0,y0,r,rgbto565(124,3,37));
    
  }  
  


}
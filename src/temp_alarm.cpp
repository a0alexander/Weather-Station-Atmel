
#include <Arduino.h>
#include <mainHead.h>
#include<Wire.h>
#include <gprsHead.h>


#include "DHT.h"
extern DHT dht;
 extern MCUFRIEND_kbv tft;

extern bool isDrawn;

uint8_t setTemperatureVal = 20;

void setupTemp_Alarm(){
    
drawTime(0,0,0);
if(isDrawn){return;}

Serial3.begin(9600); 
  Wire.begin();
clearDisplay();
   placeText("Current T",0.5,0.3);
   placeText("Set T",0.5,0.65);
//    placeText(altitude,0.5,0.75);

isDrawn=true;
}

char *temperatureString;

static unsigned long last_temp_alarm_update = 0;
unsigned long temp_alarm_refresh_current=0 ;

void displayTemperatureinAlarm(){
checkIncrements();

        temp_alarm_refresh_current = millis();

 if(temp_alarm_refresh_current- last_temp_alarm_update <1000){

                         return ;

        }
        last_temp_alarm_update=temp_alarm_refresh_current;

    dht.begin();

// float H = dht.readHumidity();
float T = dht.readTemperature(false);
//  float dew = calculateDewPoint(T, H);
//  float dew = (T - (100 - H) / 5);



   temperatureString= float2String(T,7,1,"C");


changeFontSize(LARGE);
if(!isnan(T)){

    if(T<setTemperatureVal){
        drawVisualTempAlarm();
        sendSMS();
    }
   placeText(temperatureString,0.5,0.45);

}
changeFontSize(SMALL);


// drawLightMeter(lux);
showSetValue();

}

char setTempString[5];
void showSetValue(){

sprintf(setTempString,"%02d %s",setTemperatureVal,"C");


    placeText(setTempString,0.5,0.75);
}


void checkIncrements(){
int upPress = digitalRead(25);
int downPress = digitalRead(19) ;

if(upPress==LOW || downPress==LOW){
static unsigned long last_interrupt_time = 0;
 unsigned long interrupt_time = millis();

 if (interrupt_time - last_interrupt_time > 200)
 {

     if(upPress==LOW){
         setTemperatureVal++;
     }else if(downPress==LOW){
         setTemperatureVal--;

     }

showSetValue();

 last_interrupt_time = interrupt_time;

}

} 




}


uint8_t SMSsent = 0;

void sendSMS()
{

    if(SMSsent>1){return;}
SMSsent++;
  Serial.println("Sending SMS...");               
  Serial3.print("AT+CMGF=1\r");                   
  delay(100);
  Serial3.print("AT+CMGS=\"+94766672555\"\r");  
  delay(500);
  Serial3.print("Temperature Alert!");      
  Serial3.println(temperatureString);      
  Serial3.print("Celcius");      
  delay(500);
  Serial3.print((char)26);
//   delay(500);
  Serial3.println();
  Serial.println("Text Sent.");
  delay(500);

}


static unsigned long last_alarm_update = 0;
unsigned long alarm_refresh_current=0 ;
bool isRectaDrawn = false;

void drawVisualTempAlarm(){
  alarm_refresh_current = millis();



  if(alarm_refresh_current-last_alarm_update>500){

      if(isRectaDrawn){
      drawRectangle(0.5,0.95,1,0.1,0x0000,false);
      // drawLineRectangle(0.5,0.96,1,0.11,currentColor,false);
      isRectaDrawn=false;
      }
      else{
      drawRectangle(0.5,0.95,1,0.1,rgbto565(255,0,0),false);
      isRectaDrawn=true;

      }
      last_alarm_update = alarm_refresh_current;

  }


}











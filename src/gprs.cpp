
#include <SoftwareSerial.h>
//SoftwareSerial Serial3(15,14);
// 
#include <String.h>
#include <gprsHead.h>
#include <Arduino.h>

 void ShowSerialData();


float scaler = 0.4;
 
void setupGPRS()
{
  Serial3.begin(9600);               // the GPRS baud rate   
  // Serial2.end() ;              // the GPRS baud rate   
              // the GPRS baud rate   
//  Serial.begin(9600);    // the GPRS baud rate 
  
 
  delay(1000);
}
 enum netStates{BEGIN,GPRS_ON,MUX,GPRS_STAT,APN,CIIR,CIFSR,CIPSPRT,CIPSTART,
CIPSEND,UPLOADING,END,GPRS_OFF};
netStates netProcess= BEGIN;

int duration=500;
bool isEnable = true;
float commonDelay = 2;
void sendDataCloud(float temp, float pres,float humid)
{
   
      
   
// ShowSerialData();

nextStep(commonDelay*3);

if(isEnable){
setAction(temp,pres,humid);

}
else{

}



} 



void ShowSerialData()
{
  while(Serial3.available()!=0)
  Serial.write(Serial3.read());
  delay(5000*0.5); 
  
}


String buff1;
int buffChar;
byte readByte;
char byteBuffer[20];
// byte readByte;




void sendData(float temp, float pres,float humid){

  // String str="GET https://api.thingspeak.com/update?api_key=HRYEH3NC0KV22OK5&field1="+String(temp)+"&field2="+(pres);
  String str="GET http://us-central1-project1-36240.cloudfunctions.net/testFunction1/post/?field1="+
  String(temp)+
  "&field2="+
  (pres)+
    "&field3="+
  (humid)+
  "&field9=60&uid=IgKCceAuWmRC2oPNl0ozlHmxAUA3";
  
  Serial3.println(str);
}

void resetBuffer() {
  memset(byteBuffer, 0, sizeof(byteBuffer));
  buffChar = 0;
}

void setAction(float temp, float pres,float humid){
// delay(2000);
Serial.print("current netProcess ");
Serial.println(netProcess);
// ShowSerialData();
switch(netProcess){


case BEGIN:Serial3.println("AT");commonDelay = 0.5;break;
case GPRS_ON:Serial3.println("AT+CIPSHUT");commonDelay = 1;break;
case MUX:Serial3.println("AT+CIPSTATUS");commonDelay = 0.5;break;
case GPRS_STAT:Serial3.println("AT+CIPMUX=0");commonDelay = 0.5;break;
case APN:Serial3.println("AT+CSTT=\"hutch3g\"");commonDelay = 0.5;break;
case CIIR:Serial3.println("AT+CIICR");commonDelay = 2;break;
case CIFSR:Serial3.println("AT+CIFSR");commonDelay = 1;break;
case CIPSPRT:Serial3.println("AT+CIPSPRT=0");commonDelay = 1;break;
case CIPSTART:Serial3.println("AT+CIPSTART=\"TCP\",\"us-central1-project1-36240.cloudfunctions.net\",\"80\"");
commonDelay = 4;break;
case CIPSEND:Serial3.println("AT+CIPSEND");commonDelay = 2;break;
case UPLOADING:sendData( temp, pres,humid);commonDelay = 1;break;
case END:Serial3.println((char)26);commonDelay = 3;break;
case GPRS_OFF:Serial3.println("AT+CIPSHUT");commonDelay = 1;break;
default: netProcess = BEGIN;break;
// case BEGIN:Serial3.println((char)26);;break;


}
delay(100);
  while (Serial3.available()){
    // readByte = Serial3.read();
    //   byteBuffer[buffChar++]=  readByte;
    
    //   // if ( readByte == '\n' ){
    //   //   break;
    //   // }

    // if(buffChar>20){
    //     resetBuffer(); 
    // }
    Serial.write(Serial3.read());

  }
  // Serial.println(byteBuffer);
  //       resetBuffer();
  //       buffChar=0;

    // Serial.write(Serial3.read());
    // String buff1 = Serial3.readString();
    // char byteBufer*;
    
  

    
    
isEnable=false;


// nextStep();







}


int countStep= 0;
unsigned long currentTime1;
unsigned long previousTime1;

void nextStep(float delay){

 float del  =  delay*1000;

unsigned long currentTime1 = millis();
if((currentTime1 - previousTime1)>(int)del){
  
  netProcess = countStep;
countStep++;
if(countStep>GPRS_OFF){
  countStep=0;
}

previousTime1 = currentTime1;
isEnable=true;
}



}
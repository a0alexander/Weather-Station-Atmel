

#include <Arduino.h>
#include <mainHead.h>

#include <MCUFRIEND_kbv.h>



// tft = h1.tft;

enum homeStates{TEMP,AQI,SOIL,GPS,FIRE,SET,DEF1,INIT};
volatile homeStates selectionState= INIT;

void selectIcon(float xPerc, float yPerc, float wPerc, float hPerc);


void initDisplay();
class Icon{
    public:
        float xPerc;
        float yPerc;
        float wPerc;
        float hPerc;
        char* iconName;

void createIcon(float xPerc,float yPerc,float wPerc,float hPerc,char* iconName){
    this->xPerc = xPerc;
    this->yPerc = yPerc;
    this->wPerc = wPerc;
    this->hPerc = hPerc;
    this->iconName = iconName;
}
        

};
void selectIcon(Icon icon);
void setIconText(Icon icon);

    Icon icon1, icon2, icon3, icon4, icon5, icon6;

bool hasRun = false;
void InitVars(){


if(hasRun){return;}

float iconHeight = 0.2;
float iconWidth = 0.3;
// changeFontSize(SMALL);

icon1.createIcon(0.25,0.3,iconWidth,iconHeight,"TEMP");
icon2.createIcon(0.75,0.3,iconWidth,iconHeight,"AQI");

icon3.createIcon(0.25,0.6,iconWidth,iconHeight,"SOIL");
icon4.createIcon(0.75,0.6,iconWidth,iconHeight,"GPS");

icon5.createIcon(0.25,0.9,iconWidth,iconHeight,"FIRE");
icon6.createIcon(0.75,0.9,iconWidth,iconHeight,"SET.");

hasRun=true;

}

// Icon iconArr[6] = {icon1, icon2,icon3,icon4,icon5,icon6};
bool isMode= false;
volatile uint8_t currIcon=0;



void printHome(MCUFRIEND_kbv tft){
InitVars();
// drawBlinker(5,0.9,0.1,rgbto565(0,0,0),500);
drawTime(0,0,0);


switch (selectionState)


{

case TEMP:drawTemperatureSensor(); recordMeasurement();isMode=true ;break;
case AQI :Serial.println("select aqi"); initAqi();readAirQuality() ; break;
case SOIL:drawSoilSense();readSoilMoisture(); ; break;
case GPS: drawGPSInterface(); break;
case FIRE: ; break;
case SET: ; break;
case DEF1: ;break;
case INIT :  initDisplay();selectIcon(icon1);currIcon=0; selectionState=DEF1;isMode=false;  break;
default:    break;
}




checkPress();

stateShift();
// selectIcon(*iconArr[1]);



    // delay(1000);









// currIcon++;


}

   
    



void selectIcon(float xPerc, float yPerc, float wPerc, float hPerc){

    drawLineRectangle(xPerc,yPerc,wPerc,hPerc,0xffff,true);


}

void selectIcon(Icon icon){

    drawLineRectangle(icon.xPerc,icon.yPerc,icon.wPerc,icon.hPerc,0xffff,false);


}


void initDisplay()
{// draw the text with black boxes to overrite previous selections
// drawTime(23,45,43);
setIconText(icon1);
setIconText(icon2);
setIconText(icon3);
setIconText(icon4);
setIconText(icon5);
setIconText(icon6);
// selectIcon(icon1);
// currIcon=0;

}



void setIconText(Icon icon){

    uint16_t col1 = 0x0000;

    drawRectangle(icon.xPerc,icon.yPerc,icon.wPerc+0.02,icon.hPerc+0.02,col1,false);
     placeText(icon.iconName,icon.xPerc,icon.yPerc);


}



void button1(){


 static unsigned long last_interrupt_time = 0;
 unsigned long interrupt_time = millis();

 if (interrupt_time - last_interrupt_time > 200)
 {
       Serial.println("pressed");
// drawTime(99,45,43);
clearDisplay();
selectionState = currIcon;
        // updateOnChange();

 }
 last_interrupt_time = interrupt_time;

}


bool stateShiftVar;
extern bool isDrawn;

void button2(){


 static unsigned long last_interrupt_time = 0;
 unsigned long interrupt_time = millis();
 
 if (interrupt_time - last_interrupt_time > 200)
 {
       Serial.println("back pressed");
// drawTime(99,45,43);
//   isDrawn = false;
//   currIcon=0;
stateShiftVar=true;
        selectionState = INIT;
 }
 last_interrupt_time = interrupt_time;

}

void stateShift(){
    if(stateShiftVar==true){
  clearDisplay();
        updateOnChange();

    }

stateShiftVar = false;
}



void updateOnChange(){


isDrawn = false;
Serial.println(currIcon);


initDisplay();

        // selectionState = currIcon;

    // }
  


    // Serial.println((int)readVal);

switch(currIcon){

    case 0:selectIcon(icon1) ;break;
    case 1: selectIcon(icon2);break;
    case 2: selectIcon(icon3);break;
    case 3: selectIcon(icon4);break;
    case 4:selectIcon(icon5) ;break;
    case 5:selectIcon(icon6) ;break;
    case 9:;break;
    // case 6:selectIcon(icon1) ;break;
    default: ;break;
}
}




void checkPress(){

if(digitalRead(43)==LOW){
static unsigned long last_interrupt_time = 0;
 unsigned long interrupt_time = millis();

 if (interrupt_time - last_interrupt_time > 200)
 {
switch(selectionState){

    case DEF1: handleHomePageCursor() ;break;
    case TEMP:handleTemperatureCursor();break;
    default: ;break;


     }

 last_interrupt_time = interrupt_time;

}

}         


}
    
extern bool dataOn;

void handleTemperatureCursor(){

if(dataOn==true){

    dataOn=false;
}else if(dataOn==false){


    dataOn = true;
}



}

void handleHomePageCursor(){

  

 
 



    Serial.print("button 3 pressed");
    currIcon = currIcon+1;
if(currIcon>5 || currIcon<0){
    currIcon=0;
}

updateOnChange();


     

 }



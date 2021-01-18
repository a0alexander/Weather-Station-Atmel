

#include <Arduino.h>
#include<Wire.h>
#include <mainHead.h>
#include <MCUFRIEND_kbv.h>


extern MCUFRIEND_kbv tft;

volatile miscStates selectedMisc= INITIAL;

    Icon tAlarm_icon, alti_icon;
uint8_t cursorSelecter =0;

volatile bool exitMisc = true;

void showMiscMenu(){


selectedMisc= INITIAL;
exitMisc = true;
while(exitMisc){



    switch(selectedMisc){
        case TEMP_ALARM:setupTemp_Alarm();displayTemperatureinAlarm();break;
        case ALTITUDE:setupMisc();displayMisc()  ;break;
        case RED:checkNextPressOnMisc();selectButtonMiscProcess();break;
        case EXIT:exitMisc=false ;break;
        case INITIAL:clearDisplay(); initMiscVars();initMiscDisplay();
        selectIcon(tAlarm_icon);selectedMisc=RED;exitMisc = true;
        cursorSelecter=0;detachInterrupt(digitalPinToInterrupt(19)) ; break;


    }



}




}




bool hasMisMenuRun = false;



void initMiscVars(){


if(hasMisMenuRun){return;}

float iconHeight = 0.25;
float iconWidth = 0.3;
// changeFontSize(SMALL);

tAlarm_icon.createIcon(0.25,0.3,iconWidth,iconHeight,"T Alert");

// delay(100);
alti_icon.createIcon(0.75,0.3,iconWidth,iconHeight,"Altitude");


hasMisMenuRun=true;

}


void initMiscDisplay()
{// draw the text with black boxes to overrite previous selections
// drawTime(23,45,43);
setIconText(tAlarm_icon);
setIconText(alti_icon);




// if(!isIconDrawn){
// placeIcons();
// isIconDrawn=true;
// }


// setIconText(icon2);
// setIconText(icon3);
// setIconText(icon4);
// setIconText(icon5);
// setIconText(icon6);
// selectIcon(icon1);
// currIcon=0;

}



void checkNextPressOnMisc(){

if(digitalRead(25)==LOW){
static unsigned long last_interrupt_time = 0;
 unsigned long interrupt_time = millis();

 if (interrupt_time - last_interrupt_time > 200)
 {

if(selectedMisc==RED){
        initMiscDisplay();
cursorSelecter=cursorSelecter+1;

    if(cursorSelecter>1){
            cursorSelecter=0;
    }
  

    miscIconSelector();

}

 last_interrupt_time = interrupt_time;

}

}         


}


void miscIconSelector(){

    switch(cursorSelecter){
        case 0:selectIcon(tAlarm_icon) ;break;
        case 1:selectIcon(alti_icon) ;break;
    }



}



void selectButtonMiscProcess(){

if(digitalRead(19)==LOW){
static unsigned long last_interrupt_time = 0;
 unsigned long interrupt_time = millis();

 if (interrupt_time - last_interrupt_time > 200)
 {

     selectedMisc = cursorSelecter;
    //      if(cursorSelecter==0){
    //     selectedMisc = TEMP_ALARM;
    // }
    // else if(cursorSelecter==1){
    //     selectedMisc = ALTITUDE;
        
    // }


 last_interrupt_time = interrupt_time;

}

}








}






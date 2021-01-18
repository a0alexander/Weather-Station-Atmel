
#include <Arduino.h>



void setupGPRS();
void sendDataCloud(float temp, float pres);
void sendDataCloud(float temp, float pres,float humid);
void setAction(float temp, float pres);
void setAction(float temp, float pres,float humid);
void nextStep(float delay);
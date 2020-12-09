
#include <Arduino.h>



void setupGPRS();
void sendDataCloud(float temp, float pres);
void setAction(float temp, float pres);
void nextStep(float delay);



#include <Arduino.h>

#include <MCUFRIEND_kbv.h>


enum FontSize{XSMALL,SMALL, MEDIUM,LARGE};

uint8_t conv2d(const char* p);

void drawTime(int16_t hour,int16_t mins,int16_t sec);
void clearDisplay();
void placeText(char* s,float xPerc, float yPerc);
void drawHoriLine(float xPos, float yPos, float len, uint16_t color);
void placeIcon(const uint16_t Icon[],float xPerc, float yPerc, int16_t dims);
void placeIconMasked(const uint16_t Icon[],float xPerc, float yPerc, int16_t dims,int16_t col);
void drawRectangle(float xPerc, float yPerc,float wPerc, float hPerc,uint16_t col ,bool rnd);
uint16_t rgbto565(uint8_t r, uint8_t g, uint8_t b);
void placeText(char* s,float xPerc, float yPerc);

void clearText(char* text, int xPos,int yPos);
struct textData getTextData(String string, int x, int y);
char* float2String(float T1,int numLength, int numDeci,char* unit);
void recordMeasurement();
void drawTemperatureSensor();
void drawHome();
void switchPage();
void printHome(MCUFRIEND_kbv tft);
// class home{
//     public:
//     MCUFRIEND_kbv tft;

//     void definetft(MCUFRIEND_kbv tft){
//             this->tft = tft;
//     }

// };

// home h1;


void drawLineRectangle(float xPerc, float yPerc,float wPerc, float hPerc,uint16_t col ,bool rnd);
void drawGPSInterface();
void initGPS();


void button1();
void button2();
void updateOnChange();
void checkPress();
void handleHomePageCursor();

void initAqi();
void readAirQuality();
int averageVal();
void stateShift();



void changeFontSize(FontSize font);
// void drawBlinker(int radius, float xPerc, float yPerc,uint16_t color );
void drawCircleRing(float xPerc, float yPerc,float bigRadius, float smallRadius, float percFull, int numCircles);
void drawBlinker(int radius, float xPerc, float yPerc,uint16_t color,int blinkDuration );
void colorCodeCircle(float perc,int x0, int y0, int r);


void readSoilMoisture();
void drawSoilSense();
void readSoilVal();
void minMax(int val);
int averageSoilVal(int val);

void handleTemperatureCursor();
void setupRTC ();
void getRTCTime();
void getReadableDay(uint8_t dayOfWeek,uint8_t monthRTC);
void drawDate();


void setupLux();
void getLuminosity();
void displayLux();
void drawLightMeter(float fluxVal);


void drawCircleColorRing(float xPerc, float yPerc,float bigRadius, float smallRadius, float percFull, int numCircles,int aqiChar);
void setCircleRingColor(float perc,int x0, int y0, int r);
void drawNotifierRect(int COval);

void placeIcons();
void displayMisc();
void setupMisc();
float calculateDewPoint(float T, float H);
void displayAltitude();
void moveCursor();

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

void showMiscMenu();
void initMiscVars();
void initMiscDisplay();
enum miscStates{TEMP_ALARM,ALTITUDE,RED,EXIT,INITIAL};
void checkNextPressOnMisc();
void miscIconSelector();
void selectButtonMiscProcess();


void setupTemp_Alarm();
void displayTemperatureinAlarm();
void showSetValue(uint8_t setTemperatureVal);
void showSetValue();
void checkIncrements();
void sendSMS();
void drawVisualTempAlarm();
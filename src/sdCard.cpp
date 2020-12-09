

/*
 *  Arduino SD Card Tutorial Example
 *  
 *  by Dejan Nedelkovski, www.HowToMechatronics.com
 */
#include <SD.h>
#include <Arduino.h>
#include <sdcard.h>
//#include <SPI.h>
File myFile;

void writeToSD(float T, float P) {
    
//  Serial.begin(9600);
pinMode(53, OUTPUT);


  
  if (SD.begin())
  {
    Serial.println("SD card is ready to use.");
  } else
  {
    Serial.println("SD card initialization failed");
    return;
  }
  
  // Create/Open file 
  myFile = SD.open("weather1.txt", FILE_WRITE);
  
  // if the file opened okay, write to it:
  if (myFile) {
    Serial.println("Writing to file...");
    
 myFile.print(T); 
  myFile.print(","); 
 myFile.print(P);
 myFile.println();
    myFile.close(); // close the file
    Serial.println("Done.");
    SD.end();
  }
  // if the file didn't open, print an error:
  else {
    Serial.println("error opening test.txt");
  }



}


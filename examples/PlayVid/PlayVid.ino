#include <SD.h>
#include <SPI.h>
#include <ILI9341_t3n.h>
#include <JPEGDEC.h>
#include <Audio.h>
#include <play_sd_aac.h>
#include "MjpegTFT_t4.h"

#define TFT_DC  37
#define TFT_CS 38
#define TFT_RST 8
#define TFT_SCK 27
#define TFT_MISO 39
#define TFT_MOSI 26

#define CS_PIN BUILTIN_SDCARD

ILI9341_t3n tft = ILI9341_t3n(TFT_CS, TFT_DC, TFT_RST, TFT_MOSI, TFT_SCK, TFT_MISO);

AudioOutputI2S           i2s1;           //xy=334,89
AudioPlaySdAac          Aac;
AudioConnection         patchCord1(Aac,0,i2s1,0);
AudioConnection         patchCord2(Aac,1,i2s1,1);
AudioControlSGTL5000     sgtl5000_1;     //xy=240,153


File mjpeg;
JPEGDEC jpeg;

char filetoopen[50] = "3.vid";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(ILI9341_BLACK);
  AudioMemory(24);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);
  if(!SD.begin(CS_PIN)){
    while(true){Serial.println("Unable to acces the SD card"); delay(500);}
  }
  mjpeg = SD.open(filetoopen);
  if(!mjpeg){
      while(true){
        Serial.printf("The file %s was not found on the SD card!",filetoopen);
        delay(500);
      }
  }
}

int JPEGDraw(JPEGDRAW *pDraw) {
  tft.writeRect(pDraw->x, pDraw->y, pDraw->iWidth, pDraw->iHeight, pDraw->pPixels);
  return 1;
}

void loop() {
  // put your main code here, to run repeatedly:
  playVid(mjpeg,jpeg,JPEGDraw,Aac);
  while(true);
}

#include <SD.h>
#include <SPI.h>
#include <play_sd_aac.h>
#include <JPEGDEC.h>
#include <Audio.h>

int playVid(File mjpeg,JPEGDEC jpeg,int JPEGDraw,AudioPlaySdAac &playAac,uint32_t vidstart=0);

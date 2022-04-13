#include "MjpegTFT_t4.h"

#define JPGBUFSIZE 100000

int playVid(File mjpeg,JPEGDEC jpeg,int JPEGDraw,AudioPlaySdAac &playAac,uint32_t vidstart=0){
  //Initalizing the variables
  uint8_t *jpgbuf = (uint8_t*)malloc(JPGBUFSIZE);
  uint32_t audpos = 0;
  uint16_t fps = 0;
  uint16_t frames = 0;
  uint16_t fsize = 0;
  
  //Getting fps,frames and the position where the audio is stored
  mjpeg.seek(vidstart);
  mjpeg.read(&fps,2);
  mjpeg.read(&frames,2);
  mjpeg.read(&audpos,4);
  //Starting audio
  playAac.stop();
  playAac.startpos = audpos;
  playAac.play(mjpeg.name());
  delay(25); // Change to sync the audio with the video
  
  //Getting the time the programm started
  int64_t startprog = micros();
  
  //Starting rendering the video
  for(int i = 0; i <= frames ; i++){
    //Reading the next frame
    AudioNoInterrupts();
    mjpeg.read(&fsize,2);
    mjpeg.read(jpgbuf,fsize);
    AudioInterrupts();
    //Decoding the jpeg and displaying it
    jpeg.openRAM(jpgbuf,fsize,JPEGDraw);
    jpeg.decode(0,0,0);
    //If the decoding took too long skip the frame
    if((1000000 / fps * (i+1)) + startprog - micros() < 0 ){
      continue;
    }
    //Waiting for the right framerate
    delayMicroseconds((1000000 / fps * (i+1)) + startprog - micros());
  }
  playAac.stop();
  free(jpgbuf);
  return 0;
}

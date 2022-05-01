# MjpegTFT_t4
A Mjpeg like Video Player for the Teensy 4.1 development Boards.
## Usage
  ### Dependencies
  #### Linux/Unix
  Install [ffmpeg](https://ffmpeg.org) and [python3](https://python.org)
  #### Teensy
  You have to install the [Teensy Audio Library](https://github.com/PaulStoffregen/Audio),[Teensy Audio Codecs Library (My Version)](https://github.com/1337Misom/Arduino-Teensy-Codec-lib),[JPEGDEC](https://github.com/bitbank2/JPEGDEC) and [ILI9341_t3n (My Version)](https://github.com/1337Misom/ILI9341_t3n) library.
  ### Creating a Video
  - First install the Dependencies for your PC
  - Then run the create.py script in the scripts folder.
  ### Using with Teensy
  To run the Video Player example:
  - Install the Dependencies for the Teensy
  - Clone the repo to your Arduino libraries Folder and Go to File -> examples -> MjpegTFT_t4 -> PlayVid.
  - Change The `CS_PIN` To your SD CS PIN and all the defines for the TFT to your pins
  - Change `filetoopen` to the name of your video file
## File Format
This is a pretty basic Video format it is build up like this:
### The Header
  1. The first seven bytes are the header : 0x00,0x00,0x00,0x4A,0x41,0x56,0xFF
  2. The next two bytes are the fps
  3. The two following are the amount of frames in the video
  4. And the next four are the position of the aac audio
### Video
  Each jpeg has two bytes before it, with the size of the jpeg.
### Audio
  Audio is just an aac file behind the whole video.
## Todo (PR's appreciated)
- Some kind of API
- Better sync with audio and video
- Using DMA to run in background

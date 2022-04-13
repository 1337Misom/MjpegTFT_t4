# MjpegTFT_t4
A Mjpeg like Video Player for the Teensy 4.1 development Boards.
## Usage
  ### Dependencies
  #### Linux
  Install [ffmpeg](https://ffmpeg.org) and [python3](https://python.org)
  #### Teensy
  You have to install the [Teensy Audio Library](https://github.com/PaulStoffregen/Audio) and The [Teensy Audio Codecs Library](https://github.com/FrankBoesing/Arduino-Teensy-Codec-lib) library.
  ### Creating a Video
  - First install the Dependencies for your PC
  - Then run the create.py script in the scripts folder.
  ### Using with Teensy
  To run the Video Player:
  - Install the Dependencies for the Teensy
  - Clone the repo to your Arduino sketchbook and Go to File -> Sketchbook -> MjpegTFT_t4.
  - Change The `CS_PIN` To your SD CS PIN and all the defines for the TFT to your pins
  - Change `filetoopen` to the name of your video file
## File Format
This is a pretty basic Video format it is build up like this:
### The Header
  1. The first two bytes are the fps
  2. The two following are the amount of frames in the video
  3. And next four are the position of the aac audio
### Video
  Each jpeg has two bytes before it with the size of the jpeg.
### Audio
  Audio is just an aac file behind the whole video
## Todo
- Some kind of API
- Better sync with audio and video

import sys
import os
import re
import argparse
parser=argparse.ArgumentParser()
parser.add_argument("x",help="The width of the finished video",type=int)
parser.add_argument("y",help="The height of the finished video",type=int)
parser.add_argument("fps",help="The framerate for the finished video",type=int)
parser.add_argument("inputfile",help="The video to convert",type=str)
parser.add_argument("outputfile",help="The output file",type=str)
args = parser.parse_args()
x = args.x
y = args.y
fps = args.fps
inp = args.inputfile
out = args.outputfile

os.system("ffmpeg -i {} -s {}x{} -qscale:v 2 -filter:v fps={} {}.mjpeg".format(inp,x,y,fps,out))
os.system("ffmpeg -i {} -ar 44100 {}.aac".format(inp,out))
aac = open(out+".aac","rb")
vid = open(out+".mjpeg","rb")
vidbuf = vid.read()
vidsplit = vidbuf.split(b'\xff\xd9')
frames = len(vidsplit)-1
mjpegsize = (int(os.path.getsize(out+".mjpeg")+8)) + (frames*2)
outf = open(out,"wb")
outf.write(fps.to_bytes(2,byteorder='little'))
outf.write(frames.to_bytes(2,byteorder='little'))
outf.write(mjpegsize.to_bytes(4,byteorder='little'))
for i in vidsplit:
    outf.write((len(i)+2).to_bytes(2,byteorder='little'))
    outf.write(i)
    outf.write(b'\xff\xd9')
outf.write(aac.read())
outf.close()
aac.close()
vid.close()
os.remove(out+".mjpeg")
os.remove(out+".aac")
print("Done")
exit(0)

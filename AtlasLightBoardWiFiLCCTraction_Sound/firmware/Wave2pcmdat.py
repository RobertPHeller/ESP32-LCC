#!/usr/bin/python3
import wave

def Wave2pcmdat(wavefile,pcmdatfile,name):
    input = wave.open(wavefile,"r")
    output = open(pcmdatfile,"w")
    chans = input.getnchannels()
    bytessample = input.getsampwidth()
    #print("bytessample is ",bytessample)
    frate = input.getframerate()
    frames = input.getnframes()
    output.write("#include <stdint.h>\n\n")
    output.write("uint16_t %s_PCM[] = {\n"%(name))
    sampsperline = 10
    output.write("    ")
    for i in range(0,frames):
        frame = input.readframes(1)
        #print("frame is ",frame)
        sample = 0
        for j in range(0,chans):
            chsamp = 0
            #print("j is ",j)
            for kk in range(0,bytessample):
                k = (bytessample-1)-kk
                #print("k is ",k)
                #print("chsamp is ", chsamp)
                #print("frame[(j*bytessample)+k] is ",frame[(j*bytessample)+k])
                chsamp = (chsamp << 8) + frame[j+k]
            sample += chsamp
        average = int(round(sample / chans))
        #print("average is ",average)
        output.write("0x%04x, "%(average))
        sampsperline -= 1
        if (sampsperline == 0):
            output.write("\n    ")
            sampsperline = 10
    if (sampsperline < 10):
        output.write("\n")
    output.write("};\n")
    output.write("#define %s_BYTES (sizeof(%s_PCM))\n"%(name,name))
    output.close()
    input.close()
    
import sys
Wave2pcmdat(sys.argv[1],sys.argv[2],sys.argv[3])


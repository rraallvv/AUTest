//
//  main.c
//  AUTest
//
//  Created by Tom Schroeder on 2/26/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <CoreAudio/CoreAudio.h>
#include <AudioToolbox/AudioToolbox.h>

int main(int argc, char *argv[])
{
   AUGraph audioGraph;
   NewAUGraph(&audioGraph);
   
   AudioComponentDescription cd;
   AUNode outputNode;
   AudioUnit outputUnit;
   
   cd.componentManufacturer = kAudioUnitManufacturer_Apple;
   cd.componentFlags = 0;
   cd.componentFlagsMask = 0;
   cd.componentType = kAudioUnitType_Output;
   cd.componentSubType = kAudioUnitSubType_DefaultOutput;
   
   AUGraphNewNode(audioGraph, &cd, 0, NULL, &outputNode);
   AUGraphGetNodeInfo(audioGraph, outputNode, 0, 0, 0, &outputUnit);
   
   AUNode mixerNode;
   AudioUnit mixerUnit;
   
   cd.componentManufacturer = kAudioUnitManufacturer_Apple;
   cd.componentFlags = 0;
   cd.componentFlagsMask = 0;
   cd.componentType = kAudioUnitType_Mixer;
   cd.componentSubType = kAudioUnitSubType_StereoMixer;
   
   AUGraphNewNode(audioGraph, &cd, 0, NULL, &mixerNode);
   AUGraphGetNodeInfo(audioGraph, mixerNode, 0, 0, 0, &mixerUnit);
   
   AUGraphConnectNodeInput(audioGraph, mixerNode, 0, outputNode, 0);
   
   AUGraphOpen(audioGraph);
   AUGraphInitialize(audioGraph);
   AUGraphStart(audioGraph);
   
   AUNode synthNode;
   AudioUnit synthUnit;
   
   cd.componentManufacturer = kAudioUnitManufacturer_Apple;
   cd.componentFlags = 0;
   cd.componentFlagsMask = 0;
   cd.componentType = kAudioUnitType_MusicDevice;
   cd.componentSubType = kAudioUnitSubType_DLSSynth;
   
   AUGraphNewNode(audioGraph, &cd, 0, NULL, &synthNode);
   AUGraphGetNodeInfo(audioGraph, synthNode, 0, 0, 0, &synthUnit);
   
   AUGraphConnectNodeInput(audioGraph, synthNode, 0, mixerNode, 0);
   
   AUGraphUpdate(audioGraph, NULL);
   CAShow(audioGraph);
   
   MusicDeviceMIDIEvent(synthUnit, 0x90, 60, 127, 0);
   sleep(1);
   MusicDeviceMIDIEvent(synthUnit, 0x90, 62, 127, 0);
   sleep(1);
   MusicDeviceMIDIEvent(synthUnit, 0x90, 64, 127, 0);
   sleep(1);
   
   sleep(5);
   
   return(0);
}



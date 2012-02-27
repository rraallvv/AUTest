//
//  main.c
//  AUTest
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

   AUGraphAddNode(audioGraph, &cd, &outputNode);
   AUGraphNodeInfo(audioGraph, outputNode, &cd, &outputUnit);
   
   AUNode mixerNode;
   AudioUnit mixerUnit;
   
   cd.componentManufacturer = kAudioUnitManufacturer_Apple;
   cd.componentFlags = 0;
   cd.componentFlagsMask = 0;
   cd.componentType = kAudioUnitType_Mixer;
   cd.componentSubType = kAudioUnitSubType_StereoMixer;
   
   AUGraphAddNode(audioGraph, &cd, &mixerNode);
   AUGraphNodeInfo(audioGraph, mixerNode, &cd, &mixerUnit);
   
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
   
   AUGraphAddNode(audioGraph, &cd, &synthNode);
   AUGraphNodeInfo(audioGraph, synthNode, &cd, &synthUnit);
   
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



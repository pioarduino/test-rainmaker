#include "AudioTools.h"
#include "AudioTools/AudioCodecs/CodecFLAC.h"
#include "AudioTools/AudioLibs/AudioBoardStream.h"

AudioInfo info(44100, 2, 16);
SineWaveGenerator<int16_t> sineWave( 32000);  // subclass of SoundGenerator with max amplitude of 32000
GeneratedSoundStream<int16_t> sound( sineWave); // Stream generated from sine wave
HexDumpOutput out(Serial);
EncodedAudioStream encoder(&out, new FLACEncoder()); // encode and write
StreamCopy copier(encoder, sound);     

void setup() {
  Serial.begin(115200);
  AudioToolsLogger.begin(Serial, AudioToolsLogLevel::Warning);

  // Setup sine wave
  sineWave.begin(info, N_B4);

  // start encoder
  encoder.begin(info);

  Serial.println("Test started...");
}


void loop() { 
  copier.copy();
}

#ifndef audioProcessor_h
#define audioProcessor_h

#include "Arduino.h"
#include <VectorXf.h>
#include "resonateBulb.h"

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

class AudioProcessor {
public:
  AudioProcessor();
  void setup(AudioOutputI2S* _i2s1,AudioInputI2S* _i2s2, AudioMixer4* _mixer1, AudioMixer4* _mixer2, AudioAnalyzePeak* _peak1, AudioSynthWaveformSine* _sine1, AudioEffectFreeverb* _freeverb1, AudioEffectDelay* _delay1, AudioControlSGTL5000* _sgtl5000);
  void process();

  AudioOutputI2S *i2s1;
  AudioInputI2S *i2s2;
  AudioMixer4 *mixer1;
  AudioMixer4 *mixer2;
  AudioAnalyzePeak *peak1;
  AudioSynthWaveformSine *sine1;
  AudioEffectFreeverb *freeverb1;
  AudioEffectDelay *delay1;
  AudioControlSGTL5000 *sgtl5000;
};

#endif

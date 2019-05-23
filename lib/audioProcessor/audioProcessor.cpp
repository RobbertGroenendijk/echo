#include "AudioProcessor.h"

AudioProcessor::AudioProcessor() {

}
void AudioProcessor::setup(AudioOutputI2S* _i2s1,AudioInputI2S* _i2s2, AudioMixer4* _mixer1, AudioMixer4* _mixer2, AudioAnalyzePeak* _peak1, AudioSynthWaveformSine* _sine1, AudioEffectFreeverb* _freeverb1, AudioEffectDelay* _delay1, AudioControlSGTL5000* _sgtl5000,AudioSynthWaveformSineModulated* _sineFM1) {

  AudioMemory(750);

  i2s1 = _i2s1;
  i2s2 = _i2s2;
  mixer1 = _mixer1;
  mixer2 = _mixer2;
  peak1 = _peak1;
  sine1 = _sine1;
  freeverb1 = _freeverb1;
  delay1 = _delay1;
  sgtl5000 = _sgtl5000;
  sineFM1 = _sineFM1;

  sgtl5000->enable();
  sgtl5000->volume(0.42);

  sgtl5000->inputSelect(AUDIO_INPUT_MIC);
  sgtl5000->micGain(30);

  mixer1->gain(0,0.75);
  mixer1->gain(1,0.75);

  mixer2->gain(0,0.60);
  mixer2->gain(1,0.0);

  delay1->delay(0, 1);

  freeverb1->roomsize(0.8);
  freeverb1->damping(0.9);

  previousMillis = 0;

}
void AudioProcessor::process() {

    if (peak1->available()) {
      AudioNoInterrupts();
      sgtl5000->dacVolumeRamp();

      float peak = peak1->read();
      currentPeak = peak; // Load public var for resonate read-out

      sine1->amplitude(peak);
      sine1->frequency((peak*1.3)*600+20);

      sineFM1->amplitude(peak);
      sineFM1->frequency((peak*800)+20);
      AudioInterrupts();
  }

}

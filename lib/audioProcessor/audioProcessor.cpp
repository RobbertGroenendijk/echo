#include "AudioProcessor.h"

AudioProcessor::AudioProcessor() {

}
void AudioProcessor::setup(AudioOutputI2S* _i2s1,AudioInputI2S* _i2s2, AudioMixer4* _mixer1, AudioMixer4* _mixer2, AudioAnalyzePeak* _peak1, AudioSynthWaveformSine* _sine1, AudioEffectFreeverb* _freeverb1, AudioEffectDelay* _delay1, AudioControlSGTL5000* _sgtl5000) {
  AudioMemory(190);

  i2s1 = _i2s1;
  i2s2 = _i2s2;
  mixer1 = _mixer1;
  mixer2 = _mixer2;
  peak1 = _peak1;
  sine1 = _sine1;
  freeverb1 = _freeverb1;
  delay1 = _delay1;
  sgtl5000 = _sgtl5000;

  sgtl5000->enable();
  sgtl5000->volume(0.75);

  sgtl5000->inputSelect(AUDIO_INPUT_MIC);
  sgtl5000->micGain(30);

  mixer1->gain(0,0.75);
  mixer1->gain(1,0.75);

  mixer2->gain(0,0.75);
  mixer2->gain(1,0.75);

  delay1->delay(0, 500);

  //sine1.frequency(500);
  //sine1.amplitude(0.3);

  freeverb1->roomsize(0.8);
  freeverb1->damping(0.9);
}
void AudioProcessor::process() {
  if (peak1->available()) {
    float peak = peak1->read();
    //Serial.println(peak);
    sine1->amplitude(peak);
    sine1->frequency((peak*500)+100);
  }
}

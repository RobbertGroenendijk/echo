#include "installation.h"

Installation::Installation() {
  Serial.println("Installation constructor triggered");
}
void Installation::setup() {
  Serial.println("Installation setup triggered");

  horizontalDimensions = Vec2f(INSTALLATION_X, INSTALLATION_Z);
  verticalDimensions = Vec2f(0,INSTALLATION_Y);

  tlc.begin();
  tlc.write();

  for (int i = 0; i < NUM_CREATURES; i++) {
    creatureArray[i].setup(horizontalDimensions,verticalDimensions);
  }
  Vec3f testLocation = Vec3f(50,50,50);
  for (int i = 0; i < NUM_LIGHTS; i++) {
    lightArray[i].setup(horizontalDimensions,verticalDimensions, testLocation);
    lightArray[i].passPointers(&creatureArray[0].creature_location,resonateArray);
  }
}
void Installation::setupAudioProcessor(AudioOutputI2S* _i2s1,AudioInputI2S* _i2s2, AudioMixer4* _mixer1, AudioMixer4* _mixer2, AudioAnalyzePeak* _peak1, AudioSynthWaveformSine* _sine1, AudioEffectFreeverb* _freeverb1, AudioEffectDelay* _delay1, AudioControlSGTL5000* _sgtl5000) {
  audioProcessor.setup(_i2s1,_i2s2,_mixer1,_mixer2,_peak1,_sine1,_freeverb1,_delay1,_sgtl5000);
}
void Installation::resonate() {
  int newResonates = 0;
  for (int i = 0; i < NUM_RESONATE; i++) {
    if (resonateArray[i].bulb_life < 1) {
      if (newResonates < 20) {
        Vec3f newDirection = Vec3f(cos((TWO_PI/20)*newResonates),sin((TWO_PI/20)*newResonates));
        resonateArray[i].setup(creatureArray[0].creature_location, newDirection);
      }
    }
  }

}
void Installation::loop() {
  //Serial.println("Installation loop");

  for (int i = 0; i < NUM_CREATURES; i++) {
    creatureArray[i].loop();
  }
  for (int i = 0; i < NUM_LIGHTS; i++) {
    lightArray[i].loop();

    if (millis()%1000 < 500) {
      tlc.setPWM(i, 65000);
    } else {
      tlc.setPWM(i, 20000);
    }

  }
  for (int i = 0; i < NUM_RESONATE; i++) {
    if (resonateArray[i].bulb_life > 0) {
      resonateArray[i].loop();
    }
  }

  audioProcessor.process();
  tlc.write();
}

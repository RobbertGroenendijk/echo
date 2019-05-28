#include "installation.h"

Installation::Installation() {
  Serial.println("Installation constructor triggered");
}
void Installation::setup() {
  Serial.println("Installation setup triggered");

  horizontalDimensions = Vec2f(INSTALLATION_X, INSTALLATION_Z);
  verticalDimensions = Vec2f(0,INSTALLATION_Y);

  creatureArray[0].setup(horizontalDimensions,verticalDimensions);

  for (int i = 0; i < NUM_LIGHTS; i++) {
    //Vec3f testLocation = Vec3f(random(0,80),random(0,80),random(0,80));
    Vec3f lightLocation = lightLocationArray[i];
    lightArray[i].setup(horizontalDimensions,verticalDimensions, lightLocation);
    lightArray[i].passPointers(&creatureArray[0].creature_location,resonateArray);
  }
  tlc.begin();
  tlc.write();

  resonateTimer = 0.0;
  tlcTimer = 0.0;
}
void Installation::setupAudioProcessor(AudioOutputI2S* _i2s1,AudioInputI2S* _i2s2, AudioMixer4* _mixer1, AudioMixer4* _mixer2, AudioAnalyzePeak* _peak1, AudioSynthWaveformSine* _sine1, AudioEffectFreeverb* _freeverb1, AudioEffectDelay* _delay1, AudioControlSGTL5000* _sgtl5000,AudioSynthWaveformSineModulated* _sineFM1) {
  audioProcessor.setup(_i2s1,_i2s2,_mixer1,_mixer2,_peak1,_sine1,_freeverb1,_delay1,_sgtl5000,_sineFM1);
}
void Installation::resonate(float _peak) {
  int newResonates = 0;
  for (int i = 0; i < NUM_RESONATE; i++) {
    if (resonateArray[i].bulb_life < 1) {
      if (newResonates < 10) {
        Vec3f newDirection = Vec3f(cos((TWO_PI/10)*newResonates),sin((TWO_PI/10)*newResonates),sin(random(0,TWO_PI)));
        resonateArray[i].setup(creatureArray[0].creature_location, newDirection, _peak);
        newResonates++;
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
    //tlc.setPWM(i,lightArray[i].brightness); // NO GAMMA CORRECTION
    tlc.setPWM(i,gamma16[int(lightArray[i].brightness)]); // GAMMA CORRECTION
  }

  float currentPeak = audioProcessor.currentPeak;
  if (currentPeak > 0.2) {
    if (millis() - resonateTimer > 500) {
      resonate(currentPeak);
        Serial.println("resonate");
        resonateTimer = millis();
    }
  }

  for (int i = 0; i < NUM_RESONATE; i++) {
    if (resonateArray[i].bulb_life > 0) {
      resonateArray[i].loop();
    }

  } // End of resonateArray loop


  if (millis() - tlcTimer > 50) {
    tlc.write(); // Limit use of SPI for less audio interference
    tlcTimer = millis();
  }
  audioProcessor.process();
}

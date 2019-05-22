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
    Vec3f testLocation = Vec3f(random(0,80),random(0,80),random(0,80));
    //Vec3f lightLocation = lightLocationArray[i];
    lightArray[i].setup(horizontalDimensions,verticalDimensions, testLocation);
    lightArray[i].passPointers(&creatureArray[0].creature_location,resonateArray);
  }
  tlc.begin();
  tlc.write();
}
void Installation::setupAudioProcessor(AudioOutputI2S* _i2s1,AudioInputI2S* _i2s2, AudioMixer4* _mixer1, AudioMixer4* _mixer2, AudioAnalyzePeak* _peak1, AudioSynthWaveformSine* _sine1, AudioEffectFreeverb* _freeverb1, AudioEffectDelay* _delay1, AudioControlSGTL5000* _sgtl5000,AudioSynthWaveformSineModulated* _sineFM1) {
  audioProcessor.setup(_i2s1,_i2s2,_mixer1,_mixer2,_peak1,_sine1,_freeverb1,_delay1,_sgtl5000,_sineFM1);
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
    tlc.setPWM(i,lightArray[i].brightness);
    /*
    float pwm = millis()%65000;
    float truePWM = constrain(pwm,0,55000);
    tlc.setPWM(i,truePWM);
    */

  }

  float currentPeak = audioProcessor.currentPeak;
  for (int i = 0; i < NUM_RESONATE; i++) {

    if (currentPeak > 0.5) {
      if (millis() - resonateTimer > 500) {
        if (resonateArray[i].bulb_life == 0) {
          for (int i = 0; i < 10; i++) {
            Vec3f bulbDirection = Vec3f(cos((TWO_PI/10)*i),sin((TWO_PI/10)*i),0);
            resonateArray[i].setup(creatureArray[0].creature_location, bulbDirection);
          }
          resonateTimer = millis();
        }
      }
    }


    if (resonateArray[i].bulb_life > 0) {
      resonateArray[i].loop();
    }

  } // End of resonateArray loop

  audioProcessor.process();
  if (millis() % 200 == 1) {
    tlc.write(); // Limit use of SPI for less audio interference
  }
}

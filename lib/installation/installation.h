#ifndef installation_h
#define installation_h

#include "Arduino.h"
#include <VectorXf.h>
#include "creature.h"
#include "light.h"
#include "resonateBulb.h"
#include "audioProcessor.h"

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

//#include <SPI.h>
#include <Adafruit_TLC59711.h>

#define NUM_CREATURES 1
#define NUM_LIGHTS 120
#define NUM_RESONATE 100

#define NUM_TLC59711 10
#define dataPin 29
#define clockPin 30

#define INSTALLATION_X 80 // Width
#define INSTALLATION_Z 80 // Depth
#define INSTALLATION_Y 80 // Height

class Installation {
public:
  Installation();
  void setup();
  void setupAudioProcessor(AudioOutputI2S* _i2s1,AudioInputI2S* _i2s2, AudioMixer4* _mixer1, AudioMixer4* _mixer2, AudioAnalyzePeak* _peak1, AudioSynthWaveformSine* _sine1, AudioEffectFreeverb* _freeverb1, AudioEffectDelay* _delay1, AudioControlSGTL5000* _sgtl5000, AudioSynthWaveformSineModulated* _sineFM1);
  void loop();
  void resonate();

  Vec2f horizontalDimensions;
  Vec2f verticalDimensions;

  Creature creatureArray[1];
  Light lightArray[120];
  ResonateBulb resonateArray[100];
  AudioProcessor audioProcessor;

  Adafruit_TLC59711 tlc = Adafruit_TLC59711(NUM_TLC59711, clockPin, dataPin);

  unsigned long resonateTimer;
private:
  Vec3f lightLocationArray[120] = {
    Vec3f(1,1,1),
  };

};

#endif

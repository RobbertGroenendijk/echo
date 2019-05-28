#ifndef installation_h
#define installation_h

#include "Arduino.h"

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

#include <VectorXf.h>

#include "../gammaCorrection/gammaCorrection.cpp"

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
  void resonate(float _peak);

  Vec2f horizontalDimensions;
  Vec2f verticalDimensions;

  Creature creatureArray[1];
  Light lightArray[120];
  ResonateBulb resonateArray[100];
  AudioProcessor audioProcessor;

  Adafruit_TLC59711 tlc = Adafruit_TLC59711(NUM_TLC59711, clockPin, dataPin);

  unsigned long resonateTimer;
  unsigned long tlcTimer;
private:
  Vec3f lightLocationArray[120] = {
    Vec3f(65.0,18.5,37.0), // 0
    Vec3f(59.0,21.0,16.5), // 1
    Vec3f(57.5,15.0,50.0), // 2
    Vec3f(53.0,21.0,48.5), // 3
    Vec3f(57.0,28.0,36.0), // 4
    Vec3f(52.0,29.0,28.0), // 5
    Vec3f(48.0,25.5,11.0), // 6
    Vec3f(75.0,19.0,63.0), // 7
    Vec3f(71.5,26.0,50.0), // 8
    Vec3f(69.5,21.0,13.0), // 9
    Vec3f(70.0,15.0,25.0), // 10
    Vec3f(64.0,26.5,24.0), // 11
    Vec3f(30.0,24.0,57.0), // 12
    Vec3f(34.0,19.0,46.0), // 13
    Vec3f(36.0,25.0,20.0), // 14
    Vec3f(40.0,15.0,23.0), // 15
    Vec3f(44.0,17.0,37.0), // 16
    Vec3f(44.0,22.0,18.0), // 17
    Vec3f(0.0,0.0,0.0), //SKIP 18
    Vec3f(17.5,16.0,21.0), // 19
    Vec3f(14.5,23.0,24.0), // 20
    Vec3f(21.0,27.0,37.0), // 21
    Vec3f(22.0,19.0,37.0), // 22
    Vec3f(24.0,23.0,26.0), // 23
    Vec3f(77.0,36.0,23.0), // 24
    Vec3f(72.0,36.0,30.0), // 25
    Vec3f(82.0,40.0,38.0), // 26
    Vec3f(78.0,43.0,50.0), // 27
    Vec3f(83.0,46.0,16.0), // 28
    Vec3f(78.0,49.0,34.0), // 29
    Vec3f(80.0,28.0,42.0), // 30
    Vec3f(69.0,30.0,40.0), // 31
    Vec3f(62.0,32.0,52.0), // 32
    Vec3f(55.0,34.0,23.0), // 33
    Vec3f(66.0,35.5,18.0), // 34
    Vec3f(53.5,39.0,42.0), // 35
    Vec3f(37.0,35.0,54.0), // 36
    Vec3f(33.0,41.0,66.0), // 37
    Vec3f(27.0,38.0,19.0), // 38
    Vec3f(18.5,41.0,17.0), // 39
    Vec3f(24.0,45.0,32.0), // 40
    Vec3f(27.0,48.0,59.0), // 41
    Vec3f(41.0,26.0,42.0), // 42
    Vec3f(41.5,32.0,38.0), // 43
    Vec3f(46.0,33.0,48.0), // 44
    Vec3f(33.0,32.0,32.0), // 45
    Vec3f(31.0,29.0,45.0), // 46
    Vec3f(20.0,35.0,40.0), // 47
    Vec3f(58.0,43.0,13.0), // 48
    Vec3f(61.0,38.0,61.0), // 49
    Vec3f(67.0,43.0,58.0),
    Vec3f(72.0,47.0,10.0),
    Vec3f(66.0,48.0,39.0),
    Vec3f(61.0,49.0,53.0),
    Vec3f(52.0,45.0,37.0),
    Vec3f(53.0,58.0,17.0),
    Vec3f(59.0,54.0,63.0),
    Vec3f(60.0,57.0,44.0),
    Vec3f(58.0,64.0,22.0),
    Vec3f(52.0,64.0,38.0),
    Vec3f(40.0,55.0,61.0),
    Vec3f(46.0,52.0,60.0),
    Vec3f(43.0,58.0,13.0),
    Vec3f(47.0,54.0,54.0),
    Vec3f(48.0,61.5,60.0),
    Vec3f(39.0,64.0,30.0), //65
    Vec3f(47.0,36.5,33.0),
    Vec3f(38.5,40.0,13.0),
    Vec3f(42.5,41.0,46.0),
    Vec3f(47.0,42.0,27.0),
    Vec3f(36.0,46.0,65.0), //70
    Vec3f(43.0,46.0,35.0),
    Vec3f(71.0,62.5,67.0),
    Vec3f(69.0,66.0,34.0),
    Vec3f(61.5,67.0,46.0),
    Vec3f(55.0,69.0,31.0), //75
    Vec3f(52.0,73.0,7.0),
    Vec3f(56.5,77.0,42.0),
    Vec3f(78.0,63.0,58.0),
    Vec3f(74.0,56.0,26.0),
    Vec3f(68.0,57.0,18.0), //80
    Vec3f(70.0,52.0,68.0),
    Vec3f(62.0,56.0,41.0),
    Vec3f(64.0,55.0,48.0),
    Vec3f(25.0,54.0,34.0),
    Vec3f(25.0,58.0,14.0), //85
    Vec3f(22.0,68.0,29.0),
    Vec3f(19.0,52.0,39.0),
    Vec3f(16.0,61.0,20.0),
    Vec3f(15.0,67.0,35.0),
    Vec3f(40.0,63.0,49.0), //90
    Vec3f(37.0,58.0,31.0),
    Vec3f(34.0,65.0,13.0),
    Vec3f(32.0,51.0,45.0),
    Vec3f(31.5,58.0,62.0),
    Vec3f(27.5,65.0,37.0), //95
    Vec3f(83.0,81.0,40.0),
    Vec3f(78.0,85.0,19.0),
    Vec3f(78.0,79.0,54.0),
    Vec3f(71.0,86.0,33.0),
    Vec3f(80.0,74.0,30.0), //100
    Vec3f(76.0,71.0,57.0),
    Vec3f(67.0,86.0,11.0),
    Vec3f(68.0,77.0,23.0),
    Vec3f(61.0,83.0,22.0),
    Vec3f(71.0,71.0,41.0), //105
    Vec3f(67.0,72.0,24.0),
    Vec3f(62.0,74.0,44.0),
    Vec3f(36.0,76.0,40.0),
    Vec3f(18.0,80.0,35.0),
    Vec3f(25.0,79.0,8.0), //110
    Vec3f(30.0,79.0,57.0),
    Vec3f(35.5,80.0,39.0),
    Vec3f(43.0,79.0,44.0),
    Vec3f(34.5,70.0,25.0),
    Vec3f(39.0,66.0,38.0), //115
    Vec3f(47.0,68.0,17.0),
    Vec3f(29.0,73.0,31.0),
    Vec3f(24.0,75.0,45.0),
    Vec3f(42.0,75.0,19.0),
  };
};

#endif

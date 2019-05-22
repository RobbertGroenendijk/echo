// General includes
#include <arduino.h>

// Personal includes
#include <installation.h>

// Audio Library includes
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

AudioInputI2S            i2s2;           //xy=241,341
AudioSynthWaveformSine   sine1;          //xy=334,552
AudioMixer4              mixer1;         //xy=395,359
AudioSynthWaveformSineModulated sine_fm1;       //xy=522,543
AudioAnalyzePeak         peak1;          //xy=523,326
AudioEffectDelay         delay1;         //xy=716,408
AudioEffectFreeverb      freeverb1;      //xy=833,270
AudioMixer4              mixer2;         //xy=1031,290
AudioOutputI2S           i2s1;           //xy=1215,284
AudioConnection          patchCord1(i2s2, 0, mixer1, 0);
AudioConnection          patchCord2(i2s2, 1, mixer1, 1);
AudioConnection          patchCord3(sine1, delay1);
AudioConnection          patchCord4(mixer1, peak1);
AudioConnection          patchCord5(sine_fm1, delay1);
AudioConnection          patchCord6(delay1, 0, freeverb1, 0);
AudioConnection          patchCord7(delay1, 0, mixer2, 1);
AudioConnection          patchCord8(freeverb1, 0, mixer2, 0);
AudioConnection          patchCord9(mixer2, 0, i2s1, 0);
AudioConnection          patchCord10(mixer2, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=249,147

Installation installation;

unsigned long serialTimestamp;

void setup() {
  Serial.begin(9600);

  installation.setup();
  installation.setupAudioProcessor(&i2s1,&i2s2,&mixer1,&mixer2,&peak1,&sine1,&freeverb1,&delay1,&sgtl5000_1,&sine_fm1);

  serialTimestamp = 0.0;
}

void loop() {
  installation.loop();

  if (millis() - serialTimestamp > 200) {
    Serial.print(installation.creatureArray[0].creature_location[0]);
    Serial.print("/");
    Serial.print(installation.creatureArray[0].creature_location[1]);
    Serial.print("/");
    Serial.print(installation.creatureArray[0].creature_location[2]);
    Serial.print("/");
    Serial.print(installation.creatureArray[0].target_location[0]);
    Serial.print("/");
    Serial.print(installation.creatureArray[0].target_location[1]);
    Serial.print("/");
    Serial.print(installation.creatureArray[0].target_location[2]);
    Serial.print("/");
    Serial.println(char(3));

    serialTimestamp = millis();
  }
}

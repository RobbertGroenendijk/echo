#ifndef light_h
#define light_h

#include "Arduino.h"
#include "../resonateBulb/resonateBulb.h"
#include <VectorXf.h>
#include <Adafruit_TLC59711.h>

#define NUM_TLC59711 10
#define data 25
#define clock 24

#define RESONATE_LENGTH 100

class Light {
public:
  Light();
  void setup(Vec2f _horizontalDimensions,Vec2f _verticalDimensions,Vec3f _location);
  void passPointers(Vec3f *_creatureLocation, ResonateBulb _resonateArray[]);
  void loop();

  void watchCreature();
  void watchResonate();
  void plusBrightness(float _amount);
  void minBrightness(float _amount);

  Vec2f horizontalDimensions;
  Vec2f verticalDimensions;
  Vec3f light_location;

  Vec3f *creature_location;
  ResonateBulb *resonateArray;

  float brightness;

  Adafruit_TLC59711 tlc = Adafruit_TLC59711(NUM_TLC59711, clock, data);
private:

};

#endif

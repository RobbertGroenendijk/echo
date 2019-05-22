#ifndef light_h
#define light_h

#include "Arduino.h"
#include "../resonateBulb/resonateBulb.h"
#include <VectorXf.h>

#define RESONATE_LENGTH 100

class Light {
public:
  Light();
  void setup(Vec2f _horizontalDimensions,Vec2f _verticalDimensions,Vec3f _location);
  void passPointers(Vec3f *_creatureLocation, ResonateBulb _resonateArray[]);
  void loop();

  void watchCreature();
  void watchResonate();
  void plusCreatureBrightness(float _amount);
  void minCreatureBrightness(float _amount);
  void plusResonateBrightness(float _amount);
  void minResonateBrightness(float _amount);

  Vec2f horizontalDimensions;
  Vec2f verticalDimensions;
  Vec3f light_location;

  Vec3f *creature_location;
  ResonateBulb *resonateArray;

  float brightness;
  float creatureBrightness;
  float resonateBrightness;
private:

};

#endif

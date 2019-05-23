#ifndef resonateBulb_h
#define resonateBulb_h

#include "Arduino.h"
#include <VectorXf.h>

class ResonateBulb {
public:
  ResonateBulb();
  void setup(Vec3f _creatureLocation, Vec3f _bulbDirection);
  void loop();
  void move();
  void age();
  void checkEdges();

  Vec3f bulb_direction;
  Vec3f bulb_origin;
  Vec3f bulb_location;

  float bulb_speed;

  float bulb_radius;

  float bulb_life;
  float bulb_ageRate;

private:

};

#endif

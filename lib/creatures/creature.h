#ifndef creature_h
#define creature_h

#include "Arduino.h"
#include <VectorXf.h>

class Creature {
public:
  Creature();
  void setup(Vec2f _horizontalDimensions, Vec2f _verticalDimensions);
  void loop();

  void applyForce(Vec3f _force);
  void seek();
  void move();

  void checkTarget();
  void setTarget();

  void triggerBeserk();
  void checkBeserk();
  void upBeserkSpeed();
  void lowerBeserkSpeed();

  Vec2f horizontalDimensions;
  Vec2f verticalDimensions;

  Vec3f creature_location;
  Vec3f creature_acceleration;
  Vec3f creature_velocity;

  int size;
  bool beserk;
  float beserkTimer;

  Vec3f target_location;

  float maxSpeed;
  float maxForce;
  float maxInitSpeed;
  float maxInitForce;
  float maxBeserkSpeed;
  float maxBeserkForce;
};

#endif

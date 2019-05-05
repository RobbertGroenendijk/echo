#ifndef installation_h
#define installation_h

#include "Arduino.h"
#include <VectorXf.h>
#include "creature.h"
#include "light.h"
#include "resonateBulb.h"

#define NUM_CREATURES 1
#define NUM_LIGHTS 120
#define NUM_RESONATE 100


#define INSTALLATION_X 100 // Width
#define INSTALLATION_Z 100 // Depth
#define INSTALLATION_Y 100 // Height

class Installation {
public:
  Installation();
  void setup();
  void loop();
  void resonate();

  Vec2f horizontalDimensions;
  Vec2f verticalDimensions;

  Creature creatureArray[1];
  Light lightArray[120];
  ResonateBulb resonateArray[100];

private:
};

#endif

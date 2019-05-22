#include <light.h>

Light::Light() {
  Serial.println("Light constructor triggered");

  brightness = 0;
}
void Light::setup(Vec2f _horizontalDimensions, Vec2f _verticalDimensions, Vec3f _location) {
  Serial.println("Light setup triggered");

  horizontalDimensions = _horizontalDimensions;
  verticalDimensions = _verticalDimensions;
  light_location = _location;

  brightness = 0;
  creatureBrightness = 0;
  resonateBrightness = 0;
}

void Light::passPointers(Vec3f *_creatureLocation, ResonateBulb _resonateArray[]) {
    creature_location = _creatureLocation;
    resonateArray = _resonateArray; // Arrays are always passed as pointers in C / C++
}

void Light::loop() {
  watchCreature();
  watchResonate();

  float trueBrightness = creatureBrightness + resonateBrightness;
  brightness = constrain(trueBrightness,0,50000);
}
void Light::watchCreature() {
  float distance = light_location.distance(*creature_location);
  if (distance < 25) {
    plusCreatureBrightness(2000);
  } else {
    minCreatureBrightness(500);
    minResonateBrightness(1000); // Check here, in resonate function this will always be declining because of the amount of resonateBulbs
  }
}
void Light::watchResonate() {
  for (int i = 0; i < RESONATE_LENGTH; i++) {
    if (resonateArray[i].bulb_life > 0) {
      float distance = light_location.distance(resonateArray[i].bulb_location);
      float radius = resonateArray[i].bulb_radius;

      if (distance < radius) {
        plusResonateBrightness(5000);
      }
    }
  }
}
void Light::plusCreatureBrightness(float _amount) {
  if (creatureBrightness < 65000) {
    creatureBrightness += _amount;
  }
  if (creatureBrightness > 65000) {
    creatureBrightness = 65000;
  }
}
void Light::minCreatureBrightness(float _amount) {
  if (creatureBrightness > 0) {
    creatureBrightness -= _amount;
  }
  if (creatureBrightness < 0) {
    creatureBrightness = 0;
  }
}
void Light::plusResonateBrightness(float _amount) {
  if (resonateBrightness < 65000) {
    resonateBrightness += _amount;
  }
  if (resonateBrightness > 65000) {
    resonateBrightness = 65000;
  }
}
void Light::minResonateBrightness(float _amount) {
  if (resonateBrightness > 0) {
    resonateBrightness -= _amount;
  }
  if (resonateBrightness < 0) {
    resonateBrightness = 0;
  }
}

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
}

void Light::passPointers(Vec3f *_creatureLocation, ResonateBulb _resonateArray[]) {
    creature_location = _creatureLocation;
    resonateArray = _resonateArray; // Arrays are always passed as pointers in C / C++
}

void Light::loop() {
  watchCreature();


}
void Light::watchCreature() {
  float distance = light_location.distance(*creature_location);
  if (distance < 25) {
    plusBrightness(4);
  } else {
    minBrightness(1);
  }
}
void Light::watchResonate() {
  for (int i = 0; i < RESONATE_LENGTH; i++) {
    if (resonateArray[i].bulb_life > 0) {
      float distance = light_location.distance(resonateArray[i].bulb_location);
      float radius = resonateArray[i].bulb_radius;

      if (distance < radius) {
        plusBrightness(10);
      }
    }
  }
}
void Light::plusBrightness(float _amount) {
  if (brightness < 255) {
    brightness += _amount;
  }
}
void Light::minBrightness(float _amount) {
  if (brightness > 0) {
    brightness -= _amount;
  }
}

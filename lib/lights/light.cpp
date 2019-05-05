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

  //tlc.begin();
  //tlc.write();
}

void Light::passPointers(Vec3f *_creatureLocation) {
    creature_location = _creatureLocation;
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

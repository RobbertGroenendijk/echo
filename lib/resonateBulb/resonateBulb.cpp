#include <resonateBulb.h>

ResonateBulb::ResonateBulb() {

}
void ResonateBulb::setup(Vec3f _creatureLocation, Vec3f _bulbDirection) {
  bulb_location = _creatureLocation;
  bulb_origin = _creatureLocation;
  bulb_direction = _bulbDirection;
  bulb_direction.normalize();

  bulb_speed = 5.0;

  bulb_life = 200;
  bulb_ageRate = 1;
  bulb_radius = 10;
}
void ResonateBulb::loop() {
  checkEdges();
  move();
  age();
}
void ResonateBulb::move() {
  Vec3f computedSpeed = bulb_direction * bulb_speed;
  bulb_location += computedSpeed;
}
void ResonateBulb::age() {
  bulb_life -= bulb_ageRate;
}
void ResonateBulb::checkEdges() {
  // X axis
  if (bulb_location[0] < 0) {
    bulb_direction *= -1;
  } else if (bulb_location[0] > 100) {
    bulb_direction *= -1;
  }

  // Y axis
  if (bulb_location[1] < 0) {
    bulb_direction *= -1;
  } else if (bulb_location[1] > 100) {
    bulb_direction *= -1;
  }

  // Z axis
  if (bulb_location[2] < 0) {
    bulb_direction *= -1;
  } else if (bulb_location[2] > 100) {
    bulb_direction *= -1;
  }
}

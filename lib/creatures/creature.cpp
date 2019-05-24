#include <creature.h>

Creature::Creature() {
  Serial.println("Creature constructor triggered");
}
void Creature::setup(Vec2f _horizontalDimensions, Vec2f _verticalDimensions) {
  Serial.println("Creature setup triggered");

  horizontalDimensions = _horizontalDimensions;
  verticalDimensions = _verticalDimensions;

  creature_location = Vec3f(40.0,40.0,40.0);
  creature_acceleration = Vec3f(0.0,0.0,0.0);
  creature_velocity = Vec3f(0.0,0.0,0.0);

  target_location = Vec3f(
    random(0,horizontalDimensions.x),
    random(0,horizontalDimensions.y),
    random(0,verticalDimensions.y));

  maxSpeed = 1.0;
  maxForce = 0.2;
  maxInitSpeed = maxSpeed;
  maxInitForce = maxForce;
  maxBeserkSpeed = 0.5;
  maxBeserkForce = maxSpeed/75;

  size = 50;
  beserk = false;
}
void Creature::loop() {
  seek();
  move();

  checkTarget();

  if (beserk) {
    checkBeserk();
    upBeserkSpeed();
  } else {
    lowerBeserkSpeed();
  } // End of beserk statement
}
void Creature::applyForce(Vec3f _force) {
  creature_acceleration += _force;
}
void Creature::seek() {
  Vec3f desiredVector = target_location - creature_location;
  Vec3f n_desiredVector = desiredVector.getNormalized();
  Vec3f f_desiredVector = n_desiredVector * maxForce;
  Vec3f steer = f_desiredVector - creature_velocity;

  Vec3f force = steer;
  applyForce(force);
}
void Creature::move() {
  creature_velocity += creature_acceleration;
  creature_velocity.limit(maxSpeed);
  creature_location += creature_velocity;

  Serial.println(creature_velocity[0]);

  creature_acceleration = Vec3f(0.0);
}
void Creature::checkTarget() {
  float distance = creature_location.distance(target_location);

  if (distance < 10.0) {
    setTarget();
  }
}
void Creature::setTarget() {
  target_location = Vec3f(random(0.0,80.0),random(0.0,80.0),random(0.0,80.0));
}
void Creature::triggerBeserk() {
  if (!beserk) {
    beserk = true;
    beserkTimer = millis(); // Keep track of when Beserk state starts
  }
}
void Creature::checkBeserk() {
  if (millis() - beserkTimer > 2500 && beserk == true) {
    beserk = false;
  }
}
void Creature::upBeserkSpeed() {
  if (maxForce < maxBeserkForce) {
    float forceDifference = maxBeserkForce - maxForce;
    maxForce += (forceDifference/100);
  }
  if (maxSpeed < maxBeserkSpeed) {
    float speedDifference = maxBeserkSpeed - maxSpeed;
    maxSpeed += (speedDifference/100);
  }
}
void Creature::lowerBeserkSpeed() {
  if (maxForce > maxInitForce) {
    float forceDifference = maxInitForce - maxForce;
    maxForce += (forceDifference/100);
  }
  if (maxSpeed < maxInitSpeed) {
    float speedDifference = maxInitSpeed - maxSpeed;
    maxSpeed += (speedDifference/100);
  }
}

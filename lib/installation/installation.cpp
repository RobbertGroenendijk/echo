#include "installation.h"

Installation::Installation() {
  Serial.println("Installation constructor triggered");
}
void Installation::setup() {
  Serial.println("Installation setup triggered");

  horizontalDimensions = Vec2f(INSTALLATION_X, INSTALLATION_Z);
  verticalDimensions = Vec2f(0,INSTALLATION_Y);

  for (int i = 0; i < NUM_CREATURES; i++) {
    creatureArray[i].setup(horizontalDimensions,verticalDimensions);
  }
  Vec3f testLocation = Vec3f(50,50,50);
  for (int i = 0; i < NUM_LIGHTS; i++) {
    lightArray[i].setup(horizontalDimensions,verticalDimensions, testLocation);
    lightArray[i].passPointers(&creatureArray[0].creature_location);
  }
}
void Installation::resonate() {
  int newResonates = 0;
  for (int i = 0; i < NUM_RESONATE; i++) {
    if (resonateArray[i].bulb_life < 1) {
      if (newResonates < 20) {
        Vec3f newDirection = Vec3f(cos((PI/20)*newResonates),sin((PI/20)*newResonates));
        resonateArray[i].setup(creatureArray[0].creature_location, newDirection);
      }
    }
  }
}
void Installation::loop() {
  //Serial.println("Installation loop");

  for (int i = 0; i < NUM_CREATURES; i++) {
    creatureArray[i].loop();
  }
  for (int i = 0; i < NUM_LIGHTS; i++) {
    lightArray[i].loop();
  }
  for (int i = 0; i < NUM_RESONATE; i++) {
    if (resonateArray[i].bulb_life > 0) {
      resonateArray[i].loop();
    }
  }
}

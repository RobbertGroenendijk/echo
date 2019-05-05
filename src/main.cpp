// General includes
#include <arduino.h>

// Personal includes
#include <installation.h>

Installation installation;

unsigned long serialTimestamp;

void setup() {
  installation.setup();

  Serial.begin(9600);

  serialTimestamp = 0.0;
}

void loop() {
  installation.loop();

  if (millis() - serialTimestamp > (1000/60)) {
    Serial.print(installation.creatureArray[0].creature_location[0]);
    Serial.print("/");
    Serial.print(installation.creatureArray[0].creature_location[1]);
    Serial.print("/");
    Serial.print(installation.creatureArray[0].creature_location[2]);
    Serial.print("/");
    Serial.print(installation.creatureArray[0].target_location[0]);
    Serial.print("/");
    Serial.print(installation.creatureArray[0].target_location[1]);
    Serial.print("/");
    Serial.print(installation.creatureArray[0].target_location[2]);
    Serial.print("/");
    Serial.println(char(3));

    serialTimestamp = millis();
  }
}

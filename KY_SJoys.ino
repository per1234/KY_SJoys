#include "KY_SJoys.h"

uint8_t VRx = 0;
uint8_t VRy = 1;
uint8_t SW  = 8;

KY_SJoys joystick(VRx, VRy, SW);

void setup() {
  // put your setup code here, to run once:
  joystick.initialize();
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.print("X: ");Serial.print(joystick.readVRx());
  //Serial.print(", Y: ");Serial.print(joystick.readVRy());
  Serial.print("X: ");Serial.print(joystick.readVRx(0,100));
  Serial.print(", Y: ");Serial.print(joystick.readVRy(0,100));
  Serial.print(", B: ");Serial.println(joystick.readSW());
  delay(250);
}

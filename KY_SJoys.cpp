/*
   KY_SJoys.cpp
   
   Copyright © 2017, by Wissem Boussetta

   This file is part of The KY-SJoys Keyes Joystick library for for arduino (KY-SJoys).

   KY-SJoys is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "KY_SJoys.h"
#include <Arduino.h>

KY_SJoys::KY_SJoys(uint8_t VRx, uint8_t VRy, uint8_t SW) {
  this->VRx = VRx;
  this->VRx = VRy;
  this->SW = SW;
}


void KY_SJoys::initialize() {
  pinMode(this->SW, INPUT);
  digitalWrite(this->SW, HIGH);
}

uint16_t KY_SJoys::readVRx() {
  return (uint16_t)analogRead(this->VRx);
}

int KY_SJoys::readVRx(int toLow, int toHigh) {
  uint16_t VRx = this->readVRx();
  return map(VRx, AXIS_MIN_VALUE, AXIS_MAX_VALUE, toLow, toHigh);
}

uint16_t KY_SJoys::readVRy() {
  return (uint16_t)analogRead(this->VRy);
}

int KY_SJoys::readVRy(int toLow, int toHigh) {
  uint16_t VRy = this->readVRy();
  return map(VRy, AXIS_MIN_VALUE, AXIS_MAX_VALUE, toLow, toHigh);
}

uint8_t KY_SJoys::readSW() {
  return (uint8_t)digitalRead(this->SW);
}

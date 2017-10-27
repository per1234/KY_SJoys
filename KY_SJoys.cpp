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

KY_SJoys::KY_SJoys(uint8_t VRx, uint8_t VRy, uint8_t SW, short sensitivity) {
  this->Pin[VRX_PIN] = VRx;
  this->Pin[VRY_PIN] = VRy;
  this->Pin[SW_PIN]  = SW;
  this->sensitivity = sensitivity;
}


void KY_SJoys::initialize() {
  pinMode(this->Pin[SW_PIN], INPUT);
  digitalWrite(this->Pin[SW_PIN], HIGH);
}

uint16_t KY_SJoys::readVRx() {
  return roundNum((uint16_t)analogRead(this->Pin[VRX_PIN]), this->sensitivity);
}

int KY_SJoys::readVRx(int toLow, int toHigh) {
  uint16_t VRx = this->readVRx();
  return map(VRx, AXIS_MIN_VALUE, AXIS_MAX_VALUE, toLow, toHigh);
}

uint16_t KY_SJoys::readVRy() {
  return roundNum((uint16_t)analogRead(this->Pin[VRY_PIN]), this->sensitivity);
}

int KY_SJoys::readVRy(int toLow, int toHigh) {
  uint16_t VRy = this->readVRy();
  return map(VRy, AXIS_MIN_VALUE, AXIS_MAX_VALUE, toLow, toHigh);
}

uint8_t KY_SJoys::readSW() {
  return (uint8_t)digitalRead(this->Pin[SW_PIN]);
}

SJoysInfo KY_SJoys::read() {
  SJoysInfo info = {this->readVRx(),
                    this->readVRy(),
                    this->readSW(),
                   };
  return info;
}

SJoysInfo KY_SJoys::read(int toLow, int toHigh) {
  SJoysInfo info = {this->readVRx(toLow, toHigh),
                    this->readVRy(toLow, toHigh),
                    this->readSW(),
                   };
  return info;
}

uint16_t KY_SJoys::roundNum(uint16_t toRound, uint8_t num) {
  uint16_t rem = toRound % num;
  return rem > (num / 2) ? (toRound - rem + num) : (toRound - rem);
}


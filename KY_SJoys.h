/*
   KY_SJoys.h

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

#ifndef KY_SJoys_h
#define KY_SJoys_h

#include <stdint.h>

#define SJOY_PIN_NBR    3
#define VRX_PIN         0
#define VRY_PIN         1
#define SW_PIN          2

#define EPSILON         5
#define AXIS_MIN_VALUE  0
#define AXIS_MAX_VALUE  1024

typedef struct SJoysInfo {
  short VRx;
  short VRy;
  short SW;
} SJoysInfo;

class KY_SJoys {
  public:
    KY_SJoys(uint8_t VRx, uint8_t VRy, uint8_t SW, short sensitivity);
    void initialize();
    uint16_t readVRx();
    uint16_t readVRy();
    uint8_t  readSW();
    /* */
    int readVRx(int toLow, int toHigh);
    int readVRy(int toLow, int toHigh);
    /* */
    SJoysInfo read();
    SJoysInfo read(int toLow, int toHigh);
  private:
    uint8_t Pin[SJOY_PIN_NBR];
    short sensitivity;
};

#endif

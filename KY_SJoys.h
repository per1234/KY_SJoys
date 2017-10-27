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

/*
   The <stdint.h> header shall declare sets of integer types having specified widths.
   It's intended to limit the variables size we are using and the system workload.
*/
#include <stdint.h>
/* Keyes SJoystick pins number */
#define SJOY_PIN_NBR    3
/* Macros used as reference to adress
   the Keyes SJoystick pins */
#define VRX_PIN         0
#define VRY_PIN         1
/* This pins have to be attached to a Digital Pin Usable For Interrupts.
   Use digital pin 2 or 3 with arduino uno boards. */
#define SW_PIN          2
/* Used as a default value for the sensitivity */
#define EPSILON         16
/* Maximum and Minimum X and Y Axis values default range. */
#define AXIS_MIN_VALUE  0
#define AXIS_MAX_VALUE  1024

/*
   This truct is defined to store SJoystick state when a
   SJoysInfo KY_SJoys::read() request occurs:
*/
typedef struct SJoysInfo {
  short VRx;  // X Axis status value.
  short VRy;  // Y Axis status value.
  short SW;   // Switch Button status.
} SJoysInfo;

/* Class definition of the Keyes SJoystick */
class KY_SJoys {
  public:
    KY_SJoys(uint8_t VRx, uint8_t VRy, uint8_t SW, short sensitivity);
    void initialize();
    uint16_t readVRx();   // Reads the X Axis status value.
    uint16_t readVRy();   // Reads the Y Axis status value.
    uint8_t  readSW();    // Reads the Switch Button status.

    int readVRx(int toLow, int toHigh);   // Reads the X Axis status value and re-maps it to a new range.
    int readVRy(int toLow, int toHigh);   // Reads the X Axis status value and re-maps it to a new range.

    /* Reads X Axis, Y Axis and the Switch Button in a one time operation
       and store it in a SJoysInfo struct. */
    SJoysInfo read();
    /* Does the same as SJoysInfo KY_SJoys::read() and re-maps it to a new range */
    SJoysInfo read(int toLow, int toHigh);
    /* KY_SJoys::roundNum() Rounds an integer 'toRound' to nearest multiple of 'num' */
    uint16_t roundNum(uint16_t toRound, uint8_t num);
  private:
    uint8_t Pin[SJOY_PIN_NBR];  /* used to store the Arduino pins connected to the Keyes SJoytick pins */
    short   sensitivity;        /* defines the measurements sensitivity */
};

#endif

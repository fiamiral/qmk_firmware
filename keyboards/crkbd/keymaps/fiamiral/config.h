/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

//#define USE_MATRIX_I2C

/* Select hand configuration */

//#define MASTER_LEFT
#define EE_HANDS

#define OLED_FONT_H "keyboards/crkbd/lib/glcdfont.c"


// Reduce size
#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE
#define NO_ACTION_ONESHOT
#define NO_MUSIC_MODE

#define NO_AUTO_SHIFT_SPECIAL
#define NO_AUTO_SHIFT_NUMERIC
#define AUTO_SHIFT_TIMEOUT 175
#define AUTO_SHIFT_MODIFIERS
#define AUTO_SHIFT_TIMEOUT_PER_KEY

#define TAPPING_TERM 200
#define PERMISSIVE_HOLD
#define IGNORE_MOD_TAP_INTERRUPT

// RGB
#ifdef RGBLIGHT_ENABLE
    #define RGBLIGHT_LAYERS
    #undef RGBLED_NUM
    #define RGBLED_NUM 54
    #undef RGBLED_SPLIT
    #define RGBLED_SPLIT {27, 27}
    #define RGBLIGHT_SPLIT
    #define RGBLIGHT_SLEEP
    #define RGBLIGHT_DEFAULT_HUE 123
    #define RGBLIGHT_DEFAULT_SAT 90
    #define RGBLIGHT_DEFAULT_VAL 112
#endif


// 1000hz polling
#define USB_POLLING_INTERVAL_MS 1
#define QMK_KEYS_PER_SCAN 12

// combo
# define COMBO_COUNT 5

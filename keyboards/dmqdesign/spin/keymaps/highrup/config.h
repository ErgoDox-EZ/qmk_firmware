/* Copyright 2019-2020 DMQ Design
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#define SSD1306OLED
#define RGBLIGHT_HUE_STEP 8
#define OLED_FONT_H "keyboards/dmqdesign/spin/keymaps/highrup/glcdfont.c"

#define TAP_CODE_DELAY 10
#define TAPPING_TERM 175
#define OLED_DISABLE_TIMEOUT

#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
//#define NO_ACTION_ONESHOT

#define DISABLE_LEADER
#ifdef LOCKING_SUPPORT_ENABLE
#    undef LOCKING_SUPPORT_ENABLE
#endif
#ifdef LOCKING_RESYNC_ENABLE
#    undef LOCKING_RESYNC_ENABLE
#endif

#undef RGBLIGHT_ANIMATIONS
//#define RGBLIGHT_EFFECT_STATIC

#define DRIVER_LED_TOTAL 3

#ifndef NO_DEBUG
#define NO_DEBUG
#endif // !NO_DEBUG
#if !defined(NO_PRINT) && !defined(CONSOLE_ENABLE)
#define NO_PRINT
#endif // !NO_PRINT

// place overrides here

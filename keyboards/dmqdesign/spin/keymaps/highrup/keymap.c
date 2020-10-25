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

#include QMK_KEYBOARD_H
#if OLED_DRIVER_ENABLE
#ifdef SNAKE_ENABLE
#include "snake.h"
#endif
#include "oled.c"
#endif
#define _BASE 0
#define _MID 1
#define _RAISE 2
#define _ADJUST 3
#define _GAME 4
#define _PHOTOSHOP 5
#define _INDESIGN 6
#define _SNAKE 7

#define PC_UNDO LCTL(KC_Z)
#define PC_REDO LCTL(KC_Y)
#define PC_CUT LCTL(KC_X)
#define PC_COPY LCTL(KC_C)
#define PC_PSTE LCTL(KC_V)
#define PC_FLDR LCTL(LSFT(KC_N))
#define EC_APPS ENABLE_APPSWITCHER
#define EC_TABS ENABLE_TABSWITCHER
#define EC_SHOP ENABLE_PSHOP
#define EC_MUSIC ENABLE_MUSIC

// Game layer shortcuts.
#define HEIRL LSFT(KC_H)
#define MOUNT LSFT(KC_X)
#define ACHIEV LSFT(KC_J)

// Mix of Photoshop, Illustrator, Premiere, and Experience Design shortcuts.
#define SAVE LCTL(KC_S)
#define OPEN LCTL(KC_O)
#define COPY LCTL(KC_C)
#define PAST LCTL(KC_V)
#define CUNDO LCTL(LALT(KC_Z))
#define INVRT LCTL(LSFT(KC_I))
#define NLAYR LSFT(LCTL(KC_N))
#define UNDO LCTL(KC_Z)
#define TRANS LCTL(KC_T)
#define ALGNL LCTL(LSFT(KC_L))
#define ALGNC LCTL(LSFT(KC_C))
#define ALGNR LCTL(LSFT(KC_R))
#define BRNGF LCTL(KC_RBRC)
#define BRNGB LCTL(KC_LBRC)

// Illustrator layer shortcuts.
#define SHAPE LSFT(KC_M)
#define RULER LCTL(LALT(KC_R))

// Premiere layer shortcuts.
#define REDO LCTL(LSFT(KC_Z))
#define EXPRT LCTL(KC_M)
#define IMPRT LCTL(KC_I)
#define PCOPY LCTL(KC_V)
#define PPSTE LCTL(LSFT(KC_V))

// Indesign layer shortcuts. (can be used with others too.)
#define NEW LCTL(KC_N)
#define LOCK LCTL(KC_L)
#define SYMB LCTL(KC_K)
#define HIDE LCTL(KC_SCLN)
#define RPEAT LCTL(KC_R)
#define MASK LCTL(LSFT(KC_M))
#define GROUP LCTL(KC_G)
#define UNGRP LCTL(LSFT(KC_G))
#define VIEW LCTL(KC_TAB)
#define HORZ LSFT(KC_C)
#define VERT LSFT(KC_M)

enum keycodes {
    ENABLE_APPSWITCHER = SAFE_RANGE,
    ENABLE_TABSWITCHER,
    ENABLE_ADJUST,
    ENABLE_MEDIA,
    ENABLE_GAME,
    ENABLE_GAME2,
    ENABLE_PSHOP,
    ENABLE_PSHOP2,
    ENABLE_INDES,
    ENABLE_INDES2,
    MC_QMK,
    SNAKE,
};

// For Photoshop:
uint8_t opacity = 60;
uint8_t opacity_increment = 5;

uint8_t size = 60;
uint8_t size_increment = 5;

//The below layers are intentionally empty in order to give a good starting point for how to configure multiple layers.
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(/* Base */
                SNAKE,      KC_KP_2,    KC_KP_3,    ENABLE_TABSWITCHER,
                KC_KP_4,    KC_KP_5,    KC_KP_6,    ENABLE_MEDIA,
                KC_KP_7,    KC_KP_8,    KC_KP_9,    ENABLE_APPSWITCHER,
                KC_LSFT,    KC_LCTRL,   KC_LALT
                ),

    [_MID] = LAYOUT(
                KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
                KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
                KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
                KC_TRNS,    KC_TRNS,    KC_TRNS
                ),

    [_RAISE] = LAYOUT(
                KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
                KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
                KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
                KC_TRNS,    KC_TRNS,    KC_TRNS
                ),

    [_ADJUST] = LAYOUT(
                RESET,      KC_TRNS,    MC_QMK,     KC_TRNS,
                KC_TRNS,    KC_TRNS,    KC_TRNS,    ENABLE_ADJUST,
                KC_LGUI,    KC_TRNS,    RGB_TOG,    KC_TRNS,
                KC_TRNS,    KC_TRNS,    KC_TRNS
                ),

    [_GAME] = LAYOUT(
                KC_NO,      KC_NO,      KC_NO,      ENABLE_GAME,
                KC_M,       KC_I,       HEIRL,      ENABLE_GAME2,
                ACHIEV,     KC_N,       MOUNT,      KC_TRNS,
                KC_TRNS,    KC_TRNS,    KC_TRNS
                ),

    [_PHOTOSHOP] = LAYOUT(
                KC_TRNS,    KC_TRNS,    KC_TRNS,    ENABLE_PSHOP,
                KC_TRNS,    KC_TRNS,    KC_TRNS,    ENABLE_PSHOP2,
                KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
                KC_TRNS,    KC_TRNS,    KC_TRNS
                ),

    [_INDESIGN] = LAYOUT(
                KC_TRNS,    KC_TRNS,    KC_TRNS,    ENABLE_INDES,
                KC_TRNS,    KC_TRNS,    KC_TRNS,    ENABLE_INDES2,
                KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
                KC_TRNS,    KC_TRNS,    KC_TRNS
                ),

    [_SNAKE] = LAYOUT(
                KC_LEFT,    KC_RIGHT,   KC_TRNS,    ENABLE_INDES,
                KC_TRNS,    KC_TRNS,    KC_TRNS,    ENABLE_INDES2,
                KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
                KC_TRNS,    KC_TRNS,    KC_TRNS
                )
};

// Light LEDs 6 to 9 and 12 to 15 red when caps lock is active. Hard to ignore!
const rgblight_segment_t PROGMEM my_base_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 3, 180, 255, 255},       // Light 3 LEDs, starting with LED 1
    {1, 3, 170, 200, 255},       // Light 3 LEDs, starting with LED 2
    {2, 3, 160, 170, 255}       // Light 3 LEDs, starting with LED 3
);
const rgblight_segment_t PROGMEM my_mid_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 3, 175, 190, 255},       // These are test colors until i set gradients
    {1, 3, 180, 210, 255},
    {2, 3, 180, 255, 255}
);
const rgblight_segment_t PROGMEM my_music_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 3, 220, 255, 255},
    {1, 3, 205, 220, 255},
    {2, 3, 200, 170, 255}
);
const rgblight_segment_t PROGMEM my_adjust_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 3, 0, 0, 255},
    {1, 3, 0, 0, 155},
    {2, 3, 0, 0, 100}
);
const rgblight_segment_t PROGMEM my_game_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 3, 0, 230, 255},
    {1, 3, 255, 210, 255},
    {2, 3, 10, 170, 255}
);
const rgblight_segment_t PROGMEM my_photoshop_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 3, 170, 255, 255},
    {1, 3, 160, 220, 255},
    {2, 3, 155, 170, 255}
);
const rgblight_segment_t PROGMEM my_indesign_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 3, 200, 255, 255},
    {1, 3, 190, 220, 255},
    {2, 3, 185, 170, 255}
);
const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 3, 0, 0, 255},
    {1, 3, 0, 0, 255},
    {2, 3, 0, 0, 0}
);
const rgblight_segment_t PROGMEM my_numlock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 3, 0, 0, 0},
    {1, 3, 0, 0, 255},
    {2, 3, 0, 0, 255}
);

// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_base_layer,
    my_mid_layer,
    my_music_layer,
    my_adjust_layer,
    my_game_layer,
    my_photoshop_layer,
    my_indesign_layer,
    my_capslock_layer,
    my_numlock_layer
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    // Call the post init code.
    rgblight_enable_noeeprom(); // enables Rgb, without saving settings
    rgblight_sethsv_noeeprom(255, 255, 0); // sets the color to teal/cyan without saving
    //rgblight_sethsv_at(HSV_WHITE, 0);
    //rgblight_sethsv_at(HSV_WHITE, 1);
    //rgblight_sethsv_at(HSV_WHITE, 2);
    rgblight_layers = my_rgb_layers;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    // Both layers will light up if both kb layers are active
    rgblight_set_layer_state(0, layer_state_cmp(state, 0));       // Layers 1-7
    rgblight_set_layer_state(1, layer_state_cmp(state, 1));
    rgblight_set_layer_state(2, layer_state_cmp(state, 2));
    rgblight_set_layer_state(3, layer_state_cmp(state, 3));
    rgblight_set_layer_state(4, layer_state_cmp(state, 4));
    rgblight_set_layer_state(5, layer_state_cmp(state, 5));
    rgblight_set_layer_state(6, layer_state_cmp(state, 6));
    return state;
}

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(7, led_state.caps_lock);       // These are seperate layers for key toggles
    rgblight_set_layer_state(8, led_state.num_lock);
    return true;
}

void matrix_init_user(void) {
    #ifdef SNAKE_ENABLE
      snake_first_time = false;
    #endif
}

// For Resetting Layer State:
layer_state_t selected_layer = 0;

static uint16_t key_timer;
bool appswitcher_enabled = false;
bool tabswitcher_enabled = false;
bool adjust_enabled = false;
bool media_enabled = false;
bool game_enabled = false;
bool game2_enabled = false;
bool pshop_enabled = false;
bool pshop2_enabled = false;
bool indes_enabled = false;
bool indes2_enabled = false;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
oled_timer = timer_read32();
switch (keycode) {
  case ENABLE_APPSWITCHER:
    if (record->event.pressed) {
      key_timer = timer_read();  // start the timer
      appswitcher_enabled = true;
      encoder_enabled = true;
      register_code16(KC_LALT);
      tap_code16(KC_TAB);
      tap_code16(LSFT(KC_TAB));
    } else {
      if (timer_elapsed(key_timer) < TAPPING_TERM) {
        appswitcher_enabled = false;
        encoder_enabled = true;
        mute_enabled = true;
        unregister_code16(KC_LALT);
        tap_code16(KC_MUTE);
        encoder_enabled = false;
      } else if (timer_elapsed(key_timer) < TAPPING_TERM + 500) {
        appswitcher_enabled = false;
        encoder_enabled = true;
        unregister_code16(KC_LALT);
        selected_layer = 0;
        layer_clear();
        encoder_enabled = false;
    } else {
      appswitcher_enabled = false;
      encoder_enabled = false;
      unregister_code16(KC_LALT);
      }
    }
    return false;
  case ENABLE_TABSWITCHER:
    if (record->event.pressed) {
      key_timer = timer_read();  // start the timer
      tabswitcher_enabled = true;
      encoder_enabled = true;
      register_code16(KC_LCTL);
      tap_code16(KC_TAB);
      tap_code16(LSFT(KC_TAB));
    } else {
      if (timer_elapsed(key_timer) < TAPPING_TERM) {
        tabswitcher_enabled = false;
        encoder_enabled = false;
        unregister_code16(KC_LCTL);
      	tap_code16(LCTL(KC_R));
    } else {
      tabswitcher_enabled = false;
      encoder_enabled = false;
      unregister_code16(KC_LCTL);
      }
    }
    return false;
  case ENABLE_MEDIA:
    if (record->event.pressed) {
      key_timer = timer_read();  // start the timer
      media_enabled = true;
      encoder_enabled = true;
    } else {
      if (timer_elapsed(key_timer) < TAPPING_TERM) {
        media_enabled = false;
        encoder_enabled = false;
        tap_code(KC_MPLY);
    } else {
      media_enabled = false;
      encoder_enabled = false;
      }
    }
    return false;
  case ENABLE_ADJUST:
    if (record->event.pressed) {
      adjust_enabled = true;
      encoder_enabled = true;
    } else {
      adjust_enabled = false;
      encoder_enabled = false;
    }
    return false;
  case ENABLE_GAME:
    if (record->event.pressed) {
      key_timer = timer_read();  // start the timer
      game_enabled = true;
      encoder_enabled = true;
      register_code16(KC_LCTL);
    } else {
      if (timer_elapsed(key_timer) < TAPPING_TERM) {
        game_enabled = false;
        encoder_enabled = false;
        unregister_code16(KC_LCTL);
      } else {
        game_enabled = false;
        encoder_enabled = false;
        unregister_code16(KC_LCTL);
      }
    }
    return false;
  case ENABLE_GAME2:
    if (record->event.pressed) {
      key_timer = timer_read();  // start the timer
      game2_enabled = true;
      encoder_enabled = true;
      register_code16(KC_LSFT);
    } else {
      if (timer_elapsed(key_timer) < TAPPING_TERM) {
        game2_enabled = false;
        encoder_enabled = false;
        unregister_code16(KC_LSFT);
        tap_code(KC_ESC);
      } else {
        game2_enabled = false;
        encoder_enabled = false;
        unregister_code16(KC_LSFT);
      }
    }
    return false;
  case ENABLE_PSHOP:
    if (record->event.pressed) {
      key_timer = timer_read();  // start the timer
      pshop_enabled = true;
      encoder_enabled = true;
    } else {
      if (timer_elapsed(key_timer) < TAPPING_TERM) {
        pshop_enabled = false;
        encoder_enabled = false;
        tap_code(KC_B);
      } else {
        pshop_enabled = false;
        encoder_enabled = false;
      }
    }
    return false;
  case ENABLE_PSHOP2:
    if (record->event.pressed) {
      key_timer = timer_read();  // start the timer
      pshop2_enabled = true;
      encoder_enabled = true;
    } else {
      if (timer_elapsed(key_timer) < TAPPING_TERM) {
        pshop2_enabled = false;
        encoder_enabled = false;
        tap_code(KC_B);
      } else {
        pshop2_enabled = false;
        encoder_enabled = false;
      }
    }
    return false;
  case ENABLE_INDES:
    if (record->event.pressed) {
      key_timer = timer_read();  // start the timer
      indes_enabled = true;
      encoder_enabled = true;
    } else {
      if (timer_elapsed(key_timer) < TAPPING_TERM) {
        indes_enabled = false;
        encoder_enabled = false;
        tap_code(KC_NO);
      } else {
        indes_enabled = false;
        encoder_enabled = false;
      }
    }
    return false;
  case ENABLE_INDES2:
    if (record->event.pressed) {
      key_timer = timer_read();  // start the timer
      indes2_enabled = true;
      encoder_enabled = true;
    } else {
      if (timer_elapsed(key_timer) < TAPPING_TERM) {
        indes2_enabled = false;
        tap_code(KC_NO);
      } else {
        indes2_enabled = false;
      }
    }
    return false;
  case MC_QMK:
    if(record->event.pressed) {
      key_timer = timer_read();  // start the timer
      return false;
    } else {
      if (timer_elapsed(key_timer) < TAPPING_TERM) {
        SEND_STRING ("cd C:/qmk_firmware"); // Change the character(s) to be sent on tap here
        tap_code(KC_ENT);
        return false;
      } else {
        SEND_STRING ("make dmqdesign/spin:highrup"); // Change the character(s) to be sent on hold here
        tap_code(KC_ENT);
        return true;
      }
    }
    return false;
  case SNAKE:
    #ifdef SNAKE_ENABLE
      if (record->event.pressed) {
        // snake_init();
        snake_first_time = true;
        layer_on(_SNAKE);
      }
    #endif
    return false;
  #ifdef SNAKE_ENABLE
  if (IS_LAYER_ON(_SNAKE)) {
    snake_key = keycode;
    if (record->event.pressed)
    {
      snake_new_key = true;
    }
  }
  #endif
  }
  if (record->event.pressed) {
    #ifdef OLED_DRIVER_ENABLE
      oled_timer = timer_read32();
      add_keylog(keycode);
    #endif
  }
  return true;
}

void matrix_render_user(struct CharacterMatrix *matrix) {
    if (IS_LAYER_ON(_SNAKE)) {
      #ifdef SNAKE_ENABLE
      snake_frame(matrix);
      #endif
    }
}

void encoder_update_user(uint8_t index, bool clockwise) {
oled_timer = timer_read32();
uint8_t currentLayer = biton32(layer_state);
  if (index == 0) { /* First encoder */
  //break each encoder update into a switch statement for the current layer
    switch (currentLayer) {
      case _PHOTOSHOP:
        if (pshop_enabled) {
          if (!clockwise) {
            tap_code16(LSFT(KC_MINS));
          } else {
            tap_code16(LSFT(KC_EQL));
          }
        } else {
          uint8_t mods = get_mods();
          if (mods & MOD_MASK_SHIFT) {
            if (!clockwise) {
              unregister_mods(MOD_MASK_SHIFT);
              if (opacity < 0 + opacity_increment) {
                opacity = 0;
              } else {
                opacity -= opacity_increment;
              }
            } else {
              unregister_mods(MOD_MASK_SHIFT);
              if (opacity > 100 - opacity_increment) {
                opacity = 100;
              } else {
                opacity += opacity_increment;
              }
            }
            if(mods & MOD_BIT(KC_LSFT)){
              register_code(KC_LSFT);
            }
            if(mods & MOD_BIT(KC_RSFT)){
              register_code(KC_RSFT);
            }

            uint8_t opacity_to_type = opacity;
              if (opacity_to_type == 0) {
                opacity_to_type = 1;
              }

              uint8_t last = opacity_to_type % 10;
              uint8_t first = opacity_to_type / 10 % 10;
              uint8_t digits[2] = {first, last};
              for(int i = 0; i < 2; ++i) {
                switch (digits[i]) {
                case 0: tap_code(KC_0); break;
                case 1: tap_code(KC_1); break;
                case 2: tap_code(KC_2); break;
                case 3: tap_code(KC_3); break;
                case 4: tap_code(KC_4); break;
                case 5: tap_code(KC_5); break;
                case 6: tap_code(KC_6); break;
                case 7: tap_code(KC_7); break;
                case 8: tap_code(KC_8); break;
                case 9: tap_code(KC_9); break;
              }
            }
          } else {
            if (!clockwise) {
              tap_code16(LCTL(KC_Z));
            } else {
              tap_code16(LSFT(LCTL(KC_Z)));
            }
          }
        }
        break;
      case _GAME:
        if (game_enabled) {
          if (!clockwise) {
            tap_code16(KC_TAB);
          } else {
            tap_code16(LSFT(KC_TAB));
          }
        } else {
          if (!clockwise) {
            tap_code(KC_TAB);
          } else {
            tap_code16(LSFT(KC_TAB));
          }
        }
        break;
      default:
        if (tabswitcher_enabled) {
          if (!clockwise) {
            tap_code16(LSFT(KC_TAB));
          } else {
            tap_code16(KC_TAB);
          }
        } else {
          uint8_t mods = get_mods();
          if (mods & MOD_MASK_SHIFT) {
            if (!clockwise) {
              tap_code(KC_WBAK);
            } else {
              tap_code(KC_WFWD);
            }
          } else {
            if (!clockwise) {
              tap_code16(LCTL(KC_PGUP));
            } else {
              tap_code16(LCTL(KC_PGDN));
            }
          }
        }
        break;
    }
  } else if (index == 1) { /* Second encoder */
    switch (currentLayer) {
      case _PHOTOSHOP:
        if (pshop2_enabled) {
          if (!clockwise) {
            tap_code16(LSFT(KC_RBRC));
          } else {
            tap_code16(LSFT(KC_LBRC));
          }
        } else {
          if (!clockwise) {
            tap_code(KC_LBRC);
          } else {
            tap_code(KC_RBRC);
          }
        }
        break;
      case _GAME:
        if (game2_enabled) {
          if (!clockwise) {
            tap_code(KC_RBRC);
          } else {
            tap_code(KC_LBRC);
          }
        } else {
          if (!clockwise) {
            tap_code16(KC_WH_D);
          } else {
            tap_code16(KC_WH_U);
          }
        }
        break;
      case _RAISE:
        if (media_enabled) {
          if (!clockwise) {
            tap_code(KC_MPRV);
          } else {
            tap_code(KC_MNXT);
          }
        } else {
          uint8_t mods = get_mods();
          if (mods & MOD_MASK_SHIFT) {
            if (!clockwise) {
              unregister_mods(MOD_MASK_SHIFT);
              tap_code(KC_LEFT);
            } else {
              unregister_mods(MOD_MASK_SHIFT);
              tap_code(KC_RIGHT);
            }
            if(mods & MOD_BIT(KC_LSFT)){
              register_code(KC_LSFT);
            }
            if(mods & MOD_BIT(KC_RSFT)){
              register_code(KC_RSFT);
            }
          } else {
            if (!clockwise) {
              tap_code16(KC_NO);
            } else {
              tap_code16(KC_NO);
            }
          }
        }
        break;
      case _ADJUST:
        if (adjust_enabled) {
          if (!clockwise) {
            tap_code16(RGB_RMOD);
          } else {
            tap_code16(RGB_MOD);
          }
        } else {
          uint8_t mods = get_mods();
          if (mods & MOD_MASK_SHIFT) {
            if (!clockwise) {
              rgblight_decrease_val();
            } else {
              rgblight_increase_val();
            }
          } else {
            if (!clockwise) {
              rgblight_decrease_hue();
            } else {
              rgblight_increase_hue();
            }
          }
        }
        break;
      default:
        if (media_enabled) {
          if (!clockwise) {
            tap_code(KC_NO);
          } else {
            tap_code(KC_NO);
          }
        } else {
          uint8_t mods = get_mods();
          if (mods & MOD_MASK_SHIFT) {
            if (!clockwise) {
              unregister_mods(MOD_MASK_SHIFT);
              tap_code(KC_LEFT);
            } else {
              unregister_mods(MOD_MASK_SHIFT);
              tap_code(KC_RIGHT);
            }
            if(mods & MOD_BIT(KC_LSFT)){
              register_code(KC_LSFT);
            }
            if(mods & MOD_BIT(KC_RSFT)){
              register_code(KC_RSFT);
            }
          } else {
            if (!clockwise) {
              tap_code16(KC_WH_U);
            } else {
              tap_code16(KC_WH_D);
            }
          }
        }
        break;
    }
  } else if (index == 2) { /* Third encoder */
    switch (currentLayer) {
      default:
        if (appswitcher_enabled) {
          if (!clockwise) {
            tap_code16(LSFT(KC_TAB));
          } else {
            tap_code16(KC_TAB);
          }
          return;
        } else {
          uint8_t mods = get_mods();
          if (mods & MOD_MASK_SHIFT) {
            if (!clockwise) {
              selected_layer --;
            } else {
              selected_layer ++;
            }
            layer_clear();
            layer_on(selected_layer % 7);
            return;
          } else {
            if (!clockwise) {
              tap_code(KC_VOLU);
              mute_enabled = false;
            } else {
              tap_code(KC_VOLD);
              mute_enabled = false;
            }
          }
        }
        break;
      }
   }
}

#include QMK_KEYBOARD_H
#define _BL 0
#define _PS 1
#define _AI 2
#define _IN 3
#define _WL 4

enum my_keycodes {
  ENABLE_APPSWITCHER = SAFE_RANGE, //encoder triggers for secondary functions
  ENABLE_TABSWITCHER,
  ENABLE_AUDIO,
  ENABLE_WOW,
  ENABLE_WOW2,
  ENABLE_PSHOP,
  ENABLE_PSHOP2,
  ENABLE_ILLUS,
  ENABLE_ILLUS2,
  ENABLE_INDES,
  ENABLE_INDES2,
  FIRST_KEY, // macros for single and double press
  SECOND_KEY,
  THIRD_KEY,
};

layer_state_t selected_layer = 0;

// For Photoshop:
uint8_t opacity = 60;
uint8_t opacity_increment = 5;

const uint16_t PROGMEM fn_actions[] = {
// use FUNC(#) for actions in keymap
    [0] = ACTION_MODS_KEY(MOD_LALT | MOD_LCTL, KC_Z),              // step back
    [1] = ACTION_MODS_KEY(MOD_LSFT | MOD_LCTL, KC_Z),              // step forward
    [2] = ACTION_MODS_KEY(MOD_LCTL, KC_S),                         // save
    [3] = ACTION_MODS_KEY(MOD_LALT, KC_BSPC),                      // fill
    [4] = ACTION_MODS_KEY(MOD_LSFT, KC_M),                         // marquee select
    [5] = ACTION_MODS_KEY(MOD_LALT, KC_LBRC),                      // prev layer
    [6] = ACTION_MODS_KEY(MOD_LALT, KC_RBRC),                      // next layer
    [7] = ACTION_MODS_KEY(MOD_LCTL, KC_MINS),                      // zoom out
    [8] = ACTION_MODS_KEY(MOD_LCTL, KC_EQL),                       // zoom in
    [9] = ACTION_MODS_KEY(MOD_LSFT | MOD_LCTL, KC_X),              // liquify filter
    [10] = ACTION_MODS_KEY(MOD_LSFT, KC_MINS),                     // prev layer blending
    [11] = ACTION_MODS_KEY(MOD_LSFT | MOD_LALT, KC_N),             // normal layer blending
    [12] = ACTION_MODS_KEY(MOD_LSFT, KC_EQL),                      // next layer blending
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Macropad
 * ,--------------------.
 * | Enc1 | Enc2 | Enc3 |
 * |------+------+------|
 * |   1  |   2  |   3  |
 * `--------------------'
 */
[_BL] = LAYOUT(
	ENABLE_APPSWITCHER, ENABLE_AUDIO, ENABLE_TABSWITCHER,
	FIRST_KEY, SECOND_KEY, THIRD_KEY
),
[_PS] = LAYOUT(
	ENABLE_APPSWITCHER, ENABLE_PSHOP, ENABLE_PSHOP2,
	_______,  _______,  _______
),
[_AI] = LAYOUT(
	ENABLE_APPSWITCHER, ENABLE_ILLUS, ENABLE_ILLUS2,
	_______,  _______,  _______
),
[_IN] = LAYOUT(
	ENABLE_APPSWITCHER, ENABLE_INDES, ENABLE_INDES2,
	_______,  _______,  _______
),
[_WL] = LAYOUT(
	ENABLE_APPSWITCHER, ENABLE_WOW, ENABLE_WOW2,
	_______,  _______,  _______
),
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
  uint8_t layer = biton32(layer_state);
  // INSERT CODE HERE: turn off all leds
  switch (layer) {
    default: //  for any other layers, or the default layer
      rgblight_sethsv_at(190, 255, 255, 0);
      rgblight_sethsv_at(185, 200, 255, 1);
      rgblight_sethsv_at(160, 110, 255, 2);
      break; // add case for each layer
    case 1:
      rgblight_sethsv_at(175, 200, 255, 0);
      rgblight_sethsv_at(170, 150, 255, 1);
      rgblight_sethsv_at(160, 160, 255, 2);
      break;
    case 2:
      rgblight_sethsv_at(6, 245, 255, 0);
      rgblight_sethsv_at(12, 240, 255, 1);
      rgblight_sethsv_at(7, 245, 255, 2);
      break;
    case 3:
      rgblight_sethsv_at(235, 230, 255, 0);
      rgblight_sethsv_at(250, 230, 255, 1);
      rgblight_sethsv_at(190, 225, 255, 2);
      break;
    case 4:
      rgblight_sethsv_at(18, 255, 255, 0);
      rgblight_sethsv_at(10, 240, 255, 1);
      rgblight_sethsv_at(255, 250, 255, 2);
      break;
    }
};

bool appswitcher_enabled = false;
bool tabswitcher_enabled = false;
bool audio_enabled = false;
bool wow_enabled = false;
bool wow2_enabled = false;
bool pshop_enabled = false;
bool pshop2_enabled = false;
bool illus_enabled = false;
bool illus2_enabled = false;
bool indes_enabled = false;
bool indes2_enabled = false;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
static uint16_t my_hash_timer;
  switch (keycode) {
    case FIRST_KEY:
      if(IS_LAYER_ON(1)) {
        if(record->event.pressed) {
          my_hash_timer = timer_read();  // start the timer
          return false;
        } else {
          if (timer_elapsed(my_hash_timer) < TAPPING_TERM) {
            tap_code(KC_V); // Set MOVE tool in photoshop, sent on tap here
            return false;
          } else {
            tap_code16(LSFT(KC_M)); // Set SELECTION tool in photoshop, sent on hold here
            return true;
          }
        }
      } else if(IS_LAYER_ON(2)) {
        if(record->event.pressed) {
          my_hash_timer = timer_read();  // start the timer
          return false;
        } else {
          if (timer_elapsed(my_hash_timer) < TAPPING_TERM) {
            tap_code(KC_V); // Change the character(s) to be sent on tap here
            return false;
          } else {
            tap_code16(LSFT(KC_A)); // Change the character(s) to be sent on hold here
            return true;
          }
        }
      } else if(IS_LAYER_ON(3)) {
        if(record->event.pressed) {
          my_hash_timer = timer_read();  // start the timer
          return false;
        } else {
          if (timer_elapsed(my_hash_timer) < TAPPING_TERM) {
            tap_code(KC_V); // Change the character(s) to be sent on tap here
            return false;
          } else {
            tap_code(KC_E); // Change the character(s) to be sent on hold here
            return true;
          }
        }
      } else if(IS_LAYER_ON(4)) {
        if(record->event.pressed) {
          my_hash_timer = timer_read();  // start the timer
          return false;
        } else {
          if (timer_elapsed(my_hash_timer) < TAPPING_TERM) {
            tap_code(KC_M); // Opens WORLD MAP in wow, sent on tap
            return false;
          } else {
            tap_code16(LSFT(KC_J)); // Opens ACHIEVEMENTS in wow, sent on hold
            return true;
          }
        }
      } else {
        if(record->event.pressed) {
          my_hash_timer = timer_read();  // start the timer
          return false;
        } else {
          if (timer_elapsed(my_hash_timer) < TAPPING_TERM) {
            tap_code16(LCTL(KC_R)); // REFRESH in browser, sent on tap here
            return false;
          } else {
            tap_code16(LCTL(KC_W)); // CLOSE tab in browser, sent on hold here
            return true;
          }
        }
      break;
    }
  }
  switch (keycode) {
    case SECOND_KEY:
      if(IS_LAYER_ON(1)) {
        if(record->event.pressed) {
          my_hash_timer = timer_read();  // start the timer
          return false;
        } else {
          if (timer_elapsed(my_hash_timer) < TAPPING_TERM) {
            tap_code16(KC_P); // Set PEN tool in photoshop, sent on tap here
            return false;
          } else {
            tap_code16(LSFT(KC_U)); // Set SHAPE tool in photoshop, sent on hold here
            return true;
          }
        }
      } else if(IS_LAYER_ON(2)) {
        if(record->event.pressed) {
          my_hash_timer = timer_read();  // start the timer
          return false;
        } else {
          if (timer_elapsed(my_hash_timer) < TAPPING_TERM) {
            tap_code(KC_T); // Change the character(s) to be sent on tap here
            return false;
          } else {
            tap_code16(LSFT(KC_O)); // Change the character(s) to be sent on hold here
            return true;
          }
        }
      } else if(IS_LAYER_ON(3)) {
        if(record->event.pressed) {
          my_hash_timer = timer_read();  // start the timer
          return false;
        } else {
          if (timer_elapsed(my_hash_timer) < TAPPING_TERM) {
            tap_code(KC_M); // Change the character(s) to be sent on tap here
            return false;
          } else {
            tap_code(KC_L); // Change the character(s) to be sent on hold here
            return true;
          }
        }
      } else if(IS_LAYER_ON(4)) {
        if(record->event.pressed) {
          my_hash_timer = timer_read();  // start the timer
          return false;
        } else {
          if (timer_elapsed(my_hash_timer) < TAPPING_TERM) {
            tap_code(KC_I); //  Opens the DUNGEON/RAID finder in wow, sent on tap here
            return false;
          } else {
            tap_code(KC_N); // Opens the TALENT TREE in wow, sent on hold here
            return true;
          }
        }
      } else {
        if(record->event.pressed) {
          my_hash_timer = timer_read();  // start the timer
          return false;
        } else {
          if (timer_elapsed(my_hash_timer) < TAPPING_TERM) {
            tap_code16(LCTL(KC_B)); // Opens BOOKMARKS in browser, sent on tap here
            return false;
          } else {
             tap_code16(LCTL(KC_H)); // Opens HISTORY in browser, sent on hold here
             return true;
          }
        }
      break;
    }
  }
  switch (keycode) {
    case THIRD_KEY:
      if(IS_LAYER_ON(1)) {
        if(record->event.pressed) {
          my_hash_timer = timer_read();  // start the timer
          return false;
        } else {
          if (timer_elapsed(my_hash_timer) < TAPPING_TERM) {
            tap_code16(LCTL(KC_S)); // Save file in photoshop, sent on tap here
            return false;
          } else {
            tap_code16(LSFT(LCTL(KC_S))); // Save file as in photoshop, sent on hold here
            return true;
          }
        }
      } else if(IS_LAYER_ON(2)) {
        if(record->event.pressed) {
          my_hash_timer = timer_read();  // start the timer
          return false;
        } else {
          if (timer_elapsed(my_hash_timer) < TAPPING_TERM) {
            tap_code(KC_NUBS); // Change the character(s) to be sent on tap here
            return false;
          } else {
            tap_code(KC_I); // Change the character(s) to be sent on hold here
            return true;
          }
        }
      } else if(IS_LAYER_ON(3)) {
        if(record->event.pressed) {
          my_hash_timer = timer_read();  // start the timer
          return false;
        } else {
          if (timer_elapsed(my_hash_timer) < TAPPING_TERM) {
            tap_code(KC_NO); // Change the character(s) to be sent on tap here
            return false;
          } else {
            tap_code(KC_NO); // Change the character(s) to be sent on hold here
            return true;
          }
        }
      } else if(IS_LAYER_ON(4)) {
        if(record->event.pressed) {
          my_hash_timer = timer_read();  // start the timer
          return false;
        } else {
          if (timer_elapsed(my_hash_timer) < TAPPING_TERM) {
            tap_code16(LSFT(KC_H)); // Opens HEIRLOOMS in wow, sent on tap
            return false;
          } else {
            tap_code16(LSFT(KC_Q)); // Opens the MOUNTS in wow, sent on hold here
            return true;
          }
        }
      } else {
        if(record->event.pressed) {
          my_hash_timer = timer_read();  // start the timer
          return false;
        } else {
          if (timer_elapsed(my_hash_timer) < TAPPING_TERM) {
            tap_code16(LALT(KC_M)); // Minimize web browser, sent on tap here
            return false;
          } else {
             tap_code(KC_MYCM); // Open MY COMPUTER in windows, sent on hold here
             return true;
          }
        }
      break;
    }
  }
  switch (keycode) {
    case ENABLE_APPSWITCHER:
      if (record->event.pressed) {
        my_hash_timer = timer_read();  // start the timer
        appswitcher_enabled = true;
        register_code16(KC_LALT);
        tap_code16(KC_TAB);
        tap_code16(LSFT(KC_TAB));
      } else {
        if (timer_elapsed(my_hash_timer) < TAPPING_TERM) {
        appswitcher_enabled = false;
        unregister_code16(KC_LALT);
        selected_layer = 0;
        layer_clear();
      } else {
        appswitcher_enabled = false;
        unregister_code16(KC_LALT);
        }
      }
      return false;
    case ENABLE_TABSWITCHER:
      if (record->event.pressed) {
        tabswitcher_enabled = true;
        register_code16(KC_LCTL);
        tap_code16(KC_TAB);
        tap_code16(LSFT(KC_TAB));
      } else {
        if (timer_elapsed(my_hash_timer) < TAPPING_TERM) {
        unregister_code16(KC_LCTL);
        reset_keyboard();
      } else {
        tabswitcher_enabled = false;
        unregister_code16(KC_LCTL);
        }
      }
      return false;
    case ENABLE_AUDIO:
      if (record->event.pressed) {
        my_hash_timer = timer_read();  // start the timer
        audio_enabled = true;
      } else {
        if (timer_elapsed(my_hash_timer) < TAPPING_TERM) {
        audio_enabled = false;
        tap_code(KC_MUTE);
        return false;
      } else {
        audio_enabled = false;
        }
      }
      return false;
    case ENABLE_WOW:
      if (record->event.pressed) {
        my_hash_timer = timer_read();  // start the timer
        wow_enabled = true;
        register_code16(KC_LCTL);
      } else {
        if (timer_elapsed(my_hash_timer) < TAPPING_TERM) {
        wow_enabled = false;
        unregister_code16(KC_LCTL);
      } else {
        wow_enabled = false;
        unregister_code16(KC_LCTL);
        }
      }
      return false;
    case ENABLE_WOW2:
      if (record->event.pressed) {
        my_hash_timer = timer_read();  // start the timer
        wow2_enabled = true;
        register_code16(KC_LSFT);
      } else {
        wow2_enabled = false;
        if (timer_elapsed(my_hash_timer) < TAPPING_TERM) {
        unregister_code16(KC_LSFT);
        tap_code(KC_ESC);
      } else {
        wow2_enabled = false;
        unregister_code16(KC_LSFT);
        }
      }
      return false;
    case ENABLE_PSHOP:
      if (record->event.pressed) {
        my_hash_timer = timer_read();  // start the timer
        pshop_enabled = true;
      } else {
        if (timer_elapsed(my_hash_timer) < TAPPING_TERM) {
        tap_code(KC_ESC);
      } else {
        pshop_enabled = false;
        }
      }
      return false;
    case ENABLE_PSHOP2:
      if (record->event.pressed) {
        my_hash_timer = timer_read();  // start the timer
        pshop2_enabled = true;
      } else {
        if (timer_elapsed(my_hash_timer) < TAPPING_TERM) {
        tap_code(KC_B);
      } else {
        pshop2_enabled = false;
        }
      }
      return false;
    case ENABLE_ILLUS:
      if (record->event.pressed) {
        my_hash_timer = timer_read();  // start the timer
        illus_enabled = true;
      } else {
        if (timer_elapsed(my_hash_timer) < TAPPING_TERM) {
        tap_code(KC_P);
      } else {
        illus_enabled = false;
        }
      }
      return false;
    case ENABLE_ILLUS2:
      if (record->event.pressed) {
        my_hash_timer = timer_read();  // start the timer
        illus2_enabled = true;
      } else {
        if (timer_elapsed(my_hash_timer) < TAPPING_TERM) {
        tap_code(KC_B);
      } else {
        illus2_enabled = false;
        }
      }
      return false;
    case ENABLE_INDES:
      if (record->event.pressed) {
        my_hash_timer = timer_read();  // start the timer
        indes_enabled = true;
      } else {
        if (timer_elapsed(my_hash_timer) < TAPPING_TERM) {
        tap_code(KC_NO);
      } else {
        indes_enabled = false;
        }
      }
      return false;
    case ENABLE_INDES2:
      if (record->event.pressed) {
        my_hash_timer = timer_read();  // start the timer
        indes2_enabled = true;
      } else {
        if (timer_elapsed(my_hash_timer) < TAPPING_TERM) {
        tap_code(KC_NO);
      } else {
        indes2_enabled = false;
        }
      }
      return false;
    default:
      return true; // Process all other keycodes normally
  }
}

void encoder_update_user(uint8_t index, bool clockwise) {
if (index == 0) {
    switch(index){
        default:
            if (appswitcher_enabled) {
                if (clockwise) {
                    tap_code16(LSFT(KC_TAB));
                } else {
                    tap_code16(KC_TAB);
                }
            }
            if (appswitcher_enabled == false) {
                if (clockwise) {
                    selected_layer --;
                } else {
                    selected_layer ++;
                }
                layer_clear();
                layer_on(selected_layer % 5);
            }
            break;
        }
    }
if (index == 1) {
    switch(biton32(layer_state)){
        default:
            if (audio_enabled) {
                if (clockwise) {
                    tap_code(KC_MPRV);
                } else {
                    tap_code(KC_MNXT);
                }
            }
            if (audio_enabled == false) {
                if (clockwise){
                    tap_code(KC_VOLD);
                } else {
                    tap_code(KC_VOLU);
                }
            }
            break;
        case 1:
            if (pshop_enabled) {
                if (clockwise){
                    tap_code16(LALT(LCTL(KC_Z)));
                } else {
                    tap_code16(LSFT(LCTL(KC_Z)));
                }
            }
            if (pshop_enabled == false) {
                if (clockwise){
                    tap_code16(LSFT(KC_LBRC));
                } else {
                    tap_code16(LSFT(KC_RBRC));
                }
            }
            break;
        case 2:
            if (illus_enabled) {
                  if (clockwise) {
                     tap_code(KC_MINS);
                  } else {
                     tap_code16(LSFT(KC_EQL));
                  }
            }
            if (illus_enabled == false) {
                  if (clockwise){
                     tap_code(KC_NO);
                  } else {
                     tap_code(KC_NO);
                  }
            }
            break;
        case 4:
            if (wow_enabled) {
                if (clockwise) {
                    tap_code16(LSFT(KC_TAB));
                } else {
                    tap_code16(KC_TAB);
                }
            }
            if (wow_enabled == false) {
                if (clockwise){
                    tap_code16(LSFT(KC_TAB));
                } else {
                    tap_code(KC_TAB);
                }
            }
            break;
        }
    }
else if (index == 2) {
    switch(biton32(layer_state)){
        default:
            if (tabswitcher_enabled) {
                if (clockwise) {
                    tap_code16(LSFT(KC_TAB));
                } else {
                    tap_code16(KC_TAB);
                }
            }
            if (tabswitcher_enabled == false) {
                if (clockwise){
                    tap_code(KC_WH_U);
                } else {
                    tap_code(KC_WH_D);
                }
            }
            break;
        case 1:
            if (pshop2_enabled) {
                if (!clockwise) {
                    if (opacity > 100 - opacity_increment) {
                        opacity = 100;
                    } else {
                        opacity += opacity_increment;
                    }
                } else {
                    if (opacity < 0 + opacity_increment) {
                        opacity = 0;
                    } else {
                        opacity -= opacity_increment;
                    }
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
            }
            if (pshop2_enabled == false) {
                if (clockwise){
                    tap_code(KC_LBRC);
                } else {
                    tap_code(KC_RBRC);
                }
            }
            break;
        case 2:
            if (illus2_enabled) {
                if (clockwise) {
                    tap_code(KC_NO);
                } else {
                    tap_code(KC_NO);
                }
            }
            if (illus2_enabled == false) {
                if (clockwise){
                    tap_code(KC_NO);
                } else {
                    tap_code(KC_NO);
                }
            }
            break;
        case 4:
            if (wow2_enabled) {
                if (clockwise) {
                    tap_code(KC_LBRC);
                } else {
                    tap_code(KC_RBRC);
                }
            }
            if (wow2_enabled == false) {
                if (clockwise){
                    tap_code(KC_WH_U);
                } else {
                    tap_code(KC_WH_D);
                }
            }
            break;
        }
    }
}

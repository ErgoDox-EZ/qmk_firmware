#include QMK_KEYBOARD_H
#define _BL 0
#define _PS 1
#define _AI 2
#define _IN 3
#define _WL 4

enum my_keycodes {
  ENABLE_APPSWITCHER = SAFE_RANGE, //encoder triggers for secondary functions
  ENABLE_TABSWITCHER,
  ENABLE_MUSIC,
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
  KC_QMK,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* _BL
 * ,--------------------.
 * | Apps | Audio| Tabs |
 * |------+------+------|
 * | Rfrsh| BkMrk|MinWin|
 * |------+------+------|
 * |ClsTab| Hstry| MyPC |
 * `--------------------'
 */
[_BL] = LAYOUT(
	ENABLE_APPSWITCHER, ENABLE_MUSIC, ENABLE_TABSWITCHER,
	FIRST_KEY, SECOND_KEY, THIRD_KEY
),
/* _PS
 * ,--------------------.
 * | Apps | Pshop|Pshop2|
 * |------+------+------|
 * | Move |  Pen | Save |
 * |------+------+------|
 * | Selct| Shape| SavAs|
 * `--------------------'
 */
[_PS] = LAYOUT(
	ENABLE_APPSWITCHER, ENABLE_PSHOP, ENABLE_PSHOP2,
	_______,  _______,  _______
),
/* _AI
 * ,--------------------.
 * | Apps | Illus|Illus2|
 * |------+------+------|
 * |   1  |   2  |   3  |
 * |------+------+------|
 * |   4  |   5  |   6  |
 * `--------------------'
 */
[_AI] = LAYOUT(
	ENABLE_APPSWITCHER, ENABLE_ILLUS, ENABLE_ILLUS2,
	_______,  _______,  _______
),
/* _IN
 * ,--------------------.
 * | Apps | Indes|Indes2|
 * |------+------+------|
 * |   1  |   2  |   3  |
 * |------+------+------|
 * |   4  |   5  |   6  |
 * `--------------------'
 */
[_IN] = LAYOUT(
	ENABLE_APPSWITCHER, ENABLE_INDES, ENABLE_INDES2,
	_______,  _______,  _______
),
/* _WL
 * ,--------------------.
 * | Apps |  Wow | Wow2 |
 * |------+------+------|
 * |   1  |   2  |   3  |
 * |------+------+------|
 * |   4  |   5  |   6  |
 * `--------------------'
 */
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

// For Photoshop:
uint8_t opacity = 60;
uint8_t opacity_increment = 5;

// For Resetting Layer State:
layer_state_t selected_layer = 0;

bool wow_enabled = false;
bool wow2_enabled = false;
bool pshop_enabled = false;
bool pshop2_enabled = false;
bool illus_enabled = false;
bool illus2_enabled = false;
bool indes_enabled = false;
bool indes2_enabled = false;
bool music_enabled = false;
bool appswitcher_enabled = false;
bool tabswitcher_enabled = false;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
static uint16_t key_timer;
switch (keycode) {
  case FIRST_KEY:
    if(IS_LAYER_ON(_PS)) {
      if(record->event.pressed) {
        key_timer = timer_read();  // start the timer
        return false;
      } else {
        if (timer_elapsed(key_timer) < TAPPING_TERM) {
          tap_code(KC_V); // Set MOVE tool in photoshop, sent on tap here
          return false;
        } else {
          tap_code16(LSFT(KC_M)); // Set SELECTION tool in photoshop, sent on hold here
          return true;
        }
      }
    } else if(IS_LAYER_ON(_AI)) {
      if(record->event.pressed) {
        key_timer = timer_read();  // start the timer
        return false;
      } else {
        if (timer_elapsed(key_timer) < TAPPING_TERM) {
          tap_code(KC_V); // Change the character(s) to be sent on tap here
          return false;
        } else {
          tap_code(KC_I); // Change the character(s) to be sent on hold here
          return true;
        }
      }
    } else if(IS_LAYER_ON(_IN)) {
      if(record->event.pressed) {
        key_timer = timer_read();  // start the timer
        return false;
      } else {
        if (timer_elapsed(key_timer) < TAPPING_TERM) {
          tap_code(KC_V); // Change the character(s) to be sent on tap here
          return false;
        } else {
          tap_code(KC_I); // Change the character(s) to be sent on hold here
          return true;
        }
      }
    } else if(IS_LAYER_ON(_WL)) {
      if(record->event.pressed) {
        key_timer = timer_read();  // start the timer
        return false;
      } else {
        if (timer_elapsed(key_timer) < TAPPING_TERM) {
          tap_code(KC_M); // Opens WORLD MAP in wow, sent on tap here
          return false;
        } else {
          tap_code16(LSFT(KC_J)); // Opens ACHIEVEMENTS in wow, sent on hold here
          return true;
        }
      }
    } else {
      if(record->event.pressed) {
        key_timer = timer_read();  // start the timer
        return false;
      } else {
        if (timer_elapsed(key_timer) < TAPPING_TERM) {
          tap_code16(LCTL(KC_W)); // CLOSE tab in browser, sent on tap here
          return false;
        } else {
          tap_code16(LCTL(KC_R)); // REFRESH in browser, sent on hold here
          return true;
        }
      }
    }
    break;
  case SECOND_KEY:
    if(IS_LAYER_ON(_PS)) {
      if(record->event.pressed) {
        key_timer = timer_read();  // start the timer
        return false;
      } else {
        if (timer_elapsed(key_timer) < TAPPING_TERM) {
          tap_code16(KC_P); // Set PEN tool in photoshop, sent on tap here
          return false;
        } else {
          tap_code16(LSFT(KC_U)); // Set SHAPE tool in photoshop, sent on hold here
          return true;
        }
      }
    } else if(IS_LAYER_ON(_AI)) {
      if(record->event.pressed) {
        key_timer = timer_read();  // start the timer
        return false;
      } else {
        if (timer_elapsed(key_timer) < TAPPING_TERM) {
          tap_code(KC_T); // Change the character(s) to be sent on tap here
          return false;
        } else {
          tap_code(KC_NUBS); // Change the character(s) to be sent on hold here
          return true;
        }
      }
    } else if(IS_LAYER_ON(_IN)) {
      if(record->event.pressed) {
        key_timer = timer_read();  // start the timer
        return false;
      } else {
        if (timer_elapsed(key_timer) < TAPPING_TERM) {
          tap_code(KC_M); // Change the character(s) to be sent on tap here
          return false;
        } else {
          tap_code(KC_L); // Change the character(s) to be sent on hold here
          return true;
        }
      }
    } else if(IS_LAYER_ON(_WL)) {
      if(record->event.pressed) {
        key_timer = timer_read();  // start the timer
        return false;
      } else {
        if (timer_elapsed(key_timer) < TAPPING_TERM) {
          tap_code(KC_I); //  Opens the DUNGEON/RAID finder in wow, sent on tap here
          return false;
        } else {
          tap_code(KC_N); // Opens the TALENT TREE in wow, sent on hold here
          return true;
        }
      }
    } else {
      if(record->event.pressed) {
        key_timer = timer_read();  // start the timer
        return false;
      } else {
        if (timer_elapsed(key_timer) < TAPPING_TERM) {
          tap_code16(LCTL(KC_B)); // Opens BOOKMARKS in browser, sent on tap here
          return false;
        } else {
           tap_code16(LCTL(KC_H)); // Opens HISTORY in browser, sent on hold here
           return true;
        }
      }
    }
    break;
  case THIRD_KEY:
    if(IS_LAYER_ON(_PS)) {
      if(record->event.pressed) {
        key_timer = timer_read();  // start the timer
        return false;
      } else {
        if (timer_elapsed(key_timer) < TAPPING_TERM) {
          tap_code16(LCTL(KC_S)); // Save file in photoshop, sent on tap here
          return false;
      } else {
        tap_code16(LSFT(LCTL(KC_S))); // Save file as in photoshop, sent on hold here
        return true;
        }
      }
    } else if(IS_LAYER_ON(_AI)) {
      if(record->event.pressed) {
        key_timer = timer_read();  // start the timer
        return false;
      } else {
        if (timer_elapsed(key_timer) < TAPPING_TERM) {
          tap_code16(LSFT(KC_O)); // Change the character(s) to be sent on tap here
          return false;
        } else {
          tap_code16(LALT(LCTL(KC_P))); // Change the character(s) to be sent on hold here
          return true;
        }
      }
    } else if(IS_LAYER_ON(_IN)) {
      if(record->event.pressed) {
        key_timer = timer_read();  // start the timer
        return false;
      } else {
        if (timer_elapsed(key_timer) < TAPPING_TERM) {
          tap_code(KC_NO); // Change the character(s) to be sent on tap here
          return false;
        } else {
          tap_code(KC_NO); // Change the character(s) to be sent on hold here
          return true;
        }
      }
    } else if(IS_LAYER_ON(_WL)) {
      if(record->event.pressed) {
        key_timer = timer_read();  // start the timer
        return false;
      } else {
        if (timer_elapsed(key_timer) < TAPPING_TERM) {
          tap_code16(LSFT(KC_H)); // Opens HEIRLOOMS in wow, sent on tap here
          return false;
        } else {
          tap_code16(LSFT(KC_X)); // Opens the MOUNTS in wow, sent on hold here
          return true;
        }
      }
    } else {
      if(record->event.pressed) {
        key_timer = timer_read();  // start the timer
        return false;
      } else {
        if (timer_elapsed(key_timer) < TAPPING_TERM) {
          tap_code(KC_MYCM); // Open MY COMPUTER, sent on tap here
          return false;
        } else {
          SEND_STRING ("make abstract/ellipse/rev1:highrup"); // Sends QMK SCRIPT to flash macropad, sent on hold here
          tap_code(KC_ENT);
          return true;
        }
      }
    }
    break;
}
switch (keycode) {
  case ENABLE_APPSWITCHER:
    if (record->event.pressed) {
      key_timer = timer_read();  // start the timer
      appswitcher_enabled = true;
      register_code16(KC_LALT);
      tap_code16(KC_TAB);
      tap_code16(LSFT(KC_TAB));
    } else {
      if (timer_elapsed(key_timer) < TAPPING_TERM) {
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
      key_timer = timer_read();  // start the timer
      tabswitcher_enabled = true;
      register_code16(KC_LCTL);
      tap_code16(KC_TAB);
      tap_code16(LSFT(KC_TAB));
    } else {
      if (timer_elapsed(key_timer) < TAPPING_TERM) {
        tabswitcher_enabled = false;
        unregister_code16(KC_LCTL);
        tap_code16(LCTL(KC_R));
      } else {
        tabswitcher_enabled = false;
        unregister_code16(KC_LCTL);
      }
    }
    return false;
  case ENABLE_MUSIC:
    if (record->event.pressed) {
      key_timer = timer_read();  // start the timer
      music_enabled = true;
    } else {
      if (timer_elapsed(key_timer) < TAPPING_TERM) {
        music_enabled = false;
        tap_code(KC_MUTE);
        return false;
      } else {
        music_enabled = false;
      }
    }
    return false;
  case ENABLE_WOW:
    if (record->event.pressed) {
      key_timer = timer_read();  // start the timer
      wow_enabled = true;
      register_code16(KC_LCTL);
    } else {
      if (timer_elapsed(key_timer) < TAPPING_TERM) {
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
      key_timer = timer_read();  // start the timer
      wow2_enabled = true;
      register_code16(KC_LSFT);
    } else {
      if (timer_elapsed(key_timer) < TAPPING_TERM) {
      wow2_enabled = false;
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
      key_timer = timer_read();  // start the timer
      pshop_enabled = true;
    } else {
      if (timer_elapsed(key_timer) < TAPPING_TERM) {
        pshop_enabled = false;
        tap_code(KC_ESC);
      } else {
        pshop_enabled = false;
      }
    }
    return false;
  case ENABLE_PSHOP2:
    if (record->event.pressed) {
      key_timer = timer_read();  // start the timer
      pshop2_enabled = true;
    } else {
      if (timer_elapsed(key_timer) < TAPPING_TERM) {
        pshop2_enabled = false;
        tap_code(KC_B);
      } else {
        pshop2_enabled = false;
      }
    }
    return false;
  case ENABLE_ILLUS:
    if (record->event.pressed) {
      key_timer = timer_read();  // start the timer
      illus_enabled = true;
    } else {
      if (timer_elapsed(key_timer) < TAPPING_TERM) {
        illus_enabled = false;
        tap_code(KC_P);
      } else {
        illus_enabled = false;
      }
    }
    return false;
  case ENABLE_ILLUS2:
    if (record->event.pressed) {
      key_timer = timer_read();  // start the timer
      illus2_enabled = true;
    } else {
      if (timer_elapsed(key_timer) < TAPPING_TERM) {
        illus2_enabled = false;
        tap_code(KC_B);
      } else {
        illus2_enabled = false;
      }
    }
    return false;
  case ENABLE_INDES:
    if (record->event.pressed) {
      key_timer = timer_read();  // start the timer
      indes_enabled = true;
    } else {
      if (timer_elapsed(key_timer) < TAPPING_TERM) {
        indes_enabled = false;
        tap_code(KC_NO);
      } else {
        indes_enabled = false;
      }
    }
    return false;
  case ENABLE_INDES2:
    if (record->event.pressed) {
      key_timer = timer_read();  // start the timer
      indes2_enabled = true;
    } else {
      if (timer_elapsed(key_timer) < TAPPING_TERM) {
        indes2_enabled = false;
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
    switch(biton32(layer_state)) {
    default:
      if (appswitcher_enabled) {
        if (!clockwise) {
          tap_code16(LSFT(KC_TAB));
        } else {
          tap_code16(KC_TAB);
        }
      } if (appswitcher_enabled == false) {
        if (!clockwise) {
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
  switch(biton32(layer_state)) {
    case 1:
      if (pshop_enabled) {
        if (!clockwise) {
          register_code16(LALT(LCTL(KC_Z)));
          unregister_code16(LALT(LCTL(KC_Z)));
        } else {
          register_code16(LSFT(LCTL(KC_Z)));
          unregister_code16(LSFT(LCTL(KC_Z)));
        }
      } else {
        if (!clockwise) {
          if (opacity < 0 + opacity_increment) {
            opacity = 0;
          } else {
            opacity -= opacity_increment;
          }
        } else {
          if (opacity > 100 - opacity_increment) {
            opacity = 100;
          } else {
            opacity += opacity_increment;
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
      break;
    case 2:
      if (illus_enabled) {
        if (!clockwise) {
          tap_code(KC_MINS);
        } else {
          tap_code(KC_EQL);
        }
      } else {
        if (!clockwise) {
          register_code16(LCTL(KC_Z));
          unregister_code16(LCTL(KC_Z));
        } else {
          register_code16(LSFT(LCTL(KC_Z)));
          unregister_code16(LSFT(LCTL(KC_Z)));
        }
      }
      break;
    case 4:
      if (wow_enabled) {
        if (!clockwise) {
          tap_code16(LSFT(KC_TAB));
        } else {
          tap_code16(KC_TAB);
        }
      } else {
        if (!clockwise) {
          tap_code16(LSFT(KC_TAB));
        } else {
          tap_code(KC_TAB);
        }
      }
      break;
    default:
      if (music_enabled) {
        if (!clockwise) {
          tap_code(KC_MPRV);
        } else {
          tap_code(KC_MNXT);
        }
      } else {
        if (!clockwise) {
          tap_code(KC_VOLD);
        } else {
          tap_code(KC_VOLU);
        }
      }
      break;
    }
  }
if (index == 2) {
  switch(biton32(layer_state)) {
    case 1:
      if (pshop2_enabled == false) {
        if (!clockwise) {
          register_code(KC_LBRC);
          unregister_code(KC_LBRC);
          } else {
          register_code(KC_RBRC);
          unregister_code(KC_RBRC);
        }
      } else {
        if (!clockwise) {
          register_code16(LSFT(KC_LBRC));
          unregister_code16(LSFT(KC_LBRC));
        } else {
          register_code16(LSFT(KC_RBRC));
          unregister_code16(LSFT(KC_RBRC));
        }
      }
      break;
    case 2:
      if (illus2_enabled) {
        if (!clockwise) {
          tap_code(KC_NO);
        } else {
          tap_code(KC_NO);
        }
      } else {
        if (!clockwise) {
          register_code(KC_LBRC);
          unregister_code(KC_LBRC);
          } else {
          register_code(KC_RBRC);
          unregister_code(KC_RBRC);
        }
      }
      break;
    case 4:
      if (wow2_enabled) {
        if (!clockwise) {
          tap_code(KC_LBRC);
        } else {
          tap_code(KC_RBRC);
        }
      } else {
        if (!clockwise) {
          tap_code(KC_WH_U);
        } else {
          tap_code(KC_WH_D);
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
        if (!clockwise) {
          tap_code(KC_WH_U);
        } else {
          tap_code(KC_WH_D);
        }
      }
      break;
    }
  }
}

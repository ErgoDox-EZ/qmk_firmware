#include QMK_KEYBOARD_H
#ifdef AUDIO_ENABLE
#include "muse.h"
#endif
#include "eeprom.h"
#include "keymap_german.h"
#include "keymap_nordic.h"
#include "keymap_french.h"
#include "keymap_spanish.h"
#include "keymap_hungarian.h"
#include "keymap_swedish.h"
#include "keymap_br_abnt2.h"
#include "keymap_canadian_multilingual.h"
#include "keymap_german_ch.h"
#include "keymap_jp.h"
#include "keymap_bepo.h"
#include "keymap_italian.h"
#include "keymap_slovenian.h"
#include "keymap_danish.h"
#include "keymap_norwegian.h"
#include "keymap_portuguese.h"

#define KC_MAC_UNDO LGUI(KC_Z)
#define KC_MAC_CUT LGUI(KC_X)
#define KC_MAC_COPY LGUI(KC_C)
#define KC_MAC_PASTE LGUI(KC_V)
#define KC_PC_UNDO LCTL(KC_Z)
#define KC_PC_CUT LCTL(KC_X)
#define KC_PC_COPY LCTL(KC_C)
#define KC_PC_PASTE LCTL(KC_V)
#define ES_LESS_MAC KC_GRAVE
#define ES_GRTR_MAC LSFT(KC_GRAVE)
#define ES_BSLS_MAC ALGR(KC_6)
#define NO_PIPE_ALT KC_GRAVE
#define NO_BSLS_ALT KC_EQUAL
#define LSA_T(kc) MT(MOD_LSFT | MOD_LALT, kc)
#define BP_NDSH_MAC ALGR(KC_8)

enum planck_keycodes {
  RGB_SLD = EZ_SAFE_RANGE,
  HSV_17_255_211,
  HSV_0_0_255,
  ST_MACRO_0,
  ST_MACRO_1,
  ST_MACRO_2,
  DE_LSPO,
  DE_RSPC,
};

enum planck_layers {
  _BASE,
  _LOWER,
  _RAISE,
  _ADJUST,
  _LAYER4,
  _LAYER5,
  _LAYER6,
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_planck_grid(KC_ESCAPE,KC_Q,KC_W,KC_E,KC_R,KC_T,DE_Z,KC_U,KC_I,KC_O,KC_P,KC_BSPACE,KC_TAB,KC_A,KC_S,KC_D,KC_F,KC_G,KC_H,KC_J,KC_K,KC_L,DE_PLUS,KC_ENTER,KC_LSHIFT,DE_Y,KC_X,KC_C,KC_V,KC_B,KC_N,KC_M,KC_COMMA,KC_DOT,DE_MINS,LT(5,DE_HASH),LCTL_T(KC_SYSTEM_WAKE),KC_LGUI,KC_LALT,LT(5,KC_NO),TT(1),KC_SPACE,KC_NO,TT(2),KC_LEFT,KC_DOWN,KC_UP,KC_RIGHT),

  [_LOWER] = LAYOUT_planck_grid(KC_TRANSPARENT,KC_F1,KC_F2,KC_F3,KC_F4,KC_F5,KC_F6,KC_F7,KC_F8,KC_F9,KC_F10,KC_TRANSPARENT,KC_TRANSPARENT,ST_MACRO_0,KC_CALCULATOR,ST_MACRO_1,LGUI(KC_M),LGUI(KC_L),LALT(LCTL(KC_DELETE)),KC_NO,KC_NO,KC_F11,KC_F12,KC_TRANSPARENT,KC_TRANSPARENT,ST_MACRO_2,TT(4),TO(6),KC_INSERT,KC_APPLICATION,KC_NO,KC_PAUSE,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_NO,KC_TRANSPARENT,KC_END,KC_PGDOWN,KC_PGUP,KC_HOME),

  [_RAISE] = LAYOUT_planck_grid(KC_TRANSPARENT,KC_1,KC_2,KC_3,KC_4,KC_5,KC_6,KC_7,KC_8,KC_9,KC_0,KC_TRANSPARENT,KC_TRANSPARENT,DE_EXLM,KC_NO,DE_LCBR,DE_LBRC,DE_LPRN,DE_RPRN,DE_RBRC,DE_RCBR,DE_EQL,DE_QST,KC_TRANSPARENT,KC_TRANSPARENT,DE_LESS,KC_NO,DE_DQOT,DE_ACUT,DE_QUOT,DE_SLSH,DE_BSLS,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_NO,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT),

  [_ADJUST] = LAYOUT_planck_grid(KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,MAGIC_TOGGLE_NKRO,KC_TRANSPARENT,WEBUSB_PAIR,KC_TRANSPARENT,LED_LEVEL,RGB_SLD,RGB_SPI,RGB_SPD,KC_TRANSPARENT,TO(6),KC_TRANSPARENT,AU_ON,AU_OFF,AU_TOG,KC_TRANSPARENT,KC_TRANSPARENT,RGB_TOG,RGB_VAI,RGB_VAD,HSV_17_255_211,RESET,KC_TRANSPARENT,KC_TRANSPARENT,MU_ON,MU_OFF,MU_TOG,KC_TRANSPARENT,KC_TRANSPARENT,RGB_MOD,RGB_HUI,RGB_HUD,HSV_0_0_255,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_NO,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT),

  [_LAYER4] = LAYOUT_planck_grid(KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_KP_PLUS,KC_KP_7,KC_KP_8,KC_KP_9,KC_KP_ASTERISK,KC_TRANSPARENT,KC_TRANSPARENT,KC_CAPSLOCK,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_KP_MINUS,KC_KP_4,KC_KP_5,KC_KP_6,KC_KP_SLASH,DE_EQL,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_NUMLOCK,KC_KP_1,KC_KP_2,KC_KP_3,KC_COMMA,KC_DOT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,TO(1),TO(0),KC_TRANSPARENT,KC_NO,KC_KP_0,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT),

  [_LAYER5] = LAYOUT_planck_grid(KC_TRANSPARENT,DE_AT,KC_TRANSPARENT,DE_EURO,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,DE_UE,KC_TRANSPARENT,DE_OE,KC_PSCREEN,KC_DELETE,KC_TRANSPARENT,DE_AE,DE_SS,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,DE_PIPE,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_AUDIO_MUTE,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_NO,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT),

  [_LAYER6] = LAYOUT_planck_grid(KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,TO(0),KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_PGUP,KC_UP,KC_PGDOWN,KC_TRANSPARENT,KC_NO,KC_TRANSPARENT,KC_NO,KC_SPACE,KC_TRANSPARENT,KC_NO,KC_SPACE,KC_NO,KC_LEFT,KC_DOWN,KC_TRANSPARENT),

};

extern bool g_suspend_state;
extern rgb_config_t rgb_matrix_config;

void keyboard_post_init_user(void) {
  rgb_matrix_enable();
}

const uint8_t PROGMEM ledmap[][DRIVER_LED_TOTAL][3] = {
    [1] = { {0,0,0}, {33,255,255}, {141,255,233}, {141,255,233}, {33,255,255}, {141,255,233}, {141,255,233}, {33,255,255}, {141,255,233}, {141,255,233}, {33,255,255}, {0,0,0}, {0,0,0}, {14,255,255}, {33,255,255}, {50,153,244}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,0}, {0,0,0}, {141,255,233}, {141,255,233}, {0,0,0}, {0,0,0}, {14,255,255}, {33,255,255}, {14,255,255}, {33,255,255}, {33,255,255}, {0,0,0}, {33,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {141,255,233}, {141,255,233}, {141,255,233}, {141,255,233} },

    [2] = { {0,0,0}, {33,255,255}, {141,255,233}, {141,255,233}, {33,255,255}, {141,255,233}, {141,255,233}, {33,255,255}, {141,255,233}, {141,255,233}, {0,0,255}, {0,0,0}, {0,0,0}, {80,145,233}, {0,0,0}, {33,255,255}, {33,255,255}, {33,255,255}, {33,255,255}, {33,255,255}, {33,255,255}, {80,145,233}, {80,145,233}, {0,0,0}, {0,0,0}, {141,255,233}, {0,0,0}, {141,255,233}, {141,255,233}, {141,255,233}, {14,255,255}, {14,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

    [3] = { {0,0,0}, {0,0,0}, {0,0,0}, {14,255,255}, {0,0,0}, {14,255,255}, {0,0,0}, {33,255,255}, {33,255,255}, {33,255,255}, {33,255,255}, {0,0,0}, {33,255,255}, {0,0,0}, {141,255,233}, {141,255,233}, {141,255,233}, {0,0,0}, {0,0,0}, {33,255,255}, {33,255,255}, {33,255,255}, {31,255,255}, {14,255,255}, {0,0,0}, {0,0,0}, {141,255,233}, {141,255,233}, {141,255,233}, {0,0,0}, {0,0,0}, {33,255,255}, {33,255,255}, {33,255,255}, {0,0,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

    [4] = { {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {33,255,255}, {14,255,255}, {14,255,255}, {14,255,255}, {33,255,255}, {0,0,0}, {0,0,0}, {0,0,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {33,255,255}, {14,255,255}, {14,255,255}, {14,255,255}, {33,255,255}, {80,145,233}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,255}, {14,255,255}, {14,255,255}, {14,255,255}, {80,145,233}, {80,145,233}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,255}, {0,0,255}, {0,0,0}, {14,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

    [5] = { {0,0,0}, {14,255,255}, {0,0,0}, {14,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {33,255,255}, {0,0,0}, {33,255,255}, {0,0,255}, {14,255,255}, {0,0,0}, {33,255,255}, {141,255,233}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {14,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {30,96,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

    [6] = { {0,0,0}, {0,0,0}, {141,255,233}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {14,255,255}, {0,0,0}, {141,255,233}, {141,255,233}, {141,255,233}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,255}, {141,255,233}, {0,0,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {30,96,255}, {30,96,255}, {30,96,255}, {0,0,0}, {141,255,233}, {141,255,233}, {141,255,233} },

};

void set_layer_color(int layer) {
  for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
    HSV hsv = {
      .h = pgm_read_byte(&ledmap[layer][i][0]),
      .s = pgm_read_byte(&ledmap[layer][i][1]),
      .v = pgm_read_byte(&ledmap[layer][i][2]),
    };
    if (!hsv.h && !hsv.s && !hsv.v) {
        rgb_matrix_set_color( i, 0, 0, 0 );
    } else {
        RGB rgb = hsv_to_rgb( hsv );
        float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
        rgb_matrix_set_color( i, f * rgb.r, f * rgb.g, f * rgb.b );
    }
  }
}

void rgb_matrix_indicators_user(void) {
  if (g_suspend_state || keyboard_config.disable_layer_led) { return; }
  switch (biton32(layer_state)) {
    case 1:
      set_layer_color(1);
      break;
    case 2:
      set_layer_color(2);
      break;
    case 3:
      set_layer_color(3);
      break;
    case 4:
      set_layer_color(4);
      break;
    case 5:
      set_layer_color(5);
      break;
    case 6:
      set_layer_color(6);
      break;
   default:
    if (rgb_matrix_get_flags() == LED_FLAG_NONE)
      rgb_matrix_set_color_all(0, 0, 0);
    break;
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case DE_LSPO:
      perform_space_cadet(record, KC_LSFT, KC_LSFT, KC_8);
      return false;
    case DE_RSPC:
      perform_space_cadet(record, KC_LSFT, KC_LSFT, KC_9);
      return false;
    case ST_MACRO_0:
    if (record->event.pressed) {
      SEND_STRING(SS_LALT(SS_LCTL(SS_TAP(X_A))));

    }
    break;
    case ST_MACRO_1:
    if (record->event.pressed) {
      SEND_STRING(SS_LCTL(SS_TAP(X_B)));

    }
    break;
    case ST_MACRO_2:
    if (record->event.pressed) {
      SEND_STRING(SS_LALT(SS_LCTL(SS_TAP(X_K))));

    }
    break;
    case RGB_SLD:
      if (record->event.pressed) {
        rgblight_mode(1);
      }
      return false;
    case HSV_17_255_211:
      if (record->event.pressed) {
        rgblight_mode(1);
        rgblight_sethsv(17,255,211);
      }
      return false;
    case HSV_0_0_255:
      if (record->event.pressed) {
        rgblight_mode(1);
        rgblight_sethsv(0,0,255);
      }
      return false;
  }
  return true;
}

#ifdef AUDIO_ENABLE
bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

void encoder_update(bool clockwise) {
    if (muse_mode) {
        if (IS_LAYER_ON(_RAISE)) {
            if (clockwise) {
                muse_offset++;
            } else {
                muse_offset--;
            }
        } else {
            if (clockwise) {
                muse_tempo+=1;
            } else {
                muse_tempo-=1;
            }
        }
    } else {
        if (clockwise) {
        #ifdef MOUSEKEY_ENABLE
            register_code(KC_MS_WH_DOWN);
            unregister_code(KC_MS_WH_DOWN);
        #else
            register_code(KC_PGDN);
            unregister_code(KC_PGDN);
        #endif
        } else {
        #ifdef MOUSEKEY_ENABLE
            register_code(KC_MS_WH_UP);
            unregister_code(KC_MS_WH_UP);
        #else
            register_code(KC_PGUP);
            unregister_code(KC_PGUP);
        #endif
        }
    }
}

void matrix_scan_user(void) {
#ifdef AUDIO_ENABLE
    if (muse_mode) {
        if (muse_counter == 0) {
            uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
            if (muse_note != last_muse_note) {
                stop_note(compute_freq_for_midi_note(last_muse_note));
                play_note(compute_freq_for_midi_note(muse_note), 0xF);
                last_muse_note = muse_note;
            }
        }
        muse_counter = (muse_counter + 1) % muse_tempo;
    }
#endif
}

bool music_mask_user(uint16_t keycode) {
    switch (keycode) {
    case RAISE:
    case LOWER:
        return false;
    default:
        return true;
    }
}
#endif

uint32_t layer_state_set_user(uint32_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

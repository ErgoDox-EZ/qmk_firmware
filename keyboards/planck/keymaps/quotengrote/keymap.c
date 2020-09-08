//KC_TRANSPARENT = _______ = transparent
//KC_NO= XXXXXXX = No OP/keine Funktion

#include QMK_KEYBOARD_H

#include "eeprom.h"
#include "keymap_german.h"

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
  _NUMPAD,
  _LT,
  _GAMING,
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_planck_grid( KC_ESCAPE ,KC_Q     ,KC_W   ,KC_E         ,KC_R ,KC_T     ,DE_Z    ,KC_U  ,KC_I     ,KC_O   ,KC_P    ,KC_BSPACE,
                                KC_TAB    ,KC_A     ,KC_S   ,KC_D         ,KC_F ,KC_G     ,KC_H    ,KC_J  ,KC_K     ,KC_L   ,DE_PLUS ,KC_ENTER,
                                KC_LSHIFT ,DE_Y     ,KC_X   ,KC_C         ,KC_V ,KC_B     ,KC_N    ,KC_M  ,KC_COMMA ,KC_DOT ,DE_MINS ,LT(5,DE_HASH),
                                KC_LCTRL  ,KC_LGUI  ,KC_LALT,LT(5,XXXXXXX),TT(1),KC_SPACE ,XXXXXXX ,TT(2) ,KC_LEFT  ,KC_DOWN,KC_UP   ,KC_RIGHT),
     
  [_LOWER] = LAYOUT_planck_grid(_______,KC_F1      ,KC_F2         ,KC_F3      ,KC_F4      ,KC_F5          ,KC_F6                 ,KC_F7     ,KC_F8    ,KC_F9      ,KC_F10 ,_______,
                                _______,ST_MACRO_0 ,KC_CALCULATOR ,ST_MACRO_1 ,LGUI(KC_M) ,LGUI(KC_L)     ,LALT(LCTL(KC_DELETE)) ,XXXXXXX   ,XXXXXXX  ,KC_F11     ,KC_F12 ,_______,
                                _______,ST_MACRO_2 ,TT(4)         ,_______    ,KC_INSERT  ,KC_APPLICATION ,XXXXXXX               ,KC_PAUSE  ,_______  ,_______    ,_______,_______,
                                _______,_______    ,_______       ,_______    ,_______    ,_______        ,XXXXXXX               ,_______   ,KC_END   ,KC_PGDOWN  ,KC_PGUP,KC_HOME),

  [_RAISE] = LAYOUT_planck_grid(_______,KC_1   ,KC_2   ,KC_3   ,KC_4   ,KC_5   ,KC_6   ,KC_7   ,KC_8   ,KC_9   ,KC_0   ,_______,
                                _______,DE_EXLM,XXXXXXX,DE_LCBR,DE_LBRC,DE_LPRN,DE_RPRN,DE_RBRC,DE_RCBR,DE_EQL ,DE_QST ,_______,
                                _______,DE_LESS,XXXXXXX,DE_DQOT,DE_ACUT,DE_QUOT,DE_SLSH,DE_BSLS,_______,_______,_______,_______,
                                _______,_______,_______,_______,_______,_______,XXXXXXX,_______,_______,_______,_______,_______),

  [_ADJUST] = LAYOUT_planck_grid(_______,_______,_______,MAGIC_TOGGLE_NKRO,_______,WEBUSB_PAIR,_______,LED_LEVEL  ,RGB_SLD,RGB_SPI,RGB_SPD        ,_______,
                                TO(6)   ,_______,_______,_______          ,_______,_______    ,_______,RGB_TOG    ,RGB_VAI,RGB_VAD,HSV_17_255_211 ,RESET,
                                _______ ,_______,_______,_______          ,_______,_______    ,_______,RGB_MOD    ,RGB_HUI,RGB_HUD,HSV_0_0_255    ,_______,
                                _______ ,_______,_______,_______          ,_______,_______    ,XXXXXXX,_______    ,_______,_______,_______        ,_______),

  [_NUMPAD] = LAYOUT_planck_grid( _______     ,_______,_______,_______,_______,KC_KP_PLUS ,KC_KP_7,KC_KP_8,KC_KP_9,KC_KP_ASTERISK ,_______,_______,
                                  KC_CAPSLOCK ,_______,_______,_______,_______,KC_KP_MINUS,KC_KP_4,KC_KP_5,KC_KP_6,KC_KP_SLASH    ,DE_EQL ,_______,
                                  _______     ,_______,_______,_______,_______,KC_NUMLOCK ,KC_KP_1,KC_KP_2,KC_KP_3,KC_COMMA       ,KC_DOT ,_______,
                                  _______     ,_______,_______,TO(1)   ,TO(0) ,_______    ,XXXXXXX,KC_KP_0,_______,_______        ,_______,_______),

  [_LT] = LAYOUT_planck_grid(     _______,DE_AT   ,_______,DE_EURO,_______,_______,_______,DE_UE        ,_______,DE_OE  ,KC_PSCREEN ,KC_DELETE,
                                  _______,DE_AE   ,DE_SS  ,_______,_______,_______,_______,_______      ,_______,_______,_______    ,_______,
                                  _______,DE_PIPE ,_______,_______,_______,_______,_______,KC_AUDIO_MUTE,_______,_______,_______    ,_______,
                                  _______,_______ ,_______,_______,_______,_______,XXXXXXX,_______      ,_______,_______,_______    ,_______),

  [_GAMING] = LAYOUT_planck_grid( _______,_______,_______,_______,_______ ,_______,_______,_______  ,_______,_______,_______,TO(0),
                                  _______,_______,_______,_______,_______ ,_______,_______,_______  ,_______,_______,_______,_______,
                                  _______,_______,_______,_______,_______ ,_______,_______,_______  ,_______,KC_PGUP,KC_UP  ,KC_PGDOWN,
                                  _______,XXXXXXX,_______,XXXXXXX,KC_SPACE,_______,XXXXXXX,KC_SPACE ,XXXXXXX,KC_LEFT,KC_DOWN,_______),

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

void matrix_scan_user(void) {}


uint32_t layer_state_set_user(uint32_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

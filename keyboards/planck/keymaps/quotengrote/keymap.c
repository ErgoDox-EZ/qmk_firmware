//_______ = _______ = transparent
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

//Deutsche Sonderzeichen definieren
#define DE_UDIA KC_LBRC // Ü - german.h
#define DE_ODIA KC_SCLN // Ö - german.h
#define DE_ADIA KC_QUOT // Ä - german.h
#define DE_SS   KC_MINS // ß - german.h
#define DE_EURO ALGR(DE_E) // € - german.h

enum {
    TDA_AE, //TT-ACTION_TAP_DANCE_FN ä
    TDA_UE, //TT-ACTION_TAP_DANCE_FN ü
    TDA_OE, //TT-ACTION_TAP_DANCE_FN ö
    TDA_SZ, //TT-ACTION_TAP_DANCE_FN ß
    TDA_EURO, //TT-ACTION_TAP_DANCE_FN €
    TDA_AT, //TT-ACTION_TAP_DANCE_FN @
    TD_PIPE, //TT-ACTION_TAP_DANCE_FN |
    TD_HOME_ARR, //TT-ACTION_TAP_DANCE_DOUBLE Pfeil hoch + Home
    TD_END_ARR, //TT-ACTION_TAP_DANCE_DOUBLE Pfeil runter + Ende
    TD_ALT, //TT-ACTION_TAP_DANCE_DOUBLE "AltGr/RALT"
    TDA_TW //TT-ACTION_TAP_DANCE_FN "Tab wiederherstellen in Browser"
};

//Funktion für TT-ACTION_TAP_DANCE_FN E+€
void F_TDA_EURO (qk_tap_dance_state_t *state, void *user_data) {
    switch(state->count){
        case 1:
            register_code(KC_E);
            unregister_code(KC_E);
            break;
        case 2:
            register_code(KC_E);
            unregister_code(KC_E);
            register_code(KC_E);
            unregister_code(KC_E);
            break;
        case 3:
            register_code16(DE_EURO);
            unregister_code16(DE_EURO);
            break;
          }
}
//Funktion für TT-ACTION_TAP_DANCE_FN Q+@
void F_TDA_AT (qk_tap_dance_state_t *state, void *user_data) {
    switch(state->count){
        case 1:
            register_code(KC_Q);
            unregister_code(KC_Q);
            break;
        case 3:
            register_code16(DE_AT);
            unregister_code16(DE_AT);
            break;
          }
}
//Funktion für TT-ACTION_TAP_DANCE_FN Y+|
void F_TD_PIPE (qk_tap_dance_state_t *state, void *user_data) {
    switch(state->count){
        case 1:
            register_code(DE_Y);
            unregister_code(DE_Y);
            break;
        case 3:
            register_code16(DE_PIPE);
            unregister_code16(DE_PIPE);
            break;
          }
}

//Funktion für TT-ACTION_TAP_DANCE_FN A+Ä
void F_TDA_AE (qk_tap_dance_state_t *state, void *user_data) {
    switch(state->count){
        case 1:
            register_code(KC_A);
            unregister_code(KC_A);
            break;
        case 2:
            register_code(KC_A);
            unregister_code(KC_A);
            register_code(KC_A);
            unregister_code(KC_A);
            break;
        case 3:
            register_code16(DE_ADIA);
            unregister_code16(DE_ADIA);
            break;
          }
}
//Funktion für TT-ACTION_TAP_DANCE_FN U+Ü
void F_TDA_UE (qk_tap_dance_state_t *state, void *user_data) {
    switch(state->count){
        case 1:
            register_code(KC_U);
            unregister_code(KC_U);
            break;
        case 2:
            register_code(KC_U);
            unregister_code(KC_U);
            register_code(KC_U);
            unregister_code(KC_U);
            break;
        case 3:
            register_code16(DE_UDIA);
            unregister_code16(DE_UDIA);
            break;
          }
}
//Funktion für TT-ACTION_TAP_DANCE_FN O+Ö
void F_TDA_OE (qk_tap_dance_state_t *state, void *user_data) {
    switch(state->count){
        case 1:
            register_code(KC_O);
            unregister_code(KC_O);
            break;
        case 2:
            register_code(KC_O);
            unregister_code(KC_O);
            register_code(KC_O);
            unregister_code(KC_O);
            break;
        case 3:
            register_code16(DE_ODIA);
            unregister_code16(DE_ODIA);
            break;
          }
}
//Funktion für TT-ACTION_TAP_DANCE_FN S+ß
void F_TDA_SZ (qk_tap_dance_state_t *state, void *user_data) {
    switch(state->count){
        case 1:
            register_code(KC_S);
            unregister_code(KC_S);
            break;
        case 2:
            register_code(KC_S);
            unregister_code(KC_S);
            register_code(KC_S);
            unregister_code(KC_S);
            break;
        case 3:
            register_code16(DE_SS);
            unregister_code16(DE_SS);
            break;
          }
}

// Funktion für TT-ACTION_TAP_DANCE_FN T+"Tab wiederherstellen in Browser"
void F_TDA_TW(qk_tap_dance_state_t *state, void *user_data) {
    switch(state->count){
        case 1:
            register_code(KC_T);
            unregister_code(KC_T);
            break;
        case 2:
            register_code(KC_T);
            unregister_code(KC_T);
            register_code(KC_T);
            unregister_code(KC_T);
            break;
        case 3:
            register_code16(KC_LCTRL);
            register_code16(KC_LSHIFT);
            register_code16(KC_T);
            unregister_code16(KC_LCTRL);
            unregister_code16(KC_LSHIFT);
            unregister_code16(KC_T);
            break;
          }
}

//TT+TDA-Funktion
qk_tap_dance_action_t tap_dance_actions[] = { //mit TD(Name) in Keymap einbinden
    [TD_HOME_ARR] = ACTION_TAP_DANCE_DOUBLE(KC_UP, KC_HOME),
    [TD_END_ARR] = ACTION_TAP_DANCE_DOUBLE(KC_DOWN, KC_END),
    [TD_ALT] = ACTION_TAP_DANCE_DOUBLE(KC_ALGR, KC_APPLICATION),
    [TD_PIPE] = ACTION_TAP_DANCE_FN(F_TD_PIPE),
    //Advanced
    [TDA_EURO] = ACTION_TAP_DANCE_FN(F_TDA_EURO),
    [TDA_AT] = ACTION_TAP_DANCE_FN(F_TDA_AT),
    [TDA_AE] = ACTION_TAP_DANCE_FN(F_TDA_AE),
    [TDA_UE] = ACTION_TAP_DANCE_FN(F_TDA_UE),
    [TDA_OE] = ACTION_TAP_DANCE_FN(F_TDA_OE),
    [TDA_SZ] = ACTION_TAP_DANCE_FN(F_TDA_SZ),
    [TDA_TW] = ACTION_TAP_DANCE_FN(F_TDA_TW)
};






const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_planck_grid(  KC_ESCAPE  ,TD(TDA_AT) ,KC_W           ,TD(TDA_EURO)     ,KC_R       ,TD(TDA_TW)     ,DE_Z                 ,TD(TDA_UE)     ,KC_I       ,TD(TDA_OE)     ,KC_P             ,KC_BSPACE,
                                 KC_TAB     ,TD(TDA_AE) ,TD(TDA_SZ)     ,KC_D             ,KC_F       ,KC_G           ,KC_H                 ,KC_J           ,KC_K       ,KC_L           ,DE_PLUS          ,KC_ENTER,
                                 KC_LSHIFT  ,TD(TD_PIPE),KC_X           ,KC_C             ,KC_V       ,KC_B           ,KC_N                 ,KC_M           ,KC_COMMA   ,KC_DOT         ,DE_MINS          ,LT(5,DE_HASH),
                                 KC_LCTRL   ,KC_LGUI    ,KC_LALT        ,TD(TD_ALT)       ,TT(1)      ,LT(5,KC_SPACE) ,XXXXXXX              ,TT(2)          ,KC_LEFT    ,TD(TD_END_ARR) ,TD(TD_HOME_ARR)  ,KC_RIGHT),

  [_LOWER] = LAYOUT_planck_grid( _______    ,KC_F1      ,KC_F2          ,KC_F3            ,KC_F4      ,KC_F5          ,KC_F6                ,KC_F7          ,KC_F8      ,KC_F9          ,KC_F10           ,_______,
                                 _______    ,ST_MACRO_0 ,KC_CALCULATOR  ,ST_MACRO_1       ,XXXXXXX    ,XXXXXXX        ,XXXXXXX              ,XXXXXXX        ,XXXXXXX    ,KC_F11         ,KC_F12           ,_______,
                                 _______    ,ST_MACRO_2 ,TT(4)          ,_______          ,KC_INSERT  ,XXXXXXX        ,XXXXXXX              ,KC_PAUSE       ,_______    ,_______        ,_______          ,_______,
                                 _______    ,_______    ,_______        ,_______          ,_______    ,_______        ,XXXXXXX              ,_______        ,_______    ,KC_PGDOWN      ,KC_PGUP          ,_______),

  [_RAISE] = LAYOUT_planck_grid( _______    ,KC_1       ,KC_2           ,KC_3             ,KC_4       ,KC_5           ,KC_6                 ,KC_7           ,KC_8       ,KC_9           ,KC_0             ,_______,
                                 _______    ,DE_EXLM    ,XXXXXXX        ,DE_LCBR          ,DE_LBRC    ,DE_LPRN        ,DE_RPRN              ,DE_RBRC        ,DE_RCBR    ,DE_EQL         ,DE_QST           ,_______,
                                 _______    ,DE_LESS    ,LSFT(DE_LESS)  ,DE_DQOT          ,DE_ACUT    ,DE_QUOT        ,DE_SLSH              ,DE_BSLS        ,_______    ,_______        ,_______          ,_______,
                                 _______    ,_______    ,_______        ,_______          ,_______    ,_______        ,XXXXXXX              ,_______        ,_______    ,_______        ,_______          ,_______),

  [_ADJUST] = LAYOUT_planck_grid(_______    ,_______    ,_______        ,MAGIC_TOGGLE_NKRO,_______    ,WEBUSB_PAIR    ,_______              ,_______        ,_______    ,_______        ,_______          ,_______,
                                 TO(6)      ,_______    ,RGB_HUI        ,RGB_VAI          ,RGB_MOD    ,RGB_SPI        ,TOGGLE_LAYER_COLOR   ,RGB_TOG        ,LED_LEVEL  ,_______        ,HSV_17_255_211   ,RESET,
                                 _______    ,_______    ,RGB_HUD        ,RGB_VAD          ,RGB_SLD    ,RGB_SPD        ,_______              ,_______        ,_______    ,_______        ,HSV_0_0_255      ,_______,
                                 _______    ,_______    ,_______        ,_______          ,_______    ,_______        ,KC_NO                ,_______        ,_______    ,_______        ,_______          ,_______),

  [_NUMPAD] = LAYOUT_planck_grid(_______    ,_______    ,_______        ,_______          ,_______    ,KC_KP_PLUS     ,KC_KP_7              ,KC_KP_8        ,KC_KP_9    ,KC_KP_ASTERISK ,_______          ,_______,
                                 KC_CAPSLOCK,_______    ,_______        ,_______          ,_______    ,KC_KP_MINUS    ,KC_KP_4              ,KC_KP_5        ,KC_KP_6    ,KC_KP_SLASH    ,DE_EQL           ,_______,
                                 _______    ,_______    ,_______        ,_______          ,_______    ,KC_NUMLOCK     ,KC_KP_1              ,KC_KP_2        ,KC_KP_3    ,KC_COMMA       ,KC_DOT           ,_______,
                                 _______    ,_______    ,_______        ,TO(1)            ,TO(0)      ,_______        ,XXXXXXX              ,KC_KP_0        ,_______    ,_______        ,_______          ,_______),

  [_LT] = LAYOUT_planck_grid(    _______    ,_______    ,_______        ,_______          ,_______    ,_______        ,_______              ,_______        ,_______    ,_______        ,KC_PSCREEN       ,KC_DELETE,
                                 _______    ,_______    ,_______        ,_______          ,_______    ,_______        ,KC_LEFT              ,KC_DOWN        ,KC_UP      ,KC_RIGHT       ,_______          ,_______,
                                 _______    ,_______    ,_______        ,_______          ,_______    ,_______        ,_______              ,KC_AUDIO_MUTE  ,_______    ,_______        ,_______          ,_______,
                                 _______    ,_______    ,_______        ,_______          ,_______    ,_______        ,XXXXXXX              ,_______        ,_______    ,_______        ,_______          ,_______),

  [_GAMING] = LAYOUT_planck_grid(_______    ,_______    ,_______        ,_______          ,_______    ,_______        ,_______              ,_______        ,_______    ,_______        ,_______          ,TO(0),
                                 _______    ,_______    ,_______        ,_______          ,_______    ,_______        ,_______              ,_______        ,_______    ,_______        ,_______          ,_______,
                                 _______    ,_______    ,_______        ,_______          ,_______    ,_______        ,_______              ,_______        ,_______    ,KC_PGUP        ,KC_UP            ,KC_PGDOWN,
                                 _______    ,XXXXXXX    ,_______        ,XXXXXXX          ,KC_SPACE   ,_______        ,XXXXXXX              ,KC_SPACE       ,XXXXXXX    ,KC_LEFT        ,KC_DOWN          ,KC_RIGHT),

};


extern bool g_suspend_state;
extern rgb_config_t rgb_matrix_config;

void keyboard_post_init_user(void) {
  rgb_matrix_enable();
}

const uint8_t PROGMEM ledmap[][DRIVER_LED_TOTAL][3] = {
    [0] = { {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,255}, {0,0,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

    [1] = { {0,0,0}, {33,255,255}, {141,255,233}, {141,255,233}, {33,255,255}, {141,255,233}, {141,255,233}, {33,255,255}, {141,255,233}, {141,255,233}, {33,255,255}, {0,0,0}, {0,0,0}, {14,255,255}, {33,255,255}, {50,153,244}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {141,255,233}, {141,255,233}, {0,0,0}, {0,0,0}, {14,255,255}, {33,255,255}, {0,0,0}, {33,255,255}, {0,0,0}, {0,0,0}, {33,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,255}, {0,0,0}, {0,0,0}, {141,255,233}, {141,255,233}, {0,0,0} },

    [2] = { {0,0,0}, {33,255,255}, {141,255,233}, {141,255,233}, {33,255,255}, {141,255,233}, {141,255,233}, {33,255,255}, {141,255,233}, {141,255,233}, {0,0,255}, {0,0,0}, {0,0,0}, {105,255,255}, {0,0,0}, {33,255,255}, {33,255,255}, {33,255,255}, {33,255,255}, {33,255,255}, {33,255,255}, {105,255,255}, {105,255,255}, {0,0,0}, {0,0,0}, {0,204,255}, {0,204,255}, {141,255,233}, {141,255,233}, {141,255,233}, {14,255,255}, {14,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

    [3] = { {0,0,0}, {0,0,0}, {0,0,0}, {14,255,255}, {0,0,0}, {14,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {33,255,255}, {0,0,0}, {35,255,255}, {105,255,255}, {249,228,255}, {154,255,255}, {85,203,158}, {0,0,255}, {0,0,255}, {0,0,0}, {31,255,255}, {14,255,255}, {0,0,0}, {0,0,0}, {35,255,255}, {105,255,255}, {249,228,255}, {154,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

    [4] = { {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {33,255,255}, {14,255,255}, {14,255,255}, {14,255,255}, {33,255,255}, {0,0,0}, {0,0,0}, {0,0,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {33,255,255}, {14,255,255}, {14,255,255}, {14,255,255}, {33,255,255}, {80,145,233}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,255}, {14,255,255}, {14,255,255}, {14,255,255}, {80,145,233}, {80,145,233}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,255}, {0,0,255}, {0,0,255}, {14,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

    [5] = { {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {33,255,255}, {14,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {154,255,255}, {249,228,255}, {105,255,255}, {14,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {33,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

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
    case ST_MACRO_0: //keepass strg +a
      if (record->event.pressed) {
        SEND_STRING(SS_LALT(SS_LCTL(SS_TAP(X_A))));
    }
    break;
    case ST_MACRO_1:  //tmux prefix
      if (record->event.pressed) {
        SEND_STRING(SS_LCTL(SS_TAP(X_B)));
    }
    break;
    case ST_MACRO_2: // keepass strg + k
      if (record->event.pressed) {
        SEND_STRING(SS_LALT(SS_LCTL(SS_TAP(X_K))));
    }
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
/*
//per Key-Tapping Time Funktion
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_SPC: //Zeit für Leertaste was als "antippen" gilt
            return 150;
        default:
            return TAPPING_TERM;
    }
}
*/

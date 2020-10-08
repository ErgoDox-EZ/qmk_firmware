//_______ = _______ = transparent
//KC_NO= XXXXXXX = No OP/keine Funktion

#include QMK_KEYBOARD_H

#include "eeprom.h"
#include "keymap_german.h"

enum planck_keycodes {
  RGB_SLD = EZ_SAFE_RANGE,
  MCR_KA,
  MCR_KK,
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
#define DE_LBRC ALGR(DE_8) // [ - german.h
#define DE_RBRC ALGR(DE_9) // ] - german.h
#define DE_LCBR ALGR(DE_7) // { - german.h
#define DE_RCBR ALGR(DE_0) // } - german.h
#define DE_LPRN S(DE_8) // ( - german.h
#define DE_RPRN S(DE_9) // ) - german.h
#define DE_TILD ALGR(DE_PLUS) // ~ - german.h
#define DE_CIRC KC_GRV  // ^ (dead) - german.h


enum {
    TD_ALT, //TT-ACTION_TAP_DANCE_DOUBLE "AltGr/RALT"
    TDA_KLMR_O, //TT-ACTION_TAP_DANCE_DOUBLE {[(
    TDA_KLMR_S, //TT-ACTION_TAP_DANCE_DOUBLE )]}
};

//Funktion für TT-ACTION_TAP_DANCE_FN "Klammern auf"
void F_TDA_KLMR_O (qk_tap_dance_state_t *state, void *user_data) {
    switch(state->count){
        case 1:
            register_code16(DE_LPRN);
            unregister_code16(DE_LPRN);
            break;
        case 2:
            register_code16(DE_LBRC);
            unregister_code16(DE_LBRC);
            break;
        case 3:
            register_code16(DE_LCBR);
            unregister_code16(DE_LCBR);
            break;
          }
}


//Funktion für TT-ACTION_TAP_DANCE_FN "Klammern zu"
void F_TDA_KLMR_S (qk_tap_dance_state_t *state, void *user_data) {
    switch(state->count){
        case 1:
            register_code16(DE_RPRN);
            unregister_code16(DE_RPRN);
            break;
        case 2:
            register_code16(DE_RBRC);
            unregister_code16(DE_RBRC);
            break;
        case 3:
            register_code16(DE_RCBR);
            unregister_code16(DE_RCBR);
            break;
          }
}

//TT+TDA-Funktion
qk_tap_dance_action_t tap_dance_actions[] = { //mit TD(Name) in Keymap einbinden; ist alles auch in den anderen Dateien auskommentiert
    [TD_ALT] = ACTION_TAP_DANCE_DOUBLE(KC_LALT, KC_ALGR),
    [TDA_KLMR_O] = ACTION_TAP_DANCE_FN(F_TDA_KLMR_O),
    [TDA_KLMR_S] = ACTION_TAP_DANCE_FN(F_TDA_KLMR_S),
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_planck_grid(  KC_ESCAPE  ,KC_Q           ,KC_W           ,KC_E                 ,KC_R       ,KC_T           ,DE_Z                 ,KC_U           ,KC_I       ,KC_O           ,KC_P             ,KC_BSPACE,
                                 KC_TAB     ,KC_A           ,DE_S           ,KC_D                 ,KC_F       ,KC_G           ,KC_H                 ,KC_J           ,KC_K       ,KC_L           ,DE_PLUS          ,KC_ENTER,
                                 KC_LSHIFT  ,DE_Y           ,KC_X           ,KC_C                 ,KC_V       ,KC_B           ,KC_N                 ,KC_M           ,KC_COMMA   ,KC_DOT         ,DE_MINS          ,LT(5,DE_HASH),
                                 KC_LCTRL   ,KC_LGUI        ,TD(TD_ALT)     ,TT(4)                ,TT(1)      ,LT(5,KC_SPACE) ,XXXXXXX              ,TT(2)          ,KC_LEFT    ,KC_DOWN        ,KC_UP            ,KC_RIGHT),

  [_LOWER] = LAYOUT_planck_grid( _______    ,KC_F1          ,KC_F2          ,KC_F3                ,KC_F4      ,KC_F5          ,KC_F6                ,KC_F7          ,KC_F8      ,KC_F9          ,KC_F10           ,_______,
                                 _______    ,MCR_KA         ,XXXXXXX        ,XXXXXXX              ,XXXXXXX    ,XXXXXXX        ,XXXXXXX              ,XXXXXXX        ,XXXXXXX    ,KC_F11         ,KC_F12           ,_______,
                                 _______    ,MCR_KK         ,XXXXXXX        ,XXXXXXX              ,KC_INSERT  ,XXXXXXX        ,XXXXXXX              ,KC_PAUSE       ,_______    ,_______        ,_______          ,_______,
                                 _______    ,_______        ,_______        ,_______              ,_______    ,_______        ,XXXXXXX              ,_______        ,_______    ,KC_PGDOWN      ,KC_PGUP          ,_______),

  [_RAISE] = LAYOUT_planck_grid( _______    ,KC_1           ,KC_2           ,KC_3                 ,KC_4       ,KC_5           ,KC_6                 ,KC_7           ,KC_8       ,KC_9           ,KC_0             ,_______,
                                 _______    ,DE_EXLM        ,DE_CIRC        ,XXXXXXX              ,XXXXXXX    ,TD(TDA_KLMR_O) ,TD(TDA_KLMR_S)       ,XXXXXXX        ,DE_TILD    ,DE_EQL         ,DE_QST           ,_______,
                                 _______    ,DE_LESS        ,LSFT(DE_LESS)  ,DE_DQOT              ,DE_ACUT    ,DE_QUOT        ,DE_SLSH              ,DE_BSLS        ,_______    ,_______        ,_______          ,_______,
                                 _______    ,_______        ,_______        ,_______              ,_______    ,_______        ,XXXXXXX              ,_______        ,_______    ,KC_END         ,KC_HOME          ,_______),

  [_ADJUST] = LAYOUT_planck_grid(_______    ,_______        ,_______        ,MAGIC_TOGGLE_NKRO    ,_______    ,WEBUSB_PAIR    ,_______              ,_______        ,_______    ,_______        ,_______          ,_______,
                                 TO(6)      ,_______        ,RGB_HUI        ,RGB_VAI              ,RGB_MOD    ,_______        ,TOGGLE_LAYER_COLOR   ,RGB_TOG        ,LED_LEVEL  ,_______        ,_______          ,RESET,
                                 _______    ,_______        ,RGB_HUD        ,RGB_VAD              ,RGB_SLD    ,_______        ,_______              ,_______        ,_______    ,_______        ,_______          ,_______,
                                 _______    ,_______        ,_______        ,_______              ,_______    ,_______        ,XXXXXXX              ,_______        ,_______    ,_______        ,_______          ,_______),

  [_NUMPAD] = LAYOUT_planck_grid(_______    ,_______        ,_______        ,_______              ,_______    ,KC_KP_PLUS     ,KC_KP_7              ,KC_KP_8        ,KC_KP_9    ,KC_KP_ASTERISK ,_______          ,_______,
                                 KC_NUMLOCK ,_______        ,_______        ,_______              ,_______    ,KC_KP_MINUS    ,KC_KP_4              ,KC_KP_5        ,KC_KP_6    ,KC_KP_SLASH    ,DE_EQL           ,_______,
                                 _______    ,_______        ,_______        ,KC_CALCULATOR        ,_______    ,_______        ,KC_KP_1              ,KC_KP_2        ,KC_KP_3    ,KC_COMMA       ,KC_DOT           ,_______,
                                 _______    ,_______        ,_______        ,_______              ,_______    ,_______        ,XXXXXXX              ,KC_KP_0        ,_______    ,_______        ,_______          ,_______),

  [_LT] = LAYOUT_planck_grid(    _______    ,DE_AT          ,_______        ,DE_EURO              ,_______    ,_______        ,_______              ,DE_UDIA        ,KC_UP      ,DE_ODIA        ,KC_PSCREEN       ,KC_DELETE,
                                 _______    ,DE_ADIA        ,DE_SS          ,_______              ,_______    ,_______        ,_______              ,KC_LEFT        ,KC_DOWN    ,KC_RIGHT       ,_______          ,_______,
                                 _______    ,DE_PIPE        ,_______        ,_______              ,_______    ,_______        ,_______              ,KC_AUDIO_MUTE  ,_______    ,_______        ,_______          ,_______,
                                 _______    ,_______        ,_______        ,_______              ,_______    ,_______        ,XXXXXXX              ,_______        ,_______    ,_______        ,_______          ,_______),

  [_GAMING] = LAYOUT_planck_grid(_______    ,_______        ,_______        ,_______              ,_______    ,_______        ,_______              ,_______        ,_______    ,_______        ,_______          ,TO(0),
                                 _______    ,_______        ,_______        ,_______              ,_______    ,_______        ,_______              ,_______        ,_______    ,_______        ,_______          ,_______,
                                 _______    ,_______        ,_______        ,_______              ,_______    ,_______        ,_______              ,_______        ,_______    ,KC_PGUP        ,KC_UP            ,KC_PGDOWN,
                                 _______    ,XXXXXXX        ,_______        ,XXXXXXX              ,KC_SPACE   ,KC_SPACE       ,XXXXXXX              ,KC_SPACE       ,XXXXXXX    ,KC_LEFT        ,KC_DOWN          ,KC_RIGHT),

};


extern bool g_suspend_state;
extern rgb_config_t rgb_matrix_config;

void keyboard_post_init_user(void) {
  rgb_matrix_enable();
}

const uint8_t PROGMEM ledmap[][DRIVER_LED_TOTAL][3] = {
    [0] = { {0,0,255}, {141,255,233}, {141,255,233}, {141,255,233}, {141,255,233}, {141,255,233}, {141,255,233}, {141,255,233}, {141,255,233}, {141,255,233}, {141,255,233}, {14,255,255}, {14,255,255}, {141,255,233}, {141,255,233}, {141,255,233}, {141,255,233}, {141,255,233}, {141,255,233}, {141,255,233}, {141,255,233}, {141,255,233}, {141,255,233}, {14,255,255}, {14,255,255}, {141,255,233}, {141,255,233}, {141,255,233}, {141,255,233}, {141,255,233}, {141,255,233}, {141,255,233}, {141,255,233}, {141,255,233}, {141,255,233}, {14,255,255}, {14,255,255}, {14,255,255}, {14,255,255}, {14,255,255}, {14,255,255}, {0,0,255}, {14,255,255}, {14,255,255}, {14,255,255}, {14,255,255}, {14,255,255} },

    [1] = { {0,0,0}, {33,255,255}, {141,255,233}, {141,255,233}, {33,255,255}, {141,255,233}, {141,255,233}, {33,255,255}, {141,255,233}, {141,255,233}, {33,255,255}, {0,0,0}, {0,0,0}, {14,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {141,255,233}, {141,255,233}, {0,0,0}, {0,0,0}, {14,255,255}, {0,0,0}, {0,0,0}, {33,255,255}, {0,0,0}, {0,0,0}, {33,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,255}, {0,0,0}, {0,0,0}, {141,255,233}, {141,255,233}, {0,0,0} },

    [2] = { {0,0,0}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {14,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {0,0,255}, {0,0,0}, {0,0,0}, {105,255,255}, {105,255,255}, {0,0,0}, {0,0,0}, {33,255,255}, {33,255,255}, {0,0,0}, {0,0,0}, {105,255,255}, {105,255,255}, {0,0,0}, {0,0,0}, {0,204,255}, {0,204,255}, {141,255,233}, {141,255,233}, {141,255,233}, {14,255,255}, {14,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,255}, {0,0,0}, {0,0,0}, {141,255,233}, {141,255,233}, {0,0,0} },

    [3] = { {0,0,0}, {0,0,0}, {0,0,0}, {14,255,255}, {0,0,0}, {14,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {33,255,255}, {0,0,0}, {35,255,255}, {105,255,255}, {249,228,255}, {0,0,0}, {141,255,233}, {141,255,233}, {141,255,233}, {0,0,0}, {0,0,0}, {14,255,255}, {0,0,0}, {0,0,0}, {35,255,255}, {105,255,255}, {249,228,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

    [4] = { {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {33,255,255}, {14,255,255}, {14,255,255}, {14,255,255}, {33,255,255}, {0,0,0}, {0,0,0}, {0,0,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {33,255,255}, {14,255,255}, {14,255,255}, {14,255,255}, {33,255,255}, {80,145,233}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {14,255,255}, {14,255,255}, {14,255,255}, {80,145,233}, {80,145,233}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,255}, {14,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

    [5] = { {0,0,0}, {85,203,158}, {0,0,0}, {85,203,158}, {0,0,0}, {0,0,0}, {0,0,0}, {85,203,158}, {105,255,255}, {85,203,158}, {33,255,255}, {33,255,255}, {0,0,0}, {85,203,158}, {85,203,158}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {154,255,255}, {249,228,255}, {14,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {85,203,158}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {33,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,255}, {0,0,0}, {154,255,255}, {249,228,255}, {105,255,255}, {14,255,255} },

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
    case 0:
      set_layer_color(0);      //setzt damit die Start-RGB-Konfiguration außer Kraft
      break;
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
      {
      rgb_matrix_set_color_all(0, 0, 0);
      }
    break;
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case MCR_KA: //keepass strg +a
      if (record->event.pressed) {
        SEND_STRING(SS_LALT(SS_LCTL(SS_TAP(X_A))));
    }
    break;
    case MCR_KK: // keepass strg + k
      if (record->event.pressed) {
        SEND_STRING(SS_LALT(SS_LCTL(SS_TAP(X_K))));
    }
    break;
    case RGB_SLD:
      if (record->event.pressed) {
        rgblight_mode(1);
      }
      return false;
    break;
  }
  return true;
}

void matrix_scan_user(void) {}


uint32_t layer_state_set_user(uint32_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

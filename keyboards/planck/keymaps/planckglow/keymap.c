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

#define PC_UNDO LCTL(KC_Z)
#define PC_REDO LSFT(KC_Z)
#define PC_CUT LCTL(KC_X)
#define PC_COPY LCTL(KC_C)
#define PC_PSTE LCTL(KC_V)
#define ES_LESS_MAC KC_GRAVE
#define ES_GRTR_MAC LSFT(KC_GRAVE)
#define ES_BSLS_MAC ALGR(KC_6)
#define NO_PIPE_ALT KC_GRAVE
#define NO_BSLS_ALT KC_EQUAL
#define TG_LYC TOGGLE_LAYER_COLOR
#define KC_APPS ENABLE_APPSWITCHER
#define KC_TABS ENABLE_TABSWITCHER
#define KC_ADIO ENABLE_AUDIO
#define KC_MOVE ENABLE_MOUSE

// Mix of Photoshop, Illustrator, Premiere, and Experience Design shortcuts.
#define SAVE  LCTL(KC_S)
#define OPEN  LCTL(KC_O)
#define COPY  LCTL(KC_C)
#define PAST  LCTL(KC_V)
#define CUNDO LCTL(LALT(KC_Z))
#define INVERT LCTL(LSFT(KC_I))
#define NLAYER LSFT(LCTL(KC_N))
#define UNDO LCTL(KC_Z)
#define TRANS LCTL(KC_T)
#define ALIGNL LCTL(LSFT(KC_L))
#define ALIGNC LCTL(LSFT(KC_C))
#define ALIGNR LCTL(LSFT(KC_R))
#define BRINGF LCTL(KC_RBRC)
#define BRINGB LCTL(KC_LBRC)

// Illustrator layer shortcuts.
#define SHAPE LSFT(KC_M)
#define RULER LCTL(LALT(KC_R))

// Premiere layer shortcuts.
#define REDO LCTL(LSFT(KC_Z))
#define EXPORT LCTL(KC_M)
#define IMPORT LCTL(KC_I)
#define PCOPY LCTL(KC_V)
#define PPASTE LCTL(LSFT(KC_V))

// Experience Design layer shortcuts. (can be used with others too.)
#define NEW LCTL(KC_N)
#define LOCK LCTL(KC_L)
#define SYMB LCTL(KC_K)
#define HIDE LCTL(KC_SCLN)
#define REPEAT LCTL(KC_R)
#define MASK LCTL(LSFT(KC_M))
#define GROUP LCTL(KC_G)
#define UNGRP LCTL(LSFT(KC_G))
#define VIEW LCTL(KC_TAB)
#define HORZ LSFT(KC_C)
#define VERT LSFT(KC_M)

// Custom planck keycodes
enum planck_keycodes {
  RGB_SLD = EZ_SAFE_RANGE,
  ENABLE_APPSWITCHER,
  ENABLE_TABSWITCHER,
  ENABLE_AUDIO,
  ENABLE_MOUSE,
  AI_SWEB,
  PC_ALL,
  PC_SAVE,
  KC_CMD,
  KC_SRCH,
  KC_TUBE,
};

enum planck_layers {
  _BASE,
  _LOWER,
  _RAISE,
  _ADJUST,
  _PHOTOSHOP,
  _INDESIGN
};

// Custom tap dance key; add any other multi-tap dance keys to this enum
enum td_keycodes {
  PSHOP = 0
};

typedef struct {
  bool is_press_action;
  int state;
} tap;

// Define a press type for as many tap dance states as you need
enum td_states {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
};

// Function associated with all tap dances
int cur_dance (qk_tap_dance_state_t *state);

// Functions associated with individual tap dances
void td_finished (qk_tap_dance_state_t *state, void *user_data);
void td_reset (qk_tap_dance_state_t *state, void *user_data);

// Define quick release layers here
#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* _QWERTY
* ,-----------------------------------------------------------------------------------.
* |  Tab |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
* |------+------+------+------+------+-------------+------+------+------+------+------|
* |  Esc |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
* |------+------+------+------+------+------|------+------+------+------+------+------|
* | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  | Enter|
* |------+------+------+------+------+------+------+------+------+------+------+------|
* | Apps | Ctrl |  Alt |  GUI | Lower|    Space    | Raise| Left | Down |  Up  | Right|
* `-----------------------------------------------------------------------------------'
*/

[_BASE] = LAYOUT_planck_grid(
	KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_BSPC,
	TD(PSHOP),KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,
	KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_ENT,
	KC_APPS,  KC_LCTL,  KC_LALT,  KC_LGUI,  LOWER,    KC_SPC,   KC_NO,    RAISE,    KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT
),

/* _LOWER
* ,-----------------------------------------------------------------------------------.
* |  Del |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  |      |
* |------+------+------+------+------+-------------+------+------+------+------+------|
* | Caps | PgUp | PgDn | Home |  End | ScnS |      |      |   `  |   [  |   ]  |      |
* |------+------+------+------+------+------|------+------+------+------+------+------|
* |      |  Ins |  Cut | Copy | Pste |      |      |      |      |      |      |      |
* |------+------+------+------+------+------+------+------+------+------+------+------|
* | Audio|      |      |      |      |    Space    |      | Prev | Next | Vol- | Vol+ |
* `-----------------------------------------------------------------------------------'
*/

[_LOWER] = LAYOUT_planck_grid(
	KC_DEL,   KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,  KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,  _______,
	KC_CAPS,  PC_ALL,   PC_SAVE,  KC_HOME,  KC_END,   KC_PSCR,  _______,  _______,  KC_GRV,   KC_LBRC,  KC_RBRC,  _______,
	_______,  KC_INS,   PC_CUT,   PC_COPY,  PC_PSTE,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
	KC_ADIO,  _______,  _______,  _______,  _______,  _______,  KC_NO,    _______,  KC_MPLY,  KC_MNXT,  KC_VOLD,  KC_VOLU
),

/* _RAISE
* ,-----------------------------------------------------------------------------------.
* |      |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |      |
* |------+------+------+------+------+-------------+------+------+------+------+------|
* | NLck |      |      |      |  Run | Srch | Tube |      |   -  |   \  |   =  |      |
* |------+------+------+------+------+------|------+------+------+------+------+------|
* |      |      |      |      |      |      |      |      |      |      |      |      |
* |------+------+------+------+------+------+------+------+------+------+------+------|
* | Tabs |      |      |      |      |    Space    |      |      |      |      |      |
* `-----------------------------------------------------------------------------------'
*/

[_RAISE] = LAYOUT_planck_grid(
	_______,  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     _______,
	KC_NLCK,  _______,  _______,  _______,  KC_CMD,   KC_SRCH,  KC_TUBE,  _______,  KC_MINS,  KC_NUBS,  KC_EQL,   _______,
	_______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
	KC_TABS,  _______,  _______,  _______,  _______,  _______,  KC_NO,    _______,  _______,  _______,  _______,  _______
),

/* _ADJUST
* ,-----------------------------------------------------------------------------------.
* |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  | F10  | F11  | F12  |
* |------+------+------+------+------+-------------+------+------+------+------+------|
* |      |      |  V-  |  V+  | L_C  |      |      | Muse | Mode |      |      | DFU  |
* |------+------+------+------+------+------|------+------+------+------+------+------|
* |      |      |  H-  |  H-  | RGB  |      |      |      |      |      |      |      |
* |------+------+------+------+------+------+------+------+------+------+------+------|
* | Mouse|      |      |      |      |    Space    |      |      |      |      |      |
* `-----------------------------------------------------------------------------------'
*/

[_ADJUST] = LAYOUT_planck_grid(
	KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,
	_______,  _______,  RGB_VAD,  RGB_VAI,  TG_LYC,   _______,  _______,  MU_TOG,   MU_MOD,   _______,  _______,  RESET,
	_______,  _______,  RGB_HUD,  RGB_HUI,  RGB_MOD,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
	KC_MOVE,  _______,  _______,  _______,  _______,  _______,  KC_NO,    _______,  _______,  _______,  _______,  _______
),

[_PHOTOSHOP] = LAYOUT_planck_grid(
	KC_DEL,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
	_______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
	KC_LSFT,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
	_______,  _______,  _______,  _______,  _______,  _______,  KC_NO,    _______,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT
),

[_INDESIGN] = LAYOUT_planck_grid(
	_______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
	_______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
	_______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
	_______,  _______,  _______,  _______,  _______,  _______,  KC_NO,    _______,  _______,  _______,  _______,  _______
),

};

#ifdef AUDIO_ENABLE
  float plover_song[][2]     = SONG(PLOVER_SOUND);
  float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif

extern bool g_suspend_state;
extern rgb_config_t rgb_matrix_config;

void keyboard_post_init_user(void) {
  rgb_matrix_enable();
}

// PURPLE 193,184,134 > 194,168,156 > 193,142,179 > 193,120,199 > 196,91,214
// CYAN 138,125,240 > 137,101,243 > 138,66,247 > 138,31,250 > 141,9,255

const uint16_t PROGMEM ledmap[][DRIVER_LED_TOTAL][3] = {

[0] = {
	{193,120,199}, {138,125,240}, {138,125,240}, {138,125,240}, {138,125,240}, {138,125,240}, {138,125,240}, {138,125,240}, {138,125,240}, {138,125,240}, {138,125,240}, {193,120,199},
	{193,142,179}, {137,101,243}, {137,101,243}, {137,101,243}, {137,101,243}, {137,101,243}, {137,101,243}, {137,101,243}, {137,101,243}, {137,101,243}, {137,101,243}, {193,142,179},
	{194,168,156}, {138,66,247},  {138,66,247},  {138,66,247},  {138,66,247},  {138,66,247},  {138,66,247},  {138,66,247},  {138,66,247},  {138,66,247},  {138,66,247},  {194,168,156},
	{0,0,0},       {194,168,156}, {193,142,179}, {193,120,199}, {196,91,214},  {138,31,250},  {196,91,214},  {193,120,199}, {193,142,179}, {194,168,156}, {193,184,134}
},
[1] = {
	{193,120,199}, {193,120,199}, {193,120,199}, {193,120,199}, {193,120,199}, {193,120,199}, {193,120,199}, {193,120,199}, {193,120,199}, {193,120,199}, {193,120,199}, {0,0,0},
	{138,125,240}, {137,101,243}, {137,101,243}, {137,101,243}, {137,101,243}, {196,91,214},  {0,0,0},       {0,0,0},       {196,91,214},  {196,91,214},  {196,91,214},  {0,0,0},
	{0,0,0},       {196,91,214},  {138,66,247},  {138,66,247},  {138,66,247},  {0,0,0},       {0,0,0},       {0,0,0},       {0,0,0},       {0,0,0},       {0,0,0},       {0,0,0},
	{0,0,0},       {0,0,0},       {0,0,0},       {0,0,0},       {196,91,214},  {0,0,0},       {0,0,0},       {137,101,243}, {138,66,247},  {138,31,250},  {141,9,255}
},
[2] = {
	{193,120,199}, {138,125,240}, {138,125,240}, {138,125,240}, {138,125,240}, {138,125,240}, {138,125,240}, {138,125,240}, {138,125,240}, {138,125,240}, {138,125,240}, {0,0,0},
	{138,125,240}, {0,0,0},       {0,0,0},       {0,0,0},       {196,91,214},  {193,142,179}, {193,184,134}, {0,0,0},       {196,91,214},  {193,142,179}, {193,184,134}, {0,0,0},
	{0,0,0},       {0,0,0},       {0,0,0},       {0,0,0},       {0,0,0},       {0,0,0},       {0,0,0},       {0,0,0},       {0,0,0},       {0,0,0},       {0,0,0},       {0,0,0},
	{0,0,0},       {0,0,0},       {0,0,0},       {0,0,0},       {0,0,0},       {0,0,0},       {196,91,214},  {0,0,0},       {0,0,0},       {0,0,0},       {0,0,0}
},
[3] = {
	{193,120,199}, {193,120,199}, {193,120,199}, {193,120,199}, {193,120,199}, {193,120,199}, {193,120,199}, {193,120,199}, {193,120,199}, {193,120,199}, {193,120,199}, {193,120,199},
	{0,0,0},       {0,0,0},       {137,101,243}, {137,101,243}, {137,101,243}, {0,0,0},       {0,0,0},       {193,142,179}, {193,184,134}, {0,0,0},       {0,0,0},       {255,200,255},
	{0,0,0},       {0,0,0},       {138,66,247},  {138,66,247},  {138,66,247},  {0,0,0},       {0,0,0},       {0,0,0},       {0,0,0},       {0,0,0},       {0,0,0},       {0,0,0},
	{0,0,0},       {0,0,0},       {0,0,0},       {0,0,0},       {196,91,214},  {0,0,0},       {196,91,214},  {0,0,0},       {0,0,0},       {0,0,0},       {0,0,0}
},
[4] = {
	{193,120,199}, {138,125,240}, {138,125,240}, {138,125,240}, {138,125,240}, {138,125,240}, {138,125,240}, {138,125,240}, {138,125,240}, {138,125,240}, {138,125,240}, {0,0,0},
	{193,120,199}, {137,101,243}, {137,101,243}, {137,101,243}, {0,0,0},       {137,101,243}, {137,101,243}, {137,101,243}, {0,0,0},       {137,101,243}, {0,0,0},       {0,0,0},
	{194,168,156}, {138,66,247},  {138,66,247},  {138,66,247},  {138,66,247},  {138,66,247},  {0,0,0},       {138,66,247},  {0,0,0},       {0,0,0},       {0,0,0},       {194,168,156},
	{0,0,0},       {0,0,0},       {0,0,0},       {0,0,0},       {0,0,0},       {200,150,255}, {0,0,0},       {0,0,0},       {0,0,0},       {0,0,0},       {0,0,0}
},
[5] = {
	{0,0,0},       {0,0,0},       {0,0,0},       {200,150,255}, {200,150,255}, {200,150,255}, {0,0,0},       {200,150,255}, {200,150,255}, {200,150,255}, {200,150,255}, {0,0,0},
	{193,120,199}, {0,0,0},       {200,150,255}, {0,0,0},       {200,150,255}, {200,150,255}, {200,150,255}, {200,150,255}, {0,0,0},       {0,0,0},       {0,0,0},       {0,0,0},
	{194,168,156}, {200,150,255}, {200,150,255}, {200,150,255}, {200,150,255}, {200,150,255}, {200,150,255}, {200,150,255}, {0,0,0},       {0,0,0},       {0,0,0},       {0,0,0},
	{0,0,0},       {0,0,0},       {0,0,0},       {0,0,0},       {0,0,0},       {200,150,255}, {0,0,0},       {0,0,0},       {0,0,0},       {0,0,0},       {0,0,0}
},
};

// Control the front layer indicators here
// void planck_ez_right_led_level(uint8_t level) {}
// void planck_ez_left_led_level(uint8_t level) {}

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
      set_layer_color(0);
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
   default:
    if (rgb_matrix_get_flags() == LED_FLAG_NONE)
      rgb_matrix_set_color_all(0, 0, 0);
    break;
  }
}

// Determine the current tap dance state
int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (!state->pressed) {
      return SINGLE_TAP;
    } else {
      return SINGLE_HOLD;
    }
  } else if (state->count == 2) {
    return DOUBLE_TAP;
  }
  else return 8;
}

// Initialize tap structure associated with example tap dance key
static tap pshop_tap_state = {
  .is_press_action = true,
  .state = 0
};

// Functions that control what our tap dance key does
void td_finished (qk_tap_dance_state_t *state, void *user_data) {
  pshop_tap_state.state = cur_dance(state);
  switch (pshop_tap_state.state) {
    case SINGLE_TAP:
      tap_code(KC_ESC);
      break;
    case SINGLE_HOLD:
      layer_on(_INDESIGN);
      break;
    case DOUBLE_TAP:
      // check to see if the layer is already set
      if (layer_state_is(_PHOTOSHOP)) {
        // if already set, then switch it off
        layer_off(_PHOTOSHOP);
      } else {
        // if not already set, then switch the layer on
        layer_on(_PHOTOSHOP);
      }
      break;
  }
}

void td_reset (qk_tap_dance_state_t *state, void *user_data) {
  // If the key was held down and now is released then switch off the layer
  if (pshop_tap_state.state==SINGLE_HOLD) {
    layer_off(_INDESIGN);
  }
  pshop_tap_state.state = 0;
}

// Associate our tap dance key with its functionality
qk_tap_dance_action_t tap_dance_actions[] = {
  [PSHOP] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, td_finished, td_reset, 275),
};

bool appswitcher_enabled = false;
bool tabswitcher_enabled = false;
bool audio_enabled = false;
bool mouse_enabled = false;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
static uint16_t my_hash_timer;
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
        tap_code(KC_MUTE);
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
        tabswitcher_enabled = false;
        tap_code(KC_NO);
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
        tap_code(KC_MPLY);
        }
      }
      return false;
    case ENABLE_MOUSE:
      if (record->event.pressed) {
        my_hash_timer = timer_read();  // start the timer
        mouse_enabled = true;
      } else {
        mouse_enabled = false;
      }
      return false;
    case RGB_SLD:
      if (record->event.pressed) {
        rgblight_mode(1);
      }
      return false;
    case AI_SWEB:
      if(record->event.pressed) {
	// Save for Web Macro.
	SEND_STRING(SS_LSFT(SS_LALT(SS_LCTRL("s"))));
      }
      return false;
    case PC_ALL:
      if(record->event.pressed) {
        my_hash_timer = timer_read();  // start the timer
        return false;
      } else {
        if (timer_elapsed(my_hash_timer) < TAPPING_TERM) {
          tap_code(KC_PGUP); // Change the character(s) to be sent on tap here
          return false;
        } else {
          tap_code16(LCTL(KC_A)); // Change the character(s) to be sent on hold here
          return true;
        }
      }
      return false;
    case PC_SAVE:
      if(record->event.pressed) {
        my_hash_timer = timer_read();  // start the timer
        return false;
      } else {
        if (timer_elapsed(my_hash_timer) < TAPPING_TERM) {
          tap_code(KC_PGDN); // Change the character(s) to be sent on tap here
          return false;
        } else {
          tap_code16(LCTL(KC_S)); // Change the character(s) to be sent on hold here
          return true;
        }
      }
      return false;
    case KC_CMD:
      if(record->event.pressed) {
	tap_code16(LGUI(KC_R));
        SEND_STRING ("dl-single"); // Change the character(s) to be sent on hold here
        tap_code(KC_ENT);
      }
      return false;
    case KC_SRCH:
      if(record->event.pressed) {
	tap_code16(LGUI(KC_R));
        SEND_STRING ("http://www.google.com"); // Change the character(s) to be sent on hold here
        tap_code(KC_ENT);
      }
      return false;
    case KC_TUBE:
      if(record->event.pressed) {
	tap_code16(LGUI(KC_R));
        SEND_STRING ("http://www.youtube.com"); // Change the character(s) to be sent on hold here
        tap_code(KC_ENT);
      }
      return false;
  }
  return true;
}

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

void encoder_update_user(uint8_t index, bool clockwise) {
    switch(biton32(layer_state)){
        // Assign per layer functionality for the encoder
        case _BASE:
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
            } else if (appswitcher_enabled) {
                if (!clockwise) {
                    tap_code16(LSFT(KC_TAB));
                } else {
                    tap_code16(KC_TAB);
                }
            } else {
                if (!clockwise) {
                    tap_code(KC_VOLD);
                } else {
                    tap_code(KC_VOLU);
                }
            }
            break;
        case _LOWER:
            if (audio_enabled) {
                if (!clockwise) {
                    tap_code16(PC_UNDO);
                } else {
                    tap_code16(PC_REDO);
                }
            } else {
                if (!clockwise) {
                #ifdef MOUSEKEY_ENABLE
                    tap_code(KC_WH_L);
                #else
                    tap_code(KC_MPRV);
                #endif
                } else {
                #ifdef MOUSEKEY_ENABLE
                    tap_code(KC_WH_R);
                #else
                    tap_code(KC_MNXT);
                #endif
                }
            }
            break;
        case _RAISE:
            if (tabswitcher_enabled) {
                if (!clockwise) {
                    tap_code16(LSFT(KC_TAB));
                } else {
                    tap_code16(KC_TAB);
                }
            } else {
                if (!clockwise) {
                #ifdef MOUSEKEY_ENABLE
                    tap_code(KC_WH_D);
                #else
                    tap_code(KC_WBAK);
                #endif
                } else {
                #ifdef MOUSEKEY_ENABLE
                    tap_code(KC_WH_U);
                #else
                    tap_code(KC_WFWD);
                #endif
                }
            }
            break;
        case _ADJUST:
            if (mouse_enabled) {
                if (!clockwise) {
                #ifdef MOUSEKEY_ENABLE
                    tap_code16(KC_MS_D);
                #else
                    tap_code(KC_NO);
                #endif
                } else {
                #ifdef MOUSEKEY_ENABLE
                    tap_code16(KC_MS_U);
                #else
                    tap_code(KC_NO);
                #endif
                }
            } else {
                if (!clockwise) {
                #ifdef MOUSEKEY_ENABLE
                    tap_code(KC_MS_L);
                #else
                    tap_code(KC_NO);
                #endif
                } else {
                #ifdef MOUSEKEY_ENABLE
                    tap_code(KC_MS_R);
                #else
                    tap_code(KC_NO);
                #endif
                }
            }
            break;
    }
}

void dip_update(uint8_t index, bool active) {
  switch (index) {
    case _BASE:
      if (active) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(plover_song);
        #endif
        layer_on(_ADJUST);
      } else {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(plover_gb_song);
        #endif
        layer_off(_ADJUST);
      }
      break;
    case _LOWER:
      if (active) {
        muse_mode = true;
      } else {
        muse_mode = false;
        #ifdef AUDIO_ENABLE
          stop_all_notes();
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

uint32_t layer_state_set_user(uint32_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

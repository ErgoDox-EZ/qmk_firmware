/*
Copyright 2018 Jack Humbert <jack.humb@gmail.com>

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

#include "moonlander.h"

bool mcp23018_leds[3] = {0, 0, 0};

void keyboard_pre_init_kb(void) {
    setPinOutput(B5);
    setPinOutput(B4);
    setPinOutput(B3);

    writePinLow(B5);
    writePinLow(B4);
    writePinLow(B3);

    /* the array is initialized to 0, no need to re-set it here */
    // mcp23018_leds[0] = 0;  // blue
    // mcp23018_leds[1] = 0;  // green
    // mcp23018_leds[2] = 0;  // red

    keyboard_pre_init_user();
}

layer_state_t layer_state_set_kb(layer_state_t state) {
    ML_LED_1(0);
    ML_LED_2(0);
    ML_LED_3(0);
    ML_LED_4(0);
    ML_LED_5(0);
    ML_LED_6(0);

    state = layer_state_set_user(state);
    uint8_t layer = get_highest_layer(state);
    switch (layer) {
        case 1:
            ML_LED_1(1);
            ML_LED_4(1);
            break;
        case 2:
            ML_LED_2(1);
            ML_LED_5(1);
            break;
        case 3:
            ML_LED_3(1);
            break;
        case 4:
            ML_LED_4(1);
            break;
        case 5:
            ML_LED_5(1);
            break;
        case 6:
            ML_LED_6(1);
            break;
        default:
            break;
    }

    return state;
    }

// clang-format off
const is31_led g_is31_leds[DRIVER_LED_TOTAL] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |      G location
 *   |  |      |      B location
 *   |  |      |      | */
    {0, C3_2,  C1_1,  C4_2}, // 1
    {0, C2_2,  C1_2,  C4_3},
    {0, C2_3,  C1_3,  C3_3},
    {0, C2_4,  C1_4,  C3_4},
    {0, C2_5,  C1_5,  C3_5},
    {0, C2_6,  C1_6,  C3_6},
    {0, C2_7,  C1_7,  C3_7},
    {0, C2_8,  C1_8,  C3_8},
    {0, C3_1,  C2_1,  C4_1},

    {0, C7_8,  C6_8,  C8_8}, // 10
    {0, C7_7,  C6_7,  C9_8},
    {0, C8_7,  C6_6,  C9_7},
    {0, C8_6,  C7_6,  C9_6},
    {0, C8_5,  C7_5,  C9_5},
    {0, C8_4,  C7_4,  C9_4},
    {0, C8_3,  C7_3,  C9_3},
    {0, C8_2,  C7_2,  C9_2},
    {0, C8_1,  C7_1,  C9_1},

    {0, C3_10,  C1_9,   C4_10}, // 19
    {0, C2_10,  C1_10,  C4_11},
    {0, C2_11,  C1_11,  C3_11},
    {0, C2_12,  C1_12,  C3_12},
    {0, C2_13,  C1_13,  C3_13},
    {0, C2_14,  C1_14,  C3_14},
    {0, C2_15,  C1_15,  C3_15},
    {0, C2_16,  C1_16,  C3_16},
    {0, C3_9,   C2_9,   C4_9},

    {0, C7_16,  C6_16,  C8_16}, // 28
    {0, C7_15,  C6_15,  C9_16},
    {0, C8_15,  C6_14,  C9_15},
    {0, C8_10,  C7_10,  C9_10},
    {0, C8_9,   C7_9,   C9_9},
    {0, C8_11,  C7_11,  C9_11},
    {0, C8_12,  C7_12,  C9_12},
    {0, C8_13,  C7_13,  C9_13},
    {0, C8_14,  C7_14,  C9_14},

    {1, C3_2,  C1_1,  C4_2}, // 1
    {1, C2_2,  C1_2,  C4_3},
    {1, C2_3,  C1_3,  C3_3},
    {1, C2_4,  C1_4,  C3_4},
    {1, C2_5,  C1_5,  C3_5},
    {1, C2_6,  C1_6,  C3_6},
    {1, C2_7,  C1_7,  C3_7},
    {1, C2_8,  C1_8,  C3_8},
    {1, C3_1,  C2_1,  C4_1},

    {1, C7_8,  C6_8,  C8_8}, // 10
    {1, C7_7,  C6_7,  C9_8},
    {1, C8_7,  C6_6,  C9_7},
    {1, C8_6,  C7_6,  C9_6},
    {1, C8_5,  C7_5,  C9_5},
    {1, C8_4,  C7_4,  C9_4},
    {1, C8_3,  C7_3,  C9_3},
    {1, C8_2,  C7_2,  C9_2},
    {1, C8_1,  C7_1,  C9_1},

    {1, C3_10,  C1_9,   C4_10}, // 19
    {1, C2_10,  C1_10,  C4_11},
    {1, C2_11,  C1_11,  C3_11},
    {1, C2_12,  C1_12,  C3_12},
    {1, C2_13,  C1_13,  C3_13},
    {1, C2_14,  C1_14,  C3_14},
    {1, C2_15,  C1_15,  C3_15},
    {1, C2_16,  C1_16,  C3_16},
    {1, C3_9,   C2_9,   C4_9},

    {1, C7_16,  C6_16,  C8_16}, // 28
    {1, C7_15,  C6_15,  C9_16},
    {1, C8_15,  C6_14,  C9_15},
    {1, C8_10,  C7_10,  C9_10},
    {1, C8_9,   C7_9,   C9_9},
    {1, C8_11,  C7_11,  C9_11},
    {1, C8_12,  C7_12,  C9_12},
    {1, C8_13,  C7_13,  C9_13},
    {1, C8_14,  C7_14,  C9_14},

};

led_config_t g_led_config = { {
    {   0,  5, 10, 15, 20, 25, 29 },
    {   1,  6, 11, 16, 21, 26, 30 },
    {   2,  7, 12, 17, 22, 27, 31 },
    {   3,  8, 13, 18, 23, 28, NO_LED },
    {   4,  9, 14, 19, 24, NO_LED, NO_LED },
    {  32, 33, 34, 35, NO_LED, NO_LED, NO_LED },
    {  65, 61, 56, 51, 46, 41, 36 },
    {  66, 62, 57, 52, 47, 42, 37 },
    {  67, 63, 58, 53, 48, 43, 38 },
    {  NO_LED, 64, 59, 54, 49, 44, 39 },
    {  NO_LED, NO_LED, 60, 55, 50, 45, 40 },
    {  NO_LED, NO_LED, NO_LED, 71, 70, 69, 68 },
}, {
    {   0,   0 }, {   0,  12 }, {   0,  25 }, {   0,  38 }, {   0,  51 },
    {  17,   0 }, {  17,  12 }, {  17,  25 }, {  17,  38 }, {  17,  51 },
    {  34,   0 }, {  34,  12 }, {  34,  25 }, {  34,  38 }, {  34,  51 },
    {  51,   0 }, {  51,  12 }, {  51,  25 }, {  51,  38 }, {  51,  51 },
    {  68,   0 }, {  68,  12 }, {  68,  25 }, {  68,  38 }, {  68,  51 },
    {  86,   0 }, {  86,  12 }, {  86,  25 }, {  86,  38 },
    { 105,   0 }, { 105,  12 }, { 105,  25 },
    {  90,  55 }, { 105,  68 }, { 116,  86 }, { 116, 59 },

    { 250,   0 }, { 250,  12 }, { 250,  25 }, { 250,  38 }, { 250,  51 },
    { 233,   0 }, { 233,  12 }, { 233,  25 }, { 233,  38 }, { 233,  51 },
    { 216,   0 }, { 216,  12 }, { 216,  25 }, { 216,  38 }, { 216,  51 },
    { 198,   0 }, { 198,  12 }, { 198,  25 }, { 198,  38 }, { 198,  51 },
    { 181,   0 }, { 181,  12 }, { 181,  25 }, { 181,  38 }, { 181,  51 },
    { 163,   0 }, { 163,  12 }, { 163,  25 }, { 163,  38 },
    { 146,   0 }, { 146,  12 }, { 146,  25 },
    { 161,  55 }, { 161,  68 }, { 146,  86 }, { 131, 59 }

}, {
    1, 1, 1, 1, 1, 4,
    4, 4, 4, 1, 4, 4,
    4, 4, 1, 4, 4, 4,
    4, 1, 4, 4, 4, 4,
    1, 4, 4, 4, 4, 4,
    4, 4, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 4,
    4, 4, 4, 1, 4, 4,
    4, 4, 1, 4, 4, 4,
    4, 1, 4, 4, 4, 4,
    1, 4, 4, 4, 4, 4,
    4, 4, 1, 1, 1, 1
} };
// clang-format on

#ifdef AUDIO_ENABLE
bool music_mask_kb(uint16_t keycode) {
    switch (keycode) {
    case QK_LAYER_TAP ... QK_ONE_SHOT_LAYER_MAX:
    case QK_LAYER_TAP_TOGGLE ... QK_LAYER_MOD_MAX:
    case QK_MOD_TAP ... QK_MOD_TAP_MAX:
    case AU_ON ... MUV_DE:
    case RESET:
    case EEP_RST:
        return false;
    default:
        return music_mask_user(keycode);
    }
}
#endif

#ifdef SWAP_HANDS_ENABLE
// swap-hands action needs a matrix to define the swap
// clang-format off
const keypos_t hand_swap_config[MATRIX_ROWS][MATRIX_COLS] = {
    /* Left hand, matrix positions */
    {{6,6}, {5,6}, {4,6}, {3,6}, {2,6}, {1,6},{0,6}},
    {{6,7}, {5,7}, {4,7}, {3,7}, {2,7}, {1,7},{0,7}},
    {{6,8}, {5,8}, {4,8}, {3,8}, {2,8}, {1,8},{0,8}},
    {{6,9}, {5,9}, {4,9}, {3,9}, {2,9}, {1,9},{0,9}},
    {{6,10},{5,10},{4,10},{3,10},{2,10},{1,10},{0,10}},
    {{6,11},{5,11},{4,11},{3,11},{2,11},{1,11},{0,11}},
    /* Right hand, matrix positions */
    {{6,0}, {5,0}, {4,0}, {3,0}, {2,0}, {1,0},{0,0}},
    {{6,1}, {5,1}, {4,1}, {3,1}, {2,1}, {1,1},{0,1}},
    {{6,2}, {5,2}, {4,2}, {3,2}, {2,2}, {1,2},{0,2}},
    {{6,3}, {5,3}, {4,3}, {3,3}, {2,3}, {1,3},{0,3}},
    {{6,4}, {5,4}, {4,4}, {3,4}, {2,4}, {1,4},{0,4}},
    {{6,5}, {5,5}, {4,5}, {3,5}, {2,5}, {1,5},{0,5}},
};
// clang-format on
#endif

#if defined(AUDIO_ENABLE) && defined(MUSIC_MAP)
// clang-format off
const uint8_t music_map[MATRIX_ROWS][MATRIX_COLS] = LAYOUT_moonlander(
    58, 59, 60, 61, 62, 63, 64,    65, 66, 67, 68, 69, 70, 71,
    44, 45, 46, 47, 48, 49, 50,    51, 52, 53, 54, 55, 56, 57,
    30, 31, 32, 33, 34, 35, 36,    37, 38, 39, 40, 41, 42, 43,
    18, 19, 20, 21, 22, 23,            24, 25, 26, 27, 28, 29,
     8,  9, 10, 11, 12,      3,     4,     13, 14, 15, 16, 17,
                     0,  1,  2,     5,  6,  7
);
// clang-format on
#endif

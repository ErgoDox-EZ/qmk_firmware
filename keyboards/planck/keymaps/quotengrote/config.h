#pragma once

//#define ENCODER_RESOLUTION 4

/*
  Set any config.h overrides for your specific keymap here.
  See config.h options at https://docs.qmk.fm/#/config_options?id=the-configh-file
*/
#define ORYX_CONFIGURATOR //auch für led
#define FIRMWARE_VERSION u8"Ppzmm/554eY"

//tap dance
#define TAPPING_TERM 200 //in milliseconds
//#define TAPPING_TERM_PER_KEY //tapping term per key, als funktion

//led startup farbe + muster

/*
#define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_ALPHAS_MODS //Sets the default mode, if none has been set; modus von links, unten und rechts eine farbe haben, und die anderen tasten eine andere/ RGB_MATRIX_ALPHAS_MODS,         // Static dual hue, speed is hue for secondary hue, rgb_spi ist außen, rgb_hui innen
#define RGB_MATRIX_STARTUP_SAT 254 //Sets the default saturation value, if none has been set
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 220 // Sets the default brightness value, if none has been set

#define RGB_MATRIX_STARTUP_HUE 155 // Sets the default hue value, if none has been set //innen // dunkles blau
#define RGB_MATRIX_STARTUP_SPD 115 // Sets the default animation speed, if none has been set //außen // um 110 ist orange
*/
#define RGB_DISABLE_TIMEOUT 600000 // number of milliseconds to wait until rgb automatically turns off = 10min
#define RGB_DISABLE_WHEN_USB_SUSPENDED true // turn off effects when suspended


/* deaktiviert die meisten animationen */
#define DISABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#define DISABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
#define DISABLE_RGB_MATRIX_BAND_SAT
#define DISABLE_RGB_MATRIX_BAND_SPIRAL_SAT
#define DISABLE_RGB_MATRIX_BAND_SPIRAL_VAL
#define DISABLE_RGB_MATRIX_BAND_VAL
#define DISABLE_RGB_MATRIX_BREATHING
#define DISABLE_RGB_MATRIX_CYCLE_ALL
#define DISABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#define DISABLE_RGB_MATRIX_CYCLE_OUT_IN
#define DISABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
#define DISABLE_RGB_MATRIX_CYCLE_PINWHEEL
#define DISABLE_RGB_MATRIX_CYCLE_SPIRAL
#define DISABLE_RGB_MATRIX_CYCLE_UP_DOWN
#define DISABLE_RGB_MATRIX_DIGITAL_RAIN
#define DISABLE_RGB_MATRIX_DUAL_BEACON
#define DISABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#define DISABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
#define DISABLE_RGB_MATRIX_MULTISPLASH
#define DISABLE_RGB_MATRIX_RAINBOW_BEACON
#define DISABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#define DISABLE_RGB_MATRIX_RAINBOW_PINWHEELS
#define DISABLE_RGB_MATRIX_RAINDROPS
#define DISABLE_RGB_MATRIX_SOLID_MULTISPLASH
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
#define DISABLE_RGB_MATRIX_SOLID_SPLASH
#define DISABLE_RGB_MATRIX_SPLASH
#define DISABLE_RGB_MATRIX_TYPING_HEATMAP
#define DISABLE_RGB_MATRIX_ALPHAS_MODS

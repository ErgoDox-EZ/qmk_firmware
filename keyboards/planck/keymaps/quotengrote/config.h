#pragma once

#define ENCODER_RESOLUTION 4

/*
  Set any config.h overrides for your specific keymap here.
  See config.h options at https://docs.qmk.fm/#/config_options?id=the-configh-file
*/
#define ORYX_CONFIGURATOR //auch für led
#define FIRMWARE_VERSION u8"Ppzmm/554eY"

//tap dance
#define TAPPING_TERM 200 //in milliseconds


//led startup farbe + muster
#define RGB_DISABLE_TIMEOUT 600000 // number of milliseconds to wait until rgb automatically turns off = 10min
#define RGB_DISABLE_WHEN_USB_SUSPENDED true // turn off effects when suspended
#define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_ALPHAS_MODS //Sets the default mode, if none has been set; modus von links, unten und rechts eine farbe haben, und die unneren tasten eine andere/ RGB_MATRIX_ALPHAS_MODS,         // Static dual hue, speed is hue for secondary hue, rgb_spi ist außen, rgb_hui innen
#define RGB_MATRIX_STARTUP_SAT 254 //Sets the default saturation value, if none has been set
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 220 // Sets the default brightness value, if none has been set

#define RGB_MATRIX_STARTUP_HUE 128 // Sets the default hue value, if none has been set
#define RGB_MATRIX_STARTUP_SPD 10 // Sets the default animation speed, if none has been set

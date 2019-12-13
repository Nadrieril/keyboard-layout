/*
  Set any config.h overrides for your specific keymap here.
  See config.h options at https://docs.qmk.fm/#/config_options?id=the-configh-file
*/
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
#define QMK_KEYS_PER_SCAN 4
#undef IGNORE_MOD_TAP_INTERRUPT
#define PERMISSIVE_HOLD
// #undef TAPPING_TERM
// #define TAPPING_TERM 50
// #define RETRO_TAPPING

// Mouse scrolling
#define MK_3_SPEED
#define MK_MOMENTARY_ACCEL
#define MK_W_INTERVAL_UNMOD 80
#define MK_W_INTERVAL_0 200
#define MK_W_INTERVAL_1 40
#define MK_W_INTERVAL_2 20

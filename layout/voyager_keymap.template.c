// Layers:
// 7: super
// 6: alt-gr
// 5: shift
// 2: ???
// 1: symbols and numpad
// 0: base
#define SHIFT_LAYER_ID 5
#define RALT_LAYER_ID 6
#define SUPER_LAYER_ID 7
#define LAYER2 2
#define LAYER1 1

#include "common.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
__KEYMAP_GOES_HERE__
};

/// Chords

enum combos {
  LAYER2_CHORD,
  LAYER2_CHORD2,
};

const uint16_t PROGMEM layer2_chord[] = {KC_SPC, MO(LAYER1), COMBO_END};
const uint16_t PROGMEM layer2_chord2[] = {KC_LSFT, MO(LAYER1), COMBO_END};
combo_t key_combos[] = {
    [LAYER2_CHORD] = COMBO(layer2_chord, MO(LAYER2)),
    [LAYER2_CHORD2] = COMBO(layer2_chord2, MO(LAYER2)),
};

/// RGB

extern rgb_config_t rgb_matrix_config;

const uint8_t PROGMEM ledmap[][3] = {
    [LAYER1] = {74,255,127},
    [LAYER2] = {41,255,127},
};

void set_layer_color(int layer) {
  HSV hsv = {
    .h = pgm_read_byte(&ledmap[layer][0]),
    .s = pgm_read_byte(&ledmap[layer][1]),
    .v = pgm_read_byte(&ledmap[layer][2]),
  };
  RGB rgb = hsv_to_rgb(hsv);
  float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
  rgb_matrix_set_color_all(f * rgb.r, f * rgb.g, f * rgb.b);
}

bool rgb_matrix_indicators_user(void) {
  if (keyboard_config.disable_layer_led) { return false; }

  int active_layer = biton32(layer_state);
  switch (active_layer) {
    case LAYER1:
    case LAYER2:
      set_layer_color(active_layer);
      break;
   default:
    if (rgb_matrix_get_flags() == LED_FLAG_NONE)
      rgb_matrix_set_color_all(0, 0, 0);
    break;
  }
  return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    return process_mod_layers(keycode, record);
}

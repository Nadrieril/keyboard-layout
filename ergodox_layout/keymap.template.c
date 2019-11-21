#include "ergodox_ez.h"
#include "debug.h"
#include "action_layer.h"
#include "version.h"
#define ANY(kc) kc

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
__KEYMAP_GOES_HERE__
};

uint32_t layer_state_set_user(uint32_t state) {
    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    if (state & (1<<1)) {
        ergodox_right_led_1_on();
    }
    if (state & (1<<2)) {
        ergodox_right_led_2_on();
    }
    if (state & (1<<3)) {
        ergodox_right_led_3_on();
        swap_hands = true;
    } else {
        swap_hands = false;
    }
    if (state & (1<<4)) {
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
    }
    return state;
};

#include "ergodox_ez.h"
#include "debug.h"
#include "action_layer.h"
#include "version.h"
#define ANY(kc) kc

enum custom_keycodes {
    PLACEHOLDER = SAFE_RANGE,
    SHIFT_LAYER,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
__KEYMAP_GOES_HERE__
};

// Layers:
// 5: shift
// 4: error (when pressing the old shift keys)
// 3: swap_hands
// 2: qwerty for gaming
// 1: numpad and fn layer
// 0: base

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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // If special shift layer is on.
    if (layer_state & (1<<5)) {
        action_t action = action_for_key(5, record->event.key);
        // Keys defined on the special shift layer should not be processed shifted.
        if (action.code != ACTION_TRANSPARENT) {
            unregister_code(KC_LSFT);
            process_action(record, action);
            register_code(KC_LSFT);
            return false;
        }
    }

    switch (keycode) {
        case SHIFT_LAYER:
            if (record->event.pressed) {
                register_code(KC_LSFT);
                layer_on(5);
            } else {
                unregister_code(KC_LSFT);
                layer_off(5);
            }
            return false; // Skip all further processing of this key
        default:
            return true; // Process all other keycodes normally
    }
}

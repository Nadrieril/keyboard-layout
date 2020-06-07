#include "ergodox_ez.h"
#include "debug.h"
#include "action_layer.h"
#include "version.h"

// Layers:
// 15: swap_hands
// 11: alt-gr
// 10: shift
// 5: numpad and fn layer
// 1: workman layout
// 0: base
#define WORKMAN_LAYER_ID 1
#define FN_LAYER_ID 5
#define SHIFT_LAYER_ID 10
#define RALT_LAYER_ID 11
#define SWAP_LAYER_ID 15

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
__KEYMAP_GOES_HERE__
};

uint32_t layer_state_set_user(uint32_t state) {
    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();

    if (state & (1<<WORKMAN_LAYER_ID)) {
        ergodox_right_led_2_on();
    }
    if (state & (1<<FN_LAYER_ID)) {
        ergodox_right_led_1_on();
    }
    if (state & (1<<SWAP_LAYER_ID)) {
        ergodox_right_led_3_on();
        swap_hands = true;
    } else {
        swap_hands = false;
    }

    return state;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // If special shift layer is on.
    if (layer_state & (1<<SHIFT_LAYER_ID)) {
        action_t action = action_for_key(SHIFT_LAYER_ID, record->event.key);
        // Keys defined on the special modifier layer should not be processed modified.
        if (action.code != ACTION_TRANSPARENT) {
            if (record->event.pressed) {
                unregister_code(KC_LSFT);
            }
            process_action(record, action);
            if (!record->event.pressed) {
                register_code(KC_LSFT);
            }
            return false;
        }
    }

    // If special alt-gr layer is on.
    if (layer_state & (1<<RALT_LAYER_ID)) {
        action_t action = action_for_key(RALT_LAYER_ID, record->event.key);
        // Keys defined on the special modifier layer should not be processed modified.
        if (action.code != ACTION_TRANSPARENT) {
            if (record->event.pressed) {
                unregister_code(KC_RALT);
            }
            process_action(record, action);
            if (!record->event.pressed) {
                register_code(KC_RALT);
            }
            return false;
        }
    }

    switch (keycode) {
        case KC_LSFT:
            if (record->event.pressed) {
                register_code(KC_LSFT);
                layer_on(SHIFT_LAYER_ID);
            } else {
                unregister_code(KC_LSFT);
                layer_off(SHIFT_LAYER_ID);
            }
            return false; // Skip all further processing of this key
        case KC_RALT:
            if (record->event.pressed) {
                register_code(KC_RALT);
                layer_on(RALT_LAYER_ID);
            } else {
                unregister_code(KC_RALT);
                layer_off(RALT_LAYER_ID);
            }
            return false; // Skip all further processing of this key
        default:
            return true; // Process all other keycodes normally
    }
}

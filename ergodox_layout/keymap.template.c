#include "ergodox_ez.h"
#include "debug.h"
#include "action_layer.h"
#include "version.h"

#define ANY(kc) kc
enum custom_keycodes {
    PLACEHOLDER = SAFE_RANGE,
    EHAT, // ê
};

// Layers:
// 15: swap_hands
// 11: alt-gr
// 10: shift
// 6: symbols layer
// 5: numpad and arrows layer
// 1: alternative layout
// 0: base
#define ALT_LAYOUT_LAYER_ID 1
#define FN_LAYER_ID 5
#define SYMBOLS_LAYER_ID 6
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

    if (state & (1<<ALT_LAYOUT_LAYER_ID)) {
        ergodox_right_led_2_on();
    }
    if (state & (1<<FN_LAYER_ID)) {
        ergodox_right_led_1_on();
    }
    if (state & (1<<SYMBOLS_LAYER_ID)) {
        ergodox_right_led_3_on();
    }
    if (state & (1<<SWAP_LAYER_ID)) {
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        swap_hands = true;
    } else {
        swap_hands = false;
    }

    return state;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case EHAT:
            if (record->event.pressed) {
                unregister_code(KC_RALT);
                SEND_STRING(SS_TAP(X_LBRC)"e");
                register_code(KC_RALT);
            }
            return true;
    }

    if (keycode == KC_LSFT || keycode == LSFT_T(keycode)) {
        if (record->event.pressed) {
            layer_on(SHIFT_LAYER_ID);
        } else {
            layer_off(SHIFT_LAYER_ID);
        }
        return true;
    }
    if (keycode == KC_RALT || keycode == RALT_T(keycode)) {
        if (record->event.pressed) {
            layer_on(RALT_LAYER_ID);
        } else {
            layer_off(RALT_LAYER_ID);
        }
        return true;
    }

    // Keys defined on the special modifier layer should not be processed
    // modified. I'm replicating behavior from tmk_core here. See
    // store_or_get_action mostly.
    keypos_t key = record->event.key;
    uint8_t layer;
    // Get the layer on which the key is defined
    if (record->event.pressed) {
        layer = layer_switch_get_layer(key);
        update_source_layers_cache(key, layer);
    } else {
        layer = read_source_layers_cache(key);
    }
    // If the layer is a special mod layer, _and_ if it is currently active, we
    // temporarily unregister the modifier so that the key can be processed
    // unmodified. If the layer is inactive, the modifier has already been
    // (un)registered so we're good.
    if (layer_state_is(layer) && (layer == SHIFT_LAYER_ID || layer == RALT_LAYER_ID)) {
        action_t action = action_for_key(layer, key);
        if (record->event.pressed) {
            if (layer == SHIFT_LAYER_ID && keycode != LSFT(keycode)) {
                unregister_code(KC_LSFT);
            }
            if (layer == RALT_LAYER_ID && keycode != RALT(keycode)) {
                unregister_code(KC_RALT);
            }
        }
        process_action(record, action);
        if (!record->event.pressed) {
            if (layer == SHIFT_LAYER_ID && keycode != LSFT(keycode)) {
                register_code(KC_LSFT);
            }
            if (layer == RALT_LAYER_ID && keycode != RALT(keycode)) {
                register_code(KC_RALT);
            }
        }
        return false;
    }

    return true;
}

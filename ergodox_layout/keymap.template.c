#include "ergodox_ez.h"
#include "debug.h"
#include "action_layer.h"
#include "version.h"

#define ANY(kc) kc

// Custom keycodes
enum custom_keycodes {
    PLACEHOLDER = SAFE_RANGE,
    EHAT, // ê
};
// Tap Dance declarations
enum {
    // ALT when held or tapped once, SYMBOLS layer held or tapped twice
    TD_ALT_OR_SYMBOLS,
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

bool is_layer_on(uint32_t state, uint32_t layer) {
    if (state & (1<<layer)) {
        return true;
    } else {
        return false;
    }
}

uint32_t layer_state_set_user(uint32_t state) {
    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();

    if (is_layer_on(FN_LAYER_ID) || is_layer_on(SWAP_LAYER_ID)) {
        ergodox_right_led_1_on();
    }
    if (is_layer_on(ALT_LAYOUT_LAYER_ID) || is_layer_on(SWAP_LAYER_ID)) {
        ergodox_right_led_2_on();
    }
    if (is_layer_on(SYMBOLS_LAYER_ID) || is_layer_on(SWAP_LAYER_ID)) {
        ergodox_right_led_3_on();
    }
    swap_hands = is_layer_on(SWAP_LAYER_ID);

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

// See https://docs.qmk.fm/#/tap_hold?id=tap-hold-configuration-options
uint16_t get_tapping_term(uint16_t keycode) {
    switch (keycode) {
        case TD(TD_ALT_OR_SYMBOLS):
            return 500;
        default:
            return TAPPING_TERM;
    }
}
bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    // warning: reversed. See https://github.com/qmk/qmk_firmware/issues/8999
    switch (keycode) {
        default:
            return false;
    }
}
bool get_ignore_mod_tap_interrupt(uint16_t keycode) {
    switch (keycode) {
        case LSFT_T(KC_SPC):
            return true;
        default:
            return false;
    }
}
bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LSFT_T(KC_SPC):
            return true;
        default:
            return false;
    }
}

/// Tap dance
// From https://github.com/walkerstop/qmk_firmware/blob/fanoe/keyboards/wheatfield/blocked65/keymaps/walker/keymap.c
// See also https://beta.docs.qmk.fm/using-qmk/software-features/feature_tap_dance
void alt_finished (qk_tap_dance_state_t *state, void *user_data);
void alt_reset (qk_tap_dance_state_t *state, void *user_data);
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_ALT_OR_SYMBOLS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, alt_finished, alt_reset),
};

typedef struct {
    int state;
} tap;

enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD,
    DOUBLE_TAP,
    DOUBLE_HOLD,
    TRIPLE_TAP,
    TRIPLE_HOLD
};

int cur_dance (qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->pressed) return SINGLE_HOLD;
        else return SINGLE_TAP;
    }
    else if (state->count == 2) {
        if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    else if (state->count == 3) {
        if (state->interrupted || !state->pressed)  return TRIPLE_TAP;
        else return TRIPLE_HOLD;
    }
    else return 0;
}


static tap alttap_state = {
    .state = 0
};

void alt_finished (qk_tap_dance_state_t *state, void *user_data) {
    alttap_state.state = cur_dance(state);
    switch (alttap_state.state) {
        case SINGLE_TAP:
            register_code(KC_LALT);
            unregister_code(KC_LALT);
            break;
        case DOUBLE_TAP:
            set_oneshot_layer(SYMBOLS_LAYER_ID, ONESHOT_START);
            clear_oneshot_layer_state(ONESHOT_PRESSED);
            break;
        case SINGLE_HOLD:
            register_code(KC_LALT);
            break;
        case DOUBLE_HOLD:
            layer_on(SYMBOLS_LAYER_ID);
            break;
    }
}

void alt_reset (qk_tap_dance_state_t *state, void *user_data) {
    switch (alttap_state.state) {
        case SINGLE_TAP:
        case DOUBLE_TAP:
            break;
        case SINGLE_HOLD:
            unregister_code(KC_LALT);
            break;
        case DOUBLE_HOLD:
            layer_off(SYMBOLS_LAYER_ID);
            break;
    }
    alttap_state.state = 0;
}

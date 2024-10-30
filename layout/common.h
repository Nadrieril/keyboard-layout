#include "version.h"
#include QMK_KEYBOARD_H

#define ANY(kc) kc
#define ACTUAL(kc) kc

// Custom keycodes
enum custom_keycodes {
    PLACEHOLDER = SAFE_RANGE,
    KC_GBP, // £
    KC_EUR, // €
    EHAT, // ê
    EACUTE, // é
    EGRAV, // è
    AGRAV, // à
    UGRAV, // ù
    CCED, // ç
};

void process_common_custom_keycodes(uint16_t keycode, keyrecord_t *record) {
    bool azerty = false;
    if (record->event.pressed) {
        switch (keycode) {
            case KC_GBP:
                if (azerty) SEND_STRING(SS_LSFT("}"));
                else SEND_STRING(SS_TAP(X_PAUS) "$gbp");
                break;
            case KC_EUR:
                if (azerty) SEND_STRING(SS_RALT("e"));
                else SEND_STRING(SS_TAP(X_PAUS) "$eur");
                break;
            case EHAT:
                if (azerty) SEND_STRING(SS_TAP(X_LBRC)"e");
                else SEND_STRING(SS_TAP(X_PAUS) SS_LSFT("6") "e");
                break;
            case EACUTE:
                if (azerty) SEND_STRING(SS_TAP(X_2));
                else SEND_STRING(SS_TAP(X_PAUS) SS_TAP(X_QUOT) "e");
                break;
            case EGRAV:
                if (azerty) SEND_STRING(SS_TAP(X_7));
                else SEND_STRING(SS_TAP(X_PAUS) SS_TAP(X_GRV) "e");
                break;
            case UGRAV:
                if (azerty) SEND_STRING(SS_TAP(X_QUOT));
                else SEND_STRING(SS_TAP(X_PAUS) SS_TAP(X_GRV) "u");
                break;
            case AGRAV:
                if (azerty) SEND_STRING(SS_TAP(X_0));
                else SEND_STRING(SS_TAP(X_PAUS) SS_TAP(X_GRV) "a");
                break;
            case CCED:
                if (azerty) SEND_STRING(SS_TAP(X_9));
                else SEND_STRING(SS_TAP(X_PAUS) ",c");
                break;
        }
    }
}

// Modifier layers: Shift and super happen automatically when pressing the
// corresponding modifier. altgr is a normal layer.
// The layer constants must be set.
bool process_mod_layers(uint16_t keycode, keyrecord_t *record) {
    if (keycode == KC_LSFT) {
        if (record->event.pressed) {
            layer_on(SHIFT_LAYER_ID);
        } else {
            layer_off(SHIFT_LAYER_ID);
        }
        return true;
    }
    if (keycode == KC_LGUI) {
        if (record->event.pressed) {
            layer_on(SUPER_LAYER_ID);
        } else {
            layer_off(SUPER_LAYER_ID);
        }
        return true;
    }
    // if (keycode == KC_RALT) {
    //     if (record->event.pressed) {
    //         layer_on(RALT_LAYER_ID);
    //     } else {
    //         layer_off(RALT_LAYER_ID);
    //     }
    //     return true;
    // }

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
    bool special_mod_layer = layer_state_is(layer) && (layer == SHIFT_LAYER_ID /* || layer == RALT_LAYER_ID */);

    // If the layer is a special mod layer, _and_ if it is currently active, we
    // temporarily unregister the modifier so that the key can be processed
    // unmodified. If the layer is inactive, the modifier has already been
    // (un)registered so we're good.
    if (special_mod_layer && record->event.pressed) {
        if (layer == SHIFT_LAYER_ID) {
            unregister_code(KC_LSFT);
        }
        // if (layer == RALT_LAYER_ID) {
        //     unregister_code(KC_RALT);
        // }
    }

    process_common_custom_keycodes(keycode, record);

    if (special_mod_layer) {
        action_t action = action_for_key(layer, key);
        process_action(record, action);
    }

    if (special_mod_layer && !record->event.pressed) {
        if (layer == SHIFT_LAYER_ID) {
            register_code(KC_LSFT);
        }
        // if (layer == RALT_LAYER_ID) {
        //     register_code(KC_RALT);
        // }
    }

    return !special_mod_layer;
}

// Helpers
bool is_layer_on(layer_state_t state, uint8_t layer) {
    return layer_state_cmp(state, layer);
}

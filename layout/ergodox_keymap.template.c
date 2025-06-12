#include "debug.h"
#include "action_layer.h"

// Layers:
// 15: swap_hands
// 13: super
// 11: alt-gr
// 10: shift
// 8: QWERTY
// 7: windows compat + gaming layer
// 6: symbols layer
// 5: numpad layer
// 3: sudoku with letters
// 2: sudoku
// 1: alternative layout
// 0: base
#define ALT_LAYOUT_LAYER_ID 1
#define SUDOKU_LAYER_ID 2
#define SUDOKU_LETTERS_LAYER_ID 3
#define FN_LAYER_ID 5
#define SYMBOLS_LAYER_ID 6
#define GAME_LAYER_ID 7
#define QWERTY_LAYER_ID 8
#define SHIFT_LAYER_ID 10
#define RALT_LAYER_ID 11
#define SUPER_LAYER_ID 13
#define SWAP_LAYER_ID 15

// The top-right key cycles between
// - base layer
// - qwerty (blue led)
// - game (blue+green leds)
// - sudoku (green leds)

#include "common.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
__KEYMAP_GOES_HERE__
};

layer_state_t layer_state_set_user(layer_state_t state) {
    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();

    if (is_layer_on(state, FN_LAYER_ID)
            || is_layer_on(state, SUDOKU_LETTERS_LAYER_ID)
            ) {
        ergodox_right_led_1_on();
        ergodox_right_led_1_set(10);
    }
    if (is_layer_on(state, ALT_LAYOUT_LAYER_ID)
            || is_layer_on(state, QWERTY_LAYER_ID)
            || is_layer_on(state, GAME_LAYER_ID)
        ) {
        ergodox_right_led_2_on();
        ergodox_right_led_2_set(10);
    }
    if (is_layer_on(state, SYMBOLS_LAYER_ID)
            || is_layer_on(state, GAME_LAYER_ID)
            || is_layer_on(state, SUDOKU_LAYER_ID)
            || is_layer_on(state, SUDOKU_LETTERS_LAYER_ID)) {
        ergodox_right_led_3_on();
        ergodox_right_led_3_set(10);
    }
    swap_hands = is_layer_on(state, SWAP_LAYER_ID);

    return state;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    return process_mod_layers(keycode, record);
}

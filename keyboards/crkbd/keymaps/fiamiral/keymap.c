/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include <stdio.h>

//--------------------------------
// Keymap
//--------------------------------

// define tap dance
enum tap_dance_keys {
    TD_LBRC,
    TD_RBRC,
};

void dance_lbrackets(qk_tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1:
            SEND_STRING("(");
            break;
        case 2:
            SEND_STRING("{");
            break;
        case 3:
            SEND_STRING("[");
            break;
    }
};
void dance_rbrackets(qk_tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1:
            SEND_STRING(")");
            break;
        case 2:
            SEND_STRING("}");
            break;
        case 3:
            SEND_STRING("]");
            break;
    }
};

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_LBRC] = ACTION_TAP_DANCE_FN(dance_lbrackets),
    [TD_RBRC] = ACTION_TAP_DANCE_FN(dance_rbrackets),
};


// custom auto shift
bool get_custom_auto_shifted_key(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        // Normal auto shift
        case KC_F1 ... KC_F12:
        // Custom auto shift
        case KC_DOT:
        case KC_COMM:
        case KC_SLSH:
        case KC_COLN:
        case KC_QUOT:
        case KC_BSLS:
        case KC_AMPR:
        case KC_ASTR:
        case KC_PIPE:
        case KC_CIRC:
        case KC_AT:
        case KC_LEFT:
        case KC_DOWN:
        case KC_UP:
        case KC_RIGHT:
        case S(KC_LEFT):
        case S(KC_DOWN):
        case S(KC_UP):
        case S(KC_RIGHT):
            return true;
        default:
            return false;
    }
}

#define AUTOSHIFT_PRESS_DOUBLE(base,modified) case base: \
                                                 register_code16((!shifted) ? base : modified); \
                                                 break;
#define AUTOSHIFT_RELEASE_DOUBLE(base,modified) case base: \
                                                 unregister_code16((!shifted) ? base : modified); \
                                                 break;

void autoshift_press_user(uint16_t keycode, bool shifted, keyrecord_t *record) {
    switch(keycode) {
        AUTOSHIFT_PRESS_DOUBLE(KC_DOT, KC_EXLM);
        AUTOSHIFT_PRESS_DOUBLE(KC_COMM, KC_QUES);
        AUTOSHIFT_PRESS_DOUBLE(KC_SLSH, KC_TILD);
        AUTOSHIFT_PRESS_DOUBLE(KC_COLN, KC_SCLN);
        AUTOSHIFT_PRESS_DOUBLE(KC_QUOT, KC_DQUO);
        AUTOSHIFT_PRESS_DOUBLE(KC_BSLS, KC_GRV);
        AUTOSHIFT_PRESS_DOUBLE(KC_AMPR, KC_ASTR);
        AUTOSHIFT_PRESS_DOUBLE(KC_PIPE, KC_PLUS);
        AUTOSHIFT_PRESS_DOUBLE(KC_CIRC, KC_HASH);
        AUTOSHIFT_PRESS_DOUBLE(KC_AT, KC_PERC);
        AUTOSHIFT_PRESS_DOUBLE(KC_LEFT, KC_HOME);
        AUTOSHIFT_PRESS_DOUBLE(KC_DOWN, KC_PGDN);
        AUTOSHIFT_PRESS_DOUBLE(KC_UP, KC_PGUP);
        AUTOSHIFT_PRESS_DOUBLE(KC_RGHT, KC_END);
        AUTOSHIFT_PRESS_DOUBLE(S(KC_LEFT), S(KC_HOME));
        AUTOSHIFT_PRESS_DOUBLE(S(KC_DOWN), S(KC_PGDN));
        AUTOSHIFT_PRESS_DOUBLE(S(KC_UP), S(KC_PGUP));
        AUTOSHIFT_PRESS_DOUBLE(S(KC_RGHT), S(KC_END));
        default:
            if (shifted) {
                add_weak_mods(MOD_BIT(KC_LSFT));
            }
            // & 0xFF gets the Tap key for Tap Holds, required when using Retro Shift
            register_code16((IS_RETRO(keycode)) ? keycode & 0xFF : keycode);
    }
}

void autoshift_release_user(uint16_t keycode, bool shifted, keyrecord_t *record) {
    switch(keycode) {
        AUTOSHIFT_RELEASE_DOUBLE(KC_DOT, KC_EXLM);
        AUTOSHIFT_RELEASE_DOUBLE(KC_COMM, KC_QUES);
        AUTOSHIFT_RELEASE_DOUBLE(KC_SLSH, KC_TILD);
        AUTOSHIFT_RELEASE_DOUBLE(KC_COLN, KC_SCLN);
        AUTOSHIFT_RELEASE_DOUBLE(KC_QUOT, KC_DQUO);
        AUTOSHIFT_RELEASE_DOUBLE(KC_BSLS, KC_GRV);
        AUTOSHIFT_RELEASE_DOUBLE(KC_AMPR, KC_ASTR);
        AUTOSHIFT_RELEASE_DOUBLE(KC_PIPE, KC_PLUS);
        AUTOSHIFT_RELEASE_DOUBLE(KC_CIRC, KC_HASH);
        AUTOSHIFT_RELEASE_DOUBLE(KC_AT, KC_PERC);
        AUTOSHIFT_RELEASE_DOUBLE(KC_LEFT, KC_HOME);
        AUTOSHIFT_RELEASE_DOUBLE(KC_DOWN, KC_PGDN);
        AUTOSHIFT_RELEASE_DOUBLE(KC_UP, KC_PGUP);
        AUTOSHIFT_RELEASE_DOUBLE(KC_RGHT, KC_END);
        AUTOSHIFT_RELEASE_DOUBLE(S(KC_LEFT), S(KC_HOME));
        AUTOSHIFT_RELEASE_DOUBLE(S(KC_DOWN), S(KC_PGDN));
        AUTOSHIFT_RELEASE_DOUBLE(S(KC_UP), S(KC_PGUP));
        AUTOSHIFT_RELEASE_DOUBLE(S(KC_RGHT), S(KC_END));
        default:
            // & 0xFF gets the Tap key for Tap Holds, required when using Retro Shift
            // The IS_RETRO check isn't really necessary here, always using
            // keycode & 0xFF would be fine.
            unregister_code16((IS_RETRO(keycode)) ? keycode & 0xFF : keycode);
    }
}

uint16_t get_autoshift_timeout(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case KC_LEFT:
        case KC_DOWN:
        case KC_UP:
        case KC_RIGHT:
        case S(KC_LEFT):
        case S(KC_DOWN):
        case S(KC_UP):
        case S(KC_RIGHT):
            return 2 * get_generic_autoshift_timeout();
        default:
            return get_generic_autoshift_timeout();
    }
}

// define layer
enum layer_number {
    _EUCALYN = 0,
    _SYMBOL,
    _NUMBER,
    _GAMING,
    _GAMING_FN,
};

// define keymap
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = { \
  /* EUCALYN
   * /-----------------------------------------------------\                 /-----------------------------------------------------\
   * |        |        |        |        |        |        |                 |        |        |        |        |        |        |
   * |        | ESCAPE |    ,   |    .   |    P   |    Q   |                 |    Y   |    G   |    D   |    M   |    F   |        |
   * |        |        |    ?   |    !   |        |        |                 |        |        |        |        |        |        |
   * |--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|
   * |        |        |        |        |        |        |                 |        |        |        |        |        |        |
   * |        |    A   |    O   |    E   |    I   |    U   |                 |    B   |    N   |    T   |    R   |    S   |        |
   * |        |        |        |        |        |        |                 |        |        |        |        |        |        |
   * |--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|
   * |        |        |        |        |        |        |                 |        |        |        |        |        |        |
   * |   ALT  |    Z   |    X   |    C   |    V   |    W   |                 |    H   |    J   |    K   |    L   |    -   |        |
   * |        |        |        |        |        |        |                 |        |        |        |        |        |        |
   * \-----------------------------------+--------+--------|-----------------|--------+--------+-----------------------------------/
   *                                     |        |        |        |        |        |        |
   *                                     |        |   TAB  |  SPACE |  ENTER | ESCAPE | BSPACE |
   *                                     |  CTRL  | NUMBER |   GUI  |        | SYMBOL |        |
   *                                     \-----------------------------------------------------/
   */
  #define TAB_NUM LT(_NUMBER, KC_TAB)
  #define SPC_GUI GUI_T(KC_SPC)
  #define ESC_SYM LT(_SYMBOL, KC_ESC)
  [_EUCALYN] = LAYOUT_split_3x6_3(
       _______,  KC_ESC, KC_COMM,  KC_DOT,    KC_P,    KC_Q,                      KC_Y,    KC_G,    KC_D,    KC_M,    KC_F, _______,
       _______,    KC_A,    KC_O,    KC_E,    KC_I,    KC_U,                      KC_B,    KC_N,    KC_T,    KC_R,    KC_S, _______,
       KC_LALT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_W,                      KC_H,    KC_J,    KC_K,    KC_L, KC_MINS, _______,
                                           KC_LCTL, TAB_NUM,  SPC_GUI,  KC_ENT, ESC_SYM, KC_BSPC
  ),
  /* SYMBOL
   * /-----------------------------------------------------\                 /-----------------------------------------------------\
   * |        |        |        |        |        |        |                 |        |        |        |        |        |        |
   * |        |    ^   |    <   |    &   |    >   |    $   |                 | GAMING |        |        |        |        |        |
   * |        |    #   |        |    *   |        |        |                 |        |        |        |        |        |        |
   * |--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|
   * |        |        |        |        |        |        |                 |        |        |        |        |        |        |
   * |        |    '   |  ( { [ |    =   |  ) } ] |    :   |                 |        |    ←   |    ↓   |    ↑   |    →   |        |
   * |        |    "   |        |        |        |    ;   |                 |        |  HOME  |  PGDN  |  PGUP  |   END  |        |
   * |--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|
   * |        |        |        |        |        |        |                 |        |        |        |        |        |        |
   * |        |    @   |    /   |    |   |    \   |    _   |                 |        |   S-←  |   S-↓  |   S-↑  |   S-→  |        |
   * |        |    %   |    ~   |    +   |    `   |        |                 |        | S-HOME | S-PGDN | S-PGUP |  S-END |        |
   * \-----------------------------------+--------+--------|-----------------|--------+--------+-----------------------------------/
   *                                     |        |        |        |        |        |        |
   *                                     |        |        |        |        |        |        |
   *                                     |        |        |        |        |        |        |
   *                                     \-----------------------------------------------------/
   */
  #define D_LBRC TD(TD_LBRC)
  #define D_RBRC TD(TD_RBRC)
  #define S_LEFT S(KC_LEFT)
  #define S_DOWN S(KC_DOWN)
  #define S_UP S(KC_UP)
  #define S_RGHT S(KC_RGHT)
  #define TO_GAME TO(_GAMING)
  [_SYMBOL] = LAYOUT_split_3x6_3(
       _______, KC_CIRC,   KC_LT, KC_AMPR,   KC_GT,  KC_DLR,                   TO_GAME, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
       _______, KC_QUOT,  D_LBRC,  KC_EQL,  D_RBRC, KC_COLN,                   XXXXXXX, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, _______,
       _______,   KC_AT, KC_SLSH, KC_PIPE, KC_BSLS, KC_UNDS,                   XXXXXXX,  S_LEFT,  S_DOWN,    S_UP,  S_RGHT, _______,
                                           _______, _______, _______, _______, _______, _______
  ),
  /* NUMBER
   * /-----------------------------------------------------\                 /-----------------------------------------------------\
   * |        |        |        |        |        |        |                 |        |        |        |        |        |        |
   * |        |   F1   |   F2   |   F3   |   F4   |   F5   |                 |    /   |    7   |    8   |    9   |    *   |        |
   * |        |        |        |        |        |        |                 |        |        |        |        |        |        |
   * |--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|
   * |        |        |        |        |        |        |                 |        |        |        |        |        |        |
   * |        |   F6   |   F7   |   F8   |   F9   |  F10   |                 |    -   |    4   |    5   |    6   |    +   |        |
   * |        |        |        |        |        |        |                 |        |        |        |        |        |        |
   * |--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|
   * |        |        |        |        |        |        |                 |        |        |        |        |        |        |
   * |        |  F11   |  F12   |        |        |  PrSc  |                 |        |    1   |    2   |    3   |    .   |        |
   * |        |        |        |        |        |        |                 |        |        |        |        |        |        |
   * \-----------------------------------+--------+--------|-----------------|--------+--------+-----------------------------------/
   *                                     |        |        |        |        |        |        |
   *                                     |        |        |        |        |        |    0   |
   *                                     |        |        |        |        |        |        |
   *                                     \-----------------------------------------------------/
   */
  [_NUMBER] = LAYOUT_split_3x6_3(
       _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                   KC_SLSH,    KC_7,    KC_8,    KC_9, KC_ASTR, _______,
       _______,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,                   KC_MINS,    KC_4,    KC_5,    KC_6, KC_PLUS, _______,
       _______,  KC_F11,  KC_F12, XXXXXXX, XXXXXXX, KC_PSCR,                   XXXXXXX,    KC_1,    KC_2,    KC_3,  KC_DOT, _______,
                                           _______, _______, _______, _______, _______,    KC_0
  ),  /* GAMING
   * /-----------------------------------------------------\                 /-----------------------------------------------------\
   * |        |        |        |        |        |        |                 |        |        |        |        |        |        |
   * |        |   TAB  |    Q   |    W   |    E   |    R   |                 | EUCALYN|    7   |    8   |    9   |        |        |
   * |        |   F1   |   F2   |        |   F3   |   F4   |                 |        |        |        |        |        |        |
   * |--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|
   * |        |        |        |        |        |        |                 |        |        |        |        |        |        |
   * |        |  SHIFT |    A   |    S   |    D   |    F   |                 |        |    4   |    5   |    6   |        |        |
   * |        |        |        |        |        |    G   |                 |        |        |        |        |        |        |
   * |--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|
   * |        |        |        |        |        |        |                 |        |        |        |        |        |        |
   * |        |  LCTRL |    Z   |    X   |    C   |    V   |                 |   F12  |    1   |    2   |    3   |        |        |
   * |        |  RCTRL |    B   |    N   |    M   |    L   |                 |        |        |        |        |        |        |
   * \-----------------------------------+--------+--------|-----------------|--------+--------+-----------------------------------/
   *                                     |        |        |        |        |        |        |
   *                                     |   Fn   |  SPACE |        |        |        |    0   |
   *                                     |        |        |        |        |        |        |
   *                                     \-----------------------------------------------------/
   */
  #define MO_GMFN MO(_GAMING_FN)
  #define TO_ECLN TO(_EUCALYN)
  [_GAMING] = LAYOUT_split_3x6_3(
       XXXXXXX,  KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,                   TO_ECLN,    KC_7,    KC_8,    KC_9, XXXXXXX, XXXXXXX,
       XXXXXXX, KC_LSFT,    KC_A,    KC_S,    KC_D,    KC_F,                   XXXXXXX,    KC_4,    KC_5,    KC_6, XXXXXXX, XXXXXXX,
       XXXXXXX, KC_LCTL,    KC_Z,    KC_X,    KC_C,    KC_V,                    KC_F12,    KC_1,    KC_2,    KC_3, XXXXXXX, XXXXXXX,
                                           MO_GMFN,  KC_SPC, XXXXXXX, XXXXXXX, XXXXXXX,    KC_0
  ),
  [_GAMING_FN] = LAYOUT_split_3x6_3(
       XXXXXXX,   KC_F1,   KC_F2, _______,   KC_F3,   KC_F4,                   XXXXXXX,    KC_7,    KC_8,    KC_9, XXXXXXX, XXXXXXX,
       XXXXXXX, _______, _______, _______, _______,    KC_G,                   XXXXXXX,    KC_4,    KC_5,    KC_6, XXXXXXX, XXXXXXX,
       XXXXXXX, KC_RCTL,    KC_B,    KC_N,    KC_M,    KC_L,                   XXXXXXX,    KC_1,    KC_2,    KC_3, XXXXXXX, XXXXXXX,
                                           _______,  KC_SPC, XXXXXXX, XXXXXXX, XXXXXXX,    KC_0
  )
};

// rgblight
const rgblight_segment_t PROGMEM rgb_eucalyn[] = RGBLIGHT_LAYER_SEGMENTS(
    {  7,  6, HSV_WHITE},
    { 15,  2, HSV_WHITE},
    { 19,  4, HSV_WHITE},
    { 34,  6, HSV_WHITE},
    { 42,  6, HSV_WHITE},
    { 49,  2, HSV_WHITE},
    { 17,  2, HSV_ORANGE},
    { 48,  1, HSV_ORANGE},
    {  6,  1, HSV_TURQUOISE},
    { 13,  2, HSV_TURQUOISE},
    { 33,  1, HSV_TURQUOISE},
    { 40,  2, HSV_TURQUOISE},
    { 23,  1, HSV_TURQUOISE}
);

const rgblight_segment_t PROGMEM rgb_symbol[] = RGBLIGHT_LAYER_SEGMENTS(
    {  7,  6, HSV_ORANGE},
    { 15,  9, HSV_ORANGE},
    { 38,  2, HSV_GREEN},
    { 42,  2, HSV_GREEN},
    { 46,  4, HSV_GREEN},
    { 36,  1, HSV_RED},
    {  6,  1, HSV_TURQUOISE},
    { 13,  2, HSV_TURQUOISE},
    { 33,  1, HSV_TURQUOISE},
    { 40,  2, HSV_TURQUOISE}
);

const rgblight_segment_t PROGMEM rgb_number[] = RGBLIGHT_LAYER_SEGMENTS(
    {  7,  1, HSV_TURQUOISE},
    {  8,  4, HSV_MAGENTA},
    { 16,  8, HSV_MAGENTA},
    { 37, 10, HSV_BLUE},
    { 35,  2, HSV_ORANGE},
    { 48,  3, HSV_ORANGE},
    {  6,  1, HSV_TURQUOISE},
    { 13,  2, HSV_TURQUOISE},
    { 33,  1, HSV_TURQUOISE},
    { 40,  1, HSV_TURQUOISE}
);

const rgblight_segment_t PROGMEM rgb_gaming[] = RGBLIGHT_LAYER_SEGMENTS(
    // WASD key
    { 11,  1, HSV_PINK},
    { 16,  2, HSV_PINK},
    { 19,  1, HSV_PINK},
    // Other key
    {  7,  4, HSV_WHITE},
    { 12,  2, HSV_WHITE},
    { 15,  1, HSV_WHITE},
    { 18,  1, HSV_WHITE},
    { 20,  4, HSV_WHITE},
    // Screenshot
    { 34,  1, HSV_ORANGE},
    // Numpad
    { 37,  3, HSV_BLUE},
    { 41,  7, HSV_BLUE},
    // Fn
    { 14,  1, HSV_CYAN},
    // Back to eucalyn
    { 36,  1, HSV_RED}
);

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    rgb_eucalyn,
    rgb_symbol,
    rgb_number,
    rgb_gaming
);

void keyboard_post_init_user(void) {
    rgblight_layers = my_rgb_layers;
    rgblight_sethsv_range(0, 0, 0, 0, 54);
    rgblight_sethsv_range(HSV_TURQUOISE, 24, 3);
    rgblight_sethsv_range(HSV_TURQUOISE, 51, 3);
};

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, _EUCALYN));
    rgblight_set_layer_state(1, layer_state_cmp(state, _SYMBOL));
    rgblight_set_layer_state(2, layer_state_cmp(state, _NUMBER));
    rgblight_set_layer_state(3, layer_state_cmp(state, _GAMING));
    switch (get_highest_layer(state)) {
        case _EUCALYN:
        case _SYMBOL:
        case _NUMBER:
            autoshift_enable();
            break;
        default:
            autoshift_disable();
            break;
    }
    return state;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    return true;
};

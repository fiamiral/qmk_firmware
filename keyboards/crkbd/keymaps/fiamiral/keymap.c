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
// custom auto shift
bool get_custom_auto_shifted_key(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        // EUCALYN
        case KC_COMM:
        case KC_DOT:
        // SYMBOL
        case KC_CIRC:
        case KC_LBRC:
        case KC_AMPR:
        case KC_RBRC:
        case KC_QUOT:
        case KC_LPRN:
        case KC_EQL:
        case KC_RPRN:
        case KC_COLN:
        case KC_AT:
        case KC_SLSH:
        case KC_PIPE:
        case KC_BSLS:
        // NUMBER
        case KC_0:
        case KC_1:
        case KC_2:
        case KC_3:
        case KC_4:
        case KC_5:
        case KC_6:
        case KC_7:
        case KC_8:
        case KC_9:
        case KC_PLUS:
        case KC_MINS:
        // MOVE
        case KC_UP:
        case KC_DOWN:
        case KC_LEFT:
        case KC_RGHT:
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
        // EUCALYN
        AUTOSHIFT_PRESS_DOUBLE(KC_COMM, KC_QUES);
        AUTOSHIFT_PRESS_DOUBLE(KC_DOT, KC_EXLM);
        // SYMBOL
        AUTOSHIFT_PRESS_DOUBLE(KC_CIRC, KC_HASH);
        AUTOSHIFT_PRESS_DOUBLE(KC_LBRC, KC_LT);
        AUTOSHIFT_PRESS_DOUBLE(KC_AMPR, KC_ASTR);
        AUTOSHIFT_PRESS_DOUBLE(KC_RBRC, KC_GT);
        AUTOSHIFT_PRESS_DOUBLE(KC_QUOT, KC_DQUO);
        AUTOSHIFT_PRESS_DOUBLE(KC_LPRN, KC_LCBR);
        AUTOSHIFT_PRESS_DOUBLE(KC_EQL, KC_UNDS);
        AUTOSHIFT_PRESS_DOUBLE(KC_RPRN, KC_RCBR);
        AUTOSHIFT_PRESS_DOUBLE(KC_COLN, KC_SCLN);
        AUTOSHIFT_PRESS_DOUBLE(KC_AT, KC_PERC);
        AUTOSHIFT_PRESS_DOUBLE(KC_SLSH, KC_TILD);
        AUTOSHIFT_PRESS_DOUBLE(KC_PIPE, KC_PLUS);
        AUTOSHIFT_PRESS_DOUBLE(KC_BSLS, KC_GRV);
        // NUMBER
        AUTOSHIFT_PRESS_DOUBLE(KC_0, KC_EQL);
        AUTOSHIFT_PRESS_DOUBLE(KC_1, KC_F1);
        AUTOSHIFT_PRESS_DOUBLE(KC_2, KC_F2);
        AUTOSHIFT_PRESS_DOUBLE(KC_3, KC_F3);
        AUTOSHIFT_PRESS_DOUBLE(KC_4, KC_F4);
        AUTOSHIFT_PRESS_DOUBLE(KC_5, KC_F5);
        AUTOSHIFT_PRESS_DOUBLE(KC_6, KC_F6);
        AUTOSHIFT_PRESS_DOUBLE(KC_7, KC_F7);
        AUTOSHIFT_PRESS_DOUBLE(KC_8, KC_F8);
        AUTOSHIFT_PRESS_DOUBLE(KC_9, KC_F9);
        AUTOSHIFT_PRESS_DOUBLE(KC_PLUS, KC_ASTR);
        AUTOSHIFT_PRESS_DOUBLE(KC_MINS, KC_SLSH);
        // MOVE
        AUTOSHIFT_PRESS_DOUBLE(KC_UP, KC_PGUP);
        AUTOSHIFT_PRESS_DOUBLE(KC_DOWN, KC_PGDN);
        AUTOSHIFT_PRESS_DOUBLE(KC_LEFT, KC_HOME);
        AUTOSHIFT_PRESS_DOUBLE(KC_RGHT, KC_END);
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
        // EUCALYN
        AUTOSHIFT_RELEASE_DOUBLE(KC_COMM, KC_QUES);
        AUTOSHIFT_RELEASE_DOUBLE(KC_DOT, KC_EXLM);
        // SYMBOL
        AUTOSHIFT_RELEASE_DOUBLE(KC_CIRC, KC_HASH);
        AUTOSHIFT_RELEASE_DOUBLE(KC_LBRC, KC_LT);
        AUTOSHIFT_RELEASE_DOUBLE(KC_AMPR, KC_ASTR);
        AUTOSHIFT_RELEASE_DOUBLE(KC_RBRC, KC_GT);
        AUTOSHIFT_RELEASE_DOUBLE(KC_QUOT, KC_DQUO);
        AUTOSHIFT_RELEASE_DOUBLE(KC_LPRN, KC_LCBR);
        AUTOSHIFT_RELEASE_DOUBLE(KC_EQL, KC_UNDS);
        AUTOSHIFT_RELEASE_DOUBLE(KC_RPRN, KC_RCBR);
        AUTOSHIFT_RELEASE_DOUBLE(KC_COLN, KC_SCLN);
        AUTOSHIFT_RELEASE_DOUBLE(KC_AT, KC_PERC);
        AUTOSHIFT_RELEASE_DOUBLE(KC_SLSH, KC_TILD);
        AUTOSHIFT_RELEASE_DOUBLE(KC_PIPE, KC_PLUS);
        AUTOSHIFT_RELEASE_DOUBLE(KC_BSLS, KC_GRV);
        // NUMBER
        AUTOSHIFT_RELEASE_DOUBLE(KC_0, KC_EQL);
        AUTOSHIFT_RELEASE_DOUBLE(KC_1, KC_F1);
        AUTOSHIFT_RELEASE_DOUBLE(KC_2, KC_F2);
        AUTOSHIFT_RELEASE_DOUBLE(KC_3, KC_F3);
        AUTOSHIFT_RELEASE_DOUBLE(KC_4, KC_F4);
        AUTOSHIFT_RELEASE_DOUBLE(KC_5, KC_F5);
        AUTOSHIFT_RELEASE_DOUBLE(KC_6, KC_F6);
        AUTOSHIFT_RELEASE_DOUBLE(KC_7, KC_F7);
        AUTOSHIFT_RELEASE_DOUBLE(KC_8, KC_F8);
        AUTOSHIFT_RELEASE_DOUBLE(KC_9, KC_F9);
        AUTOSHIFT_RELEASE_DOUBLE(KC_PLUS, KC_ASTR);
        AUTOSHIFT_RELEASE_DOUBLE(KC_MINS, KC_SLSH);
        // MOVE
        AUTOSHIFT_RELEASE_DOUBLE(KC_UP, KC_PGUP);
        AUTOSHIFT_RELEASE_DOUBLE(KC_DOWN, KC_PGDN);
        AUTOSHIFT_RELEASE_DOUBLE(KC_LEFT, KC_HOME);
        AUTOSHIFT_RELEASE_DOUBLE(KC_RGHT, KC_END);
        default:
            // & 0xFF gets the Tap key for Tap Holds, required when using Retro Shift
            // The IS_RETRO check isn't really necessary here, always using
            // keycode & 0xFF would be fine.
            unregister_code16((IS_RETRO(keycode)) ? keycode & 0xFF : keycode);
    }
}

uint16_t get_autoshift_timeout(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        default:
            return get_generic_autoshift_timeout();
    }
}

// define layer
enum layer_number {
    _EUCALYN = 0,
    _SYMBOL,
    _NUMBER,
    _MOVE,
    _GAMING,
    _GAMING_FN,
};

// define
#define SYM_N LT(_SYMBOL, KC_N)
#define NUM_E LT(_NUMBER, KC_E)
#define MOV_I LT(_MOVE,   KC_I)

#define GUI_Z LGUI_T(KC_Z)
#define ALT_X LALT_T(KC_X)
#define CTL_C LCTL_T(KC_C)
#define SFT_V LSFT_T(KC_V)

#define SFT_J RSFT_T(KC_J)
#define CTL_K RCTL_T(KC_K)
#define ALT_L RALT_T(KC_L)
#define GUI_MIN RGUI_T(KC_MINS)

// combos
enum combos {
    EI_SPACE,
    OI_TAB,
    NT_ENTER,
    TR_BSPC,
    DM_DEL,
};

const uint16_t PROGMEM ei_space[] = {NUM_E, MOV_I, COMBO_END};
const uint16_t PROGMEM oi_tab[]   = {KC_O,  MOV_I, COMBO_END};
const uint16_t PROGMEM nt_enter[] = {SYM_N, KC_T,  COMBO_END};
const uint16_t PROGMEM tr_bspc[]  = {KC_T,  KC_R,  COMBO_END};
const uint16_t PROGMEM dm_del[]   = {KC_D,  KC_M,  COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    [EI_SPACE] = COMBO(ei_space, KC_SPACE),
    [OI_TAB]   = COMBO(oi_tab, KC_TAB),
    [NT_ENTER] = COMBO(nt_enter, KC_ENTER),
    [TR_BSPC]  = COMBO(tr_bspc, KC_BSPC),
    [DM_DEL]   = COMBO(dm_del, KC_DEL),
};

// define keymap
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = { \
  [_EUCALYN] = LAYOUT_split_3x6_3(
       XXXXXXX, KC_ESC,  KC_COMM, KC_DOT,  KC_P,    KC_Q,     KC_Y,    KC_G,    KC_D,    KC_M,    KC_F,    XXXXXXX,
       XXXXXXX, KC_A,    KC_O,    NUM_E,   MOV_I,   KC_U,     KC_B,    SYM_N,   KC_T,    KC_R,    KC_S,    XXXXXXX,
       XXXXXXX, GUI_Z,   ALT_X,   CTL_C,   SFT_V,   KC_W,     KC_H,    SFT_J,   CTL_K,   ALT_L,   GUI_MIN, XXXXXXX,
                                  XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX
  ),
  [_SYMBOL] = LAYOUT_split_3x6_3(
       XXXXXXX, KC_CIRC, KC_LBRC, KC_AMPR, KC_RBRC, KC_DLR,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
       XXXXXXX, KC_QUOT, KC_LPRN, KC_EQL,  KC_RPRN, KC_COLN,  XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
       XXXXXXX, KC_AT,   KC_SLSH, KC_PIPE, KC_BSLS, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                  XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX
  ),
  [_NUMBER] = LAYOUT_split_3x6_3(
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  KC_MINS, KC_7,    KC_8,    KC_9,    KC_F12,  XXXXXXX,
       XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX,  KC_PLUS, KC_4,    KC_5,    KC_6,    KC_F11,  XXXXXXX,
       XXXXXXX, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,  KC_0,    KC_1,    KC_2,    KC_3,    KC_F10,  XXXXXXX,
                                  XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX
  ),
  [_MOVE] = LAYOUT_split_3x6_3(
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, KC_UP,   XXXXXXX, XXXXXXX, TO(_GAMING),
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX,  XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, XXXXXXX,
       XXXXXXX, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                  XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX
  ),
  /* GAMING
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
    rgblight_set_layer_state(3, layer_state_cmp(state, _NUMBER));
    rgblight_set_layer_state(4, layer_state_cmp(state, _GAMING));
    switch (get_highest_layer(state)) {
        case _EUCALYN:
        case _SYMBOL:
        case _NUMBER:
        case _MOVE:
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

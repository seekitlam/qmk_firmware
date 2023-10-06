/* Copyright 2022 nikchi
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

enum layers{
  MAC_BASE,
  WIN_BASE,
  MAC_FN,
  WIN_FN
};

enum tap{
  TD_CTCPS = 0,
  TD_SLNUM
};
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_CTCPS] = ACTION_TAP_DANCE_DOUBLE(KC_LCTL, KC_CAPS),
    [TD_SLNUM] = ACTION_TAP_DANCE_DOUBLE(KC_PSLS, KC_NUM)
};

enum my_keycodes{
    ENCU = SAFE_RANGE,
    ENCD
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  bool shift_active = get_mods() & MOD_MASK_SHIFT;
  bool alt_active = get_mods() & MOD_MASK_ALT;
  bool ctrl_active = get_mods() & MOD_MASK_CTRL;
  switch (keycode) {
    case ENCU:
      if (record->event.pressed) {
        if (shift_active) { //right arrows with shift
            tap_code(KC_RGHT);
        } else if (alt_active) { //alt tab defaults to next window
            tap_code(KC_TAB);
        } else if (ctrl_active) {
            tap_code(KC_UP);
        } else { //default volume down
            tap_code(KC_VOLU);
        }
      } else {
      }
      return false; // Skip all further processing of this key
    case ENCD:
      if (record->event.pressed) {
        if (shift_active) { //left arrow with shift
            tap_code(KC_LEFT);
        } else if (alt_active) { //alt tab but with one shot mod
            add_oneshot_mods(MOD_MASK_SHIFT);
            tap_code(KC_TAB);
        } else if (ctrl_active) {
            tap_code(KC_DOWN);
        }  else { //default volume down
            tap_code(KC_VOLD);
        }
      } else {
      }
      return false; // Skip all further processing of this key
    default:
        return true;
  }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MAC_BASE] = LAYOUT_all(
		KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL, KC_PGUP, KC_PGDN, KC_MUTE,
		KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_PSLS, KC_PAST,
		KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, KC_P7, KC_P8, KC_P9, KC_PMNS,
		KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, KC_P4, KC_P5, KC_P6, KC_PPLS,
		KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP, KC_P1, KC_P2, KC_P3,
		KC_LCTL, KC_LALT, KC_LGUI, KC_SPC, KC_RGUI, MO(2), KC_LEFT, KC_DOWN, KC_RGHT, KC_P0, KC_PDOT, KC_PENT
    ),

    [WIN_BASE] = LAYOUT_all(
		KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_MRWD, KC_MFFD, KC_DEL, KC_NUM, KC_END, KC_MUTE,
		KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_PSLS, KC_PAST,
		KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, KC_P7, KC_P8, KC_P9, KC_PMNS,
		KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, KC_P4, KC_P5, KC_P6, KC_PPLS,
		KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP, KC_P1, KC_P2, KC_P3,
		KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_RALT, MO(3), KC_LEFT, KC_DOWN, KC_RGHT, KC_P0, KC_PDOT, KC_PENT
    ),

    [MAC_FN] = LAYOUT_all(
		RGB_TOG,KC_BRID, KC_BRIU, LGUI(KC_TAB), LGUI(KC_Z), KC_MAIL, LGUI(KC_D), KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU, RESET, KC_SLEP, KC_NO, KC_MSTP,
		KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, RGB_TOG, KC_NO, KC_NO,
		KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, RGB_MOD, KC_NO, KC_NO, KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO,
		KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO, KC_NO, KC_NO,
		KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, RGB_VAI, KC_NO,   KC_NO, KC_NO,
		KC_NO,  0x5d61, KC_NO, KC_NO, KC_NO, KC_NO, RGB_SPI, RGB_VAD, RGB_SPD, KC_NO, KC_NO, KC_NO
    ),

    [WIN_FN] = LAYOUT_all(
		RGB_TOG,KC_BRID, KC_BRIU, LGUI(KC_UP), KC_F4, KC_NO, KC_NO, KC_MRWD, KC_MPLY, KC_MFFD, KC_MUTE, KC_VOLD, KC_VOLU, KC_NO, KC_NO, KC_NO, KC_NO,
		KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, RGB_TOG, KC_NO, KC_NO,
		KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, RGB_MOD, KC_NO, KC_NO, KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO,
		KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO, KC_NO, KC_NO,
		KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, RGB_VAI, KC_NO,   KC_NO, KC_NO,
		KC_NO,  0x5d61, KC_NO, KC_NO, KC_NO, KC_NO, RGB_SPI, RGB_VAD, RGB_SPD, KC_NO, KC_NO, KC_NO
    )
};

layer_state_t layer_state_set_user(layer_state_t state) {
	palSetPadMode(GPIOC,  0, PAL_MODE_OUTPUT_PUSHPULL);
    switch (get_highest_layer(state)) {
        case 0:
            palClearPad(GPIOC, 0);
            break;
        case 1:
            palSetPad(GPIOC, 0);
            break;
		case 2:
            palClearPad(GPIOC, 0);
            break;
        case 3:
			palClearPad(GPIOC, 0);
            break;
        default:
            break;
    }
  return state;
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] = { ENCODER_CCW_CW(ENCD, ENCU)},
    [1] = { ENCODER_CCW_CW(KC_NO, KC_NO)},
    [2] = { ENCODER_CCW_CW(KC_WH_D, KC_WH_U)},
    [3] = { ENCODER_CCW_CW(RGB_RMOD, RGB_MOD)},
};
#endif

bool dip_switch_update_user(uint8_t index, bool active) {
    switch (index) {
        case 0:
            if(active) { layer_on(0); } else { layer_off(0); }
            break;
        case 1:
            if(active) { layer_on(1); } else { layer_off(1); }
            break;
    }
    return true;
};


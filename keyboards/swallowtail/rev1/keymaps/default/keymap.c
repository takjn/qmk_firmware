/* Copyright 2019 e3w2q
 * Copyright 2021 takjn
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

enum preonic_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  SEND_00 = SAFE_RANGE,
  SEND_000,
  ADJUST,
  RGB_RST
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT( /* Base */
    KC_GESC,          KC_1,               KC_2,             KC_3,             KC_4,               KC_5,
    KC_TAB,           KC_Q,               KC_W,             KC_E,             KC_R,               KC_T,
    KC_LCTL,          KC_A,               KC_S,             KC_D,             KC_F,               KC_G,
    LSFT_T(KC_MINS),  KC_Z,               KC_X,             KC_C,             KC_V,               KC_B,
    ADJUST,           KC_PSCR,            KC_LGUI,          LALT_T(KC_QUOT),  LT(_LOWER,KC_LBRC), KC_SPC,

    KC_6,             KC_7,               KC_8,             KC_9,             KC_0,               KC_BSPC,
    KC_Y,             KC_U,               KC_I,             KC_O,             KC_P,               KC_BSLS,
    KC_H,             KC_J,               KC_K,             KC_L,             KC_SCLN,            KC_ENT,
    KC_N,             KC_M,               KC_COMM,          KC_DOT,           KC_UP,              RSFT_T(KC_EQL),
    KC_SPC,           LT(_RAISE,KC_RBRC), RALT_T(KC_SLSH),  KC_LEFT,          KC_DOWN,            KC_RGHT
  ),
  [_LOWER] = LAYOUT(
    KC_GRV,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,
    _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,

    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_DEL,
    _______,  _______,  _______,  KC_F11,   KC_F12,   _______,
    KC_HOME,  KC_PGUP,  KC_UP,    KC_PGDN,  KC_END,   _______,
    _______,  KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_PGUP,  _______,
    _______,  _______,  _______,  KC_HOME,  KC_PGDN,  KC_END
  ),
  [_RAISE] = LAYOUT(
    KC_GRV,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,
    _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,

    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_DEL,
    _______,  _______,  _______,  KC_F11,   KC_F12,   _______,
    KC_HOME,  KC_PGUP,  KC_UP,    KC_PGDN,  KC_END,   _______,
    _______,  KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_PGUP,  _______,
    _______,  _______,  _______,  KC_HOME,  KC_PGDN,  KC_END
  ),
  [_ADJUST] = LAYOUT(
    _______,  _______,  _______,  _______,  _______,  _______,
    _______,  RGB_TOG,  RGB_MOD,  RGB_RST,  _______,  _______,
    _______,  RGB_HUI,  RGB_SAI,  RGB_VAI,  _______,  _______,
    _______,  RGB_HUD,  RGB_SAD,  RGB_VAD,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,

    _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______
  ),
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case SEND_00:
      if (record->event.pressed) {
        // when keycode SEND_00 is pressed
        SEND_STRING("00");
      } else {
        // when keycode SEND_00 is released
      }
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_LOWER);
        layer_on(_RAISE);
      } else {
        layer_off(_LOWER);
        layer_off(_RAISE);
      }
      break;
    case RGB_RST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
        }
      #endif
      break;
  }
  return true;
}

void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

void led_set_user(uint8_t usb_led) {

}

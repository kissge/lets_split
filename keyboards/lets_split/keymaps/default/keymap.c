#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 3
#define _RAISE 4
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  IME,
  NEXT,
  PREV,
  TCLOSE,
  REOPEN,
  FORWARD,
  BACK,
  WCLOSE,
  NEWTAB,
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QWERTY] = LAYOUT_ortho_4x12(
   KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, \
   KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT, \
   KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_QUOT , \
   KC_ESC,  KC_LGUI, KC_LALT, KC_MINS, LOWER,   KC_SPC,  IME,     RAISE,   KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS \
),

[_LOWER] = LAYOUT_ortho_4x12( \
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______, \
  _______, NEWTAB,  TCLOSE,  PREV,    NEXT,    WCLOSE,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6, \
  _______, REOPEN,  _______, KC_MUTE, KC_VOLD, KC_VOLU, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, \
  RESET,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

[_RAISE] = LAYOUT_ortho_4x12( \
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL, \
  _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, BACK,    FORWARD, \
  _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, KC_PSCR, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

[_ADJUST] =  LAYOUT_ortho_4x12( \
  _______, RESET,   _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ \
)


};

#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
#endif

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_qwerty);
        #endif
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case IME:
      if (record->event.pressed) {
        SEND_STRING(SS_LALT("`"));
      }
      return false;
    case NEXT:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTRL(SS_TAP(X_PGDOWN)));
      }
      return false;
    case PREV:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTRL(SS_TAP(X_PGUP)));
      }
      return false;
    case TCLOSE:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTRL("w"));
      }
      return false;
    case REOPEN:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTRL("T"));
      }
      return false;
    case FORWARD:
      if (record->event.pressed) {
        SEND_STRING(SS_LALT(SS_TAP(X_RIGHT)));
      }
      return false;
    case BACK:
      if (record->event.pressed) {
        SEND_STRING(SS_LALT(SS_TAP(X_LEFT)));
      }
      return false;
    case WCLOSE:
      if (record->event.pressed) {
        SEND_STRING(SS_LALT(SS_TAP(X_F4)));
      }
      return false;
    case NEWTAB:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTRL("t"));
      }
      return false;
  }
  return true;
}

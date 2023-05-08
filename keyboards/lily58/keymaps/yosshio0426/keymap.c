#include QMK_KEYBOARD_H
#include "keymap_japanese.h"

// mac日本語キーボードのunderscoreはJISキーボード的にはbackslash
#define MJ_UNDS JP_BSLS
// mac日本語キーボードでbackslashを入力するにはoption + yen
#define MJ_BSLS A(JP_YEN)

const key_override_t zero_pipe = ko_make_basic(MOD_MASK_SHIFT, JP_0, JP_PIPE);
const key_override_t underscore_backslash = ko_make_basic(MOD_MASK_SHIFT, MJ_UNDS, MJ_BSLS);

// This globally defines all key overrides to be used
const key_override_t **key_overrides = (const key_override_t *[]){
	&zero_pipe,
	&underscore_backslash,
	NULL // Null terminate the array of overrides!
};

enum layer_number {
  _DEFAULT = 0,
  _RAISE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* DEFAULT
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  ^   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  | 0(|) |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | ESC  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  @   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LCTRL |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  :   |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  | _(\) |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LOpt | 英数  |Space | / LClick/       \Enter \  | Tab  | かな  | TBD  |
 *                   |      | LCMD |      |/       /         \      \ |      |  Fn  |      |
 *                   `----------------------------'           '------''--------------------'
 */

 [_DEFAULT] = LAYOUT(
  JP_CIRC,  JP_1,   JP_2,    JP_3,    JP_4,    JP_5,                     JP_6,    JP_7,    JP_8,    JP_9,    JP_0,    JP_MINS,
  KC_ESC,   JP_Q,   JP_W,    JP_E,    JP_R,    JP_T,                     JP_Y,    JP_U,    JP_I,    JP_O,    JP_P,    JP_AT,
  KC_LCTL,  JP_A,   JP_S,    JP_D,    JP_F,    JP_G,                     JP_H,    JP_J,    JP_K,    JP_L,    JP_SCLN, JP_COLN,
  KC_LSFT,  JP_Z,   JP_X,    JP_C,    JP_V,    JP_B, JP_LBRC,  JP_RBRC,  JP_N,    JP_M,    JP_COMM, JP_DOT,  JP_SLSH, MJ_UNDS,
                 KC_LOPT, LCMD_T(KC_LNG2), KC_SPC, KC_BTN1,    KC_ENT, KC_TAB, LT(_RAISE, KC_LNG1), XXXXXXX
),

/* RAISE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | F12  |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  | F11  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      | WH ↑ | MS ↑ | WH ↓ |      |                    |      |      | Home |  ↑   | End  | PgUp |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      | MS ← | MS ↓ | MS → |      |-------.    ,-------|      |      |  ←   |  ↓   |  →   | PgDn |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      | Del  |-------|    |-------|      |      | Mute | Vol↓ | Vol↑ |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |  BS  | / RClick/       \      \  |      |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

 [_RAISE] = LAYOUT(
   KC_F12,    KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,                        KC_F6,    KC_F7,    KC_F8,    KC_F9,   KC_F10,   KC_F11,
  _______,  _______,  KC_WH_U,  KC_MS_U,  KC_WH_D,  _______,                      _______,  _______,  KC_HOME,    KC_UP,   KC_END,  KC_PGUP,
  _______,  _______,  KC_MS_L,  KC_MS_D,  KC_MS_R,  _______,                      _______,  _______,  KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_PGDN,
  _______,  _______,  _______,  _______,  _______,   KC_DEL,  _______,  _______,  _______,  _______,  KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,
                            _______, _______, KC_BSPC, KC_BTN2,                 _______, _______, _______, _______
),
};

//SSD1306 OLED update loop, make sure to enable OLED_ENABLE=yes in rules.mk
#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master())
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  return rotation;
}

// When you add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

bool oled_task_user(void) {
  if (is_keyboard_master()) {
    // If you want to change the display of OLED, you need to change here
    oled_write_ln(read_layer_state(), false);
    oled_write_ln(read_keylog(), false);
    oled_write_ln(read_keylogs(), false);
    //oled_write_ln(read_mode_icon(keymap_config.swap_lalt_lgui), false);
    //oled_write_ln(read_host_led_state(), false);
    //oled_write_ln(read_timelog(), false);
  } else {
    oled_write(read_logo(), false);
  }
    return false;
}
#endif // OLED_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef OLED_ENABLE
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }
  return true;
}

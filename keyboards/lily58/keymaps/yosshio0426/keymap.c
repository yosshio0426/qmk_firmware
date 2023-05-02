#include QMK_KEYBOARD_H
#include "keymap_japanese.h"

enum layer_number {
  _DEFAULT = 0,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* DEFAULT
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  ^   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | ESC  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  @   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LCTRL |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  :   |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |  _   |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LOpt | LCMD |Space | / LClick/       \Enter \  | Tab  |  Fn  | TBD  |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

 [_DEFAULT] = LAYOUT(
  JP_CIRC,  JP_1,   JP_2,    JP_3,    JP_4,    JP_5,                     JP_6,    JP_7,    JP_8,    JP_9,    JP_0,    JP_MINS,
  KC_ESC,   JP_Q,   JP_W,    JP_E,    JP_R,    JP_T,                     JP_Y,    JP_U,    JP_I,    JP_O,    JP_P,    JP_AT,
  KC_LCTL,  JP_A,   JP_S,    JP_D,    JP_F,    JP_G,                     JP_H,    JP_J,    JP_K,    JP_L,    JP_SCLN, JP_COLN,
  KC_LSFT,  JP_Z,   JP_X,    JP_C,    JP_V,    JP_B, JP_LBRC,  JP_RBRC,  JP_N,    JP_M,    JP_COMM, JP_DOT,  JP_SLSH, JP_BSLS,
                        KC_LOPT, KC_LCMD, KC_SPC, KC_BTN1,          KC_ENT, KC_TAB, XXXXXXX, XXXXXXX
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

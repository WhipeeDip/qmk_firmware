#include QMK_KEYBOARD_H

enum ctrl_keycodes {
    U_T_AGCR = SAFE_RANGE, //USB Toggle Automatic GCR control
    DBG_TOG,               //DEBUG Toggle On / Off
    DBG_MTRX,              //DEBUG Toggle Matrix Prints
    DBG_KBD,               //DEBUG Toggle Keyboard Prints
    DBG_MOU,               //DEBUG Toggle Mouse Prints
    MD_BOOT,               //Restart into bootloader after hold timeout

    // begin my keycodes
    GUI_LOCK
};

#define TG_NKRO MAGIC_TOGGLE_NKRO //Toggle 6KRO / NKRO mode

extern RGB led_buffer[];
bool guiLocked = false; // windows key lock

keymap_config_t keymap_config;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,             KC_PSCR, KC_SLCK, KC_PAUS, \
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,   KC_INS,  KC_HOME, KC_PGUP, \
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,   KC_DEL,  KC_END,  KC_PGDN, \
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT, \
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,                              KC_UP, \
        KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                             KC_RALT, MO(1),   KC_APP,  KC_RCTL,            KC_LEFT, KC_DOWN, KC_RGHT \
    ),
    [1] = LAYOUT(
        MD_BOOT, U_T_AGCR,TG_NKRO, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,            _______, _______, KC_MUTE, \
        RGB_RMOD,_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   KC_MPLY, KC_MSTP, KC_VOLU, \
        RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, _______, _______, _______, _______, _______, _______, _______, _______, _______,   KC_MPRV, KC_MNXT, KC_VOLD, \
        RGB_TOG, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                              _______, \
        _______, GUI_LOCK,_______,                   _______,                            _______, _______, _______, _______,            _______, _______, _______ \
    ),
    /*
    [X] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,            _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                              _______, \
        _______, _______, _______,                   _______,                            _______, _______, _______, _______,            _______, _______, _______ \
    ),
    */
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
    rgb_matrix_set_flags(LED_FLAG_NONE);
    rgb_matrix_set_color_all(0, 0, 0);
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
};

void rgb_matrix_indicators_user(void) {
    uint8_t led_off = rgb_matrix_get_flags() == LED_FLAG_NONE;

    // caps lock
    if (IS_HOST_LED_ON(USB_LED_CAPS_LOCK)) {
        led_buffer[50].r = 255 - led_buffer[50].r;
        led_buffer[50].g = 255 - led_buffer[50].g;
        led_buffer[50].b = 255 - led_buffer[50].b;

        // rgb_matrix_set_color(
        //     50,
        //     255 - led_buffer[50].r,
        //     255 - led_buffer[50].g,
        //     255 - led_buffer[50].b
        // );
    } else if (led_off) {
        led_buffer[50].r = 0;
        led_buffer[50].g = 0;
        led_buffer[50].b = 0;

        // rgb_matrix_set_color(
        //     50,
        //     0,
        //     0,
        //     0
        // );
    }

    // scroll lock
    if (IS_HOST_LED_ON(USB_LED_SCROLL_LOCK)) {
        led_buffer[14].r = 255 - led_buffer[14].r;
        led_buffer[14].g = 255 - led_buffer[14].g;
        led_buffer[14].b = 255 - led_buffer[14].b;
    } else if (led_off) {
        led_buffer[14].r = 0;
        led_buffer[14].g = 0;
        led_buffer[14].b = 0;
    }

    // left gui key
    if (guiLocked) {
        led_buffer[77].r = 255 - led_buffer[77].r;
        led_buffer[77].g = 255 - led_buffer[77].g;
        led_buffer[77].b = 255 - led_buffer[77].b;
    } else if (led_off) {
        led_buffer[77].r = 0;
        led_buffer[77].g = 0;
        led_buffer[77].b = 0;
    }
};

#define MODS_SHIFT  (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT))
#define MODS_CTRL  (get_mods() & MOD_BIT(KC_LCTL) || get_mods() & MOD_BIT(KC_RCTRL))
#define MODS_ALT  (get_mods() & MOD_BIT(KC_LALT) || get_mods() & MOD_BIT(KC_RALT))

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint32_t key_timer;

    switch (keycode) {
        case U_T_AGCR:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_gcr_auto, "USB GCR auto mode");
            }
            return false;
        case DBG_TOG:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_enable, "Debug mode");
            }
            return false;
        case DBG_MTRX:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_matrix, "Debug matrix");
            }
            return false;
        case DBG_KBD:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_keyboard, "Debug keyboard");
            }
            return false;
        case DBG_MOU:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_mouse, "Debug mouse");
            }
            return false;
        case MD_BOOT:
            if (record->event.pressed) {
                key_timer = timer_read32();
            } else {
                if (timer_elapsed32(key_timer) >= BOOTKEY_HOLD_MS) {
                    reset_keyboard();
                }
            }
            return false;
        case RGB_TOG:
            if (record->event.pressed) {
              switch (rgb_matrix_get_flags()) {
                case LED_FLAG_ALL: {
                    rgb_matrix_set_flags(LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER);
                    rgb_matrix_set_color_all(0, 0, 0);
                  }
                  break;
                case LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER: {
                    rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
                    rgb_matrix_set_color_all(0, 0, 0);
                  }
                  break;
                case LED_FLAG_UNDERGLOW: {
                    rgb_matrix_set_flags(LED_FLAG_NONE);
                    rgb_matrix_disable_noeeprom();
                  }
                  break;
                default: {
                    rgb_matrix_set_flags(LED_FLAG_ALL);
                    rgb_matrix_enable_noeeprom();
                  }
                  break;
              }
            }
            return false;
        case GUI_LOCK:
            if (record->event.pressed) {
                guiLocked = !guiLocked;
            }
            return false;
        case KC_LGUI:
            if (record->event.pressed) {
                return !guiLocked;
            }
            return true;
        default:
            return true; //Process all other keycodes normally
    }
}

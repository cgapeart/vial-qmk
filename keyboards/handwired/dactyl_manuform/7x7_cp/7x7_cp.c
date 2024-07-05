// Copyright 2022 Matthew Dews (@matthew-dews)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "7x7_cp.h"

void keyboard_post_init_kb(void) {
    debug_enable   = true;
    debug_matrix   = true;
    debug_keyboard = true;
    debug_mouse    = true;

    keyboard_post_init_user();
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) {
         return OLED_ROTATION_180; // flips the display 180 degrees if offhand
    }
    return rotation;
}

// static void render_logo(void) {
//     static const char PROGMEM qmk_logo[] = {0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94, 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00};
//     oled_write_P(qmk_logo, false);
// }

bool render_status(void) {
    static char wpmBuffer[10] = {0};
    // Host Keyboard Layer Status

    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);

    oled_write_P(PSTR("WPM "), false);
    sprintf(wpmBuffer, "%d", get_current_wpm());
    oled_write(wpmBuffer, false);

    if(is_keyboard_left())
    {
        oled_write_P(PSTR("\nLEFT"), false);
    }
    else
    {
         oled_write_P(PSTR("\nRIGHT"), false);
    }
    return false;
}

bool oled_task_user(void) {

    render_status(); // Renders the current keyboard state (layer, lock, caps, scroll, etc)

    return false;
}

void oled_render_boot(bool bootloader) {
    oled_clear();
    for (int i = 0; i < 16; i++) {
        oled_set_cursor(0, i);
        if (bootloader) {
            oled_write_P(PSTR("Awaiting New Firmware "), false);
        } else {
            oled_write_P(PSTR("Rebooting "), false);
        }
    }

    oled_render_dirty(true);
}

bool shutdown_user(bool jump_to_bootloader) {
    oled_render_boot(jump_to_bootloader);
    return false;
}
typedef struct _joy_master_to_slave_t {
    int req;
} master_to_slave_t;

typedef struct _joy_slave_to_master_t {
    int16_t x;
    int16_t y;
    bool    b;
} slave_to_master_t;

joystick_config_t joystick_axes[JOYSTICK_AXIS_COUNT] = {JOYSTICK_AXIS_VIRTUAL, JOYSTICK_AXIS_VIRTUAL, JOYSTICK_AXIS_VIRTUAL, JOYSTICK_AXIS_VIRTUAL};

void joystick_axis_init(uint8_t axis) {
    if (axis >= JOYSTICK_AXIS_COUNT) return;

    // Both sides have to init their inputs., same pins on both side.
    gpio_set_pin_input(JS_X_PIN);
    gpio_set_pin_input(JS_Y_PIN);
    gpio_set_pin_input_low(JS_B_PIN);
}

void joystick_sync_slave_handler(uint8_t in_buflen, const void *in_data, uint8_t out_buflen, void *out_data) {
    slave_to_master_t       *s2m = (slave_to_master_t *)out_data;
    s2m->x = analogReadPin(JS_X_PIN);
    s2m->y = analogReadPin(JS_Y_PIN);
    s2m->b = gpio_read_pin(JS_B_PIN);
}

void keyboard_post_init_user(void) {
    transaction_register_rpc(JOYSTICK_SYNC, joystick_sync_slave_handler);
}


long map(long x, long in_min, long in_max, long out_min, long out_max) {
	  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void housekeeping_task_user(void) {
    static uint32_t last_sync = 0;
    static uint32_t last_debug_msg = 0;
    if (is_keyboard_master()) {

	    int16_t mx = 0, my= 0, mmx= 0, mmy= 0;
        int16_t sx= 0,sy= 0, smx= 0, smy= 0;
        bool mb= 0, sb= 0;

        if (timer_elapsed32(last_sync) > SPLIT_JS_SAMPLE_MS) {

            mx = analogReadPin(JS_X_PIN);
            my = analogReadPin(JS_Y_PIN);
            mb = gpio_read_pin(JS_B_PIN);

	        mmx= map(mx, JSCAL_M_X, -128,127);
	        mmy= map(my, JSCAL_M_Y, -128,127);


            joystick_set_axis(0,mmx);
            joystick_set_axis(1,mmy);

            if (mb) {
                register_joystick_button(0);
            } else {
                unregister_joystick_button(0);
            }


            master_to_slave_t m2s = {0};
            slave_to_master_t s2m = {0, 0, 0};
            if (transaction_rpc_exec(JOYSTICK_SYNC, sizeof(master_to_slave_t), &m2s, sizeof(s2m), &s2m))
            {
                IGNORE_UNSUSED(m2s); //  unused
                sx = s2m.x;
                sy = s2m.y;
                sb = s2m.b;
                smx= map(sx, JSCAL_S_X, JSCAL_OUT);
		        smy= map(sy, JSCAL_S_Y, JSCAL_OUT);
                joystick_set_axis(2, smx);
                joystick_set_axis(3, smy);

                if (sb) {
                    register_joystick_button(1);
                } else {
                    unregister_joystick_button(1);
                }
            }

            if (timer_elapsed32(last_debug_msg) > (SPLIT_JS_SAMPLE_MS * 10)) {
                dprintf("M%c%hd,%hd -> %hd,%hd, S%c%hd,%hd -> %hd,%hd\n", mb?'1':'0', mx, my, mmx, mmy, sb?'1':'0', sx, sy, smx, sy);
            }
        }
    }
}

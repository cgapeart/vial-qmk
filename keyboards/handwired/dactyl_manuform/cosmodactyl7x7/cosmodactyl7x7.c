// Copyright 2022 Matthew Dews (@matthew-dews)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "cosmodactyl7x7.h"
#include "split_util.h"
#include <print.h>
bool isOledGood = false;
int16_t sjsx = 0, sjsy = 0;
bool sjsb = 0;
#define LED_FLAG_LYR_1 0x10
#define LED_FLAG_LYR_2 0x20

// LED mappings
led_config_t g_led_config =
{
    {// Key Matrix Postion to LED index
        {0, 5, 10, 15, 21, 27, 32},
        {1, 6, 11, 16, 22, 28, 33},
        {2, 7, 12, 17, 23, 29, 34},
        {3, 8, 13, 18, 24, 30, 35},
        {4, 9, 14, 19, 25, 31, 36},
        {NO_LED, NO_LED, NO_LED, 20, 26, NO_LED, NO_LED},
        {37, 38, 39, 40, 41, 42, NO_LED},
        {43, 48, 53, 58, 64, 70, 75},
        {44, 49, 54, 59, 65, 71, 76},
        {45, 50, 55, 60, 66, 72, 77},
        {46, 51, 56, 61, 67, 73, 78},
        {47, 52, 57, 62, 68, 74, 79},
        {NO_LED, NO_LED, NO_LED, 63, 69, NO_LED, NO_LED},
        {80, 81, 82, 83, 84, 85, NO_LED}
    },
    {// LED Index to physical position
       {0, 2}, {0, 9}, {1, 17}, {1, 25}, {1, 33},
        {11, 1}, {12, 9}, {12, 17}, {13, 25}, {13, 33},
        {22, 1}, {23, 8}, {24, 16}, {24, 25}, {24, 33},
        {34, 1}, {35, 8}, {36, 16}, {36, 25}, {36, 33},
        {36, 41}, {46, 0}, {47, 7}, {47, 15}, {48, 23},
        {48, 32}, {48, 40}, {57, 1}, {57, 8}, {58, 16},
        {58, 25}, {58, 33}, {68, 1}, {68, 9}, {69, 17},
        {69, 25}, {69, 33}, {64, 47}, {73, 57}, {76, 64},
        {77, 47}, {85, 55}, {88, 61}, {224, 2}, {223, 9},
        {222, 17}, {222, 25}, {222, 33}, {212, 1}, {211, 9},
        {211, 17}, {210, 25}, {210, 33}, {201, 1}, {200, 8},
        {199, 16}, {199, 25}, {199, 33}, {188, 1}, {188, 8},
        {187, 16}, {187, 25}, {187, 33}, {187, 41}, {177, 0},
        {176, 7}, {176, 15}, {175, 23}, {175, 32}, {175, 40},
        {166, 1}, {166, 8}, {165, 16}, {165, 25}, {165, 33},
        {155, 1}, {155, 9}, {154, 17}, {154, 25}, {154, 33},
        {159, 47}, {150, 57}, {147, 64}, {146, 47}, {138, 55}, {135, 61}
    },
    {// key flags
        LED_FLAG_KEYLIGHT | LED_FLAG_LYR_1| LED_FLAG_LYR_2,
        LED_FLAG_KEYLIGHT | LED_FLAG_LYR_2,
        LED_FLAG_KEYLIGHT | LED_FLAG_LYR_1,
        LED_FLAG_KEYLIGHT | LED_FLAG_LYR_1,
        LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER,
        LED_FLAG_KEYLIGHT | LED_FLAG_LYR_1| LED_FLAG_LYR_2,
        LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT | LED_FLAG_LYR_1,
        LED_FLAG_KEYLIGHT | LED_FLAG_LYR_1,
        LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER,
        LED_FLAG_KEYLIGHT | LED_FLAG_LYR_1| LED_FLAG_LYR_2,
        LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT | LED_FLAG_LYR_1,
        LED_FLAG_KEYLIGHT | LED_FLAG_LYR_1,
        LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT | LED_FLAG_LYR_1| LED_FLAG_LYR_2,
        LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT | LED_FLAG_LYR_1,
        LED_FLAG_KEYLIGHT | LED_FLAG_LYR_1,
        LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT| LED_FLAG_LYR_2,
        LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT | LED_FLAG_LYR_1,
        LED_FLAG_KEYLIGHT | LED_FLAG_LYR_1,
        LED_FLAG_KEYLIGHT| LED_FLAG_MODIFIER,
        LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT| LED_FLAG_LYR_2,
        LED_FLAG_KEYLIGHT | LED_FLAG_LYR_1,
        LED_FLAG_KEYLIGHT | LED_FLAG_LYR_1,
        LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT| LED_FLAG_LYR_2,
        LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT| LED_FLAG_MODIFIER,
        LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER,
        LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT | LED_FLAG_LYR_1 | LED_FLAG_MODIFIER,
        LED_FLAG_KEYLIGHT| LED_FLAG_LYR_2,
        LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT |LED_FLAG_LYR_1,
        LED_FLAG_KEYLIGHT |LED_FLAG_LYR_1,
        LED_FLAG_KEYLIGHT| LED_FLAG_LYR_2,
        LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT | LED_FLAG_LYR_1,
        LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT| LED_FLAG_LYR_2,
        LED_FLAG_KEYLIGHT | LED_FLAG_LYR_1,
        LED_FLAG_KEYLIGHT | LED_FLAG_LYR_1,
        LED_FLAG_KEYLIGHT | LED_FLAG_LYR_1,
        LED_FLAG_KEYLIGHT | LED_FLAG_LYR_1,
        LED_FLAG_KEYLIGHT| LED_FLAG_LYR_2,
        LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT | LED_FLAG_LYR_1,
        LED_FLAG_KEYLIGHT | LED_FLAG_LYR_1,
        LED_FLAG_KEYLIGHT | LED_FLAG_LYR_1,
        LED_FLAG_KEYLIGHT | LED_FLAG_LYR_1,
        LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT| LED_FLAG_LYR_2,
        LED_FLAG_KEYLIGHT | LED_FLAG_LYR_1,
        LED_FLAG_KEYLIGHT | LED_FLAG_LYR_1 | LED_FLAG_LYR_2,
        LED_FLAG_KEYLIGHT | LED_FLAG_LYR_1,
        LED_FLAG_KEYLIGHT | LED_FLAG_LYR_1,
        LED_FLAG_KEYLIGHT| LED_FLAG_LYR_2,
        LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT| LED_FLAG_MODIFIER,
        LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT| LED_FLAG_MODIFIER,
        LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER
    }
};

typedef union {
    uint8_t raw[EECONFIG_USER_DATA_SIZE];
    struct {
        int16_t x_offset_left;
        int16_t y_offset_left;
        int16_t x_offset_right;
        int16_t y_offset_right;
    };
} user_config_t;
user_config_t user_config;

enum customKeyCodes
{
    U_CENTER_STICKS = SAFE_RANGE
};
bool centerSticksTrigger = false;

void keyboard_post_init_kb(void)
{
    debug_enable   = false;
    debug_matrix   = false;
    debug_keyboard = false;
    debug_mouse    = false;

    keyboard_post_init_user();
}

oled_rotation_t oled_init_kb(oled_rotation_t rotation)
{
    return OLED_ROTATION_0;
}

static void oled_render_logo(void)
{
    static const char PROGMEM qmk_logo[] = {0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94, 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00};
    oled_write_P(qmk_logo, false);
}

bool render_status(void)
{
    static char buffer[64] = {0};

    // Host Keyboard Layer Status

    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);

    oled_write_P(PSTR("WPM "), false);
    sprintf(buffer, "%d", get_current_wpm());
    oled_write(buffer, false);

    if (is_keyboard_master())
    {
        uint8_t button0 =   (joystick_state.buttons[0] & 1) ;
        uint8_t button1 = (joystick_state.buttons[0] & 2) >> 1;
        sprintf(buffer, "\n%c %5d,%5d,%1hd\n  %5d,%5d,%1hd",
            is_transport_connected()? '+':'-',
            joystick_state.axes[0],joystick_state.axes[1],button0,
            joystick_state.axes[2],joystick_state.axes[3],button1);
    }
    else
    {
        uint8_t currentMode = rgb_matrix_get_mode();
        uint8_t currentSat = rgb_matrix_get_sat();
        uint8_t currentHue = rgb_matrix_get_hue();
        uint8_t currentVal = rgb_matrix_get_val();
        uint8_t currentSpd = rgb_matrix_get_speed();

        sprintf(buffer, "\nL:%hd, M:%3hd, S:%3hd\nH:%3hd, S:%3hd, V:%3hd",
             get_highest_layer(layer_state), currentMode, currentSpd,
            currentHue, currentSat, currentVal);
    }

    oled_write_P(buffer, false);

    return false;
}

bool oled_task_kb(void)
{
    if (!oled_task_user())
    {
        return false;
    }
    oled_render_logo();
    return true;
}

bool oled_task_user(void)
{
    render_status(); // Renders the current keyboard state (layer, lock, caps, scroll, etc)

    return false;
}

void oled_render_boot(bool bootloader)
{
    oled_clear();
    oled_render_logo();
    for (int i = 0; i < 16; i++)
    {
        oled_set_cursor(0, i);
        if (bootloader)
        {
            oled_write_P(PSTR("Awaiting New Firmware "), false);
            printf("Awaiting New Firmware\n ");
        }
        else
        {
            oled_write_P(PSTR("Rebooting "), false);
            printf("rebooting\n ");
        }
    }
    printf("OLED-BOOT\n");
    oled_render_dirty(true);
}

bool shutdown_user(bool jump_to_bootloader)
{
    oled_render_boot(jump_to_bootloader);
    return false;
}
typedef struct _joy_master_to_slave_t
{
    int16_t req;
} master_to_slave_t;

typedef struct _joy_slave_to_master_t
{
    int16_t x;
    int16_t y;
    bool    b;
    int16_t reqEcho;
} slave_to_master_t;

joystick_config_t joystick_axes[JOYSTICK_AXIS_COUNT] = {JOYSTICK_AXIS_VIRTUAL, JOYSTICK_AXIS_VIRTUAL, JOYSTICK_AXIS_VIRTUAL, JOYSTICK_AXIS_VIRTUAL};

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
    if(record->event.pressed)
    {
        switch(keycode)
        {
            case U_CENTER_STICKS:
            // Offset the stick positions to treat them as centered on next joystick read., save to EEPROM
                centerSticksTrigger = true;
                return false;
        }
    }

    return true; // Let the keyboard process the record
}
void joystick_sync_slave_handler(uint8_t in_buflen, const void *in_data, uint8_t out_buflen, void *out_data)
{
    master_to_slave_t *m2s = (master_to_slave_t *)in_data;
    slave_to_master_t *s2m = (slave_to_master_t *)out_data;
    s2m->x                 = sjsx = analogReadPin(JS_X_PIN);
    s2m->y                 = sjsy = analogReadPin(JS_Y_PIN);
    s2m->b                 = sjsb = !gpio_read_pin(JS_B_PIN);
    s2m->reqEcho = m2s->req;
}

void keyboard_post_init_user(void)
{
    // Both sides have to init their inputs., same pins on both side.
    gpio_set_pin_input(JS_X_PIN);
    gpio_set_pin_input(JS_Y_PIN);
    gpio_set_pin_input_high(JS_B_PIN);

    printf("joystick input initialized\n");
    transaction_register_rpc(JOYSTICK_SYNC, joystick_sync_slave_handler);

    eeconfig_read_user_datablock(user_config.raw,0,EECONFIG_USER_DATA_SIZE);
}

void eeconfig_init_user()
{
    user_config.x_offset_left = 0;
    user_config.y_offset_left = 0;
    user_config.x_offset_right = 0;
    user_config.y_offset_right = 0;
    eeconfig_update_user_datablock(user_config.raw,0, EECONFIG_USER_DATA_SIZE);
}

long map(long x, long in_min, long in_max, long out_min, long out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}



void housekeeping_task_user(void) {
    if (!isOledGood) {
        isOledGood = oled_init(oled_init_kb(OLED_ROTATION_0));
    }
    static uint32_t last_sync       = 0;
    static int16_t req = 0;


    if (is_keyboard_master())
    {
        int16_t mx = 0, my = 0;
        int16_t sx = 0, sy = 0;
        bool    mb = 0, sb = 0;

        if (timer_elapsed32(last_sync) > SPLIT_JS_SAMPLE_MS)
        {
            last_sync = timer_read32();

            mx = map(analogReadPin(JS_X_PIN),0,1024,-512,512);
            my = map(analogReadPin(JS_Y_PIN),0,1024,512,-512);
            mb = !gpio_read_pin(JS_B_PIN);

            if(centerSticksTrigger)
            {
                user_config.x_offset_left = mx;
                user_config.y_offset_left = my;
            }

            joystick_set_axis(0, mx-user_config.x_offset_left);
            joystick_set_axis(1, my-user_config.y_offset_left);

            if (mb)
            {
                register_joystick_button(0);
            }
            else
            {
                unregister_joystick_button(0);
            }

            master_to_slave_t m2s = {++req};
            slave_to_master_t s2m = {0, 0, 0, 0};
            if (transaction_rpc_exec(JOYSTICK_SYNC, sizeof(master_to_slave_t), &m2s, sizeof(slave_to_master_t), &s2m))
            {
                sx = map(s2m.x,0,1024,512,-512);
                sy = map(s2m.y,0,1024,-512,512);
                sb = s2m.b;

                if(centerSticksTrigger)
                {
                    user_config.x_offset_right = sx;
                    user_config.y_offset_right = sy;
                }

                joystick_set_axis(2, sx - user_config.x_offset_right);
                joystick_set_axis(3, sy - user_config.y_offset_right);

                if (sb)
                {
                    register_joystick_button(1);
                }
                else
                {
                    unregister_joystick_button(1);
                }

            }
            else
            {
                dprintf("Remote RPC failed\n");
            }

            if(centerSticksTrigger)
            {
                centerSticksTrigger = false;
                eeconfig_update_user_datablock(user_config.raw,0,EECONFIG_USER_DATA_SIZE);
            }
        }
    }
}

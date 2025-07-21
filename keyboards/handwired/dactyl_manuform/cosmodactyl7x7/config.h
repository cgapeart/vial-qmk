//Copyright 2012 Colin Peart

/*
        TX      GP0    USB     VBUS
        RX      GP1    RST     VSYS
                GND            GND
        SDA     GP2            3V3_EN
        SCL     GP3            3V3
shifted NEO     GP4            ADC_VREF
        JSB     GP5            GP28
                GND            GND     JSGND
                GP6            GP27    JSX
                GP7            GP26    JSY
                GP8            RUN
        C0      GP9            GP22    R0
                GND            GND
        C1      GP10           GP21    R1
        C2      GP11           GP20    R2
        C3      GP12           GP19    R3
        C4      GP13           GP18    R4
                GND            GND
        C5      GP14           GP17    R5
        C6      GP15    SWD    GP16    R6

*/

#pragma once
//RP2040 hardware
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP25
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 200U

#define I2C_DRIVER I2CD1
#define I2C1_SCL_PIN GP3
#define I2C1_SDA_PIN GP2
#define OLED_DISPLAY_128X32
#define OLED_DRIVER ssd1306
#define OLED_TRANSPORT i2c

#define WPM_LAUNCH_CONTROL
#define OLED_TIMEOUT 20000
#define OLED_SCROLL_TIMEOUT 0
#define OLED_UPDATE_INTERVAL 50
#define OLED_FADE_OUT
#define OLED_FADE_OUT_INTERVAL 15

#define SERIAL_USART_FULL_DUPLEX
#define SERIAL_USART_RX_PIN GP0
#define SERIAL_USART_TX_PIN GP1


#define MASTER_LEFT

#define WS2812_PIO_USE_PIO1

#define JOYSTICK_BUTTON_COUNT 2
#define JOYSTICK_AXIS_COUNT 4
#define JOYSTICK_AXIS_RESOLUTION 10

#define SPLIT_TRANSACTION_IDS_USER JOYSTICK_SYNC
#define JS_X_PIN GP27
#define JS_Y_PIN GP26
#define JS_B_PIN GP5
#define SPLIT_JS_SAMPLE_MS 50
#define SPLIT_MAX_CONNECTION_ERRORS 10
#define SPLIT_CONNECTION_CHECK_TIMEOUT 500

#define EECONFIG_USER_DATA_SIZE 16


# Build Options
#   change yes to no to disable
#
SERIAL_DRIVER = vendor
JOYSTICK_ENABLE = yes
JOYSTICK_DRIVER = analog
OLED_DRIVER = ssd1306
OPT_DEFS += -DHAL_USE_I2C=TRUE

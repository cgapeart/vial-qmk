/* SPDX-License-Identifier: GPL-2.0-or-later */

#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "color.h"

#if defined(VIALRGB_ENABLE) && defined(VIALRGB_SPLIT_SYNC) && defined(RGB_MATRIX_SPLIT) && !defined(VIALRGB_NO_DIRECT)

#    ifndef VIALRGB_SPLIT_SYNC_MS
#        define VIALRGB_SPLIT_SYNC_MS 16
#    endif

#    ifndef VIALRGB_SPLIT_SYNC_MAX_LEDS
#        define VIALRGB_SPLIT_SYNC_MAX_LEDS (((RGB_MATRIX_LED_COUNT) + 1) / 2)
#    endif

typedef struct {
    uint8_t start;
    uint8_t count;
    HSV     colors[VIALRGB_SPLIT_SYNC_MAX_LEDS];
} vialrgb_direct_sync_t;

bool vialrgb_split_should_sync(void);
void vialrgb_split_prepare_direct(vialrgb_direct_sync_t *sync);
void vialrgb_split_apply_direct(const vialrgb_direct_sync_t *sync);

__attribute__((weak)) void vialrgb_split_sync_slave_kb(uint8_t start, uint8_t count);

#endif

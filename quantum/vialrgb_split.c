/* SPDX-License-Identifier: GPL-2.0-or-later */

#include "vialrgb_split.h"

#if defined(VIALRGB_ENABLE) && defined(VIALRGB_SPLIT_SYNC) && defined(RGB_MATRIX_SPLIT) && !defined(VIALRGB_NO_DIRECT)

#    include "debug.h"
#    include "rgb_matrix.h"
#    include "split_util.h"
#    include "sync_timer.h"
#    include "vialrgb.h"
#    include <string.h>

extern const uint8_t k_rgb_matrix_split[2];

#    ifdef RGB_MATRIX_EFFECT_VIALRGB_DIRECT
extern HSV g_direct_mode_colors[RGB_MATRIX_LED_COUNT];
#    endif

__attribute__((weak)) void vialrgb_split_sync_slave_kb(uint8_t start, uint8_t count) {
    (void)start;
    (void)count;
}

bool vialrgb_split_should_sync(void) {
#    ifdef RGB_MATRIX_EFFECT_VIALRGB_DIRECT
    return rgb_matrix_get_mode() == RGB_MATRIX_VIALRGB_DIRECT;
#    else
    return false;
#    endif
}

void vialrgb_split_prepare_direct(vialrgb_direct_sync_t *sync) {
#    ifdef RGB_MATRIX_EFFECT_VIALRGB_DIRECT
    if (is_keyboard_left()) {
        sync->start = k_rgb_matrix_split[0];
        sync->count = RGB_MATRIX_LED_COUNT - k_rgb_matrix_split[0];
    } else {
        sync->start = 0;
        sync->count = k_rgb_matrix_split[0];
    }

    if ((uint16_t)(sync->start + sync->count) > RGB_MATRIX_LED_COUNT) {
        sync->count = 0;
        return;
    }

    memcpy(sync->colors, &g_direct_mode_colors[sync->start], sync->count * sizeof(HSV));
#    else
    sync->start = 0;
    sync->count = 0;
#    endif
}

void vialrgb_split_apply_direct(const vialrgb_direct_sync_t *sync) {
#    ifdef RGB_MATRIX_EFFECT_VIALRGB_DIRECT
    if (sync->count == 0) {
        return;
    }
    if ((uint16_t)(sync->start + sync->count) > RGB_MATRIX_LED_COUNT) {
        dprintf("VialRGB split sync: bad packet start=%u count=%u\n", sync->start, sync->count);
        return;
    }

    memcpy(&g_direct_mode_colors[sync->start], sync->colors, sync->count * sizeof(HSV));
    vialrgb_split_sync_slave_kb(sync->start, sync->count);
    dprintf("VialRGB split sync rx: start=%u count=%u\n", sync->start, sync->count);
#    endif
}

#endif

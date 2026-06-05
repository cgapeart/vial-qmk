// Copyright 2022 Matthew Dews (@matthew-dews)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include <stdint.h>
#include <analog.h>
#include <transactions.h>
#include <gpio.h>
#include <debug.h>
#define IGNORE_UNSUSED(x) (void)x

void vialrgb_direct_fastset_kb(uint16_t first_index, uint8_t num_leds);
void vialrgb_split_sync_slave_kb(uint8_t start, uint8_t count);


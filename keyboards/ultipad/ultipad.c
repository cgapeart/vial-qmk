/* Copyright 2019 Chip
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "ultipad.h"


void keyboard_pre_init_kb(void) {
  // Set the layer LED IO as outputs
  setPinOutput(LAYER_INDICATOR_LED_0);
  setPinOutput(LAYER_INDICATOR_LED_1);
  setPinOutput(LED_NUM_LOCK_PIN);
  keyboard_pre_init_user();
}


layer_state_t layer_state_set_kb(layer_state_t state)
{

	switch(get_highest_layer(state))
	{
		case 0:
			writePin(LAYER_INDICATOR_LED_0,0);
			writePin(LAYER_INDICATOR_LED_1,0);
			break;
		case 1:
			writePin(LAYER_INDICATOR_LED_0,1);
			writePin(LAYER_INDICATOR_LED_1,0);
			break;
		case 2:
			writePin(LAYER_INDICATOR_LED_0,0);
			writePin(LAYER_INDICATOR_LED_1,1);
			break;
	}

	return state;
}


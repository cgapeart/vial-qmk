
#include "6x6_macropad.h"

layer_state_t layer_state_set_kb(layer_state_t state)
{
    switch(get_highest_layer(state))
    {
        case 0:
            rgb_matrix_set_color(43,200,0,200);
            rgb_matrix_set_color(42,0,0,0);
            rgb_matrix_set_color(41,0,0,0);
            rgb_matrix_set_color(40,0,0,0);
            break;
        case 1:
            rgb_matrix_set_color(43,0,0,0);
            rgb_matrix_set_color(42,200,0,200);
            rgb_matrix_set_color(41,0,0,0);
            rgb_matrix_set_color(40,0,0,0);
            break;
        case 2:
            rgb_matrix_set_color(43,0,0,0);
            rgb_matrix_set_color(42,0,0,0);
            rgb_matrix_set_color(41,200,0,200);
            rgb_matrix_set_color(40,0,0,0);
            break;
        case 3:
            rgb_matrix_set_color(43,0,0,0);
            rgb_matrix_set_color(42,0,0,0);
            rgb_matrix_set_color(41,0,0,0);
            rgb_matrix_set_color(40,200,0,200);
            break;
    }

    return state;
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if(res) {

        rgb_matrix_set_color(39,led_state.num_lock?128:0,0,0);
        rgb_matrix_set_color(38,0,led_state.caps_lock?128:0,0);
        rgb_matrix_set_color(37,0,0,led_state.scroll_lock?128:0);
       // rgb_matrix_set_color(36,0,0,0);
    }
    return res;
}

void matrix_init_user()
{
    //set the default layer marker.
    rgb_matrix_set_color(43,200,0,200);
    rgb_matrix_set_color(42,0,0,0);
    rgb_matrix_set_color(41,0,0,0);
    rgb_matrix_set_color(40,0,0,0);
}

#include <gbdk/platform.h>
#include "warning.h"
#include "utils.h"
#include "arrow.h"
#include "../res/warning_sprite.h"

void init_warning_graphics(void) {
    set_sprite_data(29, 1, warning_sprite);
}

void reset_warning(void) {
    hide_warning();
}

void spawn_warning(arrow_t *arrow) {
    set_sprite_tile(WARNING_SPRITE, 29);
    if (arrow->is_moving_right) {
        move_sprite(WARNING_SPRITE, LEFT_WARNING_X_LOCATION, WARNING_Y_LOCATION);
    }
    else {
        move_sprite(WARNING_SPRITE, RIGHT_WARNING_X_LOCATION, WARNING_Y_LOCATION);
    }
}

void hide_warning(void) {
    set_sprite_tile(WARNING_SPRITE, 18);
} 

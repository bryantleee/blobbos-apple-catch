#include <gbdk/platform.h>

#include "../res/arrow_sprite.h"
#include "arrow.h"

void init_arrow() {
	set_sprite_data(25, 4, arrow_sprite);
	set_sprite_tile(ARROW_SPRITE_L, 27);
	set_sprite_tile(ARROW_SPRITE_R, 28);
}

void spawn_arrow(struct arrow_t *arrow) {
	arrow->is_moving_right = !arrow->is_moving_right;
	if(arrow->is_moving_right) {
		set_sprite_prop(ARROW_SPRITE_L, 32);
		set_sprite_prop(ARROW_SPRITE_R, 32);
	}
	else {
		set_sprite_prop(ARROW_SPRITE_L, 0);
		set_sprite_prop(ARROW_SPRITE_R, 0);
	}
	move_sprite(ARROW_SPRITE_L, 20, 20);
	move_sprite(ARROW_SPRITE_R, 28, 20);
}

// void set_arrow_sprite_location(struct arrow_t *arrow, uint8_t WALL) {
// 	move_sprite(ARROW_SPRITE_L, x, y);
// 	move_sprite(ARROW_SPRITE_R, x1, y);

// 	if(arrow->x == WALL) {
// 		hide_sprite(ARROW_SPRITE_L);
// 		hide_sprite(ARROW_SPRITE_R);
// 	}
// }

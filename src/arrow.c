#include <gbdk/platform.h>
#include <rand.h>
#include <stdbool.h>

#include "../res/arrow_sprite.h"
#include "arrow.h"
#include "init.h"
#include "utils.h"

void init_arrow() {
	set_sprite_data(25, 4, arrow_sprite);
}

void spawn_arrow(struct arrow_t *arrow) {
	arrow->is_moving_right = rand() & 2;
	arrow->y = ARROW_DEFAULT_Y;
	arrow->is_active = TRUE;

	if(arrow->is_moving_right) {
		set_sprite_tile(ARROW_SPRITE_L, 28);
		set_sprite_tile(ARROW_SPRITE_R, 27);
		set_sprite_prop(ARROW_SPRITE_L, 32);
		set_sprite_prop(ARROW_SPRITE_R, 32);
		arrow->x = LEFT_WALL + 1;
	}
	else {
		set_sprite_tile(ARROW_SPRITE_L, 27);
		set_sprite_tile(ARROW_SPRITE_R, 28);
		set_sprite_prop(ARROW_SPRITE_L, 0);
		set_sprite_prop(ARROW_SPRITE_R, 0);		
		arrow->x = RIGHT_WALL - 1;

	}	
	set_arrow_sprite_location(arrow->x, arrow->y);
}

void update_arrow_location(struct arrow_t *arrow) {
	if(arrow->is_active) {
		arrow->x = arrow->is_moving_right ? arrow->x + ARROW_SPEED : arrow->x - ARROW_SPEED;
		if((arrow->is_moving_right && arrow->x >= RIGHT_WALL) ||
			(!(arrow->is_moving_right) && arrow->x <= LEFT_WALL)) {
			arrow->is_active = FALSE;
			hide_arrow();
		}
		else {
			set_arrow_sprite_location(arrow->x, arrow->y);
		}
	}
}

void set_arrow_sprite_location(uint16_t x, uint16_t y) {
	uint16_t x1 = x + 8;
	move_sprite(ARROW_SPRITE_L, x, y);
	move_sprite(ARROW_SPRITE_R, x1, y);
}

void hide_arrow() {
	set_sprite_tile(ARROW_SPRITE_L, 18);
	set_sprite_tile(ARROW_SPRITE_R, 18);
} 

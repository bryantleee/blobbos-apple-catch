#include <gbdk/platform.h>
#include <rand.h>
#include <stdbool.h>

#include "../res/arrow_sprite.h"
#include "arrow.h"
#include "basket.h"
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
		set_sprite_prop(ARROW_SPRITE_L, SPRITE_MIRROR_RIGHT);
		set_sprite_prop(ARROW_SPRITE_R, SPRITE_MIRROR_RIGHT);
		arrow->x = LEFT_WALL + 1;
	}
	else {
		set_sprite_tile(ARROW_SPRITE_L, 27);
		set_sprite_tile(ARROW_SPRITE_R, 28);
		set_sprite_prop(ARROW_SPRITE_L, SPRITE_MIRROR_LEFT);
		set_sprite_prop(ARROW_SPRITE_R, SPRITE_MIRROR_LEFT);		
		arrow->x = RIGHT_WALL - 1;

	}	
	set_arrow_sprite_location(arrow->x, arrow->y); //TODO change name to tile_locations or something better
}

void update_arrow_location(struct arrow_t *arrow, struct basket_t *basket) {
	if(arrow->is_active) {

		// adjust arrow collision check depending on the direction arrow is moving due to mirroing 
		uint16_t arrow_collision_x;
		if(arrow->is_moving_right) {
			arrow->x += ARROW_SPEED;
			arrow_collision_x = arrow->x;
		}
		else {
			arrow->x -= ARROW_SPEED;
			arrow_collision_x = arrow->x - 8;
		}
		
		if((arrow->is_moving_right && arrow_collision_x >= RIGHT_WALL) ||
			(!(arrow->is_moving_right) && arrow_collision_x <= LEFT_WALL)
			|| is_colliding(arrow_collision_x, arrow->y, 16, 8, basket->x, basket->y, 8, 16)) {
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

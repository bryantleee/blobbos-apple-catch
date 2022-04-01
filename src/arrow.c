#include <gbdk/platform.h>
#include <rand.h>
#include <stdbool.h>
#include "arrow.h"
#include "basket.h"
#include "utils.h"
#include "game_over.h"
#include "../res/arrow_sprite.h"

void init_arrow_graphics() {
	set_sprite_data(25, 4, arrow_sprite);
}

void reset_arrow(arrow_t *arrow) {
	arrow->spawn_timer = 150;
	arrow->is_active = FALSE;
	arrow->speed = ARROW_BASE_SPEED;
}

void spawn_arrow(arrow_t *arrow) {
	arrow->is_moving_right = get_random_number(0, 1);
	arrow->y = ARROW_DEFAULT_Y;
	arrow->is_active = TRUE;

	if (arrow->is_moving_right) {
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
	set_arrow_sprite_location(arrow->x, arrow->y); // TODO change name to tile_locations or something better
}

void update_arrow_location(arrow_t *arrow, basket_t *basket, uint16_t *score, uint8_t *game_state) {
	if (*score == MIN_SCORE_FOR_ARROW_TO_ACCELERATE) {
		arrow->speed = ARROW_BASE_SPEED + 1;
	}
	if (arrow->is_active) {
		arrow->x = arrow->is_moving_right ? arrow->x + arrow->speed : arrow->x - arrow->speed;
		bool arrow_collided = is_colliding(arrow->x, arrow->y, ARROW_WIDTH, ARROW_HEIGHT, basket->x, basket->y, BASKET_WIDTH, BASKET_HEIGHT);
		if ((arrow->is_moving_right && arrow->x >= RIGHT_WALL) || (!(arrow->is_moving_right) && arrow->x <= LEFT_WALL) || arrow_collided) {
			arrow->is_active = FALSE;
			hide_arrow();
			if (arrow_collided) {
				enter_game_over_state(game_state);
			}
			else {
				set_arrow_spawn_time(arrow);
			}
		}
		else {
			set_arrow_sprite_location(arrow->x, arrow->y);
		}
	}
	else if (*score > MIN_SCORE_FOR_ARROW_TO_SPAWN){
		if (-- arrow->spawn_timer == 0) {
			spawn_arrow(arrow);
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

void set_arrow_spawn_time(arrow_t *arrow) {
	arrow->spawn_timer = get_random_number(MIN_ARROW_SPAWN_TIME, MAX_ARROW_SPAWN_TIME);
}

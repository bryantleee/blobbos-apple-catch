#include <gbdk/platform.h>
#include <rand.h>
#include <stdbool.h>

#include "../res/arrow_sprite.h"
#include "arrow.h"
#include "basket.h"
#include "utils.h"

void init_arrow(struct arrow_t *arrow) {
	set_sprite_data(25, 4, arrow_sprite);
	arrow->spawn_timer = 150;
}

void spawn_arrow(struct arrow_t *arrow) {
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

void update_arrow_location(struct arrow_t *arrow, struct basket_t *basket, uint16_t *score, uint8_t *game_state) {
	if (arrow->is_active) {

		arrow->x = arrow->is_moving_right ? arrow->x + ARROW_SPEED : arrow->x - ARROW_SPEED;
	
		bool arrow_collided = is_colliding(arrow->x, arrow->y, ARROW_WIDTH, ARROW_HEIGHT, basket->x, basket->y, BASKET_WIDTH, BASKET_HEIGHT);
		if ((arrow->is_moving_right && arrow->x >= RIGHT_WALL) || (!(arrow->is_moving_right) && arrow->x <= LEFT_WALL) || arrow_collided) {
			arrow->is_active = FALSE;
			hide_arrow();
			if (arrow_collided) {
				init_game_over_state(game_state);
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

void set_arrow_spawn_time(struct arrow_t *arrow) {
	arrow->spawn_timer = get_random_number(MIN_ARROW_SPAWN_TIME, MAX_ARROW_SPAWN_TIME);
}

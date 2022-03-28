#include <gbdk/platform.h>

#include "apple.h"
#include "basket.h"
#include "utils.h"
#include "score_display.h"
#include "game_over.h"
#include "../res/apple_sprite.h"

void init_apple(struct apple_t *apple) {
    set_sprite_data(21, 4, apple_sprite);
	apple->speed = APPLE_BASE_SPEED;
}

void spawn_apple(struct apple_t * apple) {
	apple->drop_timer = APPLE_DANGLE_TIME;
	apple->x = get_random_number(LEFT_WALL, RIGHT_WALL);
	apple->y = get_random_number(APPLE_MIN_SPAWN_Y, APPLE_MAX_SPAWN_Y);

    set_sprite_tile(APPLE_TL, 21);
	set_sprite_tile(APPLE_BL, 22);
	set_sprite_tile(APPLE_TR, 23);
	set_sprite_tile(APPLE_BR, 24);
	
	set_apple_sprite_location(apple->x, apple->y);
}

void set_apple_sprite_location(uint16_t x, uint16_t y) {
	uint16_t x1 = x + 8;
    uint16_t y1 = y + 8;

    move_sprite(APPLE_TL, x, y);
	move_sprite(APPLE_TR, x1, y);
	move_sprite(APPLE_BL, x, y1);
	move_sprite(APPLE_BR, x1, y1);
}

void update_apple_location(struct apple_t *apple, struct basket_t *basket, uint16_t *score, uint8_t *game_state) {
	if (apple->drop_timer == 0) {
		apple->y += apple->speed;
		bool apple_caught = is_colliding(apple->x, apple->y, APPLE_WIDTH, APPLE_HEIGHT, basket->x, basket->y, BASKET_WIDTH, BASKET_HEIGHT);

		if (apple->y > BOTTOM_WALL || apple_caught) {
			apple->y --;
			hide_apple();

			if (apple_caught) {
				play_apple_caught_sound();
				(*score) ++;
				increment_score_display();
				spawn_apple(apple);
			}
			else {
				enter_game_over_state(game_state);
			}
		} 
		else {
			set_apple_sprite_location(apple->x, apple->y);
		}
	}
	else {
		apple->drop_timer --;
	}
}

void play_apple_caught_sound() {
	NR10_REG = 0x15;
	NR11_REG = 0x9B;
	NR12_REG = 0x73;
	NR13_REG = 0x01;
	NR14_REG = 0x85;
}

void hide_apple() {
    set_sprite_tile(APPLE_TL, 18);
	set_sprite_tile(APPLE_TR, 18);
	set_sprite_tile(APPLE_BL, 18);
	set_sprite_tile(APPLE_BR, 18);
}

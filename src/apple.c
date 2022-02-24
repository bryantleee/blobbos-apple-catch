#include <gbdk/platform.h>
#include <stdbool.h>

#include "../res/apple_sprite.h"
#include "apple.h"
#include "basket.h"
#include "init.h"
#include "utils.h"
#include "score_display.h"

void init_apple() {
    set_sprite_data(21, 4, apple_sprite);
}

void spawn_apple(struct apple_t * apple) {
	apple->x = get_random_number(LEFT_WALL, RIGHT_WALL);
	apple->y = get_random_number(0, 38);
	apple->is_active = TRUE;

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

void update_apple_location(struct apple_t *apple, struct basket_t *basket) {
	if (apple->is_active) {
		apple->y += APPLE_SPEED;
		bool apple_caught = is_colliding(apple->x, apple->y, APPLE_WIDTH, APPLE_HEIGHT, basket->x, basket->y, BASKET_WIDTH, BASKET_HEIGHT);

		if (apple->y > BOTTOM_WALL || apple_caught) {
			apple->y -= 1;
			apple->is_active = false;

			if (apple_caught) {
				increment_score_display();	

				NR10_REG = 0x15;
				NR11_REG = 0x9B;
				NR12_REG = 0x73;
				NR13_REG = 0x01;
				NR14_REG = 0x85;			
			}
			else {
				init_game_over();
			}

			hide_apple();
			
		} 
		else {
			set_apple_sprite_location(apple->x, apple->y);
		}
	}
}

void hide_apple() {
    set_sprite_tile(APPLE_TL, 18);
	set_sprite_tile(APPLE_TR, 18);
	set_sprite_tile(APPLE_BL, 18);
	set_sprite_tile(APPLE_BR, 18);
}

#include <gbdk/platform.h>
#include <stdbool.h>

#include "../res/blobbo_sprite.h"
#include "blobbo.h"

const uint8_t BLOBBO_STAND_SPEED = 2;
const uint8_t BLOBBO_CROUCH_SPEED = 1;


void set_blobbo_sprite_location(uint16_t x, uint16_t y) {
    uint16_t x1 = x + 8;
    uint16_t y1 = y + 8;

    move_sprite(BLOBBO_SPRITE_TL, x, y);
	move_sprite(BLOBBO_SPRITE_TR, x1, y);
	move_sprite(BLOBBO_SPRITE_BL, x, y1);
	move_sprite(BLOBBO_SPRITE_BR, x1, y1);
}

void set_blobbo_left() {
	set_sprite_tile(BLOBBO_SPRITE_TL, 4);
	set_sprite_tile(BLOBBO_SPRITE_TR, 6);
	set_sprite_tile(BLOBBO_SPRITE_BL, 5);
	set_sprite_tile(BLOBBO_SPRITE_BR, 7);
}

void set_blobbo_right() {
	set_sprite_tile(BLOBBO_SPRITE_TL, 0);
	set_sprite_tile(BLOBBO_SPRITE_TR, 2);
	set_sprite_tile(BLOBBO_SPRITE_BL, 1);
	set_sprite_tile(BLOBBO_SPRITE_BR, 3);
}

void set_blobbo_forward() {
	set_sprite_tile(BLOBBO_SPRITE_TL, 8);
	set_sprite_tile(BLOBBO_SPRITE_TR, 10);
	set_sprite_tile(BLOBBO_SPRITE_BL, 9);
	set_sprite_tile(BLOBBO_SPRITE_BR, 11);
}

void set_blobbo_crouching() {
	set_sprite_tile(BLOBBO_SPRITE_TL, 18);
	set_sprite_tile(BLOBBO_SPRITE_TR, 18);
	set_sprite_tile(BLOBBO_SPRITE_BL, 16);
	set_sprite_tile(BLOBBO_SPRITE_BR, 17);
}

void set_blobbo_half_crouching() {
	set_sprite_tile(BLOBBO_SPRITE_TL, 12);
	set_sprite_tile(BLOBBO_SPRITE_TR, 14);
	set_sprite_tile(BLOBBO_SPRITE_BL, 13);
	set_sprite_tile(BLOBBO_SPRITE_BR, 15);
}

void init_blobbo(struct blobbo_t *blobbo) {
    // Load the Blobbo tiles into VRAM
	set_sprite_data(0, 19, blobbo_sprite);

	// Start facing forward
	set_blobbo_forward();

	// Start Blobbo at the center x coordinate of the screen
	blobbo->x = (DEVICE_SCREEN_PX_WIDTH + DEVICE_SPRITE_PX_OFFSET_X) / 2;
    blobbo->y = BLOBBO_DEFAULT_Y; // (DEVICE_SCREEN_PX_HEIGHT + DEVICE_SPRITE_PX_OFFSET_Y) / 2;
	blobbo->state = STANDING_STATE;
	blobbo->state_timer = 0;
	blobbo->speed = BLOBBO_STAND_SPEED;
	bool is_moving_down = FALSE;
	set_blobbo_sprite_location(blobbo->x, blobbo->y);
}

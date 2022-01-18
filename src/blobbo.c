/**
    Blobbo is made of four 8x8 sprites mapped as follows:
        sprite 0: top left quarter of body (tl)
        sprite 1: top right quarter of body (tr)
        sprite 2: bottom left quarter of body (bl)
        sprite 3: bottom right quarter of body (br)
**/
#include <stdio.h>
#include <gbdk/platform.h>

#include "../res/blobbo_sprite.h"
#include "blobbo.h"


const uint8_t BLOBBO_STAND_SPEED = 2;
const uint8_t BLOBBO_CROUCH_SPEED = 1;

void set_blobbo_location(uint16_t x, uint16_t y) {
    uint8_t x1 = x + 8;
    uint8_t y1 = y + 8;

    move_sprite(0, x, y);
	move_sprite(1, x1, y);
	move_sprite(2, x, y1);
	move_sprite(3, x1, y1);
}

void set_blobbo_left() {
	set_sprite_tile(0, 4);
	set_sprite_tile(1, 6);
	set_sprite_tile(2, 5);
	set_sprite_tile(3, 7);
}

void set_blobbo_right() {
	set_sprite_tile(0, 0);
	set_sprite_tile(1, 2);
	set_sprite_tile(2, 1);
	set_sprite_tile(3, 3);
}

void set_blobbo_forward() {
	set_sprite_tile(0, 8);
	set_sprite_tile(1, 10);
	set_sprite_tile(2, 9);
	set_sprite_tile(3, 11);
}

void set_blobbo_crouching() {
	set_sprite_tile(0, 18);
	set_sprite_tile(1, 18);
	set_sprite_tile(2 ,17);
	set_sprite_tile(3, 19);
}

void set_blobbo_half_crouching() {
	set_sprite_tile(0, 12);
	set_sprite_tile(1, 14);
	set_sprite_tile(2, 13);
	set_sprite_tile(3, 15);
}

// void set_blobbo_sprite_direction(uint8_t j_input, struct blobbo_t *blobbo) {
// 	if(j_input & J_DOWN || j_input & J_B) {
		

// 	}

// }

void init_blobbo(struct blobbo_t *blobbo) {
    // Load the Blobbo sprite into VRAM & set it to 0 in the OAM
	set_sprite_data(0, 20, blobbo_sprite);

	// Start facing forward
	set_blobbo_forward();

	//start Blobbo at the center x coordinate of the screen
	blobbo->x = (DEVICE_SCREEN_PX_WIDTH + DEVICE_SPRITE_PX_OFFSET_X) / 2;
    blobbo->y = 121; // (DEVICE_SCREEN_PX_HEIGHT + DEVICE_SPRITE_PX_OFFSET_Y) / 2;
	blobbo->state = STANDING_STATE;
	blobbo->state_timer = 0;
	bool is_moving_down = FALSE;
	set_blobbo_location(blobbo->x, blobbo->y);
}

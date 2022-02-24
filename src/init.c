#include <stdio.h>

#include <gbdk/platform.h>
#include <gbdk/console.h>
#include <rand.h>

#include "blobbo.h"
#include "basket.h"
#include "arrow.h"
#include "apple.h"
#include "score_display.h"
#include "score_display.h"
#include "intro.h"

/**
    Blobbo is made of four 8x8 sprites mapped as follows:
        sprite 0: top left quarter of body (tl)
        sprite 1: top right quarter of body (tr)
        sprite 2: bottom left quarter of body (bl)
        sprite 3: bottom right quarter of body (br)
**/

// TODO: fix right wall for SMS

const uint16_t LEFT_WALL = DEVICE_SPRITE_PX_OFFSET_X;
const uint16_t RIGHT_WALL = DEVICE_SCREEN_PX_WIDTH + DEVICE_SPRITE_PX_OFFSET_X - 16;
const uint16_t BOTTOM_WALL = DEVICE_SCREEN_PX_HEIGHT;

void init_graphics(struct blobbo_t *blobbo, struct basket_t *basket) {
    // Set sprites to 8x8 mode
	SPRITES_8x8;

	init_blobbo(blobbo);
    init_basket(basket, blobbo);
    init_apple();
    init_arrow();

    // init_title_screen();
    init_score_display();

    // display_title_screen();

    SHOW_BKG;
    SHOW_SPRITES;
}

void init_sound() {
    NR52_REG = 0x8F; //turn on the sound
	NR51_REG = 0x11; //enable the sound channels
	NR50_REG = 0x77; //increase the volume to its max
}

void init_console_specific_vals() {
    // #if defined(__TARGET_gb)
    // puts("game boy");

    // #elif defined(__TARGET_gg)
    // puts("game gear");

    // #elif defined(__TARGET_sms)
    // puts("master system");

    // #else
    // puts("unrecognized system");
    // #endif
}

void init_random() {
    uint16_t seed = DIV_REG;
    seed |= (uint16_t)DIV_REG << 8;    
    initrand(seed);
}

void init_new_game() {
    reset_score_display();
}

void init_game_over() {
    NR10_REG = 0x15;
	NR11_REG = 0x9B;
	NR12_REG = 0x73;
	NR13_REG = 0x01;
	NR14_REG = 0x90;

    reset_score_display();

    // HIDE_SPRIES;
}

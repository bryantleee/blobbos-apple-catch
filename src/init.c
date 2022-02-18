#include <stdio.h>

#include <gbdk/platform.h>
#include <gbdk/console.h>
#include <rand.h>

#include "blobbo.h"
#include "basket.h"
#include "arrow.h"
#include "apple.h"

/**
    Blobbo is made of four 8x8 sprites mapped as follows:
        sprite 0: top left quarter of body (tl)
        sprite 1: top right quarter of body (tr)
        sprite 2: bottom left quarter of body (bl)
        sprite 3: bottom right quarter of body (br)
**/

// TODO: fix right wall for SMS

const uint16_t LEFT_WALL = DEVICE_SPRITE_PX_OFFSET_X;
const uint16_t RIGHT_WALL = DEVICE_SCREEN_PX_WIDTH + DEVICE_SPRITE_PX_OFFSET_X - 8;
const uint16_t BOTTOM_WALL = DEVICE_SCREEN_PX_HEIGHT;

void init_graphics(struct blobbo_t *blobbo, struct basket_t *basket) {
    // Set sprites to 8x8 mode
	SPRITES_8x8;

	init_blobbo(blobbo);
    init_basket(blobbo, basket);
    init_apple();
    init_arrow();

    SHOW_BKG;
    SHOW_SPRITES;
}

void init_console_specific_vals() {
    #if defined(__TARGET_gb)
    puts("game boy");

    #elif defined(__TARGET_gg)
    puts("game gear");

    #elif defined(__TARGET_sms)
    puts("master system");

    #else
    puts("unrecognized system");
    #endif

    // printf("%u, %u\n", (unsigned int)DEVICE_SCREEN_PX_WIDTH, (unsigned int)LEFT_WALL);
}

void init_random() {
    uint16_t seed = DIV_REG;
    seed |= (uint16_t)DIV_REG << 8;    
    initrand(seed);
}

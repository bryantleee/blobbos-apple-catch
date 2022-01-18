#include <stdio.h>

#include <gbdk/platform.h>
#include <gbdk/console.h>

#include "blobbo.h"


void init_graphics(struct Blobbo *blobbo) {
    // Set sprites to 8x8 mode
	SPRITES_8x8;
	init_blobbo(blobbo);

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
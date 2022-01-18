#include <stdio.h>
#include <rand.h>

#include <gbdk/platform.h>
#include <gbdk/console.h>

#include "blobbo.h"
#include "init.h"


struct Blobbo blobbo;

// TODO: figure out how to more smoothly animate blobbo/match his speed/feel from the original


void init() {
    init_console_specific_vals();

    init_graphics(&blobbo);
}

void main(void) {
    init();

    // game loop
    while(TRUE) { 
        uint8_t j_input = joypad();

        if(j_input & J_A) {
            printf("%u, %u\n", (unsigned int)blobbo.x, (unsigned int)BLOBBO_SPEED);
        }

        if(j_input & J_RIGHT && blobbo.x < RIGHT_WALL) {
            blobbo.x += BLOBBO_SPEED;
            set_blobbo_right();
        }
        else if(j_input & J_LEFT && blobbo.x > LEFT_WALL) {
            blobbo.x -= BLOBBO_SPEED;
            set_blobbo_left();
        }
        else {
            set_blobbo_forward();
        }
        set_blobbo_location(blobbo.x, blobbo.y);

        wait_vbl_done();
    }
}

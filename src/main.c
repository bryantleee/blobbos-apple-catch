#include <stdio.h>
#include <rand.h>

#include <gbdk/platform.h>
#include <gbdk/console.h>

#include "blobbo.h"
#include "init.h"


struct blobbo_t blobbo;

void init() {
    init_console_specific_vals();

    init_graphics(&blobbo);
}

void main(void) {
    init();

    // game loop
    while(TRUE) { 
        uint8_t j_input = joypad();

        if(j_input & J_RIGHT && blobbo.x < RIGHT_WALL) {
            blobbo.x += BLOBBO_STAND_SPEED;
            set_blobbo_right();
        }
        else if(j_input & J_LEFT && blobbo.x > LEFT_WALL) {
            blobbo.x -= BLOBBO_STAND_SPEED;
            set_blobbo_left();
        }
        else {
            set_blobbo_forward();
        }
        set_blobbo_location(blobbo.x, blobbo.y);

        wait_vbl_done();
    }
}

#include <stdio.h>
#include <rand.h>

#include <gbdk/platform.h>
#include <gbdk/console.h>

#include "../res/blobbo.h"

const uint8_t BLOBBO_SPEED = 1;
const uint8_t MOVEMENT_COOLDOWN_TIME = 70;

uint16_t LEFT_WALL;
uint16_t RIGHT_WALL;

struct Blobbo {
    uint16_t x, y;
    uint8_t movement_cooldown_timer;
    uint8_t state;
};

struct Blobbo blobbo;

// TODO: figure out how to work with the struct and set/get values from it... 
// TODO: figure out how to store it in a different file
// TODO: complete the blobbo sprite and left/right movement

// TODO: figure out how to more smoothly animate blobbo/match his speed/feel from the original

void init_console_specific_vals() {
    LEFT_WALL = DEVICE_SPRITE_PX_OFFSET_X;
    RIGHT_WALL = DEVICE_SCREEN_PX_WIDTH + DEVICE_SPRITE_PX_OFFSET_X - 8;
    
    #if defined(__TARGET_gb)
    puts("game boy");

    #elif defined(__TARGET_gg)
    puts("game gear");

    #elif defined(__TARGET_sms)
    puts("master system");

    #else
    puts("unrecognized system");
    #endif

    printf("%u, %u\n", (unsigned int)DEVICE_SCREEN_PX_WIDTH, (unsigned int)LEFT_WALL);
}


void init() {
    init_console_specific_vals();

    // Center starting position
    blobbo.x = (DEVICE_SCREEN_PX_WIDTH + DEVICE_SPRITE_PX_OFFSET_X) / 2;
    blobbo.y = (DEVICE_SCREEN_PX_HEIGHT + DEVICE_SPRITE_PX_OFFSET_Y) / 2;

    // Set sprites to 8x8 mode
    SPRITES_8x8;

    // Load the Blobbo sprite into VRAM & set it to 0 in the OAM
	set_sprite_data(0, 20, blobbo_sprite);
    set_sprite_tile(0, 8);

    SHOW_BKG;
    SHOW_SPRITES;
}

void main(void) {
    init();

    // game loop
    while(TRUE) { 
        
        uint8_t j_input = joypad();

        if(j_input & J_A) {
            printf("%u, %u\n", (unsigned int)blobbo.x, (unsigned int)blobbo.y);
        }

        if (blobbo.movement_cooldown_timer == 0) {
            if (j_input & J_RIGHT && blobbo.x < RIGHT_WALL) {
                blobbo.x += BLOBBO_SPEED;
            }
            else if (j_input & J_LEFT && blobbo.x > LEFT_WALL) {
                blobbo.x -= BLOBBO_SPEED;
            }
            if (j_input & J_UP) {
                blobbo.y -= BLOBBO_SPEED;
            }
            else if (j_input & J_DOWN) {
                blobbo.y += BLOBBO_SPEED;
            }
            blobbo.movement_cooldown_timer = MOVEMENT_COOLDOWN_TIME;
        } else {
            blobbo.movement_cooldown_timer--;
        }

        move_sprite(0, blobbo.x, blobbo.y);
    }
}

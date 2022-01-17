#include <stdio.h>
#include <rand.h>

#include <gbdk/platform.h>
#include <gbdk/console.h>

#include "../res/blobbo.h"

uint16_t blobbo_location_x;
uint16_t blobbo_location_y;
uint8_t movement_cooldown_timer;

const uint8_t BLOBBO_SPEED = 1;
const uint8_t MOVEMENT_COOLDOWN_TIME = 70;

uint16_t LEFT_WALL;
uint16_t RIGHT_WALL;

// typedef struct blobbo {
//     uint16_t location_x, location_y;
//     uint8_t movement_cooldown;
// }

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
    blobbo_location_x = (DEVICE_SCREEN_PX_WIDTH + DEVICE_SPRITE_PX_OFFSET_X) / 2;
    blobbo_location_y = (DEVICE_SCREEN_PX_HEIGHT + DEVICE_SPRITE_PX_OFFSET_Y) / 2;

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
            printf("%u, %u\n", (unsigned int)blobbo_location_x, (unsigned int)blobbo_location_y);
        }

        if (movement_cooldown_timer == MOVEMENT_COOLDOWN_TIME) {
            if (j_input & J_RIGHT && blobbo_location_x < RIGHT_WALL) {
                blobbo_location_x += BLOBBO_SPEED;
            }
            else if (j_input & J_LEFT && blobbo_location_x > LEFT_WALL) {
                blobbo_location_x -= BLOBBO_SPEED;
            }
            if (j_input & J_UP) {
                blobbo_location_y -= BLOBBO_SPEED;
            }
            else if (j_input & J_DOWN) {
                blobbo_location_y += BLOBBO_SPEED;
            }
            movement_cooldown_timer = 0;
        } else {
            movement_cooldown_timer ++;
        }

        move_sprite(0, blobbo_location_x, blobbo_location_y);
    }
}

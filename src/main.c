#include <stdio.h>
#include <rand.h>

#include <gbdk/platform.h>
#include <gbdk/console.h>

#include "../res/blobbo.h"

uint16_t blobbo_location_x;
uint16_t blobbo_location_y;
uint16_t movement_cooldown;

uint8_t BLOBBO_SPEED = 1;


// typedef struct icon_info_ {
//     uint8_t
// }

void init() {
    // Center starting position
    blobbo_location_x = DEVICE_SCREEN_PX_WIDTH / 2;
    blobbo_location_y = DEVICE_SCREEN_PX_HEIGHT / 2;

    // Set sprites to 8x8 mode
    SPRITES_8x8;

    // Load the Blobbo sprite into VRAM & set it to 0 in the OAM
	set_sprite_data(0, 20, blobbo_sprite);
    set_sprite_tile(0, 8);

    // Debug code
    #if defined(__TARGET_gg)
        puts("game gear");
    #elif defined(__TARGET_gb)
        puts("game boy");
    #elif defined(__TARGET_sms)
        puts("game sms");
    #else
        puts("unrecognized system");
    #endif

    SHOW_BKG;
    SHOW_SPRITES;
}

void main(void) {
    init();

    while(TRUE) { 
        if (movement_cooldown == 200) {
            if (joypad() & J_RIGHT) {
                blobbo_location_x += BLOBBO_SPEED;
            }
            if (joypad() & J_LEFT) {
                blobbo_location_x -= BLOBBO_SPEED;
            }
            if (joypad() & J_UP) {
                blobbo_location_y -= BLOBBO_SPEED;
            }
            if (joypad() & J_DOWN) {
                blobbo_location_y += BLOBBO_SPEED;
            }
            movement_cooldown = 0;
        } else {
            movement_cooldown ++;
        }

        move_sprite(0, blobbo_location_x, blobbo_location_y);
    }
}

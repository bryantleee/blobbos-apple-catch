#include <stdio.h>

#include <gbdk/platform.h>
#include <gbdk/console.h>

#include "blobbo.h"
#include "basket.h"
#include "arrow.h"
#include "apple.h"
#include "init.h"

struct blobbo_t blobbo;
struct basket_t basket;
struct arrow_t arrow;
struct apple_t apple;

struct blobbo_t *blobbo_ptr = &blobbo;
struct basket_t *basket_ptr = &basket;
struct arrow_t *arrow_ptr = &arrow;
struct apple_t *apple_ptr = &apple;

uint8_t game_state;
uint16_t score;

void init() {
    init_sound();

    init_console_specific_vals();

    init_graphics(blobbo_ptr, basket_ptr, arrow_ptr);

    init_random();

    game_state = GAMEPLAY_STATE;
    
    score = 0; 
    init_new_game();
}

void main(void) {
    init();
    spawn_apple(apple_ptr);

    // game loop
    while(TRUE) {
        uint8_t j_input = joypad();

        if(j_input & J_START) {
            printf("%u, %u\n", (unsigned int)DEVICE_SCREEN_PX_HEIGHT, (unsigned int)apple.drop_timer);
        }

        if (game_state == GAMEPLAY_STATE) {
        
            if (j_input & J_B) {
                if (!(arrow.is_active)) {
                    spawn_arrow(arrow_ptr);
                }
            }

            update_blobbo_location(blobbo_ptr, j_input);
            update_basket_location(basket_ptr, blobbo_ptr);
            update_arrow_location(arrow_ptr, basket_ptr);
            update_apple_location(apple_ptr, basket_ptr);

            wait_vbl_done();
        }
    }        
}

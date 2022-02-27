#include <stdio.h>

#include <gbdk/platform.h>
#include <gbdk/console.h>

#include "blobbo.h"
#include "basket.h"
#include "arrow.h"
#include "apple.h"
#include "init.h"
#include "intro.h"

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

void init_gameplay_loop() {
    
    init_sound();

    init_graphics(blobbo_ptr, basket_ptr, arrow_ptr);

    init_random();
    
    init_new_game();

    game_state = GAMEPLAY_STATE;    
}

// void set_new_game() {
//     score = 0;
//     set_bkg_data(86, SCORE_DISPLAY_TILESET_TILES_COUNT, score_display_tileset);
// }

void main(void) {
    // init_intro_credits();
    // display_intro_credits();
    
    // DISPLAY_OFF;
    // init_title_screen();
    // DISPLAY_ON;
    // display_title_screen();
    
    DISPLAY_OFF;
    init_gameplay_loop();
    DISPLAY_ON;
    
    spawn_apple(apple_ptr);
    
    // game loop
    while(TRUE) {
        uint8_t j_input = joypad();

        if (game_state == GAMEPLAY_STATE) {
        
            if (j_input & J_B) {
                if (!(arrow.is_active)) {
                    spawn_arrow(arrow_ptr);
                }
            }

            update_blobbo_location(blobbo_ptr, j_input);
            update_basket_location(basket_ptr, blobbo_ptr);
            update_arrow_location(arrow_ptr, basket_ptr);
            update_apple_location(apple_ptr, basket_ptr, &score);

            wait_vbl_done();
        }
    }        
}

#include <stdio.h>

#include <gbdk/platform.h>
#include <gbdk/console.h>

#include "blobbo.h"
#include "basket.h"
#include "arrow.h"
#include "apple.h"
#include "utils.h"
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

void main(void) {
    // init_intro_credits();
    // display_intro_credits();

    init_title_screen(&game_state);
    
    // main game loop
    while(TRUE) {
        uint8_t j_input = joypad();

        if (game_state == GAMEPLAY_STATE) {
            update_blobbo_location(blobbo_ptr, j_input);
            update_basket_location(basket_ptr, blobbo_ptr);
            update_arrow_location(arrow_ptr, basket_ptr, &score, &game_state);
            update_apple_location(apple_ptr, basket_ptr, &score, &game_state);
        }
        else if (game_state == GAME_OVER_STATE) {
            if (j_input & J_START) {
                init_gameplay_state(blobbo_ptr, basket_ptr, arrow_ptr, &game_state);
                spawn_apple(apple_ptr);
            }
        }
        else if (game_state == TITLE_SCREEN_STATE) {
            display_title_screen();
            if (j_input & J_START) {
                init_gameplay_state(blobbo_ptr, basket_ptr, arrow_ptr, &game_state);
                spawn_apple(apple_ptr);
            }
        }

        wait_vbl_done();
    }
}

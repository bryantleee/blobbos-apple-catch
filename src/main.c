#include <stdio.h>
#include <gbdk/platform.h>
#include <gbdk/console.h>
#include "blobbo.h"
#include "basket.h"
#include "arrow.h"
#include "apple.h"
#include "utils.h"
#include "intro.h"
#include "pause.h"
#include "game_over.h"
#include "spider.h"
#include "sgb_border.h"

blobbo_t blobbo;
basket_t basket;
arrow_t arrow;
apple_t apple;
spider_t spider;

blobbo_t *blobbo_ptr = &blobbo;
basket_t *basket_ptr = &basket;
arrow_t *arrow_ptr = &arrow;
apple_t *apple_ptr = &apple;
spider_t *spider_ptr = &spider;

uint8_t game_state;
uint16_t score;
uint16_t text_animation_timer;
bool start_pressed_last_frame;

void main(void) {
    set_sgb_border();
    enter_intro_credits_state();

    init_title_screen(&game_state, &text_animation_timer);
    start_pressed_last_frame = FALSE;
    
    // Main game loop
    while(TRUE) {
        const uint8_t j_input = joypad();
        const bool start_released_last_frame = !(j_input & J_START) && start_pressed_last_frame;

        if (game_state == GAMEPLAY_STATE) {
            update_blobbo_location(blobbo_ptr, j_input);
            update_basket_location(basket_ptr, blobbo_ptr);
            update_arrow_location(arrow_ptr, basket_ptr, &score, &game_state);
            update_apple_location(apple_ptr, basket_ptr, &score, &game_state);
            update_spider_location(spider_ptr, basket_ptr, &score, &game_state);
            if (start_released_last_frame) {
                enter_pause_state(&game_state);
            }
        }
        else if (game_state == GAME_OVER_STATE) {
            update_game_over(&text_animation_timer);
            if (start_released_last_frame) {
                enter_gameplay_state(blobbo_ptr, basket_ptr, apple_ptr, arrow_ptr, spider_ptr, &game_state, &score);
            }
        }
        else if (game_state == TITLE_SCREEN_STATE) {
            update_title_screen(&text_animation_timer);
            if (start_released_last_frame) {
                init_gameplay_state(&text_animation_timer);
                enter_gameplay_state(blobbo_ptr, basket_ptr, apple_ptr, arrow_ptr, spider_ptr, &game_state, &score);
            }
        }
        else if (game_state == GAMEPLAY_PAUSED_STATE) {
            if (start_released_last_frame) {
                exit_pause_state(&game_state);
            }
        }
        start_pressed_last_frame = j_input & J_START;
        wait_vbl_done();
    }
}

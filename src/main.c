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

uint8_t game_state;

struct blobbo_t *blobbo_ptr = &blobbo;
struct basket_t *basket_ptr = &basket;
struct arrow_t *arrow_ptr = &arrow;
struct apple_t *apple_ptr = &apple;

void init() {
    init_sound();

    init_console_specific_vals();

    init_graphics(blobbo_ptr, basket_ptr);

    init_random();

    game_state = GAMEPLAY_STATE;
    init_new_game();
}

void main(void) {
    init();

    // game loop
    while(TRUE) {
        uint8_t j_input = joypad();

        if (game_state == GAMEPLAY_STATE) {
        
            if (j_input & J_B) {
                if (!(arrow.is_active)) {
                    spawn_arrow(arrow_ptr);
                }
                // printf("%u, %u\n", (unsigned int)DEVICE_SCREEN_PX_HEIGHT, (unsigned int)arrow.is_moving_right);
            }
            if (j_input & J_START) {
                if (!(apple.is_active)) {
                    spawn_apple(apple_ptr);
                }
                // printf("%u, %u\n", (unsigned int)DEVICE_SCREEN_PX_HEIGHT, (unsigned int)apple.is_active);
            }

            // Code to handle Blobbo's state changing
            if (j_input & J_DOWN || j_input & J_A) {
                if (blobbo.state == STANDING_STATE) {
                    set_blobbo_half_crouching();
                    blobbo.state = HALF_CROUCH_STATE;
                    blobbo.state_timer = 2;
                    blobbo.is_moving_down = TRUE;
                }
                else if (blobbo.state == HALF_CROUCH_STATE) {
                    // If we have spent enough time in the half crouch state 
                    // transition to the full crouch state
                    if (blobbo.state_timer == 0) {
                        set_blobbo_crouching();
                        blobbo.state = FULL_CROUCH_STATE;
                        blobbo.state_timer = 0;
                        blobbo.is_moving_down = FALSE;
                        blobbo.speed = BLOBBO_CROUCH_SPEED;
                    }
                    // If we haven't spent enough time in the half crouch state
                    // continuing decrementing the timer
                    else {
                        blobbo.state_timer --;
                    }
                }
            }
            else {
                if (blobbo.state == HALF_CROUCH_STATE) {
                    // Return the standing state if blobbo is transitioning animation downwards
                    // or if Blobbo has spent enough time in half crouch state transitioning upwards
                    if (blobbo.is_moving_down || blobbo.state_timer == 0) {
                        set_blobbo_forward();
                        blobbo.state = STANDING_STATE;
                        blobbo.state_timer = 0;
                        blobbo.speed = BLOBBO_STAND_SPEED;
                    }
                    else {  
                        blobbo.state_timer --;
                    }
                }
                // Return to half crouching state from full crouching state if we let go of button
                else if (blobbo.state == FULL_CROUCH_STATE) {
                    set_blobbo_half_crouching();
                    blobbo.state = HALF_CROUCH_STATE;
                    blobbo.state_timer = 2;
                }
            }
            if (j_input & J_RIGHT && blobbo.x < RIGHT_WALL) {
                blobbo.x += blobbo.speed;
                if (blobbo.state == STANDING_STATE) {
                    set_blobbo_right();
                }
            }
            else if (j_input & J_LEFT && blobbo.x > LEFT_WALL) {
                blobbo.x -= blobbo.speed;
                if (blobbo.state == STANDING_STATE) {
                    set_blobbo_left();
                }
            }
            else {
                if (blobbo.state == STANDING_STATE) {
                    set_blobbo_forward();
                }
            }

            set_blobbo_sprite_location(blobbo.x, blobbo.y);
            update_basket_location(blobbo_ptr, basket_ptr);
            update_arrow_location(arrow_ptr, basket_ptr);
            update_apple_location(apple_ptr, basket_ptr);

            wait_vbl_done();
        }
    }        
}

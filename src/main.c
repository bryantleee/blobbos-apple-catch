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

    uint8_t current_speed = BLOBBO_STAND_SPEED;

    // game loop
    while(TRUE) { 
        uint8_t j_input = joypad();

        if(j_input & J_B) {
            printf("%u, %u\n", (unsigned int)blobbo.state, (unsigned int)blobbo.state_timer);
        }

        // Code to handle Blobbo's state changing
        if(j_input & J_DOWN || j_input & J_A) {
            if(blobbo.state == STANDING_STATE) {
                set_blobbo_half_crouching();
                blobbo.state = HALF_CROUCH_STATE;
                blobbo.state_timer = 2;
                blobbo.is_moving_down = TRUE;
            }
            else if(blobbo.state == HALF_CROUCH_STATE) {
                // If we have spent enough time in the half crouch state 
                // transition to the full crouch state
                if(blobbo.state_timer == 0) {
                    set_blobbo_crouching();
                    blobbo.state = FULL_CROUCH_STATE;
                    blobbo.state_timer = 0;
                    blobbo.is_moving_down = FALSE;
                    current_speed = BLOBBO_CROUCH_SPEED;
                }
                // If we haven't spent enough time in the half crouch state
                // continuing decrementing the timer
                else {
                    blobbo.state_timer --;
                }
            }
        }
        else {
            if(blobbo.state == HALF_CROUCH_STATE) {
                // Return the standing state if blobbo is transitioning animation downwards
                // or if Blobbo has spent enough time in half crouch state transitioning upwards
                if(blobbo.is_moving_down || blobbo.state_timer == 0) {
                    set_blobbo_forward();
                    blobbo.state = STANDING_STATE;
                    blobbo.state_timer = 0;
                    current_speed = BLOBBO_STAND_SPEED;
                }
                else {  
                    blobbo.state_timer --;
                }
            }
            else if(blobbo.state == FULL_CROUCH_STATE) {
                set_blobbo_half_crouching();
                blobbo.state = HALF_CROUCH_STATE;
                blobbo.state_timer = 2;
            }
        }

        if(j_input & J_RIGHT && blobbo.x < RIGHT_WALL) {
            blobbo.x += current_speed;
            if(blobbo.state == STANDING_STATE) {
                set_blobbo_right();
            }
        }
        else if(j_input & J_LEFT && blobbo.x > LEFT_WALL) {
            blobbo.x -= current_speed;
            if(blobbo.state == STANDING_STATE) {
                set_blobbo_left();
            }
        }
        else {
            if(blobbo.state == STANDING_STATE) {
                set_blobbo_forward();
            }
        }
        set_blobbo_location(blobbo.x, blobbo.y);

        wait_vbl_done();
    }
}

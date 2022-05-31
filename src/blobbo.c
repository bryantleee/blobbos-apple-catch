#include <gbdk/platform.h>
#include <stdbool.h>
#include "blobbo.h"
#include "utils.h"
#include "../res/blobbo_sprite.h"

/**
    Blobbo is made of four 8x8 sprites mapped as follows:
        sprite 0: top left quarter of body (tl)
        sprite 1: top right quarter of body (tr)
        sprite 2: bottom left quarter of body (bl)
        sprite 3: bottom right quarter of body (br)
**/

void set_blobbo_sprite_location(uint16_t x, uint16_t y) {
    uint16_t x1 = x + 8;
    uint16_t y1 = y + 8;

    move_sprite(BLOBBO_SPRITE_TL, x, y);
    move_sprite(BLOBBO_SPRITE_TR, x1, y);
    move_sprite(BLOBBO_SPRITE_BL, x, y1);
    move_sprite(BLOBBO_SPRITE_BR, x1, y1);
}

void set_blobbo_left() {
    set_sprite_tile(BLOBBO_SPRITE_TL, 4);
    set_sprite_tile(BLOBBO_SPRITE_TR, 6);
    set_sprite_tile(BLOBBO_SPRITE_BL, 5);
    set_sprite_tile(BLOBBO_SPRITE_BR, 7);
}

void set_blobbo_right() {
    set_sprite_tile(BLOBBO_SPRITE_TL, 0);
    set_sprite_tile(BLOBBO_SPRITE_TR, 2);
    set_sprite_tile(BLOBBO_SPRITE_BL, 1);
    set_sprite_tile(BLOBBO_SPRITE_BR, 3);
}

void set_blobbo_forward() {
    set_sprite_tile(BLOBBO_SPRITE_TL, 8);
    set_sprite_tile(BLOBBO_SPRITE_TR, 10);
    set_sprite_tile(BLOBBO_SPRITE_BL, 9);
    set_sprite_tile(BLOBBO_SPRITE_BR, 11);
}

void set_blobbo_crouching() {
    set_sprite_tile(BLOBBO_SPRITE_TL, 18);
    set_sprite_tile(BLOBBO_SPRITE_TR, 18);
    set_sprite_tile(BLOBBO_SPRITE_BL, 16);
    set_sprite_tile(BLOBBO_SPRITE_BR, 17);
}

void set_blobbo_half_crouching() {
    set_sprite_tile(BLOBBO_SPRITE_TL, 12);
    set_sprite_tile(BLOBBO_SPRITE_TR, 14);
    set_sprite_tile(BLOBBO_SPRITE_BL, 13);
    set_sprite_tile(BLOBBO_SPRITE_BR, 15);
}

void hide_blobbo() {
    set_sprite_tile(BLOBBO_SPRITE_TL, 18);
    set_sprite_tile(BLOBBO_SPRITE_TR, 18);
    set_sprite_tile(BLOBBO_SPRITE_BL, 18);
    set_sprite_tile(BLOBBO_SPRITE_BR, 18);
}

void init_blobbo_graphics() {
    // Load the Blobbo tiles into VRAM
    set_sprite_data(0, 19, blobbo_sprite);
}

void reset_blobbo(blobbo_t *blobbo) {
    hide_blobbo();

    // Start Blobbo at the center x coordinate of the screen
    blobbo->x = BLOBBO_DEFAULT_X;
    blobbo->y = BLOBBO_DEFAULT_Y;
    blobbo->state = STANDING_STATE;
    blobbo->state_timer = 0;
    blobbo->dash_recharge_timer = DASH_RECHARGE_TIMER_LENGTH;
    blobbo->speed = BLOBBO_STAND_SPEED;
    blobbo->is_moving_down = FALSE;
    blobbo->previous_j_input = 0;
    blobbo->j_b_let_go = TRUE;
    set_blobbo_sprite_location(blobbo->x, blobbo->y);
}

void update_blobbo_location(blobbo_t *blobbo, uint8_t j_input) {
    // Code to handle Blobbo's state changing
    if (j_input & J_DOWN || j_input & J_A) {
        if (blobbo->state == STANDING_STATE) {
            set_blobbo_half_crouching();
            blobbo->state = HALF_CROUCH_STATE;
            blobbo->state_timer = HALF_CROUCH_STATE_TIMER_LENGTH;
            blobbo->is_moving_down = TRUE;
        }
        else if (blobbo->state == HALF_CROUCH_STATE) {
            // If we have spent enough time in the half crouch state 
            // transition to the full crouch state
            if (blobbo->state_timer == 0) {
                set_blobbo_crouching();
                blobbo->state = FULL_CROUCH_STATE;
                blobbo->state_timer = 0;
                blobbo->is_moving_down = FALSE;
                blobbo->speed = BLOBBO_CROUCH_SPEED;
            }
            // If we haven't spent enough time in the half crouch state
            // continuing decrementing the timer
            else {
                blobbo->state_timer --;
            }
        }
    }
    else if ((j_input & J_B) && ((j_input & J_RIGHT) || (j_input & J_LEFT)) && blobbo->j_b_let_go) {
        if (blobbo->state == STANDING_STATE && blobbo->dash_recharge_timer == 0) {
            blobbo->state = DASH_STATE;
            blobbo->state_timer = DASH_STATE_TIMER_LENGTH;
            blobbo->speed = BLOBBO_DASH_SPEED;
            blobbo->previous_j_input = j_input;
            blobbo->j_b_let_go = FALSE;
        }
    }
    else {
        if (blobbo->state == HALF_CROUCH_STATE) {
            // Return the standing state if blobbo is transitioning animation downwards
            // or if Blobbo has spent enough time in half crouch state transitioning upwards
            if (blobbo->is_moving_down || blobbo->state_timer == 0) {
                set_blobbo_forward();
                blobbo->state = STANDING_STATE;
                blobbo->state_timer = 0;
                blobbo->speed = BLOBBO_STAND_SPEED;
            }
            else {  
                blobbo->state_timer --;
            }
        }
        // Return to half crouching state from full crouching state if we let go of button
        else if (blobbo->state == FULL_CROUCH_STATE) {
            set_blobbo_half_crouching();
            blobbo->state = HALF_CROUCH_STATE;
            blobbo->state_timer = HALF_CROUCH_STATE_TIMER_LENGTH;
        }
    }

    if (blobbo->state == DASH_STATE) {
        if (blobbo->state_timer == 0) {
            blobbo->state = STANDING_STATE;
            blobbo->speed = BLOBBO_STAND_SPEED;
            blobbo->dash_recharge_timer = DASH_RECHARGE_TIMER_LENGTH;
        }
        else {
            j_input = blobbo->previous_j_input;
            blobbo->state_timer --;
        }
    }
    else {
        if (blobbo->dash_recharge_timer != 0) {
            blobbo->dash_recharge_timer --;
        }
    }
    if (!(j_input & J_B)) {
        blobbo->j_b_let_go = TRUE;
    }

    // Handle directional input
    if (j_input & J_RIGHT && blobbo->x < RIGHT_WALL) {
        blobbo->x += blobbo->speed;
        if (blobbo->state == STANDING_STATE) {
            set_blobbo_right();
        }
    }
    else if (j_input & J_LEFT && blobbo->x > LEFT_WALL) {
        blobbo->x -= blobbo->speed;
        if (blobbo->state == STANDING_STATE) {
            set_blobbo_left();
        }
    }
    else {
        if (blobbo->state == STANDING_STATE) {
            set_blobbo_forward();
        }
    }

    set_blobbo_sprite_location(blobbo->x, blobbo->y);
}

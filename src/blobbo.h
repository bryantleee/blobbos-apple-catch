#ifndef BLOBBO_H_
#define BLOBBO_H_

#include <stdbool.h>

#define STANDING_STATE 0
#define HALF_CROUCH_STATE 1
#define FULL_CROUCH_STATE 2
#define DASH_STATE 3

#define BLOBBO_SPRITE_TL 0
#define BLOBBO_SPRITE_TR 1
#define BLOBBO_SPRITE_BL 2
#define BLOBBO_SPRITE_BR 3

#define BLOBBO_STAND_SPEED 2
#define BLOBBO_CROUCH_SPEED 1
#define BLOBBO_DASH_SPEED 5

#define BLOBBO_DEFAULT_X ((DEVICE_SCREEN_PX_WIDTH + DEVICE_SPRITE_PX_OFFSET_X) / 2) - 4
#define BLOBBO_DEFAULT_Y 121

#define HALF_CROUCH_STATE_TIMER_LENGTH 2
#define DASH_STATE_TIMER_LENGTH 4

#define DASH_RECHARGE_TIMER_LENGTH 20

typedef struct {
    uint16_t x, y;
    uint8_t state, state_timer, dash_recharge_timer, speed, previous_j_input;
    bool is_moving_down, j_b_let_go; // We don't users constantly holding down B to contunously dash once recharge is done
} blobbo_t;

void set_blobbo_sprite_location(uint16_t x, uint16_t y);

void set_blobbo_left();

void set_blobbo_right();

void set_blobbo_forward();

void set_blobbo_crouching();

void set_blobbo_half_crouching();

void init_blobbo_graphics();

void reset_blobbo(blobbo_t *blobbo);

void update_blobbo_location(blobbo_t *blobbo, uint8_t j_input);

void hide_blobbo();

#endif

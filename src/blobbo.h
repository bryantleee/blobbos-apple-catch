#ifndef BLOBBO_H_
#define BLOBBO_H_

#include <stdbool.h>

#define STANDING_STATE 0
#define HALF_CROUCH_STATE 1
#define FULL_CROUCH_STATE 2

extern const uint8_t BLOBBO_STAND_SPEED;
extern const uint8_t BLOBBO_CROUCH_SPEED;

struct blobbo_t {
    uint16_t x, y;
    uint8_t state, state_timer;
    bool is_moving_down;
};

void set_blobbo_sprite_location(uint16_t x, uint16_t y);

void set_blobbo_left();

void set_blobbo_right();

void set_blobbo_forward();

void set_blobbo_crouching();

void set_blobbo_half_crouching();

void init_blobbo(struct blobbo_t *blobbo);

#endif
#ifndef BLOBBO_H_
#define BLOBBO_H_

#include <stdbool.h>

#define STANDING_STATE 0
#define HALF_CROUCH_STATE 1
#define FULL_CROUCH_STATE 2

#define BLOBBO_SPRITE_TL 0
#define BLOBBO_SPRITE_TR 1
#define BLOBBO_SPRITE_BL 2
#define BLOBBO_SPRITE_BR 3

#define BLOBBO_DEFAULT_Y 121

extern const uint8_t BLOBBO_STAND_SPEED;
extern const uint8_t BLOBBO_CROUCH_SPEED;

struct blobbo_t {
    uint16_t x, y;
    uint8_t state, state_timer, speed;
    bool is_moving_down;
};

void set_blobbo_sprite_location(uint16_t x, uint16_t y);

void set_blobbo_left();

void set_blobbo_right();

void set_blobbo_forward();

void set_blobbo_crouching();

void set_blobbo_half_crouching();

void init_blobbo(struct blobbo_t *blobbo);

void update_blobbo_location(struct blobbo_t *blobbo, uint8_t j_input);

#endif
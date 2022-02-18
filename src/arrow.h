#ifndef ARROW_H_
#define ARROW_H_

#include <stdbool.h>

#define ARROW_SPRITE_L 6
#define ARROW_SPRITE_R 7

#define ARROW_DEFAULT_Y 110
#define ARROW_SPEED 3
#define SPRITE_MIRROR_RIGHT 32
#define SPRITE_MIRROR_LEFT 0

struct arrow_t {
    uint16_t x, y;
    bool is_moving_right;
    uint8_t speed, spawn_timer;
    bool is_active;
};

void init_arrow();

void spawn_arrow(struct arrow_t *arrow);

void set_arrow_sprite_location(uint16_t x, uint16_t y);

void update_arrow_location(struct arrow_t *arrow);

void hide_arrow();

#endif
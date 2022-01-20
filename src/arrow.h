#ifndef ARROW_H_
#define ARROW_H_

#include <stdbool.h>

#define ARROW_SPRITE_L 6
#define ARROW_SPRITE_R 7

struct arrow_t {
    uint16_t x, y;
    bool is_moving_right;
    uint8_t speed, spawn_timer;
};

void init_arrow();

void spawn_arrow(struct arrow_t *arrow);

#endif
#ifndef ARROW_H_
#define ARROW_H_

#include <stdbool.h>
#include "basket.h"

#define ARROW_SPRITE_L 6
#define ARROW_SPRITE_R 7
#define ARROW_WIDTH 16
#define ARROW_HEIGHT 8

#define MIN_ARROW_SPAWN_TIME 2500
#define MAX_ARROW_SPAWN_TIME 16000

#define ARROW_DEFAULT_Y 110
#define ARROW_SPEED 2
#define SPRITE_MIRROR_RIGHT 32
#define SPRITE_MIRROR_LEFT 0

struct arrow_t {
    uint16_t x, y, spawn_timer;
    bool is_moving_right, is_active;
    uint8_t speed;
};

void init_arrow(struct arrow_t *arrow);

void spawn_arrow(struct arrow_t *arrow);

void set_arrow_sprite_location(uint16_t x, uint16_t y);

void update_arrow_location(struct arrow_t *arrow, struct basket_t *basket_t);

void hide_arrow();

void set_arrow_spawn_time(struct arrow_t *arrow);

#endif
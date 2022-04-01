#ifndef ARROW_H_
#define ARROW_H_

#include <stdbool.h>
#include "basket.h"

#define ARROW_SPRITE_L 6
#define ARROW_SPRITE_R 7
#define ARROW_WIDTH 16
#define ARROW_HEIGHT 8

#define MIN_ARROW_SPAWN_TIME 180 
#define MAX_ARROW_SPAWN_TIME 540
#define MIN_SCORE_FOR_ARROW_TO_SPAWN 10
#define MIN_SCORE_FOR_ARROW_TO_ACCELERATE 50

#define ARROW_DEFAULT_Y 110
#define ARROW_BASE_SPEED 2
#define SPRITE_MIRROR_RIGHT 32
#define SPRITE_MIRROR_LEFT 0

typedef struct {
    uint16_t x, y, spawn_timer;
    bool is_moving_right, is_active;
    uint8_t speed;
} arrow_t;

void init_arrow_graphics();

void spawn_arrow(arrow_t *arrow);

void set_arrow_sprite_location(uint16_t x, uint16_t y);

void update_arrow_location(arrow_t *arrow, basket_t *basket, uint16_t *score, uint8_t *game_state);

void hide_arrow();

void set_arrow_spawn_time(arrow_t *arrow);

void reset_arrow(arrow_t *arrow);

#endif

#ifndef SPIDER_H
#define SPIDER_H

#include "basket.h"

#define SPIDER_MIN_SPAWN_Y DEVICE_SPRITE_PX_OFFSET_Y
#define SPIDER_MAX_SPAWN_Y 50
#define SPIDER_RESTING_Y 110

#define MIN_SCORE_FOR_SPIDER_TO_SPAWN 10

#define SPIDER_SPEED 1

#define SPIDER_WIDTH 16
#define SPIDER_HEIGHT 8

#define SPIDER_LEG_TIPS_L 13
#define SPIDER_LEG_L 14
#define SPIDER_BODY_L 15
#define SPIDER_BODY_R 16
#define SPIDER_LEG_R 17
#define SPIDER_LEG_TIPS_R 18

#define SPIDER_HIDDEN_STATE 0
#define SPIDER_UPPER_DANGLING_STATE 1
#define SPIDER_DESCENDING_STATE 2
#define SPIDER_LOWER_DANGLING_STATE 3
#define SPIDER_ASCENDING_STATE 4

#define SPIDER_MIN_DANGLE_TIME 60
#define SPIDER_MAX_DANGLE_TIME 80

#define SPIDER_MIN_SPAWN_TIME 180
#define SPIDER_MAX_SPAWN_TIME 540

#define LEFT_UP

typedef struct {
    uint16_t x, y, state_timer;
    uint8_t gameplay_state, graphics_state;
} spider_t;

void init_spider_graphics();

void reset_spider(spider_t *spider);

void set_spider_location(spider_t *spider);

void hide_spider();

void show_spider();

void set_spider_left_legs_up();

void set_spider_right_legs_up();

void set_spider_left_legs_down();

void set_spider_right_legs_down();

void set_spider_graphics_descending();

void set_spider_graphics_ascending();

void spawn_spider(spider_t *spider);

void update_spider_location(spider_t *spider, basket_t *basket, uint16_t *score, uint8_t *game_state);

void reset_spider_legs_props();

#endif

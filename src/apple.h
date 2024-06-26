#ifndef APPLE_H_
#define APPLE_H_

#include "basket.h"

#define APPLE_TL 8
#define APPLE_TR 9
#define APPLE_BL 10
#define APPLE_BR 11

#define APPLE_WIDTH 16
#define APPLE_HEIGHT 16

#define APPLE_MIN_SPAWN_Y DEVICE_SPRITE_PX_OFFSET_Y
#define APPLE_MAX_SPAWN_Y 50

#define APPLE_BASE_DANGLE_TIME 22
#define APPLE_FAST_DANGLE_TIME 14
#define APPLE_BASE_SPEED 2
#define MIN_SCORE_FOR_APPLE_TO_DANGLE_LESS 30

typedef struct {
    uint16_t x, y, drop_timer;
    uint8_t speed, dangle_time;
} apple_t;

void init_apple_graphics(void);

void reset_apple(apple_t *apple);

void set_apple_sprite_location(uint16_t x, uint16_t y);

void show_apple(void);

void hide_apple(void);

void spawn_apple(apple_t *apple);

void update_apple_location(apple_t *apple, basket_t *basket, uint16_t *score, uint8_t *game_state);

void play_apple_caught_sound(void);

#endif

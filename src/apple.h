#include "basket.h"

#define APPLE_TL 8
#define APPLE_TR 9
#define APPLE_BL 10
#define APPLE_BR 11

#define APPLE_WIDTH 16
#define APPLE_HEIGHT 16

#define APPLE_MIN_SPAWN_Y 0
#define APPLE_MAX_SPAWN_Y 38

#define APPLE_DANGLE_TIME 25
#define APPLE_SPEED 2

struct apple_t {
    uint16_t x, y, drop_timer;
    uint8_t speed;
};

void init_apple();

void set_apple_sprite_location(uint16_t x, uint16_t y);

void hide_apple();

void spawn_apple(struct apple_t *apple);

void update_apple_location(struct apple_t *apple, struct basket_t *basket, uint16_t *score);

void play_apple_caught_sound();

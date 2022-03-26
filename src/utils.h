#ifndef UTILS_H_
#define UTILS_H_

#include "blobbo.h"
#include "basket.h"
#include "arrow.h"
#include "apple.h"

extern const uint16_t LEFT_WALL;
extern const uint16_t RIGHT_WALL;
extern const uint16_t BOTTOM_WALL;

#define GAMEPLAY_STATE 0 // This is 0 because an equality check on 0 is most efficient
#define INTRO_CREDITS_STATE 0
#define TITLE_SCREEN_STATE 1
#define GAMEPLAY_PAUSED_STATE 2
#define GAME_OVER_STATE 3

void init_graphics(struct blobbo_t *blobbo, struct basket_t *basket, struct arrow_t *arrow);

void init_random();

void init_new_game();

void init_game_over_state(uint8_t *game_state);

void init_sound();

// Simple retangular collision check
bool is_colliding(uint8_t x1, uint8_t y1, uint8_t w1, uint8_t h1, uint8_t x2, uint8_t y2, uint8_t w2, uint8_t h2);

// Get a random number in the range [min, max]
uint16_t get_random_number(uint16_t min, uint16_t max);

void init_gameplay_state(struct blobbo_t *blobbo, struct basket_t *basket, struct apple_t *apple, struct arrow_t *arrow, uint8_t *game_state, uint16_t *score);

#endif
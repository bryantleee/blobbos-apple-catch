#ifndef UTILS_H_
#define UTILS_H_

#include "blobbo.h"
#include "basket.h"
#include "arrow.h"
#include "apple.h"
#include "spider.h"

extern const uint16_t LEFT_WALL;
extern const uint16_t RIGHT_WALL;
extern const uint16_t BOTTOM_WALL;
extern const uint16_t TOP_WALL;

#define GAMEPLAY_STATE 0 // This is 0 because an equality check on 0 is most efficient
#define INTRO_CREDITS_STATE 0
#define TITLE_SCREEN_STATE 1
#define GAMEPLAY_PAUSED_STATE 2
#define GAME_OVER_STATE 3

// Creating property macros for different use cases to maintain consistency with the other GBDK macros
#define S_DEFAULT 0x00
#define S_FLIPXY 0x60

void init_gameplay_state_graphics(uint16_t *text_animation_timer);

void init_gameplay_state(uint16_t *text_animation_timer);

void init_random();

void reset_game();

void init_sound();

// Simple retangular collision check
bool is_colliding(uint8_t x1, uint8_t y1, uint8_t w1, uint8_t h1, uint8_t x2, uint8_t y2, uint8_t w2, uint8_t h2);

// Get a random number in the range [min, max]
uint16_t get_random_number(uint16_t min, uint16_t max);

void enter_gameplay_state(blobbo_t *blobbo, basket_t *basket, apple_t *apple, arrow_t *arrow, spider_t *spider, uint8_t *game_state, uint16_t *score);

void play_start_button_noise();

#endif

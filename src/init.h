#ifndef INIT_H_
#define INIT_H_

extern const uint16_t LEFT_WALL;
extern const uint16_t RIGHT_WALL;
extern const uint16_t BOTTOM_WALL;

#define INTRO_CREDITS_STATE 0
#define TITLE_STATE 1
#define GAMEPLAY_STATE 2
#define GAME_OVER_STATE 3

void init_graphics(struct blobbo_t *blobbo, struct basket_t *basket, struct arrow_t *arrow);

void init_random();

void init_new_game();

void init_game_over();

void init_sound();

#endif
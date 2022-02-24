#ifndef BASKET_H_
#define BASKET_H_

#include "blobbo.h"

#define BASKET_SPRITE_L 4
#define BASKET_SPRITE_R 5

#define BASKET_WIDTH 16
#define BASKET_HEIGHT 8

struct basket_t {
    uint16_t x, y;
};

void set_basket_sprite_location(uint16_t x, uint16_t y);

void update_basket_location(struct basket_t *basket, struct blobbo_t *blobbo);

void init_basket(struct basket_t *basket, struct blobbo_t *blobbo);

#endif

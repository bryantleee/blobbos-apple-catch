#ifndef BASKET_H_
#define BASKET_H_

#include "blobbo.h"

struct basket_t {
    uint16_t x, y;
};

void set_basket_sprite_location(uint16_t x, uint16_t y);

void update_basket_location(struct blobbo_t *blobbo, struct basket_t *basket);

void init_basket(struct blobbo_t *blobbo, struct basket_t *basket);

#endif

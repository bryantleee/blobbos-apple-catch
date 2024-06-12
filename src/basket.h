#ifndef BASKET_H_
#define BASKET_H_

#include "blobbo.h"

#define BASKET_SPRITE_L 4
#define BASKET_SPRITE_R 5

#define BASKET_WIDTH 16
#define BASKET_HEIGHT 8

typedef struct {
    uint16_t x, y;
} basket_t;

void set_basket_sprite_location(uint16_t x, uint16_t y);

void update_basket_location(basket_t *basket, blobbo_t *blobbo);

void init_basket_graphics(void);

void reset_basket(basket_t *basket, blobbo_t *blobbo);

#endif

#include <gbdk/platform.h>
#include "blobbo.h"
#include "basket.h"
#include "../res/basket_sprite.h"

void set_basket_sprite_location(uint16_t x, uint16_t y) {
    move_sprite(4, x, y);
    move_sprite(5, x + 8, y);
}

void update_basket_location(basket_t *basket, blobbo_t *blobbo) {
    basket->x = blobbo->x;

    if (blobbo->state == STANDING_STATE) {
        basket->y = blobbo->y - 8;
    }
    else if (blobbo->state == HALF_CROUCH_STATE) {
        basket->y = blobbo->y - 4;
    }
    else if (blobbo->state == FULL_CROUCH_STATE) {
        basket->y = blobbo->y;
    }
    set_basket_sprite_location(basket->x, basket->y);
}

void init_basket_graphics(void) {
    set_sprite_data(19, 2, basket_sprite);
    set_sprite_tile(BASKET_SPRITE_L, 19);
    set_sprite_tile(BASKET_SPRITE_R, 20);
}

void reset_basket(basket_t *basket, blobbo_t *blobbo) {
    update_basket_location(basket, blobbo);
}

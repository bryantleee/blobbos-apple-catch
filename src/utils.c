#include <stdio.h>
#include <stdbool.h>
#include <gbdk/platform.h>
#include <gbdk/console.h>
#include <rand.h>

#include "utils.h"
#include "blobbo.h"
#include "basket.h"
#include "arrow.h"
#include "apple.h"
#include "score_display.h"
#include "intro.h"
#include "pause.h"
#include "../res/nature_background_tiles.h"
#include "../res/pause_text_tiles.h"

/**
    Blobbo is made of four 8x8 sprites mapped as follows:
        sprite 0: top left quarter of body (tl)
        sprite 1: top right quarter of body (tr)
        sprite 2: bottom left quarter of body (bl)
        sprite 3: bottom right quarter of body (br)
**/

const uint16_t LEFT_WALL = DEVICE_SPRITE_PX_OFFSET_X;
const uint16_t RIGHT_WALL = DEVICE_SCREEN_PX_WIDTH + DEVICE_SPRITE_PX_OFFSET_X - 16;
const uint16_t BOTTOM_WALL = DEVICE_SCREEN_PX_HEIGHT;

void init_graphics(struct blobbo_t *blobbo, struct basket_t *basket, struct arrow_t *arrow) {
	SPRITES_8x8; // Set sprites to 8x8 mode

	init_blobbo(blobbo);
    init_basket(basket, blobbo);
    init_apple();
    init_arrow(arrow);

    SHOW_BKG;
    SHOW_SPRITES;
}

void init_sound() {
    NR52_REG = 0x8F; //turn on the sound
	NR51_REG = 0x11; //enable the sound channels
	NR50_REG = 0x77; //increase the volume to its max
}

void init_random() {
    uint16_t seed = DIV_REG;
    seed |= (uint16_t)DIV_REG << 8;
    initrand(seed);
}

void init_new_game() {
    DISPLAY_OFF;
    set_bkg_data(0, NATURE_BACKGROUND_TILES_COUNT, nature_background_tileset);
    set_bkg_tiles(0, 0, NATURE_BACKGROUND_TILES_WIDTH, NATURE_BACKGROUND_TILES_HEIGHT, nature_background_tilemap);
    init_score_display();
    init_pause_state();
    reset_score_display();
    DISPLAY_ON;
}

void init_game_over_state(uint8_t *game_state) {
    NR10_REG = 0x15;
	NR11_REG = 0x9B;
	NR12_REG = 0x73;
	NR13_REG = 0x01;
	NR14_REG = 0x90;
    *game_state = GAME_OVER_STATE;
    HIDE_SPRITES;
}

bool is_colliding(uint8_t x1, uint8_t y1, uint8_t w1, uint8_t h1, uint8_t x2, uint8_t y2, uint8_t w2, uint8_t h2) {
    return (x1 < (x2 + w2)) && ((x1 + w1) > x2) && (y1 < (h2 + y2)) && ((y1 + h1) > y2);
}

uint16_t get_random_number(uint16_t min, uint16_t max) {
    return rand() % (max + 1 - min) + min;
}

void init_gameplay_state(struct blobbo_t *blobbo, struct basket_t *basket, struct apple_t *apple, struct arrow_t *arrow, uint8_t *game_state, uint16_t *score) {
    DISPLAY_OFF;
    init_sound();
    init_graphics(blobbo, basket, arrow);
    init_random();
    init_new_game();
    *game_state = GAMEPLAY_STATE;
    *score = 0;
    SHOW_SPRITES;
    DISPLAY_ON;
    spawn_apple(apple);
}

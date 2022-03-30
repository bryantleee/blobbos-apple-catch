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
#include "game_over.h"
#include "../res/nature_tiles.h"
#include "../res/pause_text_tiles.h"
#include "../res/game_over_text_tiles.h"

const uint16_t LEFT_WALL = DEVICE_SPRITE_PX_OFFSET_X;
const uint16_t RIGHT_WALL = DEVICE_SCREEN_PX_WIDTH + DEVICE_SPRITE_PX_OFFSET_X - 16;
const uint16_t BOTTOM_WALL = DEVICE_SCREEN_PX_HEIGHT;

void init_graphics(blobbo_t *blobbo, basket_t *basket, arrow_t *arrow, apple_t *apple) {
	init_blobbo(blobbo);
    init_basket(basket, blobbo);
    init_apple(apple);
    init_arrow(arrow);
    init_score_display();
    init_pause_state();
    init_game_over_state(text_animation_timer);
    
}

void init_sound() {
    NR52_REG = 0x8F; // turn on the sound
	NR51_REG = 0x11; // enable the sound channels
	NR50_REG = 0x77; // increase the volume to its max
}

void init_random() {
    uint16_t seed = DIV_REG;
    seed |= (uint16_t)DIV_REG << 8;
    initrand(seed);
}

bool is_colliding(uint8_t x1, uint8_t y1, uint8_t w1, uint8_t h1, uint8_t x2, uint8_t y2, uint8_t w2, uint8_t h2) {
    return (x1 < (x2 + w2)) && ((x1 + w1) > x2) && (y1 < (h2 + y2)) && ((y1 + h1) > y2);
}

uint16_t get_random_number(uint16_t min, uint16_t max) {
    return rand() % (max + 1 - min) + min;
}

void enter_gameplay_state(blobbo_t *blobbo, basket_t *basket, apple_t *apple, arrow_t *arrow, uint8_t *game_state, uint16_t *score, uint16_t *text_animation_timer) {
    init_graphics(blobbo, basket, arrow, apple);    
}

void init_gameplay_state() {
    DISPLAY_OFF;
    SPRITES_8x8;
    init_sound();
    init_random();
    set_bkg_data(0, NATURE_TILES_COUNT, nature_tileset);
    SHOW_SPRITES;
    SHOW_BKG;
    SHOW_SPRITES;
    DISPLAY_ON;
}

void reset_game(blobbo_t *blobbo, basket_t *basket, apple_t *apple, arrow_t *arrow, uint8_t *game_state, uint16_t *score, uint16_t *text_animation_timer) {
    set_bkg_tiles(0, 0, NATURE_TILES_WIDTH, NATURE_TILES_HEIGHT, nature_tilemap);
    *game_state = GAMEPLAY_STATE;
    *score = 0;
    reset_score_display();
    spawn_apple(apple);
}

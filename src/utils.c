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
#include "warning.h"
#include "intro.h"
#include "pause.h"
#include "game_over.h"
#include "../res/nature_tiles.h"
#include "../res/pause_text_tiles.h"
#include "../res/game_over_text_tiles.h"

const uint16_t LEFT_WALL = DEVICE_SPRITE_PX_OFFSET_X;
const uint16_t RIGHT_WALL = DEVICE_SCREEN_PX_WIDTH + DEVICE_SPRITE_PX_OFFSET_X - 16;
const uint16_t BOTTOM_WALL = DEVICE_SCREEN_PX_HEIGHT;

void init_gameplay_state_graphics(uint16_t *text_animation_timer) {
    init_blobbo_graphics();
    init_basket_graphics();
    init_apple_graphics();
    init_arrow_graphics();
    init_score_display_graphics();
    init_warning_graphics();
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

void enter_gameplay_state(blobbo_t *blobbo, basket_t *basket, apple_t *apple, arrow_t *arrow, uint8_t *game_state, uint16_t *score) {
    set_bkg_tiles(0, 0, NATURE_TILES_WIDTH, NATURE_TILES_HEIGHT, nature_tilemap);
    play_start_button_noise();
    reset_blobbo(blobbo);
    reset_basket(basket, blobbo);
    reset_apple(apple);
    reset_arrow(arrow);
    reset_score_display();
    reset_warning();
    *game_state = GAMEPLAY_STATE;
    *score = 0;
    reset_score_display();
    spawn_apple(apple);
    delay(10); // Add small delay to remove sprite ghosting effect when redrawing (consequence of GB hardware)
    SHOW_SPRITES;
}

void init_gameplay_state(uint16_t *text_animation_timer) {
    DISPLAY_OFF;
    SPRITES_8x8;
    SHOW_SPRITES;
    SHOW_BKG;
    init_sound();
    init_random();
    set_bkg_data(0, NATURE_TILES_COUNT, nature_tileset);
    init_gameplay_state_graphics(text_animation_timer);
    DISPLAY_ON;
}

void play_start_button_noise() {
    /* This sound is a bit buggy on the Analogue Pocket and will continuously play noise
        unless interrupted by another sound. Therefore, we just won't play this sound on the Analogue Pocket
        until we find a solution.
    */
    #if defined(__TARGET_gb) 
    NR10_REG = 0x23;
    NR11_REG = 0xBA;
    NR12_REG = 0x6B;
    NR13_REG = 0x0A;
    NR14_REG = 0x85;
    #endif
}

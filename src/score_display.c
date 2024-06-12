#include <gbdk/platform.h>
#include <stdbool.h>
#include "../res/score_display_tiles.h"
#include "utils.h"
#include "score_display.h"

void init_score_display_graphics(void) {
    set_bkg_data(0x63, SCORE_DISPLAY_TILESET_TILES_COUNT, score_display_tileset);
}

void reset_score_display(void) {
    for (uint8_t i = 0; i < 5; i++) {
        score_display_tilemap[i] = 0x63;
    }
    set_bkg_tiles(SCORE_DISPLAY_X, SCORE_DISPLAY_Y, SCORE_DISPLAY_TILEMAP_WIDTH, SCORE_DISPLAY_TILEMAP_HEIGHT, score_display_tilemap);
}

void increment_score_display(void) {
    score_display_tilemap[4]++;

    // Check whether we have to increase other counters (10's, 100's, etc.)
    // 10's
    if (score_display_tilemap[4] == 0x6D) {
        score_display_tilemap[3]++;
        score_display_tilemap[4] -= 10;
    }
    // 100's
    if (score_display_tilemap[3] == 0x6D) {
        score_display_tilemap[2]++;
        score_display_tilemap[3] -= 10;
    }
    // 1000's
    if (score_display_tilemap[2] == 0x6D) {
        score_display_tilemap[1]++;
        score_display_tilemap[2] -= 10;
    }
    // 10000's
    if (score_display_tilemap[1] == 0x6D) {
        score_display_tilemap[0]++;
        score_display_tilemap[1] -= 10;
    }
    
    // Draw the current score to the window
    set_bkg_tiles(SCORE_DISPLAY_X, SCORE_DISPLAY_Y, SCORE_DISPLAY_TILEMAP_WIDTH, SCORE_DISPLAY_TILEMAP_HEIGHT, score_display_tilemap);
}

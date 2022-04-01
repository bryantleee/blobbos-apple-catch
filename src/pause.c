#include <gbdk/platform.h>
#include <gbdk/console.h>
#include "utils.h"
#include "pause.h"
#include "../res/pause_text_tiles.h"
#include "../res/blank_tiles.h"

void init_pause_state() {
    set_bkg_data(0x6D, PAUSE_TEXT_TILESET_COUNT, pause_text_tileset);
}

void enter_pause_state(uint8_t *game_state) {
    play_pause_button_noise();
    *game_state = GAMEPLAY_PAUSED_STATE;
    set_bkg_tiles(PAUSE_TEXT_X, PAUSE_TEXT_Y, PAUSE_TEXT_TILEMAP_WIDTH, PAUSE_TEXT_TILEMAP_HEIGHT, pause_text_tilemap);
}

void exit_pause_state(uint8_t *game_state) {
    play_pause_button_noise();
    *game_state = GAMEPLAY_STATE;
    set_bkg_tiles(PAUSE_TEXT_X, PAUSE_TEXT_Y, PAUSE_TEXT_TILEMAP_WIDTH, PAUSE_TEXT_TILEMAP_HEIGHT, blank_tiles_tilemap);
}

void play_pause_button_noise() {
    NR10_REG = 0x23;
	NR11_REG = 0xBA;
	NR12_REG = 0x6B;
	NR13_REG = 0x0A;
	NR14_REG = 0x85;
}

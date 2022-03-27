#include <gbdk/console.h>
#include <gbdk/platform.h>
#include "utils.h"
#include "game_over.h"
#include "../res/game_over_text_tiles.h"
#include "../res/retry_text_tiles.h"

void init_game_over_state() {
    set_bkg_data(0x73, GAME_OVER_TEXT_TILESET_COUNT, game_over_text_tileset);
    set_bkg_data(0x78, RETRY_TEXT_TILESET_COUNT, retry_text_tileset);
}

void enter_game_over_state(uint8_t *game_state) {
    NR10_REG = 0x15;
	NR11_REG = 0x9B;
	NR12_REG = 0x73;
	NR13_REG = 0x01;
	NR14_REG = 0x90;
    *game_state = GAME_OVER_STATE;
    HIDE_SPRITES;
    set_bkg_tiles(GAME_OVER_X, GAME_OVER_Y, GAME_OVER_TEXT_TILEMAP_WIDTH, GAME_OVER_TEXT_TILEMAP_HEIGHT, game_over_text_tilemap);
}

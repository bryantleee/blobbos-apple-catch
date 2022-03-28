#include <gbdk/console.h>
#include <gbdk/platform.h>
#include "utils.h"
#include "game_over.h"
#include "../res/game_over_text_tiles.h"
#include "../res/retry_text_tiles.h"
#include "../res/nature_tiles.h"

void init_game_over_state(uint16_t *game_over_animation_timer) {
    set_bkg_data(0x73, GAME_OVER_TEXT_TILESET_COUNT, game_over_text_tileset);
    set_bkg_data(0x78, RETRY_TEXT_TILESET_COUNT, retry_text_tileset);
    *game_over_animation_timer = ANIMATION_CYCLE_TIME;
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
    set_bkg_tiles(RETRY_TEXT_X, RETRY_TEXT_Y, RETRY_TEXT_TILEMAP_WIDTH, RETRY_TEXT_TILEMAP_HEIGHT, retry_text_tilemap);
}

void update_game_over(uint16_t *game_over_animation_timer) {
    if (*game_over_animation_timer == 0) {
		set_bkg_tiles(RETRY_TEXT_X, RETRY_TEXT_Y, RETRY_TEXT_TILEMAP_WIDTH, RETRY_TEXT_TILEMAP_HEIGHT, retry_text_tilemap); 
		*game_over_animation_timer = ANIMATION_CYCLE_TIME;
	}
	else if(*game_over_animation_timer == HALF_ANIMATION_CYCLE_TIME) {
		set_bkg_tiles(RETRY_TEXT_X, RETRY_TEXT_Y, RETRY_TEXT_TILEMAP_WIDTH, RETRY_TEXT_TILEMAP_HEIGHT, nature_tilemap); 
		(*game_over_animation_timer) --;
	}
	else {
		(*game_over_animation_timer) --;
	}
}

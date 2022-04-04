#include <stdio.h>
#include <gbdk/platform.h>
#include "utils.h"
#include "intro.h"
#include "../res/title_screen_tiles.h"
#include "../res/blank_tiles.h"

void enter_intro_credits_state() {
	printf("                    ");
	printf("                    ");
	printf("                    ");
	printf("    Developed By    ");
	printf("     Bryant Lee     ");
	printf("                    ");
	printf("                    ");
	printf("                    ");
	printf("                    ");
	printf("                    ");
	printf("                    ");
	printf("                    ");
	printf("                    ");
	printf("                    ");
	printf("                    ");
	printf("Copyright  2019-2022");
	printf("       v2.0.1       ");

	delay(3000);
}

void init_title_screen(uint8_t *game_state, uint16_t *text_animation_timer) {
	*text_animation_timer = ANIMATION_CYCLE_TIME;
	DISPLAY_OFF;
	*game_state = TITLE_SCREEN_STATE;
	set_bkg_data(0, TITLE_SCREEN_TILESET_COUNT, title_screen_tileset);
	set_bkg_tiles(0, 0, TITLE_SCREEN_TILEMAP_WIDTH, TITLE_SCREEN_TILEMAP_HEIGHT, title_screen_tilemap);
	DISPLAY_ON;
}

void update_title_screen(uint16_t *title_screen_animation_timer) {
	if (*title_screen_animation_timer == 0) {
		set_bkg_tiles(PRESS_TEXT_X, PRESS_TEXT_Y, PRESS_TEXT_TILEMAP_WIDTH, PRESS_TEXT_TILEMAP_HEIGHT, press_text_tilemap);
		set_bkg_tiles(START_TEXT_X, START_TEXT_Y, START_TEXT_TILEMAP_WIDTH, START_TEXT_TILEMAP_HEIGHT, start_text_tilemap);
		*title_screen_animation_timer = ANIMATION_CYCLE_TIME;
	}
	else if (*title_screen_animation_timer == HALF_ANIMATION_CYCLE_TIME) {
		set_bkg_tiles(PRESS_TEXT_X, PRESS_TEXT_Y, PRESS_TEXT_TILEMAP_WIDTH, PRESS_TEXT_TILEMAP_HEIGHT, blank_tiles_tilemap);
		set_bkg_tiles(START_TEXT_X, START_TEXT_Y, START_TEXT_TILEMAP_WIDTH, START_TEXT_TILEMAP_HEIGHT, blank_tiles_tilemap);
		(*title_screen_animation_timer) --;
	}
	else {
		(*title_screen_animation_timer) --;
	}
}

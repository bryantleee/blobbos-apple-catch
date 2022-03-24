#include <stdio.h>
#include <gbdk/platform.h>

#include "utils.h"
#include "../res/title_screen_tiles.h"

void init_intro_credits() {}

void display_intro_credits() {
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
	printf("       v2.0.0       ");

	delay(3000);
}

void init_title_screen(uint8_t *game_state) {
	*game_state = TITLE_SCREEN_STATE;
	set_bkg_data(0, TITLE_SCREEN_TILESET_TILES_COUNT, title_screen_tileset);
}

void display_title_screen() {
	set_bkg_tiles(0, 0, TITLE_SCREEN_TILEMAP_WIDTH, TITLE_SCREEN_TILEMAP_HEIGHT, title_screen_tilemap);
}

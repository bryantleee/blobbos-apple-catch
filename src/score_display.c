#include <gbdk/platform.h>
#include <stdbool.h>

#include "../res/score_display_tiles.h"
#include "init.h"
#include "utils.h"

void init_score_display() {
	set_bkg_data(86, 18, score_display_tileset);
}

void reset_score_display() {
	for (int i = 0; i < 5; i ++) {
		score_display_tilemap[i] = 0x56;
	}

	set_bkg_tiles(15, 17, 5, 1, score_display_tilemap); 
}

void increment_score_display() {
	score_display_tilemap[4] ++;

	// Check whether we have to increase other counters (10's, 100's, etc.)
	// 10's
	if (score_display_tilemap[4] == 0x60) { 
		score_display_tilemap[3] ++;
		score_display_tilemap[4] -= 10;
	}
	// 100's
	if (score_display_tilemap[3] == 0x60) { 
		score_display_tilemap[2] ++;
		score_display_tilemap[3] -= 10;
	}
	// 1000's
	if (score_display_tilemap[2] == 0x60) { 
		score_display_tilemap[1] ++;
		score_display_tilemap[2] -= 10;
	}
	// 10000's
	if (score_display_tilemap[1] == 0x60) { 
		score_display_tilemap[0] ++;
		score_display_tilemap[1] -= 10;
	}
	
	// Draw the current score to the window
	set_bkg_tiles(15, 17, 5, 1, score_display_tilemap); 
}
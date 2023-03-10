#ifndef _SGB_BORDER_TILES_H
#define _SGB_BORDER_TILES_H

#include <stdint.h>
#include <gbdk/platform.h>
#include <gbdk/metasprites.h>

#define border_data_TILE_ORIGIN 0
#define border_data_TILE_W 8
#define border_data_TILE_H 8
#define border_data_WIDTH 256
#define border_data_HEIGHT 224
#define border_data_TILE_COUNT 151
#define border_data_PALETTE_COUNT 1
#define border_data_COLORS_PER_PALETTE 16
#define border_data_TOTAL_COLORS 16
#define border_data_MAP_ATTRIBUTES 0
#define border_data_MAP_ATTRIBUTES_WIDTH 32
#define border_data_MAP_ATTRIBUTES_HEIGHT 28
#define border_data_MAP_ATTRIBUTES_PACKED_WIDTH 32
#define border_data_MAP_ATTRIBUTES_PACKED_HEIGHT 28

BANKREF_EXTERN(border_data)

extern const palette_color_t border_data_palettes[16];
extern const uint8_t border_data_tiles[4832];
extern const unsigned char border_data_map[1792];

#endif

#ifndef SGB_BORDER_H_INCLUDE
#define SGB_BORDER_H_INCLUDE

#include <gb/gb.h>

#define SNES_RGB(R,G,B) (uint16_t)((B) << 10 | (G) << 5 | (R))

void set_sgb_border(unsigned char * tiledata, size_t tiledata_size,
                    unsigned char * tilemap, size_t tilemap_size,
                    unsigned char * palette, size_t palette_size);

#endif

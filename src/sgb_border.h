#ifndef SGB_BORDER_H_INCLUDE
#define SGB_BORDER_H_INCLUDE

#include <gb/gb.h>

#define SNES_RGB(R,G,B) (uint16_t)((B) << 10 | (G) << 5 | (R))

void set_sgb_border(void);

#endif

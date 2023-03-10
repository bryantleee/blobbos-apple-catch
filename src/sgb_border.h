#ifndef SGB_BORDER_H_INCLUDE
#define SGB_BORDER_H_INCLUDE

#include <gb/gb.h>

#define SNES_RGB(R,G,B) (uint16_t)((B) << 10 | (G) << 5 | (R))

/** sets SGB border

    The display must be turned on before calling this function
    (with @ref DISPLAY_ON).

    When using the SGB with a PAL SNES, a delay should be added
    just after program startup such as:

    \code{.c}
    \endcode
*/
void set_sgb_border(unsigned char * tiledata, size_t tiledata_size,
                    unsigned char * tilemap, size_t tilemap_size,
                    unsigned char * palette, size_t palette_size);

#endif

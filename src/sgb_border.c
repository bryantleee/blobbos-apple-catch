#include <gb/gb.h>
#include <gb/sgb.h>
#include <string.h>
#include "sgb_border.h"
#include "sgb_border.h"
#include "../res/sgb_border_tiles.h"

#define SGB_CHR_BLOCK0 0
#define SGB_CHR_BLOCK1 1

#define SGB_SCR_FREEZE 1
#define SGB_SCR_UNFREEZE 0

#define SGB_TRANSFER(A,B) map_buf[0]=(A), map_buf[1]=(B), sgb_transfer(map_buf) 


void set_sgb_border() {
    if (sgb_check()) {
        const unsigned char *tiledata = border_data_tiles;
        const size_t tiledata_size = sizeof(border_data_tiles);
        const unsigned char *tilemap = border_data_map;
        const size_t tilemap_size = sizeof(border_data_map);
        const unsigned char *palette = border_data_palettes;
        const size_t palette_size = sizeof(border_data_palettes);

        // Wait 4 frames for PAL SNES
        for (uint8_t i = 0; i < 4; i++) {
            wait_vbl_done();
        }

        // Initialize map buffer
        unsigned char map_buf[20];
        memset(map_buf, 0, sizeof(map_buf));

        // Freeze screen and set initial values
        SGB_TRANSFER((SGB_MASK_EN << 3) | 1, SGB_SCR_FREEZE); 
        BGP_REG = OBP0_REG = OBP1_REG = 0xE4U;

        const uint8_t tmp_lcdc = LCDC_REG;

        HIDE_SPRITES, HIDE_WIN, SHOW_BKG;
        DISPLAY_ON;

        // Prepare tilemap for SGB_BORDER_CHR_TRN (should display all 256 tiles)
        uint8_t i = 0U;
        for (uint8_t y = 0; y < 14U; y++) {
            uint8_t *dout = map_buf;
            for (uint8_t x = 0U; x < 20U; x++) {
                *dout++ = i++;
            }
            set_bkg_tiles(0, y, 20, 1, map_buf);
        }
        memset(map_buf, 0, sizeof(map_buf));

        // Transfer tile data
        uint8_t ntiles = tiledata_size >> 5;
        set_bkg_data(0, 0, tiledata); 
        SGB_TRANSFER((SGB_CHR_TRN << 3) | 1, SGB_CHR_BLOCK0);
        ntiles -= 128U;    
        tiledata += (128 * 32);
        set_bkg_data(0, ntiles << 1, tiledata); 
        SGB_TRANSFER((SGB_CHR_TRN << 3) | 1, SGB_CHR_BLOCK1);

        // Transfer map and palettes
        set_bkg_data(0, (uint8_t)(tilemap_size >> 4), tilemap);
        set_bkg_data(128, (uint8_t)(palette_size >> 4), palette);
        SGB_TRANSFER((SGB_PCT_TRN << 3) | 1, 0);

        LCDC_REG = tmp_lcdc;

        // Clear screen
        fill_bkg_rect(0, 0, 20, 18, 0);
        
        // Unfreeze screen
        SGB_TRANSFER((SGB_MASK_EN << 3) | 1, SGB_SCR_UNFREEZE); 
    }
}

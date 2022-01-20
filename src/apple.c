
#include <gbdk/platform.h>

#include "../res/apple_sprite.h"
#include "apple.h"
#include "basket.h"

void init_apple() {
    set_sprite_data(21, 4, apple_sprite);

    set_sprite_tile(APPLE_TL, 23);
	set_sprite_tile(APPLE_TR, 24);
	set_sprite_tile(APPLE_BL, 25);
	set_sprite_tile(APPLE_BR, 26);
}

// void update_apple(struct apple_t *apple, struct basket_t *basket, uint16_t lower_wall) {

//     if (apple->y > lower_wall || ) {
//         apple->y -= 1;
//     }
//     else {
        

//     }
// }
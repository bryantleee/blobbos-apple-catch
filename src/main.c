#include <stdio.h>
#include <rand.h>

#include <gbdk/platform.h>
#include <gbdk/console.h>


uint16_t blobbo_location_x;
uint16_t blobbo_location_y;

void init() {
    blobbo_location_x = DEVICE_SCREEN_PX_WIDTH  / 2;
    blobbo_location_y = DEVICE_SCREEN_PX_HEIGHT / 2;

    SHOW_BKG;
}


void main(void) {
    init();

    while(TRUE) {
        #if defined(__TARGET_gg)
            puts("game gear");
        #elif defined(__TARGET_gb)
            puts("game boy");
        #elif defined(__TARGET_sms)
            puts("game sms");
        #else
            puts("unrecognized system");
        #endif

        printf("\nx: %d", DEVICE_SCREEN_PX_WIDTH);
        printf("\ny: %d", DEVICE_SCREEN_PX_HEIGHT);
                
        waitpad(J_A);
        // initarand(sys_time);
        // for (uint8_t i = 0; i != 16; i++) 
        //     printf("rand=%hx arand=%hx\n", (uint8_t)rand(), (uint8_t)arand());
    }
}

    
    

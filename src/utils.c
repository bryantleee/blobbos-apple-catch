#include <gbdk/platform.h>
#include <stdbool.h>

bool is_colliding(uint8_t x1, uint8_t y1, uint8_t w1, uint8_t h1, uint8_t x2, uint8_t y2, uint8_t w2, uint8_t h2){
    return (x1 < (x2 + w2)) && ((x1 + w1) > x2) && (y1 < (h2 + y2)) && ((y1 + h1) > y2);
}

uint16_t get_random_number(uint16_t min, uint16_t max) {
    return rand() % (max + 1 - min) + min;
}

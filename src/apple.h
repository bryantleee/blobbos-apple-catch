#include <stdbool.h>

#define APPLE_TL 8
#define APPLE_TR 9
#define APPLE_BL 10
#define APPLE_BR 11

struct apple_t {
    uint16_t x, y;
    uint8_t speed;
};

void init_apple();

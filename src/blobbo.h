#ifndef BLOBBO
#define BLOBBO

#define BLOBBO_SPEED 1;
#define BLOBBO_MOVEMENT_COOLDOWN_TIME 70;

struct Blobbo {
    uint16_t x, y;
    uint8_t movement_cooldown_timer;
    uint8_t state;
};

void set_blobbo_location(uint16_t x, uint16_t y);

void set_blobbo_left();

void set_blobbo_right();

void set_blobbo_forward();

void set_blobbo_crouching();

void set_blobbo_half_crouching();

void init_blobbo(struct Blobbo *blobbo);

#endif
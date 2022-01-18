#ifndef INIT_H_
#define INIT_H_

extern const uint16_t LEFT_WALL;
extern const uint16_t RIGHT_WALL;

void init_graphics(struct blobbo_t *blobbo);

void init_console_specific_vals();

#endif
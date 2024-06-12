#ifndef WARNING_H_
#define WARNING_H_

#include "utils.h"
#include "blobbo.h"
#include "arrow.h"

#define WARNING_SPRITE 12

#define RIGHT_WARNING_X_LOCATION RIGHT_WALL - 13
#define LEFT_WARNING_X_LOCATION LEFT_WALL + 13
#define WARNING_Y_LOCATION BLOBBO_DEFAULT_Y - 17

void init_warning_graphics(void);

void spawn_warning(arrow_t *arrow);

void hide_warning(void);

void reset_warning(void);

#endif

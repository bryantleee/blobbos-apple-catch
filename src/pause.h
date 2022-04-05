#ifndef PAUSE_H_
#define PAUSE_H_

#define PAUSE_TEXT_X 0
#define PAUSE_TEXT_Y 17

void init_pause_state();

void enter_pause_state(uint8_t *game_state);

void exit_pause_state(uint8_t *game_state);

#endif

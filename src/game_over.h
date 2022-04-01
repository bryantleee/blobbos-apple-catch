#ifndef GAME_OVER_H_
#define GAME_OVER_H_

#define GAME_OVER_X 0
#define GAME_OVER_Y 17

#define RETRY_TEXT_X 0
#define RETRY_TEXT_Y 0

#define ANIMATION_CYCLE_TIME 100
#define HALF_ANIMATION_CYCLE_TIME ANIMATION_CYCLE_TIME / 2 

void init_game_over_state(uint16_t *game_over_animation_timer);

void enter_game_over_state(uint8_t *game_state);

void update_game_over(uint16_t *game_over_animation_timer);

#endif

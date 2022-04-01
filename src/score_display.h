#ifndef SCORE_DISPLAY_H_
#define SCORE_DISPLAY_H_

#define SCORE_DISPLAY_X 15
#define SCORE_DISPLAY_Y 17

void init_score_display_graphics();

void reset_score_display();

// Better to only include an increment operation since modulo is so costly
void increment_score_display();

#endif

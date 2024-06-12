#include <gbdk/platform.h>
#include "spider.h"
#include "basket.h"
#include "utils.h"
#include "game_over.h"
#include "../res/spider_sprite.h"

void init_spider_graphics(void) {
    set_sprite_data(30, 3, spider_sprite);
}

void reset_spider(spider_t *spider) {
    hide_spider();
    spider->gameplay_state = SPIDER_HIDDEN_STATE;
    spider->state_timer = get_random_number(SPIDER_MIN_SPAWN_TIME, SPIDER_MIN_SPAWN_TIME);
    spider->y = TOP_WALL;
    set_spider_location(spider);
    reset_spider_legs_props();
    set_spider_graphics_descending();
}

void reset_spider_legs_props(void) {
    // The spider is generated from three unique tiles
    //  and put together through horizontal and vertical reflection transformations
    set_sprite_prop(SPIDER_BODY_R, S_DEFAULT);
    set_sprite_prop(SPIDER_BODY_L, S_DEFAULT);
    set_sprite_prop(SPIDER_LEG_L, S_DEFAULT);
    set_sprite_prop(SPIDER_LEG_R, S_DEFAULT);
    set_sprite_prop(SPIDER_LEG_TIPS_R, S_DEFAULT);
    set_sprite_prop(SPIDER_LEG_TIPS_L, S_DEFAULT);
}

void set_spider_location(spider_t *spider) {
    // The spider's legs will be in different areas, depending on the spider's state
    move_sprite(SPIDER_LEG_L, spider->x - 8, spider->y);
    move_sprite(SPIDER_BODY_L, spider->x, spider->y);
    move_sprite(SPIDER_BODY_R, spider->x + 8, spider->y);
    move_sprite(SPIDER_LEG_R, spider->x + 16, spider->y);

    if (spider->gameplay_state == SPIDER_DESCENDING_STATE || spider->gameplay_state == SPIDER_UPPER_DANGLING_STATE) {
        move_sprite(SPIDER_LEG_TIPS_L, spider->x - 8, spider->y - 8);
        move_sprite(SPIDER_LEG_TIPS_R, spider->x + 16, spider->y - 8);
    }
    else if (spider->gameplay_state == SPIDER_ASCENDING_STATE || spider->gameplay_state == SPIDER_LOWER_DANGLING_STATE) {
        move_sprite(SPIDER_LEG_TIPS_L, spider->x - 8, spider->y + 8);
        move_sprite(SPIDER_LEG_TIPS_R, spider->x + 16, spider->y + 8);
    }
    else {
        move_sprite(SPIDER_LEG_TIPS_L, spider->x - 8, spider->y - 8);
        move_sprite(SPIDER_LEG_TIPS_R, spider->x + 16, spider->y - 8);
    }
}

void hide_spider(void) {
    set_sprite_tile(SPIDER_LEG_TIPS_L, 18);
    set_sprite_tile(SPIDER_LEG_L, 18);
    set_sprite_tile(SPIDER_BODY_L, 18);
    set_sprite_tile(SPIDER_BODY_R, 18);
    set_sprite_tile(SPIDER_LEG_R, 18);
    set_sprite_tile(SPIDER_LEG_TIPS_R, 18);
}

void show_spider(void) {
    set_sprite_tile(SPIDER_LEG_TIPS_L, 31);
    set_sprite_tile(SPIDER_LEG_L, 32);
    set_sprite_tile(SPIDER_BODY_L, 30);
    set_sprite_tile(SPIDER_BODY_R, 30);
    set_sprite_tile(SPIDER_LEG_R, 32);
    set_sprite_tile(SPIDER_LEG_TIPS_R, 31);
}

void set_spider_left_legs_up(void) {
    set_sprite_prop(SPIDER_BODY_R, S_DEFAULT);
    set_sprite_prop(SPIDER_LEG_R, S_DEFAULT);
    set_sprite_prop(SPIDER_LEG_TIPS_R, S_DEFAULT);
}

void set_spider_right_legs_up(void) {
    set_sprite_prop(SPIDER_BODY_R, S_FLIPX);
    set_sprite_prop(SPIDER_LEG_R, S_FLIPX);
    set_sprite_prop(SPIDER_LEG_TIPS_R, S_FLIPX);
}

void set_spider_left_legs_down(void) {
    set_sprite_prop(SPIDER_LEG_L, S_FLIPY);
    set_sprite_prop(SPIDER_LEG_TIPS_L, S_FLIPY);
}

void set_spider_right_legs_down(void) {
    set_sprite_prop(SPIDER_BODY_R, S_FLIPX);
    set_sprite_prop(SPIDER_LEG_R, S_FLIPXY);
    set_sprite_prop(SPIDER_LEG_TIPS_R, S_FLIPXY);
}

void set_spider_graphics_descending(void) {
    set_spider_left_legs_up();
    set_spider_right_legs_up();
}

void set_spider_graphics_ascending(void) {
    set_spider_left_legs_down();
    set_spider_right_legs_down();
}

void spawn_spider(spider_t *spider) {
    spider->x = get_random_number(LEFT_WALL, RIGHT_WALL);
    spider->y = get_random_number(SPIDER_MIN_SPAWN_Y, SPIDER_MAX_SPAWN_Y);
    set_spider_location(spider);
    set_spider_graphics_descending();
    
    show_spider();
}

void update_spider_location(spider_t *spider, basket_t *basket, uint16_t *score, uint8_t *game_state) {
    const bool spider_collided = is_colliding(spider->x, spider->y, SPIDER_WIDTH, SPIDER_HEIGHT, basket->x, basket->y, BASKET_WIDTH, BASKET_HEIGHT);
    if (spider_collided) {
        enter_game_over_state(game_state);
        return;
    }

    if (spider->gameplay_state == SPIDER_HIDDEN_STATE && *score > MIN_SCORE_FOR_SPIDER_TO_SPAWN) {
        if (-- spider->state_timer == 0) {
            spider->state_timer = get_random_number(SPIDER_MIN_DANGLE_TIME, SPIDER_MAX_DANGLE_TIME);
            reset_spider_legs_props();
            set_spider_graphics_descending();
            spider->gameplay_state = SPIDER_UPPER_DANGLING_STATE;
            spawn_spider(spider);
        }
    }
    else if (spider->gameplay_state == SPIDER_UPPER_DANGLING_STATE) {
        if (-- spider->state_timer == 0) {
            spider->gameplay_state = SPIDER_DESCENDING_STATE;
        }
    }
    else if (spider->gameplay_state == SPIDER_DESCENDING_STATE) {
        if (spider->y == SPIDER_RESTING_Y) {
            spider->state_timer = get_random_number(SPIDER_MIN_DANGLE_TIME, SPIDER_MAX_DANGLE_TIME);
            spider->gameplay_state = SPIDER_LOWER_DANGLING_STATE;
        }
        else {
            spider->y += SPIDER_SPEED;
            set_spider_location(spider);
        }
    }
    else if (spider->gameplay_state == SPIDER_LOWER_DANGLING_STATE) {
        if (-- spider->state_timer == 0) {
            reset_spider_legs_props();
            set_spider_graphics_ascending();
            spider->gameplay_state = SPIDER_ASCENDING_STATE;
            set_spider_location(spider);
        }
    }
    else if (spider->gameplay_state == SPIDER_ASCENDING_STATE) {
        if (spider->y == TOP_WALL) {
            spider->state_timer = get_random_number(SPIDER_MIN_SPAWN_TIME, SPIDER_MAX_SPAWN_TIME);
            spider->gameplay_state = SPIDER_HIDDEN_STATE;
            hide_spider();
        }
        else {
            spider->y -= SPIDER_SPEED;
            set_spider_location(spider);
        }
    }
}

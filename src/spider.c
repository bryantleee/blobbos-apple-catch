void init_spider_graphics() {
    set_sprite_data(25, 4, arrow_sprite);
}

void reset_spider(arrow_t *arrow) {
    hide_spider();
    arrow->spawn_timer = 150;
    arrow->is_active = FALSE;
    arrow->speed = ARROW_BASE_SPEED;
}

void hide_spider() {
    set_sprite_tile(SPIDER_SPRITE, 18);
}

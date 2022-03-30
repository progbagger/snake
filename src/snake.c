#include "snake.h"
#include "defines.h"

int is_snake_stopped(Snake *s) {
    int result = 0;
    if (!s->direction.x && !s->direction.y)
        result = 1;
    return result;
}

Snake *init_snake() {
    Snake *s = (Snake*) malloc(sizeof(Snake));
    s->head = NULL;
    s->tail = NULL;
    s->size = 0;
    s->direction = create_point(0, 0);
    s->q = init_queue();
}

void destroy_snake(Snake *s) {
    destroy_queue(s->q);
    free(s);
}

void snake_turn(Snake *s, Point direction) {

}

void snake_move(Snake *s, Point h) {

}

void snake_eat(Snake *s, Point h) {

}

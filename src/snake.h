#ifndef SRC_SNAKE_H_
#define SRC_SNAKE_H_

#include <stdio.h>

#include "queue.h"

typedef struct {
    Queue *q;
    size_t size;
    Point *head, *tail;
    Point direction;
} Snake;

Snake *init_snake();
void destroy_snake(Snake *s);
void snake_move(Snake *s, Point h);
void snake_turn(Snake *s, Point direction);
void snake_eat(Snake *s, Point h);
int is_snake_stopped(Snake *s);

#endif  // SRC_SNAKE_H_

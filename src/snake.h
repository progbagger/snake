/**
 * @file snake.h
 * @author thrixstudio@yandex.ru
 * @brief Functions to control game values
 * @version 0.1
 * @date 2022-09-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef SRC_SNAKE_H_
#define SRC_SNAKE_H_

#include <stdio.h>

#include "queue.h"

typedef struct {
  Queue *q;
  size_t size;
  size_t eaten_apples;
  size_t x, y;
  int walls;
  Point *head, *tail;
  Point prev_head, prev_tail;
  Point direction;
  Point apple;
  Point prev_apple;
  int **field;
  int speed;
} Snake;

Snake *init_snake();
void destroy_snake(Snake *s);
Snake *create_game();
int controls(Snake *s);
void snake_turn(Snake *s, Point direction);
int is_apple(Snake *s);
int snake_add_head(Snake *s);
void snake_remove_tail(Snake *s);
void generate_apple(Snake *s);
int is_snake_stopped(Snake *s);
int is_win(Snake *s);
void game();

#endif  // SRC_SNAKE_H_

/**
 * @file queue.h
 * @author thrixstudio@yandex.ru
 * @brief Queue will represent snake istelf
 * @version 0.1
 * @date 2022-09-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef SRC_QUEUE_H_
#define SRC_QUEUE_H_
typedef struct {
  int x, y;
} Point;

Point create_point(int x, int y);

struct node {
  Point data;
  struct node *next;
};

typedef struct {
  struct node *first, *last;
} Queue;

Queue *init_queue();
void destroy_queue(Queue *q);
void push_queue(Queue *q, Point value);
void push_queue_first(Queue *q, Point value);
Point pop_queue(Queue *q);
int is_queue_empty(Queue *q);

#endif  // SRC_QUEUE_H_

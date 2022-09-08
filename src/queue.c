#include "queue.h"

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Create a point object
 *
 * @param x X axis coordinate
 * @param y Y axis coordinate
 * @return Point object
 */
Point create_point(int x, int y) {
  Point result;
  result.x = x;
  result.y = y;
  return result;
}

/**
 * @brief Function to initialize queue with empty first and last elements
 *
 * @return Queue* pointer to initialized queue
 */
Queue *init_queue() {
  Queue *q = (Queue *)malloc(sizeof(Queue));
  q->first = NULL;
  q->last = NULL;
  return q;
}

/**
 * @brief Function to clean memory allocated for queue
 *
 * @param q Queue to clean
 */
void destroy_queue(Queue *q) {
  while (q->last) {
    struct node *elem = q->last;
    q->last = q->last->next;
    free(elem);
  }
  free(q);
}

/**
 * @brief Function to add element to the queue
 *
 * @param q Queue where to add element
 * @param value Value to add
 */
void push_queue(Queue *q, Point value) {
  struct node *elem = (struct node *)malloc(sizeof(struct node));
  elem->data = value;
  elem->next = q->last;
  q->last = elem;
  if (!q->first) q->first = q->last;
}

/**
 * @brief Function to delete first element of the queue
 *
 * @param q Queue where to delete element
 * @return Point returned value
 */
Point pop_queue(Queue *q) {
  struct node *elem = q->first;
  struct node *temp = q->last;
  if (q->first != q->last) {
    while (temp->next != q->first) temp = temp->next;
  }
  if (q->first != q->last)
    temp->next = NULL;
  else
    temp = NULL;
  q->first = temp;
  Point result = elem->data;
  free(elem);
  if (!q->first || !q->last) {
    q->first = NULL;
    q->last = NULL;
  }
  return result;
}

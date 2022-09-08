#include "queue.h"

#include <stdio.h>
#include <stdlib.h>

// Creating point in x y coordinates
Point create_point(int x, int y) {
  Point result;
  result.x = x;
  result.y = y;
  return result;
}

// Initiating queue to work with it
Queue *init_queue() {
  Queue *q = (Queue *)malloc(sizeof(Queue));
  q->first = NULL;
  q->last = NULL;
  return q;
}

// Freeing memory of queue
void destroy_queue(Queue *q) {
  while (q->last) {
    struct node *elem = q->last;
    q->last = q->last->next;
    free(elem);
  }
  free(q);
}

// Add element into queue head
void push_queue(Queue *q, Point value) {
  struct node *elem = (struct node *)malloc(sizeof(struct node));
  elem->data = value;
  elem->next = q->last;
  q->last = elem;
  if (!q->first) q->first = q->last;
}

// Delete first element from queue
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

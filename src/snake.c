#include "snake.h"
#include <stdlib.h>

struct node *init(int ii, int jj) {
    struct node *head = NULL;
    head = malloc(sizeof(snake));
    head->i = ii;
    head->j = jj;
    head->next = NULL;
    head->size = 1;
    return NULL;
}

struct node *push_back(struct node *head, int ii, int jj) {
    struct node *p = head;
    struct node *result = init(ii, jj);
    while (p->next != NULL)
        p = p->next;
    p->next = result;
    return result;
}

struct node *push_forward(struct node *head, int ii, int jj) {
    struct node *p = init(ii, jj);
    p->next = head;
    head = p;
    return head;
}

void destroy(struct node *head) {
    while (head != NULL) {
        struct node *p = head;
        head = head->next;
        free(p);
    }
}

void move_snake(struct node *head, int ii, int jj) {
    delete_tail(head);
    head = push_forward(head, ii, jj);
}

void delete_tail(struct node *head) {
    struct node *p = head;
    while (p->next != NULL) {
        p = p->next;
    }
    free(p);
}

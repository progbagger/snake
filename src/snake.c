#include "snake.h"
#include <stdlib.h>

snake *init(int ii, int jj) {
    snake *p = NULL;
    p = malloc(sizeof(snake));
    p->head->i = ii;
    p->head->j = jj;
    p->head->next = NULL;
    p->size = 1;
    return p;
}

snake *push_back(snake *head, int ii, int jj) {
    struct node *result = malloc(sizeof(struct node));
    head->size++;
    result->i = ii;
    result->j = jj;
    result->next = NULL;
    struct node *p = head->head;
    while (p->next != NULL)
        p = p->next;
    p->next = result;
    return head;
}

snake *push_forward(snake *head, int ii, int jj) {
    struct node *p = malloc(sizeof(struct node));
    head->size++;
    p->i = ii;
    p->j = jj;
    p->next = head->head->next;
    head->head = p;
    return head;
}

void destroy(snake *head) {
    struct node *p = head->head;
    while (p != NULL) {
        struct node *pp = p;
        p = p->next;
        free(pp);
    }
    free(head);
}

void move_snake(snake *head, int ii, int jj) {
    delete_tail(head);
    push_forward(head, ii, jj);
}

void delete_tail(snake *head) {
    struct node *p = head->head;
    while (p->next != NULL) {
        p = p->next;
    }
    free(p);
}

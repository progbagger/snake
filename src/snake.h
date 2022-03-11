#ifndef SRC_SNAKE_H_
#define SRC_SNAKE_H_

struct node {
    int i, j;
    struct node *next;
};

typedef struct stack {
    struct node *head;
    int size;
} snake;

snake *init(int ii, int jj);
snake *push_back(snake *head, int ii, int jj);
snake *push_forward(snake *head, int ii, int jj);
void destroy(snake *head);
void delete_tail(snake *head);

void move_snake(snake *head, int ii, int jj);

#endif  // SRC_SNAKE_H_

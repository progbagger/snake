#ifndef SRC_SNAKE_H_
#define SRC_SNAKE_H_

typedef struct node {
    int i, j;
    int size;
    struct node *next;
} snake;

struct node *init(int ii, int jj);
struct node *push_back(struct node *head, int ii, int jj);
struct node *push_forward(struct node *head, int ii, int jj);
void destroy(struct node *head);
void delete_tail(struct node *head);

void move_snake(struct node *head, int ii, int jj);

#endif  // SRC_SNAKE_H_

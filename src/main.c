#include <stdio.h>

#include "queue.h"

int main() {
    int i = 0, j = 0;
    Queue *q = init_queue();
    for (size_t k = 0; k < 100; k++)
        push_queue(q, create_point(i++, j++));
    while (!is_queue_empty(q)) {
        Point p = pop_queue(q);
        printf("x = %d, y = %d\n", p.x, p.y);
    }
    for (size_t k = 0; k < 100; k++)
        push_queue(q, create_point(i++, j++));
    while (!is_queue_empty(q)) {
        Point p = pop_queue(q);
        printf("x = %d, y = %d\n", p.x, p.y);
    }
    destroy_queue(q);
    return 0;
}

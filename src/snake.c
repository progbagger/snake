#include "snake.h"
#include "defines.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>

int **mem_alloc(size_t x, size_t y) {
    int **result = calloc(y, sizeof(int*));
    for (size_t i = 0; i < y; i++)
        result[i] = calloc(x, sizeof(int));
    return result;
}

void mem_free(int **m, size_t y) {
    for (size_t i = 0; i < y; i++)
        free(m[i]);
    free(m);
}

int is_snake_stopped(Snake *s) {
    int result = 0;
    if (!s->direction.x && !s->direction.y)
        result = 1;
    return result;
}

Snake *init_snake() {
    Snake *s = (Snake*) malloc(sizeof(Snake));
    s->head = NULL;
    s->tail = NULL;
    s->size = 0;
    s->walls = -1;
    s->x = 0;
    s->y = 0;
    s->direction = create_point(0, 0);
    s->q = init_queue();
    s->field = NULL;
    return s;
}

void destroy_snake(Snake *s) {
    destroy_queue(s->q);
    mem_free(s->field, s->y);
    free(s);
}

Snake *read_file(const char *file) {
    FILE *f = fopen(file, "r");
    Snake *s = init_snake();
    fscanf(f, "%lu %lu", &s->x, &s->y);
    fscanf(f, "%d", &s->walls);
    int x, y;
    fscanf(f, "%d %d", &x, &y);
    s->direction = create_point(x, y);
    fscanf(f, "%lu", &s->size);
    for (size_t i = 0; i < s->size; i++) {
        int p_x, p_y;
        fscanf(f, "%d %d", &p_x, &p_y);
        push_queue(s->q, create_point(p_x, p_y));
    }
    s->head = &s->q->last->data;
    s->tail = &s->q->first->data;
    printf("YAY!\n");
    s->field = mem_alloc(s->x, s->y);
    for (size_t i = 0; i < s->y; i++)
        for (size_t j = 0; j < s->x; j++)
            fscanf(f, "%d", &s->field[i][j]);
    struct node *temp = s->q->last;
    while (temp) {
        s->field[temp->data.y][temp->data.x] = 1;
        temp = temp->next;
    }
    fclose(f);
    generate_apple(s);
    return s;
}

Snake *create_game() {
    int n;
    Snake *s = NULL;
    const char
        file_1[] = "../datasets/1.txt";
    scanf("%d", &n);
    switch (n) {
        case 1:
            s = read_file(file_1);
            break;
    }
    srand(time(NULL));
    return s;
}

void snake_turn(Snake *s, Point direction) {
    if (direction.x) {
        if (s->direction.y)
            s->direction = direction;
    } else if (direction.y) {
        if (s->direction.x)
            s->direction = direction;
    }
}

int snake_add_head(Snake *s) {
    int result = 0;
    int x, y;
    if (!s->walls) {
        x = (s->head->x + s->direction.x + s->x) % s->x;
        y = (s->head->y + s->direction.y + s->y) % s->y;
    } else {
        x = s->head->x + s->direction.x;
        y = s->head->y + s->direction.y;
    }
    Point next_head = create_point(x, y);
    if (s->field[y][x] == 2)
        result = 1;
    else if (s->field[y][x] == 1)
        result = 2;
    push_queue(s->q, next_head);
    s->field[y][x] = 1;
    s->head = &s->q->last->data;
    s->size += 1;
    return result;
}

void snake_remove_tail(Snake *s) {
    s->field[s->tail->y][s->tail->x] = 0;
    pop_queue(s->q);
    s->tail = &s->q->first->data;
    s->size -= 1;
}

char getch() {
    char buf = 0;
    struct termios old = {0};
    fflush(stdout);
    if (tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 0;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    return buf;
}

int controls(Snake *s) {
    int result = 0;
    char c = getch();
    if (c == 'w')
        snake_turn(s, FORWARD);
    else if (c == 'a')
        snake_turn(s, LEFT);
    else if (c == 'd')
        snake_turn(s, RIGHT);
    else if (c == 's')
        snake_turn(s, DOWN);
    else if (c == 'x')
        result = 1;
    return result;
}

void generate_apple(Snake *s) {
    int x = rand() % s->x, y = rand() % s->y;
    while (s->field[y][x] == 1) {
        srand(time(NULL));
        x = rand() % s->x;
        y = rand() % s->y;
    }
    s->field[y][x] = 2;
}

void print_field(Snake *s) {
    system("clear");
    for (size_t i = 0; i < s->x + 2; i++) {
        if (s->walls)
            printf("██");
        else
            printf("░░");
    }
    printf("\n");
    for (size_t i = 0; i < s->y; i++) {
        for (size_t j = 0; j < s->x + 2; j++) {
            if (j == 0 || j == s->x + 1) {
                if (s->walls)
                    printf("██");
                else
                    printf("░░");
            } else if (s->field[i][j - 1] == 1) {
                printf("██");
            } else if (s->field[i][j - 1] == 0) {
                printf("  ");
            } else if (s->field[i][j - 1] == 2) {
                printf("▒▒");
            }
        }
        printf("\n");
    }
    for (size_t i = 0; i < s->x + 2; i++) {
        if (s->walls)
            printf("██");
        else
            printf("░░");
    }
    printf("\n");
}

void game() {
    Snake *s = create_game();
    while (1) {
        if (controls(s))
            break;
        int check = snake_add_head(s);
        if (check == 0)
            snake_remove_tail(s);
        else if (check == 2)
            break;
        else if (check == 1)
            generate_apple(s);
        print_field(s);
        usleep(200000);
    }
    destroy_snake(s);
}

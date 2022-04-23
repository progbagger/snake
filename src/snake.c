#include "snake.h"
#include "defines.h"
#include "graphics.h"
#include "reading.h"

#include <stdlib.h>
#include <time.h>
#include <unistd.h>

// Freeing field
void mem_free(int **m, size_t y) {
    for (size_t i = 0; i < y; i++)
        free(m[i]);
    free(m);
}

// Initialization of game
Snake *init_snake() {
    Snake *s = (Snake*) malloc(sizeof(Snake));
    s->head = NULL;
    s->tail = NULL;
    s->prev_head = create_point(0, 0);
    s->prev_tail = create_point(0, 0);
    s->size = 0;
    s->eaten_apples = 0;
    s->walls = -1;
    s->x = 0;
    s->y = 0;
    s->direction = create_point(0, 0);
    s->apple = create_point(0, 0);
    s->prev_apple = create_point(0, 0);
    s->q = init_queue();
    s->field = NULL;
    s->speed = 0;
    return s;
}

// Freeing game memory
void destroy_snake(Snake *s) {
    destroy_queue(s->q);
    mem_free(s->field, s->y);
    free(s);
}

// Setting speed of snake
int set_speed(int s) {
    int result = 0;
    switch (s) {
        case 1:
            result = 500000;
            break;
        case 2:
            result = 250000;
            break;
        case 3:
            result = 80000;
            break;
        case 4:
            result = 62500;
            break;
    }
    return result;
}

// Choosing level for game
Snake *create_game() {
    Snake *s = NULL;
    const int files_count = 5;
    menu_level();
    int n = input_level();
    if (n <= files_count) {
        FILES_LIST;
        s = read_file(ACCESS_FILE(n));
    } else {
        printf("Path to your map: ");
        char *str = str_input();
        s = read_file(str);
        if (str)
            free(str);
    }
    if (s) {
        GLOBAL_FILE_SUCCESS_MESSAGE;
        menu_speed();
        int speed = input_speed();
        s->speed = set_speed(speed);
        srand(time(NULL));
    } else {
        GLOBAL_FILE_ERROR_MESSAGE;
    }
    return s;
}

// Turning snake
void snake_turn(Snake *s, Point direction) {
    if (direction.x) {
        if (s->direction.y)
            s->direction = direction;
    } else if (direction.y) {
        if (s->direction.x)
            s->direction = direction;
    }
}

// Adding head to snake and checking for walls or apples
int snake_add_head(Snake *s) {
    int result = 0;
    int x, y;
    int check = 0;
    if (!s->walls) {
        x = (s->head->x + s->direction.x + s->x) % s->x;
        y = (s->head->y + s->direction.y + s->y) % s->y;
    } else {
        x = s->head->x + s->direction.x;
        y = s->head->y + s->direction.y;
    }
    Point next_head = create_point(x, y);
    // ! x and y can be only in range [0; s->x - 1] and [0; s->y - 1]
    if ((y >= (int) s->y || y < 0 || x >= (int) s->x || x < 0) && s->walls) {
        result = 2;
        check = 1;
    // * Apple encounter
    } else if (s->field[y][x] == 2) {
        result = 1;
        s->eaten_apples += 1;
    // * Collision handle
    } else if (s->field[y][x] == 1 || s->field[y][x] == 3) {
        result = 2;
    }
    if (!check) {
        push_queue(s->q, next_head);
        s->field[y][x] = 3;
        s->prev_head = create_point(s->head->x, s->head->y);
        s->head = &s->q->last->data;
        s->size += 1;
    }
    return result;
}

// Removing tail of snake
void snake_remove_tail(Snake *s) {
    s->field[s->tail->y][s->tail->x] = 0;
    s->prev_tail = create_point(s->tail->x, s->tail->y);
    pop_queue(s->q);
    s->tail = &s->q->first->data;
    s->size -= 1;
}

// Handling keyboard keys
int controls(Snake *s) {
    int result = 0;
    char c = getch();
    if (c == 'w') {
        snake_turn(s, FORWARD);
    } else if (c == 'a') {
        snake_turn(s, LEFT);
    } else if (c == 'd') {
        snake_turn(s, RIGHT);
    } else if (c == 's') {
        snake_turn(s, DOWN);
    } else if (c == 'x') {
        result = 1;
        EXIT_GAME;
    }
    return result;
}

// Generating apple in empty space of field
void generate_apple(Snake *s) {
    int x = rand() % s->x, y = rand() % s->y;
    while (s->field[y][x]) {
        x = (x + 1) % s->x;
        if (x == 0)
            y = (y + 1) % s->y;
    }
    s->field[y][x] = 2;
    s->apple.y = y;
    s->apple.x = x;
}

// Checks if player won the game
int is_win(Snake *s) {
    /*
        Player can win the game if there are
        no space to generate apple. In other words,
        Player's snake situated at a whole game field.
    */
    int result = 0;
    if (s->size == s->x * s->y)
        result = 1;
    return result;
}

// Main game function
void game() {
    CLEAR;
    Snake *s = create_game();
    if (s) {
        print_field(s);
        HIDE_CURSOR;
        usleep(s->speed);
        while (s->size != s->x * s->y) {
            if (controls(s)) {
                break;
            }
            int check = snake_add_head(s);
            if (check == 0)
                snake_remove_tail(s);
            else if (check == 2) {
                printf("Oops, collision! Game over!\n");
                usleep(500000);
                EXIT_GAME;
                break;
            }
            else if (check == 1 && !is_win(s))
                generate_apple(s);
            // print_field(s);
            change_field(s);
            usleep(s->speed);
            if (is_win(s)) {
                printf("Congratulations! You won the game!\n");
                usleep(500000);
                EXIT_GAME;
                break;
            }
        }
        destroy_snake(s);
        SHOW_CURSOR;
    }
}

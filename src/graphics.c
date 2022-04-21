#include "graphics.h"
#include "snake.h"
#include "defines.h"

void erase_head(Snake *s) {
    MOVE_CURSOR(s->prev_head.y + 2 + 1, s->prev_head.x * 2 + 3);
    printf(SNAKE);
}

void erase_tail(Snake *s) {
    MOVE_CURSOR(s->prev_tail.y + 2 + 1, s->prev_tail.x * 2 + 3);
    printf(SPACE);
}

void print_tail(Snake *s) {
    MOVE_CURSOR(s->tail->y + 2 + 1, s->tail->x * 2 + 3);
    printf(SNAKE);
}

void print_head(Snake *s) {
    MOVE_CURSOR(s->head->y + 2 + 1, s->head->x * 2 + 3);
    printf(HEAD);
}

void erase_apple(Snake *s) {
    MOVE_CURSOR(s->apple.y + 2 + 1, s->apple.x * 2 + 3);
    printf(SPACE);
}

void print_apple(Snake *s) {
    MOVE_CURSOR(s->apple.y + 2 + 1, s->apple.x * 2 + 3);
    printf(APPLE);
}

void print_status_bar(Snake *s) {
    DISPLAY_GAME_NAME;
    DISPLAY_SEPARATOR;
    DISPLAY_EATEN_APPLES;
    __APPLES(s->eaten_apples);
    DISPLAY_SEPARATOR;
    DISPLAY_SPEED;
    __SPEED((double) 1000000 / (double) s->speed);
    printf("\n");
}

void change_status(Snake *s) {
    MOVE_CURSOR(0, 17);
    __APPLES(s->eaten_apples);
}

void print_wall(Snake *s) {
    for (size_t i = 0; i < s->x + 2; i++) {
        if (s->walls)
            printf(WALLS);
        else
            printf(EDGES);
    }
    printf("\n");
}

void print_row(Snake *s) {
    for (size_t i = 0; i < s->y; i++) {
        for (size_t j = 0; j < s->x + 2; j++) {
            if (j == 0 || j == s->x + 1) {
                if (s->walls)
                    printf(WALLS);
                else
                    printf(EDGES);
            } else if (s->field[i][j - 1] == 1) {
                printf(WALLS);
            } else if (s->field[i][j - 1] == 0) {
                printf(SPACE);
            } else if (s->field[i][j - 1] == 2) {
                printf(APPLE);
            } else if (s->field[i][j - 1] == 3) {
                if ((int) i == s->head->y && (int) (j - 1) == s->head->x)
                    printf(HEAD);
                else
                    printf(SNAKE);
            }
        }
        printf("\n");
    }
}

// Printing game field on screen
void print_field(Snake *s) {
    CLEAR;
    print_status_bar(s);
    // DISPLAY_STATUS_BAR(s->size, s->eaten_apples);
    // DISPLAY_SEPARATOR;
    // double speed = 1000000 / s->speed;
    // DISPLAY_SPEED(speed);
    print_wall(s);
    print_row(s);
    print_wall(s);
}

void change_field(Snake *s) {
    erase_head(s);
    print_head(s);
    erase_tail(s);
    print_tail(s);
    erase_apple(s);
    print_apple(s);
    change_status(s);
    MOVE_CURSOR((int) (s->y + 4), 0);
    /*
        ! To apply changes to game field there are
        ! fflush(stdout) to put all printed symbols
        ! into stdout
    */
    fflush(stdout);
}

// Printing game menu for speed
void menu_speed() {
    printf("Choose speed:\n");
    printf("1 - Very low speed\n");
    printf("2 - Medium speed\n");
    printf("3 - High speed\n");
    printf("4 - Veterans\n");
}

// Printing game menu for level
void menu_level() {
    printf("Choose level:\n");
    printf("1 - Classic square level with walls\n");
    printf("2 - Classic square level without walls\n");
    printf("3 - Interesting variant with quadrants\n");
    printf("4 - Map 3 with holes at edges\n");
    printf("5 - Map 3 with holes across whole walls\n");
    printf("6 - Your map\n");
}

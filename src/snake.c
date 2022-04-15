#include "snake.h"
#include "defines.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>

// Input an string from stdin
char *str_input() {
    char *str = NULL, c = getchar();
    size_t size = 0;
    size_t mem_size = size;
    while (c != '\n') {
        if (!mem_size || size == mem_size) {
            char *tmp = str;
            mem_size += 10;
            str = reallocarray(tmp, mem_size, sizeof(char));
        }
        str[++size - 1] = c;
        c = getchar();
    }
    if (str) {
        char *tmp = str;
        str = reallocarray(tmp, size + 1, sizeof(char));
        str[size] = '\0';
    }
    return str;
}

// Allocating field
int **mem_alloc(size_t x, size_t y) {
    int **result = calloc(y, sizeof(int*));
    for (size_t i = 0; i < y; i++)
        result[i] = calloc(x, sizeof(int));
    return result;
}

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

/*
    Section below is a huge sequence of reading functions
*/

int scan_f_size(FILE *f, size_t *x, size_t *y, int *c_input, int *input_count) {
    int scan_check, check = 1;
    if ((scan_check = fscanf(f, "%lu %lu", x, y)) != 2) {
        check = 0;
        printf("%s", ERROR);
    } else {
        *c_input += 2;
        *input_count += (int) (*x * *y);
        printf("%s", SUCCESS);
    }
    printf("Size reading\n");
    return check;
}

int scan_w_status(FILE *f, int *w, int *c_input) {
    int scan_check, check = 1;
    if (!(scan_check = fscanf(f, "%d", w)) || (*w != 0 && *w != 1)) {
        check = 0;
        printf("%s", ERROR);
    } else {
        *c_input += 1;
        printf("%s", SUCCESS);
    }
    printf("Walls status reading\n");
    return check;
}

int scan_i_dir(FILE *f, int *x, int *y, int *c_input) {
    int scan_check, check = 1;
    if ((scan_check = fscanf(f, "%d %d", x, y)) != 2 || *x < -1 || *x > 1 || *y < -1 || *y > 1) {
        check = 0;
        printf("%s", ERROR);
    } else {
        *c_input += 2;
        printf("%s", SUCCESS);
    }
    printf("Initial direction reading\n");
    return check;
}

int scan_s_size(FILE *f, Snake *s, int *snake_size, int *c_input, int *input_count) {
    int scan_check, check = 1;
    if (!(scan_check = fscanf(f, "%d", snake_size)) || (size_t) (*snake_size) > s->x * s->y || *snake_size < 0) {
        check = 0;
        printf("%s", ERROR);
    } else {
        *c_input += 1;
        s->size = (size_t) (*snake_size);
        *input_count += (int) (s->size * 2);
        printf("%s", SUCCESS);
    }
    printf("Snake size reading\n");
    return check;
}

int scan_s_segments(FILE *f, Snake *s, int *c_input) {
    int scan_check, check = 1;
    printf("%sReading snake segments\n", STATUS);
    int snake_check = 1;
    if (s->size == 0) {
        printf("  %sSnake size is 0, no segments to read\n", ERROR);
        snake_check = 0;
    }
    for (size_t i = 0; i < s->size; i++) {
        int p_x, p_y;
        if ((scan_check = fscanf(f, "%d %d", &p_x, &p_y)) != 2 || (p_x < 0 || p_x > (int) (s->x - 1)) || (p_y < 0 || p_y > (int) (s->y - 1))) {
            check = 0;
            snake_check = 0;
            printf("  %sReading %lu segment\n", ERROR, i);
        } else {
            *c_input += 2;
        }
        push_queue(s->q, create_point(p_x, p_y));
    }
    if (snake_check)
        printf("%s", SUCCESS);
    else
        printf("%s", ERROR);
    printf("Reading snake segments\n");
    s->head = &s->q->last->data;
    s->tail = &s->q->first->data;
    return check;
}

int scan_field(FILE *f, Snake *s, int *c_input) {
    int scan_check, check = 1;
    s->field = mem_alloc(s->x, s->y);
    int field_check = 1;
    printf("%sReading field\n", STATUS);
    if (s->x == 0 && s->y == 0) {
        field_check = 0;
        printf("  %sField size is 0, no coordinates to read\n", ERROR);
    }
    for (size_t i = 0; i < s->y; i++)
        for (size_t j = 0; j < s->x; j++) {
            int cord = -1;
            if (!(scan_check = fscanf(f, "%d", &cord)) || (cord != 0 && cord != 1)) {
                check = 0;
                field_check = 0;
                printf("  %sReading (%lu, %lu) coordinate\n", ERROR, j + 1, i + 1);
            } else {
                s->field[i][j] = cord;
                *c_input += 1;
            }
        }
    if (field_check)
        printf("%s", SUCCESS);
    else
        printf("%s", ERROR);
    printf("Reading field\n");
    struct node *temp = s->q->last;
    while (temp) {
        s->field[temp->data.y][temp->data.x] = 3;
        temp = temp->next;
    }
    return check;
}

void valid_check(Snake *s, int check, int c_input, int input_count) {
    if (check && c_input == input_count) {
        generate_apple(s);
    } else {
        destroy_snake(s);
        s = NULL;
    }
}

// Reading game settings from file
Snake *read_file(const char *file) {
    printf("\033[1;33m---------------\033[0m\t%sReading file...\n", STATUS);
    FILE *f = fopen(file, "r");
    Snake *s = NULL;
    int check = 1, input_count = 6, c_input = 0;
    if (f) {
        s = init_snake();
        check = scan_f_size(f, &s->x, &s->y, &c_input, &input_count);
        check = scan_w_status(f, &s->walls, &c_input);
        int x, y;
        check = scan_i_dir(f, &x, &y, &c_input);
        s->direction = create_point(x, y);
        int snake_size = -1;
        check = scan_s_size(f, s, &snake_size, &c_input, &input_count);
        check = scan_s_segments(f, s, &c_input);
        check = scan_field(f, s, &c_input);
        fclose(f);
        CLOSING_FILE;
        valid_check(s, check, c_input, input_count);
    } else {
        FILE_DOES_NOT_EXIST;
    }
    return s;
}

// Printing game menu for level
void menu_level() {
    printf("Choose level:\n");
    printf("1 - Classic square level with walls\n");
    printf("2 - Classic square level without walls\n");
    printf("3 - Interesting variant with quadrants\n");
    printf("4 - Your map\n");
}

// Input level int
int input_level() {
    int result = 0;
    printf("Your choice: ");
    int check = scanf("%d", &result);
    while (getchar() != '\n') {}
    while (!check || (result < 1 || result > 4)) {
        printf("%sIncorrect input for %slevel number%s. Please, try again.\n", ERROR, BLUE, RESET);
        menu_level();
        printf("Your choice: ");
        check = scanf("%d", &result);
        while (getchar() != '\n') {}
    }
    return result;
}

// Printing game menu for speed
void menu_speed() {
    printf("Choose speed:\n");
    printf("1 - Very low speed\n");
    printf("2 - Medium speed\n");
    printf("3 - High speed\n");
    printf("4 - Veterans\n");
}

// Input speed int while user does not input correct value
int input_speed() {
    int result = 0;
    printf("Your choice: ");
    int check = scanf("%d", &result);
    while (getchar() != '\n') {}
    while (!check || (result < 1 || result > 4)) {
        printf("%sIncorrect input for %ssnake speed%s. Please, try again.\n", ERROR, BLUE, RESET);
        menu_speed();
        printf("Your choice: ");
        check = scanf("%d", &result);
        while (getchar() != '\n') {}
    }
    return result;
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
    const char *files[] = {
        "../datasets/empty_with_walls.txt",
        "../datasets/empty.txt",
        "../datasets/inner_walls.txt"
    };
    const int files_count = 3;
    menu_level();
    int n = input_level();
    if (n <= files_count) {
        s = read_file(files[n - 1]);
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
    MOVE_CURSOR(s->prev_apple.y + 2 + 1, s->prev_apple.x * 2 + 3);
    printf(SPACE);
}

void print_apple(Snake *s) {
    MOVE_CURSOR(s->apple.y + 2 + 1, s->apple.x * 2 + 3);
    printf(APPLE);
}

void change_field(Snake *s) {
    erase_head(s);
    print_head(s);
    erase_tail(s);
    print_tail(s);
    erase_apple(s);
    print_apple(s);
    MOVE_CURSOR((int) (s->y + 4), 0);
    /*
        ! To apply changes to game field there are
        ! fflush(stdout) to put all printed symbols
        ! into stdout
    */
    fflush(stdout);
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

// Function to input chars without "Enter"
char getch() {
    char buf = 0;
    struct termios old = {0};
    // fflush(stdout);
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
    // old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    return buf;
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
    DISPLAY_GAME_NAME(GAME_NAME);
    printf("\n");
    // DISPLAY_STATUS_BAR(s->size, s->eaten_apples);
    // DISPLAY_SEPARATOR;
    // double speed = 1000000 / s->speed;
    // DISPLAY_SPEED(speed);
    print_wall(s);
    print_row(s);
    print_wall(s);
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
        usleep(s->speed);
        while (s->size != s->x * s->y) {
            if (controls(s)) {
                break;
            }
            int check = snake_add_head(s);
            if (check == 0)
                snake_remove_tail(s);
            else if (check == 2) {
                printf("\nOops, collision! Game over!");
                break;
            }
            else if (check == 1 && !is_win(s))
                generate_apple(s);
            // print_field(s);
            change_field(s);
            usleep(s->speed);
            if (is_win(s)) {
                printf("\nCongratulations! You won the game!");
                break;
            }
        }
        destroy_snake(s);
        usleep(500000);
    }
}

#include "reading.h"
#include "defines.h"
#include "snake.h"
#include "graphics.h"

#include <termios.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

// Allocating field
int **mem_alloc(size_t x, size_t y) {
    int **result = calloc(y, sizeof(int*));
    for (size_t i = 0; i < y; i++)
        result[i] = calloc(x, sizeof(int));
    return result;
}

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

int scan_f_size(FILE *f, size_t *x, size_t *y, int *c_input, int *input_count) {
    int check = 1;
    if (fscanf(f, "%zu %zu", x, y) != 2) {
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
    int check = 1;
    if (!fscanf(f, "%d", w) || (*w != 0 && *w != 1)) {
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
    int check = 1;
    if (fscanf(f, "%d %d", x, y) != 2 || *x < -1 || *x > 1 || *y < -1 || *y > 1) {
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
    int check = 1;
    if (!fscanf(f, "%d", snake_size) || (size_t) (*snake_size) > s->x * s->y || *snake_size < 0) {
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
    int check = 1;
    printf("%sReading snake segments\n", STATUS);
    int snake_check = 1;
    if (s->size == 0) {
        printf("  %sSnake size is 0, no segments to read\n", ERROR);
        snake_check = 0;
    }
    for (size_t i = 0; i < s->size; i++) {
        int p_x, p_y;
        if (fscanf(f, "%d %d", &p_x, &p_y) != 2 || (p_x < 0 || p_x > (int) (s->x - 1)) || (p_y < 0 || p_y > (int) (s->y - 1))) {
            check = 0;
            snake_check = 0;
            printf("  %sReading %zu segment\n", ERROR, i);
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
    int check = 1;
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
            if (!fscanf(f, "%d", &cord) || (cord != 0 && cord != 1)) {
                check = 0;
                field_check = 0;
                printf("  %sReading (%zu, %zu) coordinate\n", ERROR, j + 1, i + 1);
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

void valid_check(Snake **s, int check, int c_input, int input_count) {
    if (check && (c_input == input_count)) {
        generate_apple(*s);
    } else {
        destroy_snake(*s);
        *s = NULL;
    }
}

// Reading game settings from file
Snake *read_file(const char *file) {
    printf("\033[1;33m---------------\033[0m\t%sReading file...\n", STATUS);
    FILE *f = NULL;
    if (file)
        f = fopen(file, "r");
    Snake *s = NULL;
    int input_count = 6, c_input = 0;
    if (f) {
        int check = 1;
        s = init_snake();
        check &= scan_f_size(f, &s->x, &s->y, &c_input, &input_count);
        check &= scan_w_status(f, &s->walls, &c_input);
        int x, y;
        check &= scan_i_dir(f, &x, &y, &c_input);
        s->direction = create_point(x, y);
        int snake_size = -1;
        check &= scan_s_size(f, s, &snake_size, &c_input, &input_count);
        check &= scan_s_segments(f, s, &c_input);
        check &= scan_field(f, s, &c_input);
        fclose(f);
        CLOSING_FILE;
        valid_check(&s, check, c_input, input_count);
    } else {
        FILE_DOES_NOT_EXIST;
    }
    return s;
}

// Input level int
int input_level() {
    int result = 0;
    printf("Your choice: ");
    int check = scanf("%d", &result);
    while (getchar() != '\n') {}
    while (!check || (result < 1 || result > 6)) {
        printf("%sIncorrect input for %slevel number%s. Please, try again.\n", ERROR, BLUE, RESET);
        menu_level();
        printf("Your choice: ");
        check = scanf("%d", &result);
        while (getchar() != '\n') {}
    }
    return result;
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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "snake.h"

#define N 54
#define M 84

int **mem_alloc();
void mem_free(int **arr);
void move(snake *s, int direction);
void eat(snake *s);
int is_collision(snake *s, int **field);
void start_field(snake *s, int **field, int param);
void work();
int input_start_pos();
int control(int *status, int *direction);
void print_map(snake *s, int **field, int status);
int file_input(snake *s, int **field, char *file);

int main() {
    work();
    return 0;
}

// основная работяга
void work() {
    int **field = mem_alloc();
    snake s;
    int dir = 0, status = 0;
    start_field(&s, field, input_start_pos());
    while (!status) {
        control(&status, &dir);
        move(&s, dir);
        eat(&s);
        if (is_collision(&s, field))
            status = 1;
        print_map(&s, field, status);
        usleep(500000);
    }
}

/*
    Управление змейкой и игрой
    в целом
*/
int control(int *status, int *direction) {

}

/*
    Кирюха, сделай тут интерактивное
    меню кароч, чтобы можно было
    стрелочками передвигаться между
    пунктами меню, будет очень круто
    Типа каждый кадр - выбор одной
    из опций меню: настройки скорости,
    выбор опций типа можно ли проходить
    сквозь края, нужны ли препятствия и тд
*/

int file_input(snake *s, int **field, char *file) {
    int status = 1;
    FILE *f = fopen(file, "r");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++)
            if (!fscanf(f, "%d", &field[i][j])) {
                status = 0;
                i = N;
                break;
            } else {
                if (field[i][j] == 2) {
                    push_forward(s, i, j);
                }
            }
    }
    return status;
}

int input_start_pos() {
    int result;
    scanf("%d", &result);
    return result;
}

// выбоор стартового поля
void start_field(snake *s, int **field, int param) {
    char *file1 = "../datasets/1.txt";
    char *file2 = "../datasets/2.txt";
    char *file3 = "../datasets/3.txt";
    char *file4 = "../datasets/4.txt";
    char *file5 = "../datasets/5.txt";
    char *file6 = "../datasets/6.txt";
    switch (param) {
        case 1:
            file_input(s, field, file1);
            break;
        case 2:
            file_input(s, field, file2);
            break;
        case 3:
            file_input(s, field, file3);
            break;
        case 4:
            file_input(s, field, file4);
            break;
        case 5:
            file_input(s, field, file5);
            break;
        case 6:
            file_input(s, field, file6);
            break;
    }
}

// выделение памяти под поле
int **mem_alloc() {
    int **result = malloc(N * sizeof(int*));
    for (int i = 0; i < N; i++)
        result[i] = malloc(M * sizeof(int));
    return result;
}

// очистка памяти
void mem_free(int **arr) {
    for (int i = 0; i < N; i++)
        free(arr[i]);
    free(arr);
}

// движение змейки
void move(snake *s, int direction) {
    switch (direction) {
        case 0:
            move_snake(s, s->head->i + 1, s->head->j);
            break;
        case 1:
            move_snake(s, s->head->i, s->head->j + 1);
            break;
        case 2:
            move_snake(s, s->head->i - 1, s->head->j);
            break;
        case 3:
            move_snake(s, s->head->i, s->head->j - 1);
            break;
    }    
}

// поедание "яблока"
void eat(snake *s) {
    // что-нибудь придумать...
}

/*
    проверка столкновения со
    стеной или с самой змейкой
*/
int is_collision(snake *s, int **field) {
    int result = 0;
    if (field[s->head->i][s->head->j] == 1 || field[s->head->i][s->head->j] == 2)
        result = 1;
    return result;
}

// отрисовка поля
void print_map(snake *s, int **field, int status) {
    system("clear");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (field[i][j] == 1 || field[i][j] == 2) {
                printf("#");
            } else { printf(" "); }
        }
    printf("\n");
    }
}

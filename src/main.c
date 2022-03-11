#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define N 54
#define M 84

int **mem_alloc();
void mem_free(int **arr);
void move(int **field, int *hi, int *hj, int *ti, int *tj, int direction);
void eat(int **field, int *hi, int *hj, int *ti, int *tj, int *size);
int is_collision(int **field, int hi, int hj);
void start_field(int **field, int *hi, int *hj, int *ti, int *tj, int s);
void work();
int input_start_pos();
int control(int *status, int *direction);
void print_map(int **field, int status);
void file_input(int **field, int *hi, int *hj, int *ti, int *tj, char *file);

int main() {
    work();
    return 0;
}

// основная работяга
void work() {
    int **field = mem_alloc(), size = 4;
    int hi, hj, ti, tj, dir = 0, status = 0;
    start_field(field, &hi, &hj, &ti, &tj, input_start_pos());
    while (!status) {
        control(&status, &dir);
        move(field, &hi, &hj, &ti, &tj, dir);
        eat(field, &hi, &hj, &ti, &tj, &size);
        if (is_collision(field, hi, hj))
            status = 1;
        print_map(field, status);
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

void file_input(int **field, int *hi, int *hj, int *ti, int *tj, char *file) {
    FILE *f = fopen(file, "r");
    fscanf(f, "%d %d %d %d", hi, hj, ti, tj);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            fscanf(f, "%d", &field[i][j]);
}

int input_start_pos() {
    int result;
    scanf("%d", &result);
    return result;
}

// выбоор стартового поля
void start_field(int **field, int *hi, int *hj, int *ti, int *tj, int s) {
    char *file1 = "../datasets/1.txt";
    char *file2 = "../datasets/2.txt";
    char *file3 = "../datasets/3.txt";
    char *file4 = "../datasets/4.txt";
    char *file5 = "../datasets/5.txt";
    char *file6 = "../datasets/6.txt";
    switch (s) {
        case 1:
            file_input(field, hi, hj, ti, tj, file1);
            break;
        case 2:
            file_input(field, hi, hj, ti, tj, file2);
            break;
        case 3:
            file_input(field, hi, hj, ti, tj, file3);
            break;
        case 4:
            file_input(field, hi, hj, ti, tj, file4);
            break;
        case 5:
            file_input(field, hi, hj, ti, tj, file5);
            break;
        case 6:
            file_input(field, hi, hj, ti, tj, file6);
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
void move(int **field, int *hi, int *hj, int *ti, int *tj, int direction) {
    switch (direction) {
        case 0:
            *hj = (*hj + 1 + M) % M;
            break;
        case 1:
            *hi += (*hi + 1 + N) % N;
            break;
        case 2:
            *ti = (*ti - 1 + M) % M;
            break;
        case 3:
            *tj = (*tj - 1 + N) % N;
            break;
    }
    field[*hi][*hj] = 2;
    field[*ti][*tj] = 0;
    
}

// поедание "яблока"
void eat(int **field, int *hi, int *hj, int *ti, int *tj, int *size) {

}

/*
    проверка столкновения со
    стеной или с самой змейкой
*/
int is_collision(int **field, int hi, int hj) {
    int result = 0;
    if (field[hi][hj] == 1 || field[hi][hj] == 2)
        result = 1;
    return result;
}

// отрисовка поля
void print_map(int **field, int status) {
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

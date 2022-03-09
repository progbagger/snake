#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N 40
#define M 40

int **mem_alloc();
void mem_free(int **arr);
void move(int **field, int **head, int **tail, int direction);
void eat(int **field, int **head, int **tail, int *size);
int is_collision(int **field);
void start_field(int s);
void work();
void snake_start_pos(int **field, int **head, int **tail, int size);
int input_start_pos();
int control();

int main() {
    work();
    return 0;
}

// основная работяга
void work() {
    int **field = mem_alloc(), size = 4;
    int **head, **tail, status = 0;
    snake_start_pos(field, head, tail, size);
    start_field(input_start_pos());
    while (!status) {

    }
}

/*
    Управление змейкой и игрой
    в целом
*/
int control() {

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
int input_start_pos() {

}

// выбоор стартового поля
void start_field(int s) {

}

// стартовая позиция змейки
void snake_start_pos(int **field, int **head, int **tail, int size) {
    /*
        Пусть змейка стартует с середины
        по вертикали и чуть левее центра
        по горизонтали. Тогда стартовая
        координата головы по n будет n / 2,
        а по m примерно m / 2 - 5
    */
    *head = field[N / 2] + M / 2 - 5;
    **head = 1;
    for (int i = 1; i < size; i++)
        *(head[N / 2] - size) = 1;
    *tail = field[N / 2] + M / 2 - 5 - size + 1;
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
void move(int **field, int **head, int **tail, int direction) {
    switch (direction) {
        case 0:
            *(*head + 1) = 1;
            break;
        case 1:
            **(head + 1) = 1;
            break;
        case 2:
            *(*head - 1) = 1;
            break;
        case 3:
            **(head - 1) = 1;
            break;
    }
}

// поедание "яблока"
void eat(int **field, int **head, int **tail, int *size) {

}

/*
    проверка столкновения со
    стеной или с самой змейкой
*/
int is_collision(int **field) {

}

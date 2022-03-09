#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

const int n = 80, m = 80;

int **mem_alloc();
void mem_free(int **arr);
void move(int **field, int **head, int **tail, int direction, int prev_direction);
void eat(int **field, int **head, int **tail, int *size);
int is_collision(int **field);
void start_field(int s);
void work();
void snake_start_pos(int **field, int **head, int **tail, int size);

int main() {
    work();
}

// основная работяга
void work() {
    int **field = mem_alloc(), size = 4;
    int *head, *tail;
    snake_start_pos(field, &head, &tail, size);
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
    *head = field[n / 2] + m / 2 - 5;
    **head = 1;
    for (int i = 1; i < size; i++)
        *(head[n / 2] - size) = 1;
    *tail = field[n / 2] + m / 2 - 5 - size + 1;
}

// выделение памяти под поле
int **mem_alloc() {
    int **result = malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++)
        result[i] = malloc(m * sizeof(int));
    return result;
}

// очистка памяти
void mem_free(int **arr) {
    for (int i = 0; i < n; i++)
        free(arr[i]);
    free(arr);
}

// движение змейки
void move(int **field, int **head, int **tail, int direction, int prev_direction) {
    switch (direction) {
        case 0:
            if (prev_direction != 2)
                *(*head + 1) = 1;
            break;
        case 1:
            if (prev_direction != 3)
                **(head + 1) = 1;
            break;
        case 2:
            if (prev_direction != 0)
                *(*head - 1) = 1;
            break;
        case 3:
            if (prev_direction != 1)
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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

const int n = 80, m = 80;

int **mem_alloc(int n, int m);
void mem_free(int n);
void move(int **field);
void eat(int **field, int *size);
int is_collision(int **field);

int main() {

}

// выделение памяти под поле
int **mem_alloc(int n, int m) {

}

// очистка памяти
void mem_free(int n) {

}

// движение змейки
void move(int **field) {

}

// поедание "яблока"
void eat(int **field, int *size) {

}

/*
    проверка столкновения со
    стеной или с самой змейкой
*/
int is_collision(int **field) {

}

#ifndef SRC_DEFINES_H_
#define SRC_DEFINES_H_

#include "queue.h"

/*
    Errors and statuses
*/

#define ERROR "\033[1;31m[ ERROR ]\033[0m - "
#define SUCCESS "\033[1;32m[ SUCCESS ]\033[0m - "
#define STATUS "\033[1;33m[ STATUS ]\033[0m - "

#define GLOBAL_FILE_ERROR_MESSAGE printf("\033[1;31m--------------- %sFile does not read correctly.\
                                          \033[1;33mExiting...\033[0m\n", ERROR)
#define GLOBAL_FILE_SUCCESS_MESSAGE printf("\033[1;32m--------------- %sFile read correctly\n", SUCCESS)

#define CLOSING_FILE printf("\033[1;33m---------------\033[0m\t%sClosing file...\n", STATUS)
#define FILE_DOES_NOT_EXIST printf("\033[1;31m---------------\033[0m\t%sFile does not exist\n", ERROR)

#define EXIT_GAME printf("%s\033[1;33mExiting...\033[0m\n", STATUS)

/*
    Sides of possible snake turns
*/
#define RIGHT create_point(1, 0)
#define LEFT create_point(-1, 0)
#define FORWARD create_point(0, -1)
#define DOWN create_point(0, 1)

/*
    Colors to print in console
*/

#define RESET "\033[0m"
#define GREEN "\033[1;32m"
#define RED "\033[1;31m"
#define WHITE "\033[1;37m"
#define BLACK "\033[30;40m"
#define GRAY "\033[2;37m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"

/*
    Controls terminal output
*/

//--------------------------------Управление положением курсора--------->
 
    //    \033[#A передвинуть курсор вверх на # строк
    //    \033[#B передвинуть курсор вниз на # строк
    //    \033[#С передвинуть курсор вправо на # столбцов
    //    \033[#D передвинуть курсор влево на # столбцов
    //    \033[#E передвинуть курсор вниз на # строк и поставить в начало строки
    //    \033[#F передвинуть курсор вверх на # строк и поставить в начало строки
    //    \033[#G переместить курсор в указанный столбец текущей строки
    //    \033[#;#H задает абсолютные координаты курсора (строка, столбец)
    //    \033]2;BLA_BLA\007   Заголовок окна xterm...

#define CLEAR printf("\033[2J\033[1;1H")

// Moving cursor in terminal at i j coordinates
// depending on left upper corner
#define MOVE_CURSOR(i, j) printf("\033[%d;%dH", i, j)
#define MEMORISE_CURSOR printf("\033[s")
#define RETURN_CURSOR printf("\033[u")

/*
    Defines to beautificate and simplify
    future management of code
*/

#define WALLS "%s██%s", BLUE, RESET
#define EDGES "%s██%s", GRAY, RESET
#define SPACE "%s  %s", BLACK, RESET
#define APPLE "%s██%s", RED, RESET
#define SNAKE "%s██%s", GREEN, RESET
#define HEAD "%s██%s", YELLOW, RESET

/*
    Game statuses and display details
*/

#define GAME_NAME "Snake"

#define DISPLAY_STATUS_BAR(snake_size, apples) printf("%sSize:%s %s%-4lu%s %s|%s %sApples:%s %s%-4lu%s", \
BLUE, RESET, GREEN, snake_size, RESET, BLUE, RESET, BLUE, RESET, RED, apples, RESET)

#define DISPLAY_GAME_NAME(name) printf("%s%s%s", GREEN, name, RESET)
#define DISPLAY_SEPARATOR printf(" %s|%s ", BLUE, RESET)
#define DISPLAY_SPEED(speed) printf("%sSpeed:%s %s%-5.2lf%s ", BLUE, RESET, YELLOW, speed, RESET);\
                             printf("%scells/sec%s\n", BLUE, RESET)

#endif  // SRC_DEFINES_H_

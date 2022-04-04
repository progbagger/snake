#ifndef SRC_DEFINES_H_
#define SRC_DEFINES_H_

#include "queue.h"

/*
    Errors and statuses
*/

#define ERROR "\033[1;31m[ ERROR ]\033[0m - "
#define SUCCESS "\033[1;32m[ SUCCESS ]\033[0m - "
#define STATUS "\033[1;33m[ STATUS ]\033[0m - "

#define GLOBAL_FILE_ERROR_MESSAGE printf("\033[1;31m--------------- %sFile does not read correctly. \033[1;33mExiting...\033[0m\n", ERROR)
#define GLOBAL_FILE_SUCCESS_MESSAGE printf("\033[1;32m--------------- %sFile read correctly\n", SUCCESS)

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
#define GRAY "\033[1;37m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"

/*
    Defines to beautificate and simplify
    future management of code
*/

#define WALLS "%s██%s", BLUE, RESET
#define EDGES "%s░░%s", GRAY, RESET
#define SPACE "%s  %s", BLACK, RESET
#define APPLE "%s██%s", RED, RESET
#define SNAKE "%s██%s", GREEN, RESET
#define HEAD "%s██%s", YELLOW, RESET

#endif  // SRC_DEFINES_H_

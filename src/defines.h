#ifndef SRC_DEFINES_H_
#define SRC_DEFINES_H_

#include "queue.h"

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

/*
    Defines to beautificate and simplify
    future management of code
*/

#define WALLS "%s██%s", WHITE, RESET
#define EDGES "%s░░%s", GRAY, RESET
#define SPACE "%s  %s", BLACK, RESET
#define APPLE "%s██%s", RED, RESET
#define SNAKE "%s██%s", GREEN, RESET

#endif  // SRC_DEFINES_H_

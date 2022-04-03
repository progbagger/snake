#ifndef SRC_DEFINES_H_
#define SRC_DEFINES_H_

#include "queue.h"

#define RIGHT create_point(1, 0)
#define LEFT create_point(-1, 0)
#define FORWARD create_point(0, -1)
#define DOWN create_point(0, 1)

// Console colors

#define RESET "\033[0m"
#define GREEN "\033[1;32m"
#define RED "\033[1;31m"
#define WHITE "\033[1;37m"
#define BLACK "\033[30;40m"
#define GRAY "\033[1;37m"

#endif  // SRC_DEFINES_H_
/**
 * @file reading.h
 * @author thrixstudio@yandex.ru
 * @brief Functions to input game settings
 * @version 0.1
 * @date 2022-09-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef SRC_READING_H_
#define SRC_READING_H_

#include "snake.h"

char getch();
char *str_input();
int input_speed();
int input_level();

Snake *read_file(const char *file);

#endif  // SRC_READING_H_

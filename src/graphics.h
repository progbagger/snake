/**
 * @file graphics.h
 * @author thrixstudio@yandex.ru
 * @brief Functions to display game in the terminal window
 * @version 0.1
 * @date 2022-09-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef SRC_GRAPHICS_H_
#define SRC_GRAPHICS_H_

#include "snake.h"

void print_field(Snake *s);
void change_field(Snake *s);

void menu_level();
void menu_speed();

#endif  // SRC_GRAPHICS_H_

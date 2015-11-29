#ifndef MAP_H
#define MAP_H

#include <stdint.h>

void init_map();
void draw_map(uint32_t ** _p_table, int _length, int _width, int _coef);
void quit_map();
void sdl_pause();

#endif //MAP_H

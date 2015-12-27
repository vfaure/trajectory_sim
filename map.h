#ifndef MAP_H
#define MAP_H

#include <stdint.h>
#include <SDL/SDL.h>
#include "algo.h"
#include "table.h"

void init_map();
void draw_map(node_s ** _p_table, int _length, int _width, int _coef);
void quit_map();
void sdl_pause();

//TODO
//void drawPixel(SDL_Surface * _p_screen, Uint16 _x, Uint16 _y, Uint32 _color);
//void drawCircle(SDL_Surface * _p_screen, int _cx, int _cy, int radius); 

#endif //MAP_H

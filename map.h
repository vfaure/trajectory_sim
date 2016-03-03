#ifndef MAP_H
#define MAP_H

#include <stdint.h>
#include <SDL/SDL.h>
#include "algo.h"
#include "table.h"
#include "traces.h"

SDL_Surface* init_map(int _length, int _width, int _coef);
void draw_map(node_s ** _p_table, int _length, int _width, int _coef, SDL_Surface* screen);
void draw_unitary_surface(node_s _node, int _coef, SDL_Surface* _p_screen);
void quit_map();
void sdl_pause();

//TODO
//void drawPixel(SDL_Surface * _p_screen, Uint16 _x, Uint16 _y, Uint32 _color);
//void drawCircle(SDL_Surface * _p_screen, int _cx, int _cy, int radius); 

#endif //MAP_H

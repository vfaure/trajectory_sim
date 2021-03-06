#ifndef _TABLE_SDL_WRAPPER_H
#define _TABLE_SDL_WRAPPER_H

#include <stdint.h>

uint32_t** createTableSdl(int _length, int _width);
void setPointOccupied(uint32_t** _p_table, int _x, int _y);
void setRectangleOccupied(uint32_t** _p_table, int _xDimension, int _yDimension, int _xPosition, int _yPosition);
void setCircleOccupied(uint32_t** _p_table, int _xCenter, int _yCenter, int _radius);


#endif //_TABLE_SDL_WRAPPER_H

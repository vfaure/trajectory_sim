#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "table_sdl_wrapper.h"

uint32_t** createTableSdl(int _length, int _width)
{
    uint32_t** p_table = malloc(_length * sizeof(uint32_t));
    memset(p_table, 0, _length * sizeof(uint32_t));
    for (int i = 0; i < _length; i++)
    {
        p_table[i] = malloc(_width * sizeof(uint32_t));
        memset(p_table[i], 0, _width * sizeof(uint32_t));
    }
    return p_table;
}


void setPointOccupied(uint32_t** _p_table, int _x, int _y)
{
    //Security to avoid buffer overflow
    //TODO : Change Hard coded Value
    if((_x < 300) && (_y < 200) && (_x >= 0) && (_y >= 0))
        _p_table[_x][_y] = (uint8_t)1;
    //printf("x:%d, y:%d\n", _x, _y);
}

void setRectangleOccupied(uint32_t** _p_table, int _xDimension, int _yDimension, int _xPosition, int _yPosition)
{
    for(int x = _xPosition; x < _xDimension + _xPosition; x++)
    {
        for(int y = _yPosition ; y < _yDimension + _yPosition; y++)
        {
            setPointOccupied(_p_table, x, y);
        }   
    }
}

void setCircleOccupied(uint32_t ** _p_table, int _xCenter, int _yCenter, int _radius)
{
    double xMax = 0.0;
    for(int y = _yCenter; y < _yCenter + _radius; y++)
    {
        xMax = sqrt((float)_radius*(float)_radius - (float)(y-_yCenter)*(float)(y-_yCenter));
        //printf("x= %d, y= %d\n", (int)round(xMax), y);
        setRectangleOccupied(_p_table, (int)round(xMax), 1, _xCenter, y);
        setRectangleOccupied(_p_table, (int)round(xMax), 1, _xCenter - (int)round(xMax) , y);
        setRectangleOccupied(_p_table, (int)round(xMax), 1, _xCenter, 2*_yCenter - y - 1);
        setRectangleOccupied(_p_table, (int)round(xMax), 1, _xCenter - (int)round(xMax), 2*_yCenter - y - 1);
    }
}

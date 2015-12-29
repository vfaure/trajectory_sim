#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "table.h"

node_s** createTable(int _length, int _width)
{
    node_s** p_table = malloc(_length * sizeof(node_s));
    memset(p_table, 0, _length * sizeof(node_s));
    for (int i = 0; i < _length; i++)
    {
        p_table[i] = malloc(_width * sizeof(node_s));
        memset(p_table[i], 0, _width * sizeof(node_s));
    }
    return p_table;
}

void initialiseTable(node_s** _table, int _length, int _width)
{
    for(int i = 0; i < _length; i++)
    {
        for(int j = 0; j < _width; j++)
        {
            _table[i][j].x = i;
            _table[i][j].y = j;
        }
    }
}

void setPoint(node_s** _p_table, int _x, int _y, nodeType_e _nodeType)
{
    //Security to avoid buffer overflow
    //TODO : Change Hard coded Value
    if((_x < TABLE_LENGTH/GRID_SIZE) && (_y < TABLE_WIDTH/GRID_SIZE) && (_x >= 0) && (_y >= 0))
        _p_table[_x][_y].nodeType = _nodeType;
    //printf("x:%d, y:%d\n", _x, _y);
}

void setRectangle(node_s** _p_table, int _xDimension, int _yDimension, int _xPosition, int _yPosition, nodeType_e _nodeType)
{
    for(int x = _xPosition; x < _xDimension + _xPosition; x++)
    {
        for(int y = _yPosition ; y < _yDimension + _yPosition; y++)
        {
            setPoint(_p_table, x, y, _nodeType);
        }   
    }
}

void setCircle(node_s** _p_table, int _xCenter, int _yCenter, int _radius, nodeType_e _nodeType)
{
    double xMax = 0.0;
    for(int y = _yCenter; y < _yCenter + _radius; y++)
    {
        xMax = sqrt((float)_radius*(float)_radius - (float)(y-_yCenter)*(float)(y-_yCenter));
        //printf("x= %d, y= %d\n", (int)round(xMax), y);
        setRectangle(_p_table, (int)round(xMax), 1, _xCenter, y, _nodeType);
        setRectangle(_p_table, (int)round(xMax), 1, _xCenter - (int)round(xMax) , y, _nodeType);
        setRectangle(_p_table, (int)round(xMax), 1, _xCenter, 2*_yCenter - y - 1, _nodeType);
        setRectangle(_p_table, (int)round(xMax), 1, _xCenter - (int)round(xMax), 2*_yCenter - y - 1, _nodeType);
    }
}

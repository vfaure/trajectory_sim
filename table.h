#ifndef _TABLE_H
#define _TABLE_H

#include <stdint.h>
#include "algo.h"

#define GRID_SIZE 5
#define TABLE_LENGTH 300
#define TABLE_WIDTH 200
#define DYNAMIC_PRINTING 1

node_s** createTable(int _length, int _width);
void initialiseTable(node_s** _table, int _length, int _width);
void setPoint(node_s** _p_table, int _x, int _y, nodeType_e _nodeType);
void setRectangle(node_s** _p_table, int _xDimension, int _yDimension, int _xPosition, int _yPosition, nodeType_e _nodeType);
void setCircle(node_s** _p_table, int _xCenter, int _yCenter, int _radius, nodeType_e _nodeType);


#endif //_TABLE_H

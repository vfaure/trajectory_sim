#ifndef _ALGO_H
#define _ALGO_H

#include <stdint.h>
#include <stddef.h>
#include <SDL/SDL.h>
//#include "map.h"

typedef enum
{
    NEW_NODE = 0,
    OBSTACLE,
    CLOSED_LIST,
    FINAL_TRAJ,
    OPEN_LIST,
    ROBOT
}nodeType_e;

typedef struct
{
    uint8_t x;
    uint8_t y;
    uint8_t nodeType; //is a nodeType_e cast in uint8_t to be sure of the size
    float cost;
    uint8_t pX;
    uint8_t pY;
}node_s;

typedef struct list list_s;

struct list
{
    node_s* p_node;
    list_s* p_nextElement;
};

void startMainLoop(node_s** _p_table, SDL_Surface* _p_screen, int _coef);
void computeNode(list_s** _p_openList, node_s* _p_node, node_s* _p_parentNode);
void addToList(list_s** _p_list, node_s* _p_node);
int removeFromList(list_s* _p_list, node_s* _p_node);
float getDistance(node_s* _p_source, node_s* _p_dest);
uint8_t setStartNode(node_s** _p_table, uint16_t _x, uint16_t _y);
uint8_t setTargetNode(node_s** _p_table, uint16_t _x, uint16_t _y);
void getPath(node_s* _p_finalNode, node_s** _p_table, SDL_Surface* _p_screen);


#endif //_ALGO_H

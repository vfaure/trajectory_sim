#ifndef _ALGO_H
#define _ALGO_H

#include <stdint.h>
#include <stddef.h>

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
    uint32_t cost;
    uint8_t pX;
    uint8_t pY;
}node_s;

typedef struct list list_s;

struct list
{
    node_s* p_node;
    list_s* p_nextElement;
};

void dealWithNode(list_s* _p_openList, node_s* _p_node, node_s* _p_parentNode);
void addToList(list_s* _p_list, node_s* _p_node);
int removeFromList(list_s* _p_list, node_s* _p_node);
void setStartNode(node_s* _p_startNode);
void setTargetNode(node_s* _p_targetNode);
uint32_t getDistance(node_s source, node_s dest);


#endif //_ALGO_H

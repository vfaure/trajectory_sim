#include <stdio.h>
#include <stdlib.h>
#include "algo.h"
#include "table.h"
#include "traces.h"

//Start Node
static node_s* g_startNode = NULL; 
static node_s* g_targetNode = NULL;

//Main loop
void startMainLoop(node_s** _p_table)
{
    //Open list
    list_s* p_openList = NULL; 
    node_s* p_currentNode = g_startNode;
    p_currentNode->cost = getDistance(p_currentNode, g_targetNode);

    while(p_currentNode != g_targetNode)
    {
        //printf("current node x=%d, y=%d \n", p_currentNode->x, p_currentNode->y);
        //Treat adjacent node
        for(int i=p_currentNode->x-1; i<=p_currentNode->x+1; i++)
        {
            for(int j=p_currentNode->y-1; j<=p_currentNode->y+1; j++)
            {
                //printf("i=%d, j=%d\n", i, j);
                if((i>=0) && (j>=0) && (i<(TABLE_LENGTH/GRID_SIZE)) && (j<(TABLE_WIDTH/GRID_SIZE)) && ((i != p_currentNode->x) || (j!=p_currentNode->y)))
                {
                    computeNode(&p_openList, &_p_table[i][j], p_currentNode);
                }
            }
        }
        if(p_openList->p_node != NULL)
        {
            p_openList->p_node->nodeType = CLOSED_LIST;
            p_currentNode = p_openList->p_node;
            removeFromList(p_openList, p_openList->p_node);
        }
        else
        {
            printf("No solution!\n");
            break;
        }
    }
    
    getPath(p_currentNode, _p_table);
}

// square of the distance to use integer
uint32_t getDistance(node_s *_p_source, node_s *_p_dest)
{
    return ((_p_dest->y - _p_source->y)*(_p_dest->y - _p_source->y) + (_p_dest->x - _p_source->x)*(_p_dest->x - _p_source->x));
}

void addToList(list_s** _p_list, node_s* _p_node)
{
    //New element is created
    list_s* p_newElement = malloc(sizeof(list_s));
    p_newElement->p_node = _p_node;
    p_newElement->p_nextElement = NULL;
    
    //If the list is empty
    //printf("cout: %d\n", _p_node->cost);
    if(*_p_list == NULL)
    {
        *_p_list = p_newElement;
    }
    else
    {
        list_s* p_tmp = *_p_list;
        list_s* p_prec = NULL;
        while(_p_node->cost > p_tmp->p_node->cost)
        {
            // printf("cout: %d\n", p_tmp->p_node->cost);
            //getchar();
            p_prec = p_tmp;
            p_tmp = p_tmp->p_nextElement;
            if(p_tmp == NULL)
            {
                break;
            }
        }
        //First element of the list
        if(p_prec == NULL)
        {
            p_newElement->p_nextElement = *_p_list;
            *_p_list = p_newElement;
        }
        else
        {
            p_prec->p_nextElement = p_newElement;
            p_newElement->p_nextElement = p_tmp; 
        }
    }
}

int removeFromList(list_s* _p_list, node_s* _p_node)
{
    if(_p_list == NULL)
    {
        printf("List is empty");
        return -1;
    }
    else
    {
        list_s* p_tmp = _p_list;
        list_s* p_prec = NULL;
        while((p_tmp->p_node->x != _p_node->x) && (p_tmp->p_node->y != _p_node->y))
        {
            if(p_tmp->p_nextElement != NULL)
            {
                p_prec = p_tmp;
                p_tmp = p_tmp->p_nextElement; 
            }
            else
            {
                printf("Element not in the list\n");
                return -2;
            }
        }
        if(p_prec != NULL)
        {
            p_prec->p_nextElement = p_tmp->p_nextElement;
        }
        else
        {
            _p_list->p_node = p_tmp->p_nextElement->p_node;
            _p_list->p_nextElement = p_tmp->p_nextElement->p_nextElement;
        }
        //free(p_tmp);
    }
    return 0;
}

void computeNode(list_s** _p_openList, node_s* _p_node, node_s* _p_parentNode)
{
    //printf("Node type = %d\n", _p_node->nodeType);//Do nothing for all other cases
    if(_p_node->nodeType == NEW_NODE)
    {
        _p_node->pX = _p_parentNode->x;
        _p_node->pY = _p_parentNode->y;
        _p_node->nodeType = OPEN_LIST;
        _p_node->cost = (_p_parentNode->cost - getDistance(_p_parentNode, g_targetNode)) + getDistance(_p_parentNode, _p_node) + getDistance(_p_node, g_targetNode);
        addToList(_p_openList, _p_node);
    }
    else if(_p_node->nodeType == OPEN_LIST)
    {
        if((_p_parentNode->cost - getDistance(_p_parentNode, g_targetNode)) + getDistance(_p_parentNode, _p_node) + getDistance(_p_node, g_targetNode) < _p_node->cost)
        {
            _p_node->cost = (_p_parentNode->cost - getDistance(_p_parentNode, g_targetNode)) + getDistance(_p_parentNode, _p_node) + getDistance(_p_node, g_targetNode);
            _p_node->pX = _p_parentNode->x;
            _p_node->pY = _p_parentNode->y;
            addToList(_p_openList, _p_node);
        }
    }
    else
        ;//Do nothing for all other cases
}

void getPath(node_s*_p_finalNode, node_s** p_table)
{
    //printf("x=%d y=%d\n",_p_finalNode->x, _p_finalNode->y);
    while((_p_finalNode->x !=  g_startNode->x) || (_p_finalNode->y != g_startNode->y))
    {
        TRACE_DEBUG("px= %d, py= %d\n", _p_finalNode->pX, _p_finalNode->pY);
        _p_finalNode->nodeType = FINAL_TRAJ; 
        _p_finalNode = &p_table[_p_finalNode->pX][_p_finalNode->pY];
    }
    _p_finalNode->nodeType = FINAL_TRAJ; 
}

uint8_t setStartNode(node_s** _p_table, uint8_t _x, uint8_t _y)
{
    if(_p_table[_x][_y].nodeType != OBSTACLE)
    {
        g_startNode = &_p_table[_x][_y];
        return 0;
    }
    else
    {
        printf("Starting point is an obstacle");
        return 1;
    }
}

uint8_t setTargetNode(node_s** _p_table, uint8_t _x, uint8_t _y)
{
    if(_p_table[_x][_y].nodeType != OBSTACLE)
    {
        g_targetNode = &_p_table[_x][_y];
        return 0;
    }
    else
    {
        printf("Target point is an obstacle");
        return 1;
    }
}

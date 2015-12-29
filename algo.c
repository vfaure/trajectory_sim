#include <stdio.h>
#include <stdlib.h>
#include "algo.h"
#include "table.h"

// square of the idstance to use integer
uint32_t getDistance(node_s _source, node_s _dest)
{
    return ((_dest.y - _source.y)*(_dest.y - _source.y) + (_dest.x - _source.x)*(_dest.x - _source.x));
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
            //printf("cout: %d\n", p_tmp->p_node->cost);
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

void dealWithNode(list_s** _p_openList, node_s* _p_node, node_s* _p_parentNode, node_s* _p_targetNode)
{
    //printf("Node type = %d\n", _p_node->nodeType);//Do nothing for all other cases
    if(_p_node->nodeType == NEW_NODE)
    {
        _p_node->pX = _p_parentNode->x;
        _p_node->pY = _p_parentNode->y;
        _p_node->nodeType = OPEN_LIST;
        _p_node->cost = (_p_parentNode->cost - getDistance(*_p_parentNode, *_p_targetNode)) + getDistance(*_p_parentNode, *_p_node) + getDistance(*_p_node, *_p_targetNode);
        addToList(_p_openList, _p_node);
    }
    else if(_p_node->nodeType == OPEN_LIST)
    {
        if((_p_parentNode->cost - getDistance(*_p_parentNode, *_p_targetNode)) + getDistance(*_p_parentNode, *_p_node) + getDistance(*_p_node, *_p_targetNode) < _p_node->cost)
        {
            _p_node->cost = (_p_parentNode->cost - getDistance(*_p_parentNode, *_p_targetNode)) + getDistance(*_p_parentNode, *_p_node) + getDistance(*_p_node, *_p_targetNode);
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
    while((_p_finalNode->x != (TABLE_LENGTH/GRID_SIZE)/2) || (_p_finalNode->y != 0))
    {
        //printf("px= %d, py= %d\n", _p_finalNode->pX, _p_finalNode->pY);
        _p_finalNode->nodeType = FINAL_TRAJ; 
        _p_finalNode = &p_table[_p_finalNode->pX][_p_finalNode->pY];
    }
    _p_finalNode->nodeType = FINAL_TRAJ; 
}

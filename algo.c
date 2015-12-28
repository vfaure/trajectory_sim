#include <stdio.h>
#include "algo.h"

// square of the idstance to use integer
uint32_t getDistance(node_s _source, node_s _dest)
{
    return ((_dest.y - _source.y)*(_dest.y - _source.y) + (_dest.x - _source.x)*(_dest.x - _source.x));
}

void addToList(list_s* _p_list, node_s* _p_node)
{
    //If the list is empty
    if(_p_list == NULL)
    {
        _p_list->p_node = _p_node;
        _p_list->p_nextElement = NULL;
    }
    else
    {
        list_s* p_tmp = _p_list;
        list_s* p_prec = NULL;
        while(_p_node->cost > p_tmp->p_node->cost)
        {
            p_prec = p_tmp;
            p_tmp = p_tmp->p_nextElement;
            if(p_tmp == NULL)
                break;
        }
        if(p_prec == NULL)
        {
            _p_list->p_node = _p_node;
            _p_list->p_nextElement = p_tmp;
        }
        else
        {
            p_prec->p_nextElement->p_node = _p_node;
            p_prec->p_nextElement->p_nextElement = p_tmp; 
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
    }
    return 0;
}

void dealWithNode(list_s* _p_openList, node_s* _p_node, node_s* _p_parentNode)
{
    printf("Node type = %d\n", _p_node->nodeType);//Do nothing for all other cases
    if(_p_node->nodeType == NEW_NODE)
    {
        _p_node->pX = _p_parentNode->x;
        _p_node->pY = _p_parentNode->y;
        _p_node->nodeType = OPEN_LIST;
        _p_node->cost = _p_parentNode->cost + getDistance(*_p_parentNode, *_p_node);
        addToList(_p_openList, _p_node);
    }
    else if(_p_node->nodeType == OPEN_LIST)
    {
        if(_p_parentNode->cost + getDistance(*_p_parentNode, *_p_node) < _p_node->cost)
        {
            _p_node->cost = _p_parentNode->cost + getDistance(*_p_parentNode, *_p_node);
            _p_node->pX = _p_parentNode->x;
            _p_node->pY = _p_parentNode->y;
        }
    }
    else
        ;//Do nothing for all other cases
}



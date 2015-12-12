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
        _p_list->node = _p_node;
        _p_list->p_nextElement = NULL;
    }
    else
    {
        //Cost
    }
}

void removeFromList(list_s* _p_list, node_s* node)
{
    if(_p_list == NULL)
    {
        printf("List is empty");
    }
}

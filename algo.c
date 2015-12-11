#include "algo.h"

// square of the idstance to use integer
uint32_t getDistance(node_s _source, node_s _dest)
{
    return ((_dest.y - _source.y)^2 + (_dest.x - _source.x)^2);
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
        ; //Add to list 
    }
}

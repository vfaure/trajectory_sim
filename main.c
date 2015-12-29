#include <stdio.h>
#include <stdlib.h>

#include "map.h"
#include "table.h"
#include "algo.h"

int main(int argc, const char* argv[])
{
    //Create the table
    node_s ** p_table = NULL;
    //memory allocation
    p_table = createTable(TABLE_LENGTH/GRID_SIZE , TABLE_WIDTH/GRID_SIZE);
    
    //initialize the table
    initialiseTable(p_table, TABLE_LENGTH/GRID_SIZE, TABLE_WIDTH/GRID_SIZE);
    
    //Fill the table
    
    // ARound the dune
    setRectangle(p_table, 2/GRID_SIZE, 20/GRID_SIZE, 80/GRID_SIZE, 0/GRID_SIZE, OBSTACLE);
    setRectangle(p_table, 2/GRID_SIZE, 20/GRID_SIZE, 220/GRID_SIZE, 0/GRID_SIZE, OBSTACLE);
    
    //Central T (construction area)
    setRectangle(p_table, 120/GRID_SIZE, 2/GRID_SIZE, 90/GRID_SIZE, 75/GRID_SIZE, OBSTACLE);
    setRectangle(p_table, 6/GRID_SIZE, 60/GRID_SIZE, 147/GRID_SIZE, 75/GRID_SIZE, OBSTACLE);
    
    //iles
    setCircle(p_table, 0/GRID_SIZE, 199/GRID_SIZE, 25/GRID_SIZE, OBSTACLE); 
    setCircle(p_table, 299/GRID_SIZE, 199/GRID_SIZE, 25/GRID_SIZE, OBSTACLE); 

    //Open list
    list_s* p_openList = NULL; 
    node_s* p_currentNode = &p_table[75][0];

    while(p_currentNode != &p_table[149][2])
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
                    dealWithNode(&p_openList, &p_table[i][j], p_currentNode, &p_table[149][2]);
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
    
    getPath(p_currentNode, p_table);

    init_map();
    draw_map(p_table, TABLE_LENGTH/GRID_SIZE, TABLE_WIDTH/GRID_SIZE, 2);
    sdl_pause();
    quit_map();
    return EXIT_SUCCESS;
}


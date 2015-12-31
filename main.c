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

    setStartNode(p_table, 0, 50);
    setTargetNode(p_table, 149, 50);
    //setStartNode(p_table, 75, 0);
    //setTargetNode(p_table, 75, 4);
    startMainLoop(p_table);

    init_map();
    draw_map(p_table, TABLE_LENGTH/GRID_SIZE, TABLE_WIDTH/GRID_SIZE, 2);
    sdl_pause();
    quit_map();
    return EXIT_SUCCESS;
}


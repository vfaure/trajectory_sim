#include <stdio.h>
#include <stdlib.h>

#include "map.h"
#include "table.h"
#include "algo.h"

int main(int argc, const char* argv[])
{
    //Create the table
    node_s ** p_table = NULL;
    p_table = createTable(150, 100);
    
    //Fill the table
    setRectangle(p_table, 2/2, 20/2, 80/2, 0, OBSTACLE);
    setRectangle(p_table, 2/2, 20/2, 220/2, 0, OBSTACLE);
    
    setRectangle(p_table, 120/2, 2/2, 90/2, 75/2, OBSTACLE);
    setRectangle(p_table, 6/2, 60/2, 147/2, 75/2, OBSTACLE);
    
    setCircle(p_table, 0/2, 199/2, 25/2, OBSTACLE); 
    setCircle(p_table, 299/2, 199/2, 25/2, OBSTACLE); 

    //init_map();
    //draw_map(p_table, 300, 200, 2);
    //sdl_pause();
    //quit_map();
    return EXIT_SUCCESS;
}


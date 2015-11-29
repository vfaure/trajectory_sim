#include <stdio.h>
#include <stdlib.h>

#include "map.h"
#include "table.h"

int main(int argc, const char* argv[])
{
    //Create the table
    uint32_t ** p_table = NULL;
    p_table = createTable(300, 200);
    
    //Fill the table
    setRectangleOccupied(p_table, 2, 20, 80, 0);
    setRectangleOccupied(p_table, 2, 20, 220, 0);
    
    setRectangleOccupied(p_table, 120, 2, 90, 75);
    setRectangleOccupied(p_table, 6, 60, 147, 75);
    
    setCircleOccupied(p_table, 0, 199, 25); 
    setCircleOccupied(p_table, 299, 199, 25); 

    init_map();
    draw_map(p_table, 300, 200, 2);
    sdl_pause();
    quit_map();
    return EXIT_SUCCESS;
}


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "map.h"
#include "table.h"
#include "algo.h"

int main(int argc, const char* argv[])
{
    if(argc != 5)
        return EXIT_FAILURE;
            
    SDL_Surface* p_screen = init_map(TABLE_LENGTH/GRID_SIZE, TABLE_WIDTH/GRID_SIZE, 2);
    //Create the table
    node_s ** p_table = NULL;
    //memory allocation
    p_table = createTable(TABLE_LENGTH/GRID_SIZE , TABLE_WIDTH/GRID_SIZE);
    
    //initialize the table
    initialiseTable(p_table, TABLE_LENGTH/GRID_SIZE, TABLE_WIDTH/GRID_SIZE);
  
    uint16_t robot_length = 30;
    uint16_t robot_width = 30;    
    uint16_t half_diag = (uint16_t) (sqrtf((robot_length * robot_length) + (robot_width * robot_width)) / 2) + GRID_SIZE;
    uint8_t grid_half_diag = half_diag / GRID_SIZE;
   
    //Fill the table
    //expand walls
    setRectangle(p_table, TABLE_LENGTH / GRID_SIZE, grid_half_diag, 0, 0, SOFT_OBSTACLE);  
    setRectangle(p_table, TABLE_LENGTH / GRID_SIZE, grid_half_diag, 0, TABLE_WIDTH/GRID_SIZE - grid_half_diag, SOFT_OBSTACLE);  
    setRectangle(p_table, grid_half_diag, TABLE_WIDTH / GRID_SIZE, 0, 0, SOFT_OBSTACLE);
    setRectangle(p_table, grid_half_diag, TABLE_WIDTH / GRID_SIZE, TABLE_LENGTH / GRID_SIZE - grid_half_diag, 0, SOFT_OBSTACLE);

    // ARound the dune
    setRectangle(p_table, (2 + half_diag * 2)/GRID_SIZE, 20/GRID_SIZE, (80 - half_diag)/GRID_SIZE, 0/GRID_SIZE, SOFT_OBSTACLE);
    setCircle(p_table, 81/GRID_SIZE, 20/GRID_SIZE, (half_diag + 1) / GRID_SIZE, SOFT_OBSTACLE);
    setRectangle(p_table, (2 + half_diag * 2)/GRID_SIZE, 20/GRID_SIZE, (220 - half_diag)/GRID_SIZE, 0/GRID_SIZE, SOFT_OBSTACLE);
    setCircle(p_table, 221/GRID_SIZE, 20/GRID_SIZE, (half_diag + 1) / GRID_SIZE, SOFT_OBSTACLE);

    setRectangle(p_table, 2/GRID_SIZE, 20/GRID_SIZE, 80/GRID_SIZE, 0/GRID_SIZE, OBSTACLE);
    setRectangle(p_table, 2/GRID_SIZE, 20/GRID_SIZE, 220/GRID_SIZE, 0/GRID_SIZE, OBSTACLE);
    
    //Central T (construction area)
    setRectangle(p_table, 120/GRID_SIZE, (2 + half_diag *2)/GRID_SIZE, 90/GRID_SIZE, (75 - half_diag + GRID_SIZE)/GRID_SIZE, SOFT_OBSTACLE);
    setCircle(p_table, 90/GRID_SIZE, 76/GRID_SIZE, (half_diag + 1) / GRID_SIZE, SOFT_OBSTACLE);
    setCircle(p_table, 210/GRID_SIZE, 76/GRID_SIZE, (half_diag + 1) / GRID_SIZE, SOFT_OBSTACLE);
    setRectangle(p_table, (5 + half_diag * 2)/GRID_SIZE, 60/GRID_SIZE, (147 - half_diag)/GRID_SIZE, 75/GRID_SIZE, SOFT_OBSTACLE);
    setCircle(p_table, 150/GRID_SIZE, 135/GRID_SIZE, (half_diag + 2) / GRID_SIZE, SOFT_OBSTACLE);

    setRectangle(p_table, 120/GRID_SIZE, 2/GRID_SIZE, 90/GRID_SIZE, 75/GRID_SIZE, OBSTACLE);
    setRectangle(p_table, 6/GRID_SIZE, 60/GRID_SIZE, 147/GRID_SIZE, 75/GRID_SIZE, OBSTACLE);
    
    //iles
    setCircle(p_table, 0/GRID_SIZE, 199/GRID_SIZE, 25/GRID_SIZE, OBSTACLE); 
    setCircle(p_table, 299/GRID_SIZE, 199/GRID_SIZE, 25/GRID_SIZE, OBSTACLE); 

    if(!setStartNode(p_table, atoi(argv[1]), atoi(argv[2])))
        if(!setTargetNode(p_table, atoi(argv[3]), atoi(argv[4])))
            startMainLoop(p_table, p_screen, 2);

    draw_map(p_table, TABLE_LENGTH/GRID_SIZE, TABLE_WIDTH/GRID_SIZE, 2, p_screen);
    sdl_pause();
    quit_map();
    return EXIT_SUCCESS;
}


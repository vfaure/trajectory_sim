#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "map.h"
#include "table.h"
#include "algo.h"

int main(int argc, const char* argv[])
{
    if(argc != 2)
        return EXIT_FAILURE;
            
    SDL_Surface* p_screen = init_map(TABLE_LENGTH/GRID_SIZE, TABLE_WIDTH/GRID_SIZE, 2);
    //Create the table
    node_s ** p_table = NULL;
    //memory allocation
    p_table = createTable(TABLE_LENGTH/GRID_SIZE , TABLE_WIDTH/GRID_SIZE);
    
    //initialize the table
    initialiseTable(p_table, TABLE_LENGTH/GRID_SIZE, TABLE_WIDTH/GRID_SIZE);
  
    FILE* f = fopen(argv[1], "r");
    if(f != NULL)
    {
        uint16_t value = 0;
        for(int i = 0; i < TABLE_LENGTH/GRID_SIZE; i++)
        {
            for(int j = 0; j < TABLE_WIDTH/GRID_SIZE; j++)
            {
                fread(&value, sizeof(uint16_t), 1, f);
                p_table[i][j].nodeType = value;
            }
        }
    }

    draw_map(p_table, TABLE_LENGTH/GRID_SIZE, TABLE_WIDTH/GRID_SIZE, 2, p_screen);
    sdl_pause();
    quit_map();
    return EXIT_SUCCESS;
}


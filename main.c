#include <stdio.h>
#include <stdlib.h>

#include "map.h"


int main(int argc, const char* argv[])
{
    printf("HelloWorld!\n");
    init_map();
    draw_map();
    sdl_pause();
    quit_map();
    return EXIT_SUCCESS;
}


#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>

#include "map.h"

void init_map()
{
    printf("Init map\n");
    if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
}

void draw_map(uint32_t** _p_table, int _length, int _width, int _coef)
{
    printf("Draw map\n");
    
    //Draw the table
    SDL_Surface *screen = NULL;
    screen = SDL_SetVideoMode(_length*_coef, _width*_coef, 32, SDL_HWSURFACE);
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 237, 232, 102));
    
    //Set occupancy grid
    SDL_Surface* unitarySurface =  SDL_CreateRGBSurface(SDL_HWSURFACE, _coef, _coef, 32, 0, 0, 0, 0);
    SDL_Rect unitarySurfacePosition;
    for(int x = 0; x < _length; x++)
    {
        for(int y = 0; y < _width; y++)
        {
            if(_p_table[x][y])
            {
                //draw occupied
                SDL_FillRect(unitarySurface, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
                unitarySurfacePosition.x = x * _coef;
                unitarySurfacePosition.y = y * _coef;     
                SDL_BlitSurface(unitarySurface, NULL, screen, &unitarySurfacePosition);
            }
        }
    }
    SDL_Flip(screen);
}

void quit_map()
{
    printf("quit map\n");
    SDL_Quit();
}

void sdl_pause()
{
    int continuer = 1;
    SDL_Event event;


    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
        }
    }
}

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>

#include "map.h"

void init_map()
{
    printf("Init map");
    if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
}

void draw_map()
{
    printf("Draw map");
    //Main surface
    SDL_Surface *screen = NULL;
    screen = SDL_SetVideoMode(600, 400, 32, SDL_HWSURFACE);
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 17, 206, 112));
    SDL_Flip(screen);

}

void quit_map()
{
    printf("quit map");
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

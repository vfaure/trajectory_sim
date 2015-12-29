#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_draw.h>

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

void draw_map(node_s** _p_table, int _length, int _width, int _coef)
{
    printf("Draw map\n");
    
    //Draw the table
    SDL_Surface *screen = NULL;
    screen = SDL_SetVideoMode(_length*_coef*GRID_SIZE, _width*_coef*GRID_SIZE, 32, SDL_HWSURFACE);
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 237, 232, 102));
    
    //Blue = sea
    //SDL_Surface* surface = SDL_CreateRGBSurface(SDL_HWSURFACE, 600, 160, 32, 0, 0, 0, 0);
    SDL_Surface* surface = SDL_CreateRGBSurface(SDL_HWSURFACE, 600, 100, 32, 0, 0, 0, 0);
    SDL_FillRect(surface, NULL, SDL_MapRGB(screen->format, 90, 147, 174));
    SDL_Rect pos;
    pos.x = 0;
    //pos.y = 240;
    pos.y = 300;
    SDL_BlitSurface(surface , NULL, screen, &pos);
    SDL_FreeSurface(surface); 
    surface = SDL_CreateRGBSurface(SDL_HWSURFACE, 120, 60, 32, 0, 0, 0, 0);
    SDL_FillRect(surface, NULL, SDL_MapRGB(screen->format, 90, 147, 174));
    pos.x = 0;
    pos.y = 240;
    SDL_BlitSurface(surface , NULL, screen, &pos);
    pos.x = 480;
    pos.y = 240;
    SDL_BlitSurface(surface , NULL, screen, &pos);
    SDL_FreeSurface(surface); 
    //Draw_FillCircle(screen, 150, 35, 115, SDL_MapRGB(screen->format, 237, 232, 102)); 
    //Draw_FillCircle(screen, 150, 35, 40, SDL_MapRGB(screen->format, 237, 232, 0)); 
    
    //start purple
    surface = SDL_CreateRGBSurface(SDL_HWSURFACE, 60, 100, 32, 0, 0, 0, 0);
    SDL_FillRect(surface, NULL, SDL_MapRGB(screen->format, 145, 94, 192));
    pos.x = 0;
    pos.y = 120;
    SDL_BlitSurface(surface , NULL, screen, &pos);

    //start green
    SDL_FillRect(surface, NULL, SDL_MapRGB(screen->format, 72, 205, 82));
    pos.x = 540;
    pos.y = 120;
    SDL_BlitSurface(surface , NULL, screen, &pos);
    SDL_FreeSurface(surface); 

    //White stripes on starting zone
    surface = SDL_CreateRGBSurface(SDL_HWSURFACE, 60, 10, 32, 0, 0, 0, 0);
    SDL_FillRect(surface, NULL, SDL_MapRGB(screen->format, 255, 255, 255));
    
    pos.x = 0;
    pos.y = 130;
    SDL_BlitSurface(surface , NULL, screen, &pos);
    
    pos.x = 0;
    pos.y = 200;
    SDL_BlitSurface(surface , NULL, screen, &pos);

    pos.x = 540;
    pos.y = 130;
    SDL_BlitSurface(surface , NULL, screen, &pos);
    
    pos.x = 540;
    pos.y = 200;
    SDL_BlitSurface(surface , NULL, screen, &pos);


    //Set occupancy grid
    SDL_Surface* unitarySurface =  SDL_CreateRGBSurface(SDL_HWSURFACE, _coef*GRID_SIZE, _coef*GRID_SIZE, 32, 0, 0, 0, 0);
    SDL_Rect unitarySurfacePosition;
    for(int x = 0; x < _length; x++)
    {
        for(int y = 0; y < _width; y++)
        {
            //printf("x= %d, y= %d \n", x, y);
            if(_p_table[x][y].nodeType == OBSTACLE)
            {
                //draw occupied
                SDL_FillRect(unitarySurface, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
                unitarySurfacePosition.x = x * _coef* GRID_SIZE;
                unitarySurfacePosition.y = y * _coef* GRID_SIZE;     
                SDL_BlitSurface(unitarySurface, NULL, screen, &unitarySurfacePosition);
            }
            if(_p_table[x][y].nodeType == OPEN_LIST)
            {
                //draw OPEN_LIST
                SDL_FillRect(unitarySurface, NULL, SDL_MapRGB(screen->format, 248, 168, 15));
                unitarySurfacePosition.x = x * _coef* GRID_SIZE;
                unitarySurfacePosition.y = y * _coef* GRID_SIZE;     
                SDL_BlitSurface(unitarySurface, NULL, screen, &unitarySurfacePosition);
            }
            if(_p_table[x][y].nodeType == CLOSED_LIST)
            {
                //draw CLOSED_LIST
                SDL_FillRect(unitarySurface, NULL, SDL_MapRGB(screen->format, 244, 18, 7));
                unitarySurfacePosition.x = x * _coef* GRID_SIZE;
                unitarySurfacePosition.y = y * _coef* GRID_SIZE;     
                SDL_BlitSurface(unitarySurface, NULL, screen, &unitarySurfacePosition);
            }
            if(_p_table[x][y].nodeType == FINAL_TRAJ)
            {
                //draw FINAL_TRAJ
                SDL_FillRect(unitarySurface, NULL, SDL_MapRGB(screen->format, 13, 183, 0));
                unitarySurfacePosition.x = x * _coef* GRID_SIZE;
                unitarySurfacePosition.y = y * _coef* GRID_SIZE;     
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

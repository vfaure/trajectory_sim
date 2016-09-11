#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>

#include "map.h"

SDL_Surface* init_map(int _length, int _width, int _coef)
{
    TRACE_INFO("Init map\n");
    if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        TRACE_ERR("Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

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

    SDL_Flip(screen);

    return screen;
}

void draw_map(node_s** _p_table, int _length, int _width, int _coef, SDL_Surface* screen)
{
    TRACE_INFO("Draw map\n");

    //Set occupancy grid
    SDL_Surface* unitarySurface =  SDL_CreateRGBSurface(SDL_HWSURFACE, _coef*GRID_SIZE, _coef*GRID_SIZE, 32, 0, 0, 0, 0);
    SDL_Rect unitarySurfacePosition;
    for(int x = 0; x < _length; x++)
    {
        for(int y = 0; y < _width; y++)
        {
            //printf("x= %d, y= %d \n", x, y);
            if((_p_table[x][y].nodeType & OPEN_LIST) == OPEN_LIST)
            {
                //draw OPEN_LIST
                SDL_FillRect(unitarySurface, NULL, SDL_MapRGB(screen->format, 248, 168, 15));
                unitarySurfacePosition.x = x * _coef* GRID_SIZE;
                unitarySurfacePosition.y = y * _coef* GRID_SIZE;     
                SDL_BlitSurface(unitarySurface, NULL, screen, &unitarySurfacePosition);
            }
            else if((_p_table[x][y].nodeType & CLOSED_LIST) == CLOSED_LIST)
            {
                //draw CLOSED_LIST
                SDL_FillRect(unitarySurface, NULL, SDL_MapRGB(screen->format, 244, 18, 7));
                unitarySurfacePosition.x = x * _coef* GRID_SIZE;
                unitarySurfacePosition.y = y * _coef* GRID_SIZE;     
                SDL_BlitSurface(unitarySurface, NULL, screen, &unitarySurfacePosition);
            }
            else if((_p_table[x][y].nodeType & FINAL_TRAJ) == FINAL_TRAJ)
            {
                //draw FINAL_TRAJ
                SDL_FillRect(unitarySurface, NULL, SDL_MapRGB(screen->format, 13, 183, 0));
                unitarySurfacePosition.x = x * _coef* GRID_SIZE;
                unitarySurfacePosition.y = y * _coef* GRID_SIZE;     
                SDL_BlitSurface(unitarySurface, NULL, screen, &unitarySurfacePosition);
            }
            else if((_p_table[x][y].nodeType & ROBOT) == ROBOT)
            {
                //draw ROBOT
                SDL_FillRect(unitarySurface, NULL, SDL_MapRGB(screen->format, 154, 0, 126));
                unitarySurfacePosition.x = x * _coef* GRID_SIZE;
                unitarySurfacePosition.y = y * _coef* GRID_SIZE;     
                SDL_BlitSurface(unitarySurface, NULL, screen, &unitarySurfacePosition);
            }
            else if((_p_table[x][y].nodeType & TEMPORARY_ALLOWED) == TEMPORARY_ALLOWED)
            {
                //draw TEMPORARY_ALLOWED
                //SDL_FillRect(unitarySurface, NULL, SDL_MapRGB(screen->format, 13, 183, 0));
                //unitarySurfacePosition.x = x * _coef* GRID_SIZE;
                //unitarySurfacePosition.y = y * _coef* GRID_SIZE;     
                //SDL_BlitSurface(unitarySurface, NULL, screen, &unitarySurfacePosition);
            }
            else if(_p_table[x][y].nodeType == OBSTACLE)
            {
                //draw occupied
                SDL_FillRect(unitarySurface, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
                unitarySurfacePosition.x = x * _coef* GRID_SIZE;
                unitarySurfacePosition.y = y * _coef* GRID_SIZE;     
                SDL_BlitSurface(unitarySurface, NULL, screen, &unitarySurfacePosition);
            }
            else if(_p_table[x][y].nodeType == FORBIDDEN)
            {
                //draw Soft_obstacle
                SDL_FillRect(unitarySurface, NULL, SDL_MapRGB(screen->format, 28, 28, 28));
                unitarySurfacePosition.x = x * _coef* GRID_SIZE;
                unitarySurfacePosition.y = y * _coef* GRID_SIZE;     
                SDL_BlitSurface(unitarySurface, NULL, screen, &unitarySurfacePosition);
            }
            else if(_p_table[x][y].nodeType == SOFT_OBSTACLE)
            {
                //draw Soft_obstacle
                SDL_FillRect(unitarySurface, NULL, SDL_MapRGB(screen->format, 121, 121, 121));
                unitarySurfacePosition.x = x * _coef* GRID_SIZE;
                unitarySurfacePosition.y = y * _coef* GRID_SIZE;     
                SDL_BlitSurface(unitarySurface, NULL, screen, &unitarySurfacePosition);
            }
        }
    }
    SDL_Flip(screen);
}

void draw_unitary_surface(node_s _node, int _coef, SDL_Surface* _p_screen)
{
    //Set occupancy grid
    SDL_Surface* unitarySurface =  SDL_CreateRGBSurface(SDL_HWSURFACE, _coef*GRID_SIZE, _coef*GRID_SIZE, 32, 0, 0, 0, 0);
    SDL_Rect unitarySurfacePosition;
    
    if(_node.nodeType == OBSTACLE)
    {
        //draw occupied
        SDL_FillRect(unitarySurface, NULL, SDL_MapRGB(_p_screen->format, 0, 0, 0));
        unitarySurfacePosition.x = _node.x * _coef* GRID_SIZE;
        unitarySurfacePosition.y = _node.y * _coef* GRID_SIZE;     
        SDL_BlitSurface(unitarySurface, NULL, _p_screen, &unitarySurfacePosition);
    }
    if(_node.nodeType == FORBIDDEN)
    {
        //draw occupied
        SDL_FillRect(unitarySurface, NULL, SDL_MapRGB(_p_screen->format, 28, 28, 28));
        unitarySurfacePosition.x = _node.x * _coef* GRID_SIZE;
        unitarySurfacePosition.y = _node.y * _coef* GRID_SIZE;     
        SDL_BlitSurface(unitarySurface, NULL, _p_screen, &unitarySurfacePosition);
    }
    if(_node.nodeType == SOFT_OBSTACLE)
    {
        //draw occupied
        SDL_FillRect(unitarySurface, NULL, SDL_MapRGB(_p_screen->format, 121, 121, 121));
        unitarySurfacePosition.x = _node.x * _coef* GRID_SIZE;
        unitarySurfacePosition.y = _node.y * _coef* GRID_SIZE;     
        SDL_BlitSurface(unitarySurface, NULL, _p_screen, &unitarySurfacePosition);
    }
    if(_node.nodeType == OPEN_LIST)
    {
        //draw OPEN_LIST
        SDL_FillRect(unitarySurface, NULL, SDL_MapRGB(_p_screen->format, 248, 168, 15));
        unitarySurfacePosition.x = _node.x * _coef* GRID_SIZE;
        unitarySurfacePosition.y = _node.y * _coef* GRID_SIZE;     
        SDL_BlitSurface(unitarySurface, NULL, _p_screen, &unitarySurfacePosition);
    }
    if(_node.nodeType == CLOSED_LIST)
    {
        //draw CLOSED_LIST
        SDL_FillRect(unitarySurface, NULL, SDL_MapRGB(_p_screen->format, 244, 18, 7));
        unitarySurfacePosition.x = _node.x * _coef* GRID_SIZE;
        unitarySurfacePosition.y = _node.y * _coef* GRID_SIZE;     
        SDL_BlitSurface(unitarySurface, NULL, _p_screen, &unitarySurfacePosition);
    }
    if(_node.nodeType == FINAL_TRAJ)
    {
        //draw FINAL_TRAJ
        SDL_FillRect(unitarySurface, NULL, SDL_MapRGB(_p_screen->format, 13, 183, 0));
        unitarySurfacePosition.x = _node.x * _coef* GRID_SIZE;
        unitarySurfacePosition.y = _node.y * _coef* GRID_SIZE;     
        SDL_BlitSurface(unitarySurface, NULL, _p_screen, &unitarySurfacePosition);
    }
    SDL_Flip(_p_screen);
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

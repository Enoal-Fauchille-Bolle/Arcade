/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** cpp for SDL encapsulation
*/

#include "SDL.hpp"
#include <SDL2/SDL.h>

SDL::SDL()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        exit(84);
    }
}

SDL::~SDL()
{
    SDL_Quit();
}

SDL_Window* SDL::createWindow(const char *title, int x, int y, int w, int h, Uint32 flags)
{
    return SDL_CreateWindow(title, x, y, w, h, flags);
}

SDL_Renderer* SDL::createRenderer(SDL_Window *win, int index, Uint32 flags)
{
    return (SDL_CreateRenderer(win, index, flags));
}

void SDL::renderClear(SDL_Renderer *render)
{
    SDL_RenderClear(render);
}

void SDL::renderPresent(SDL_Renderer *rend)
{
    SDL_RenderPresent(rend);
}

SDL_Event SDL::pollEvent(void)
{
    SDL_PollEvent(&event);
    return (event);
}

void SDL::destroyAll(SDL_Window *win, SDL_Renderer *rende)
{
    SDL_DestroyRenderer(rende);
    SDL_DestroyWindow(win);
}

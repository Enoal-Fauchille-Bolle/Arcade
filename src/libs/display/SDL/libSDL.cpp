/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** cpp for SDL
*/

#include "libSDL.hpp"

LibSDL::LibSDL()
{
    _sdl = std::make_unique<SDL>();
    _sdl->createWindow("Arcade", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    _sdl->createRenderer(_sdl->getWindow(), -1, SDL_RENDERER_ACCELERATED);
}

LibSDL::~LibSDL()
{
    if (_sdl) {
        _sdl->destroyAll(_sdl->getWindow(), _sdl->getRenderer());
    }
}

std::vector<rawEvent> LibSDL::pollEvent(void)
{
    std::vector<rawEvent> events;

    return events;
}

void LibSDL::drawObject(renderObject obj)
{
    obj = obj;
}

void LibSDL::clear(void)
{
    SDL_RenderClear(_sdl->getRenderer());
}

void LibSDL::display(void)
{
    SDL_RenderPresent(_sdl->getRenderer());
}

std::string LibSDL::getName(void)
{
    return ("SDL");
}

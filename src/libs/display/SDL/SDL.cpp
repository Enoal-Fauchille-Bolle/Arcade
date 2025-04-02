/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** cpp for SDL encapsulation
*/

#include "SDL.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

SDL::SDL()
{
    _window = nullptr;
    _renderer = nullptr;
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        exit(84);
    }
    if (TTF_Init() == -1) {
        std::cerr << "TTF_Init Error: " << TTF_GetError() << std::endl;
        SDL_Quit();
        exit(84);
    }
    if (IMG_Init(IMG_INIT_PNG) == 0) {
        std::cerr << "IMG_Init Error: " << IMG_GetError() << std::endl;
        TTF_Quit();
        SDL_Quit();
        exit(84);
    }
}

SDL::~SDL()
{
}

SDL_Window* SDL::createWindow(const char *title, int x, int y, int w, int h, Uint32 flags)
{
    _window = SDL_CreateWindow(title, x, y, w, h, flags);
    if (!_window) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(84);
    }
    return _window;
}

SDL_Renderer* SDL::createRenderer(int index, Uint32 flags)
{
    _renderer = SDL_CreateRenderer(_window, index, flags);
    if (!_renderer) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(_window);
        SDL_Quit();
        exit(84);
    }
    return _renderer;
}

void SDL::renderClear()
{
    SDL_RenderClear(_renderer);
}

void SDL::renderPresent()
{
    SDL_RenderPresent(_renderer);
}

std::vector<RawEvent> SDL::pollEvent(void)
{
    SDL_Event event;
    _hasEvent = false;
    while (SDL_PollEvent(&event)) {
        _hasEvent = true;
        if (event.type == SDL_QUIT) {
            RawEvent quitEvent;
            quitEvent.type = EventType::PRESS;
            _event.push_back(quitEvent);
        } else if (event.type == SDL_KEYDOWN) {
            RawEvent keyEvent;
            keyEvent.type = EventType::PRESS;
            switch (event.key.keysym.sym) {
                case SDLK_DELETE: keyEvent.key = KEY_DELETE; break;
                case SDLK_INSERT: keyEvent.key = KEY_INSERT; break;
                case SDLK_PAGEUP: keyEvent.key = KEY_PAGEUP; break;
                case SDLK_PAGEDOWN: keyEvent.key = KEY_PAGEDOWN; break;
                default:
                    continue;
            }
            _event.push_back(keyEvent);
        } else if (event.type == SDL_MOUSEBUTTONDOWN) {
            RawEvent mouseEvent;
            mouseEvent.type = EventType::PRESS;
            if (event.button.button == SDL_BUTTON_LEFT)
                mouseEvent.key = MOUSE_LEFT;
            else if (event.button.button == SDL_BUTTON_RIGHT)
                mouseEvent.key = MOUSE_RIGHT;
            else if (event.button.button == SDL_BUTTON_MIDDLE)
                mouseEvent.key = MOUSE_MIDDLE;
            mouseEvent.x = event.button.x;
            mouseEvent.y = event.button.y;
            _event.push_back(mouseEvent);
        }
    }
    return _event;
}

void SDL::destroyAll()
{
    if (_renderer)
        SDL_DestroyRenderer(_renderer);
    if (_window)
        SDL_DestroyWindow(_window);
    
    _renderer = nullptr;
    _window = nullptr;
    TTF_Quit();
    SDL_Quit();
    IMG_Quit();
}

void SDL::drawRectangle(renderObject obj)
{
    SDL_Rect rect;
    rect.x = obj.x;
    rect.y = obj.y;
    rect.w = obj.width;
    rect.h = obj.height;

    SDL_SetRenderDrawColor(_renderer, obj.RGB[0], obj.RGB[1], obj.RGB[2], 255);
    if (!obj.sprite.empty()) {
        SDL_Surface *surface = IMG_Load(obj.sprite.c_str());
        if (!surface) {
            std::cerr << "IMG_Load Error: " << IMG_GetError() << std::endl;
            return;
        }
        SDL_Texture *texture = SDL_CreateTextureFromSurface(_renderer, surface);
        if (!texture) {
            std::cerr << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
            SDL_FreeSurface(surface);
            return;
        }
        SDL_RenderCopy(_renderer, texture, nullptr, &rect);
        SDL_DestroyTexture(texture);
        SDL_FreeSurface(surface);
        return;
    }
    SDL_RenderFillRect(_renderer, &rect);
}

void SDL::drawCircle(renderObject obj)
{
    int radius = obj.width / 2;
    int x = obj.x + radius;
    int y = obj.y + radius;

    SDL_SetRenderDrawColor(_renderer, obj.RGB[0], obj.RGB[1], obj.RGB[2], 255);
    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            int dx = radius - w;
            int dy = radius - h;
            if ((dx * dx + dy * dy) <= (radius * radius)) {
                SDL_RenderDrawPoint(_renderer, x + dx, y + dy);
            }
        }
    }
}

void SDL::drawText(renderObject obj)
{
    TTF_Font *font = TTF_OpenFont("assets/arial.ttf", 14);
    if (!font) {
        std::cerr << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;
        return;
    }

    SDL_Color color = {
        static_cast<Uint8>(obj.RGB[0]), 
        static_cast<Uint8>(obj.RGB[1]), 
        static_cast<Uint8>(obj.RGB[2]), 
        255
    };
    

    if (obj.sprite.empty()) {
        std::cerr << "TTF_RenderText_Blended Error: Text has zero width (empty string provided)" << std::endl;
        TTF_CloseFont(font);
        return;
    }

    SDL_Surface *surface = TTF_RenderText_Blended(font, obj.sprite.c_str(), color);
    if (!surface) {
        std::cerr << "TTF_RenderText_Blended Error: " << TTF_GetError() << std::endl;
        TTF_CloseFont(font);
        return;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(_renderer, surface);
    if (!texture) {
        std::cerr << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(surface);
        TTF_CloseFont(font);
        return;
    }

    SDL_Rect destRect = {obj.x, obj.y, surface->w, surface->h};
    SDL_RenderCopy(_renderer, texture, nullptr, &destRect);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
}
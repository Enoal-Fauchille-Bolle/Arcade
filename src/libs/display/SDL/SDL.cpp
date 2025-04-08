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
#include <iostream>
#include <unordered_map>

static const std::unordered_map<SDL_Keycode, EventKey> eventTypeMap = {
    {SDL_BUTTON_LEFT, MOUSE_LEFT},
    {SDL_BUTTON_RIGHT, MOUSE_RIGHT},
    {SDL_BUTTON_MIDDLE, MOUSE_MIDDLE},
    {SDLK_a, KEYBOARD_A},
    {SDLK_b, KEYBOARD_B},
    {SDLK_c, KEYBOARD_C},
    {SDLK_d, KEYBOARD_D},
    {SDLK_e, KEYBOARD_E},
    {SDLK_f, KEYBOARD_F},
    {SDLK_g, KEYBOARD_G},
    {SDLK_h, KEYBOARD_H},
    {SDLK_i, KEYBOARD_I},
    {SDLK_j, KEYBOARD_J},
    {SDLK_k, KEYBOARD_K},
    {SDLK_l, KEYBOARD_L},
    {SDLK_m, KEYBOARD_M},
    {SDLK_n, KEYBOARD_N},
    {SDLK_o, KEYBOARD_O},
    {SDLK_p, KEYBOARD_P},
    {SDLK_q, KEYBOARD_Q},
    {SDLK_r, KEYBOARD_R},
    {SDLK_s, KEYBOARD_S},
    {SDLK_t, KEYBOARD_T},
    {SDLK_u, KEYBOARD_U},
    {SDLK_v, KEYBOARD_V},
    {SDLK_w, KEYBOARD_W},
    {SDLK_x, KEYBOARD_X},
    {SDLK_y, KEYBOARD_Y},
    {SDLK_z, KEYBOARD_Z},
    {SDLK_0, KEYBOARD_0},
    {SDLK_1, KEYBOARD_1},
    {SDLK_2, KEYBOARD_2},
    {SDLK_3, KEYBOARD_3},
    {SDLK_4, KEYBOARD_4},
    {SDLK_5, KEYBOARD_5},
    {SDLK_6, KEYBOARD_6},
    {SDLK_7, KEYBOARD_7},
    {SDLK_8, KEYBOARD_8},
    {SDLK_9, KEYBOARD_9},
    {SDLK_UP, KEYBOARD_UP},
    {SDLK_DOWN, KEYBOARD_DOWN},
    {SDLK_LEFT, KEYBOARD_LEFT},
    {SDLK_RIGHT, KEYBOARD_RIGHT},
    {SDLK_ESCAPE, KEYBOARD_ESCAPE},
    {SDLK_SPACE, KEYBOARD_SPACE},
    {SDLK_TAB, KEYBOARD_TAB},
    {SDLK_BACKSPACE, KEYBOARD_BACKSPACE},
    {SDLK_DELETE, KEYBOARD_DELETE},
    {SDLK_LSHIFT, KEYBOARD_LSHIFT},
    {SDLK_RSHIFT, KEYBOARD_RSHIFT},
    {SDLK_LCTRL, KEYBOARD_LCTRL},
    {SDLK_RCTRL, KEYBOARD_RCTRL},
    {SDLK_LALT, KEYBOARD_LALT},
    {SDLK_RALT, KEYBOARD_RALT}
};

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

void SDL::renderClear(void)
{
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderClear(_renderer);
}

void SDL::renderPresent(void)
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
            quitEvent.type = EventType::QUIT;
            _event.push_back(quitEvent);
        } else if (event.type == SDL_KEYDOWN) {
            RawEvent keyEvent;
            keyEvent.type = EventType::PRESS;
            auto it = eventTypeMap.find(event.key.keysym.sym);
            if (it != eventTypeMap.end()) {
                keyEvent.key = it->second;
            }
            _event.push_back(keyEvent);
        } else if (event.type == SDL_MOUSEBUTTONDOWN) {
            RawEvent mouseEvent;
            mouseEvent.type = EventType::PRESS;
            auto it = eventTypeMap.find(event.button.button);
            if (it != eventTypeMap.end()) {
                mouseEvent.key = it->second;
            }
            mouseEvent.x = event.button.x;
            mouseEvent.y = event.button.y;
            _event.push_back(mouseEvent);
        }
    }
    return _event;
}

void SDL::destroyAll(void)
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
        SDL_Point center = {rect.w / 2, rect.h / 2};
        SDL_RenderCopyEx(_renderer, texture, nullptr, &rect, obj.rotate, &center, SDL_FLIP_NONE);
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

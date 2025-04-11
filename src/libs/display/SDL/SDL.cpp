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
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <unordered_map>

/** 
 * @brief Maps SDL keycodes to EventKey enum values.
 *
 * This map is used to convert SDL keycodes to the corresponding EventKey
 * enum values for event handling.
 */
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
    {SDLK_RALT, KEYBOARD_RALT},
    {SDLK_RETURN, KEYBOARD_ENTER},
    {SDLK_PAGEUP, KEYBOARD_PAGEUP},
    {SDLK_PAGEDOWN, KEYBOARD_PAGEDOWN},
    {SDLK_HOME, KEYBOARD_HOME},
    {SDLK_END, KEYBOARD_END},
    {SDLK_INSERT, KEYBOARD_INSERT},
    {SDLK_F1, KEYBOARD_F1},
    {SDLK_F2, KEYBOARD_F2},
    {SDLK_F3, KEYBOARD_F3},
    {SDLK_F4, KEYBOARD_F4},
    {SDLK_F5, KEYBOARD_F5},
    {SDLK_F6, KEYBOARD_F6},
    {SDLK_F7, KEYBOARD_F7},
    {SDLK_F8, KEYBOARD_F8},
    {SDLK_F9, KEYBOARD_F9},
    {SDLK_F10, KEYBOARD_F10},
    {SDLK_F11, KEYBOARD_F11},
    {SDLK_F12, KEYBOARD_F12},
    {SDLK_MINUS, KEYBOARD_MINUS},
    {SDLK_PLUS, KEYBOARD_PLUS},
    {SDLK_COMMA, KEYBOARD_COMMA},
    {SDLK_PERIOD, KEYBOARD_PERIOD},
    {SDLK_SLASH, KEYBOARD_SLASH},
    {SDLK_SEMICOLON, KEYBOARD_SEMICOLON},
    {SDLK_QUOTE, KEYBOARD_APOSTROPHE},
    {SDLK_BACKSLASH, KEYBOARD_BACKSLASH},
    {SDLK_BACKQUOTE, KEYBOARD_GRAVE},
    {SDLK_LEFTBRACKET, KEYBOARD_LBRACKET},
    {SDLK_RIGHTBRACKET, KEYBOARD_RBRACKET}
};

SDL::SDL()
{
    _window = nullptr;
    _renderer = nullptr;
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
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

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "SDL_mixer could not initialize! Error: " << Mix_GetError() << std::endl;
    } else {
        _audioInitialized = true;
        Mix_AllocateChannels(128);
    }
}

SDL::~SDL()
{
    for (auto& pair : _soundCache) {
        if (pair.second) {
            Mix_FreeChunk(pair.second);
        }
    }
    _soundCache.clear();
    
    if (_currentMusic) {
        Mix_FreeMusic(_currentMusic);
        _currentMusic = nullptr;
    }
    
    if (_audioInitialized) {
        Mix_CloseAudio();
    }
}

/**
 * @brief Creates an SDL window.
 *
 * This function creates an SDL window with the specified parameters.
 * If the window creation fails, it prints an error message and exits the program.
 *
 * @param title The title of the window.
 * @param x The x-coordinate of the window position.
 * @param y The y-coordinate of the window position.
 * @param w The width of the window.
 * @param h The height of the window.
 * @param flags Additional flags for window creation.
 * @return A pointer to the created SDL_Window object.
 */
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

/**
 * @brief Creates an SDL renderer.
 *
 * This function creates an SDL renderer for the specified window.
 * If the renderer creation fails, it prints an error message and exits the program.
 *
 * @param index The index of the rendering driver to initialize.
 * @param flags Additional flags for renderer creation.
 * @return A pointer to the created SDL_Renderer object.
 */
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

/**
 * @brief Clears the current rendering target.
 *
 * This function sets the draw color to black and clears the current rendering target.
 */
void SDL::renderClear(void)
{
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderClear(_renderer);
}

/**
 * @brief Presents the current rendering target.
 *
 * This function updates the screen with the contents of the current rendering target.
 */
void SDL::renderPresent(void)
{
    SDL_RenderPresent(_renderer);
}

/**
 * @brief Polls events from the SDL event queue.
 *
 * This function retrieves events from the SDL event queue and processes them.
 * It returns a vector of RawEvent objects representing the events polled.
 *
 * @return A vector of RawEvent objects representing the events polled.
 */
std::vector<RawEvent> SDL::pollEvent(void)
{
    SDL_Event event;
    _hasEvent = false;

    _event.clear();
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
    for (auto& pair : _soundCache) {
        if (pair.second) {
            Mix_FreeChunk(pair.second);
        }
    }
    _soundCache.clear();
    
    if (_currentMusic) {
        Mix_FreeMusic(_currentMusic);
        _currentMusic = nullptr;
    }
    
    if (_audioInitialized) {
        Mix_CloseAudio();
    }
    
    if (_renderer)
        SDL_DestroyRenderer(_renderer);
    if (_window)
        SDL_DestroyWindow(_window);
    
    _renderer = nullptr;
    _window = nullptr;
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

/**
 * @brief Draws a rectangle on the screen.
 *
 * This function draws a rectangle on the screen using the specified
 * renderObject parameters. If a sprite is provided, it will be drawn
 * instead of the rectangle.
 *
 * @param obj The renderObject containing the rectangle parameters.
 */
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

/**
 * @brief Draws a circle on the screen.
 *
 * This function draws a circle on the screen using the specified
 * renderObject parameters.
 *
 * @param obj The renderObject containing the circle parameters.
 */
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

/**
 * @brief Draws a line on the screen.
 *
 * This function draws a line on the screen using the specified
 * renderObject parameters.
 *
 * @param obj The renderObject containing the line parameters.
 */
void SDL::drawText(renderObject obj)
{
    TTF_Font *font = TTF_OpenFont("assets/Tahoma.ttf", obj.width);
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

/**
 * @brief Processes sound events from a renderObject.
 *
 * This method plays sound based on parameters in the renderObject.
 * - Use "sound:" prefix in obj.sound to play temporary sound effects
 * - Use "music:" prefix in obj.sound to play background music
 *
 * @param obj The renderObject containing sound information
 */
void SDL::drawMusic(renderObject obj)
{
    if (!_audioInitialized || obj.sprite.empty()) {
        return;
    }
    if (obj.sprite.length() >= 13 && obj.sprite.substr(0, 13) == "assets/music_") {
        std::string musicPath = obj.sprite;
        
        if (_currentMusic != nullptr) {
            Mix_HaltMusic();
            Mix_FreeMusic(_currentMusic);
            _currentMusic = nullptr;
        }
        
        _currentMusic = Mix_LoadMUS(musicPath.c_str());
        if (!_currentMusic) {
            std::cerr << "Failed to load music: " << Mix_GetError() << std::endl;
            return;
        }
        
        if (Mix_PlayMusic(_currentMusic, -1) == -1) {
            std::cerr << "Failed to play music: " << Mix_GetError() << std::endl;
        }
        return;
    } else {
        std::string soundPath = obj.sprite;
        
        if ((soundPath == "assets/gameover.mp3" || soundPath == "assets/Minesweeper_1/boom.mp3")
            && _currentMusic != nullptr) {
            Mix_HaltMusic();
            Mix_FreeMusic(_currentMusic);
            _currentMusic = nullptr;
        }
        if (_soundCache.find(soundPath) == _soundCache.end()) {
            Mix_Chunk* chunk = Mix_LoadWAV(soundPath.c_str());
            if (!chunk) {
                std::cerr << "Failed to load sound effect: " << Mix_GetError() << std::endl;
                return;
            }
            _soundCache[soundPath] = chunk;
        }
        
        if (Mix_PlayChannel(-1, _soundCache[soundPath], 0) == -1) {
            std::cerr << "Failed to play sound effect: " << Mix_GetError() << std::endl;
        }
    }
}

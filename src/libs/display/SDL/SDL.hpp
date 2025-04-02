/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Header for SDL encapsulation
*/

#ifndef SDL_HPP_
#define SDL_HPP_

    #include <iostream>
    #include <SDL2/SDL.h>
    #include "../interfaces/IDisplay.hpp"
    #include <vector>

    #define CENTER SDL_WINDOWPOS_CENTERED
    #define SCREEN_WIDTH 1024
    #define SCREEN_HEIGHT 768

class SDL {
    public:
        SDL();
        ~SDL();
        
        SDL_Window* createWindow(const char *title, int x, int y, int w, int h, Uint32 flags);
        SDL_Renderer* createRenderer(int index, Uint32 flags);
        void renderClear();
        void renderPresent();
        std::vector<rawEvent> pollEvent(void);
        void destroyAll();

        SDL_Window* getWindow() const { return _window; }
        SDL_Renderer* getRenderer() const { return _renderer; }
        bool hasEvent() const { return _hasEvent; }

        void drawRectangle(renderObject obj);
        void drawCircle(renderObject obj);
        void drawText(renderObject obj);

    private:
        SDL_Window* _window = nullptr;
        SDL_Renderer* _renderer = nullptr;
        std::vector<rawEvent> _event;
        bool _hasEvent = false;
};

#endif /* !SDL_HPP_ */

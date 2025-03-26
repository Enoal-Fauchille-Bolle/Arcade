/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** class to encapsulate the SDL
*/

#ifndef SDL_HPP_
    #define SDL_HPP_

    #include <SDL2/SDL.h>
    #include <iostream>

class SDL {
    public:
        SDL();
        ~SDL();

        SDL_Window *createWindow(const char *title, int x, int y, int w, int h, Uint32 flags);
        SDL_Renderer *createRenderer(SDL_Window *window, int index, Uint32 flags);
        void renderClear(SDL_Renderer *renderer);
        void renderPresent(SDL_Renderer *renderer);
        SDL_Event pollEvent(void);
        void destroyAll(SDL_Window *window, SDL_Renderer *renderer);
        SDL_Renderer *getRenderer(void) { return (renderer); }
        SDL_Window *getWindow(void) { return (window); }
        SDL_Event getEvent(void) { return (event); }
        
        

    protected:
        SDL_Window *window;
        SDL_Renderer *renderer;
        SDL_Event event;
    private:
};

#endif /* !SDL_HPP_ */

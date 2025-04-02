/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** SDL graphical lib
*/

#ifndef LIBSDL_HPP_
    #define LIBSDL_HPP_

    #include "SDL.hpp"
    #include "../interfaces/IDisplay.hpp"
    #include <memory>

    #define LIBRARY_NAME "SDL"

class LibSDL : public IDisplay {
    public:
        LibSDL();
        ~LibSDL();

        std::vector<rawEvent> pollEvent(void) override;

        void drawObject(renderObject) override;

        void clear(void) override;

        void display(void) override;

        std::string getName(void) override;

        DisplayType getDType(void) override;

    protected:
    private:
        std::unique_ptr<SDL> _sdl;
};

#endif /* !LIBSDL_HPP_ */

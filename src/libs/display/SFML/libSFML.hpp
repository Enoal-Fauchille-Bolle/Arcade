/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** libSFML
*/

#ifndef LIBSFML_HPP_
    #define LIBSFML_HPP_

    #include <SFML/Graphics.hpp>
    #include <iostream>

    #include "../interfaces/IDisplay.hpp"

    #define LIBRARY_NAME "SFML"

class libSFML : public IDisplay {
    public:
        libSFML();
        ~libSFML();

        std::vector<rawEvent> pollEvent(void) final;
        void drawObject(renderObject) final;
        void clear(void) final;
        void display(void) final;

        std::string getName(void) final;

    protected:
        void drawRectangle(renderObject obj);
        void drawCircle(renderObject obj);
        void drawText(renderObject obj);
        void drawMusic(renderObject obj);

    private:
        std::string _name;
        sf::RenderWindow _window;
};

#endif /* !LIBSFML_HPP_ */

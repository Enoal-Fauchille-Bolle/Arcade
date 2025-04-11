/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** libSFML
*/

#ifndef LIBSFML_HPP_
    #define LIBSFML_HPP_

    #include <SFML/Graphics.hpp>
    #include <SFML/Window.hpp>
    #include <SFML/System.hpp>
    #include <SFML/Audio.hpp>
    #include <iostream>

    #include "../interfaces/IDisplay.hpp"

    #define LIBRARY_NAME "SFML"
    #define LIBRARY_DTYPE DisplayType::GRAPHICAL

class libSFML : public IDisplay {
    public:
        libSFML();
        ~libSFML();

        std::vector<RawEvent> pollEvent(void) final;
        void drawObject(renderObject) final;
        void clear(void) final;
        void display(void) final;

        std::string getName(void) final;
        DisplayType getDType(void) final;

    protected:
        void drawRectangle(renderObject obj);
        void drawCircle(renderObject obj);
        void drawText(renderObject obj);
        void drawMusic(renderObject obj);

    private:
        void playBackgroundMusic(const std::string &filePath, sf::Music &music, bool &isPlaying);
        void playSoundEffect(const std::string &filePath, std::map<std::string, sf::SoundBuffer> &soundBufferCache, std::map<std::string, sf::Sound> &soundEffects);
        std::string _name;
        DisplayType _dtype;
        sf::RenderWindow _window;

        sf::Music _music;
};

#endif /* !LIBSFML_HPP_ */

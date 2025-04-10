/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Ncurses
*/

#ifndef NCURSES_HPP_
    #define NCURSES_HPP_

    #include <SFML/Graphics.hpp>
    #include <iostream>
    #include <cstring>
    #include <cmath>
    #include <curses.h>
    #include <unordered_map>
    #include <climits>

    #include "../interfaces/IDisplay.hpp"

    #define LIBRARY_NAME "Ncurses"
    #define LIBRARY_DTYPE DisplayType::TERMINAL

    #define GRAPHICAL_SCREEN_WIDTH 1024
    #define GRAPHICAL_SCREEN_HEIGHT 768

    #define SCREEN_WIDTH 126
    #define SCREEN_HEIGHT 42

class Ncurses : public IDisplay {
    public:
        Ncurses();
        ~Ncurses();

        std::vector<RawEvent> pollEvent(void) final;
        void drawObject(renderObject) final;
        void clear(void) final;
        void display(void) final;

        std::string getName(void) final;
        DisplayType getDType(void) final;
        using NcursesColor = int;

    protected:
        void initColors(void);
        Ncurses::NcursesColor getClosestPredefinedColor(const RgbColor& color);

        RawEvent pollKeyboardEvent(int key);
        RawEvent pollMouseEvent(MEVENT mouseEvent);

        ScreenSize getScreenSize(void);
        bool checkScreenSize(void);

        bool checkScreenBox(void);
        void displayScreenBox(void);

        Coordinates graphicalCoordinatesToTerminal(
            Coordinates graphicalCoordinates);
        Coordinates terminalCoordinatesToGraphical(
            Coordinates graphicalCoordinates);

        bool isUtf8String(const std::string& str);
        int getCharWidth(const std::string& utf8_char);

        void drawCharacter(
            Coordinates terminalCoordinates, const std::string &sprite);

        void drawRectangleSprite(renderObject obj,
            Coordinates terminalCoordinates,
            Coordinates terminalSize);
        void drawRealRectangle(renderObject obj,
            Coordinates terminalCoordinates,
            Coordinates terminalSize);
        void drawRectangle(renderObject obj);
        void drawCircle(renderObject obj);
        void drawText(renderObject obj);
        void drawMusic(renderObject obj);

    private:
        std::string _name;
        DisplayType _dtype;
        WINDOW *_buffer;
        size_t _screenWidth = 0;
        size_t _screenHeight = 0;
};

#endif /* !NCURSES_HPP_ */

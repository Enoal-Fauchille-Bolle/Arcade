/*
** EPITECH PROJECT, 2025
** Arcade-project
** File description:
** Core
*/

#ifndef CORE_HPP_
    #define CORE_HPP_

    #include <iostream>
    #include <dlfcn.h>
    #include <filesystem>
    #include <memory>
    #include <vector>
    #include "../libs/display/interfaces/IDisplay.hpp"
    #include "../libs/game/interfaces/IGame.hpp"

class Core {
    public:
        Core(std::string path);
        ~Core();

    protected:
        void run();

    private:
        int load_display(std::string path);
        int load_game(std::string path);

        int delete_display();
        int delete_game();

        std::unique_ptr<IDisplay> _display;
        std::unique_ptr<IGame> _game;
        bool running = true;

};

#endif /* !CORE_HPP_ */

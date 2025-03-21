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
    #include "Arcade/src/libs/game/interfaces/IGame.hpp"
    #include "Arcade/src/libs/graphical/interfaces/IGraphical.hpp"

class Core {
    public:
        Core(std::string path);
        ~Core();

    protected:
        void run();

    private:
        int load_graphical(std::string path);
        int load_game(std::string path);

        int delete_graphical();
        int delete_game();

        std::unique_ptr<IGraphical>* _graphical;
        std::unique_ptr<IGame>* _game;

};

#endif /* !CORE_HPP_ */

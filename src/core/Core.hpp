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
    #include "../interfaces/IType.hpp"
    #include "LibLoader.hpp"
    #include "../libs/display/interfaces/IDisplay.hpp"
    #include "../libs/game/interfaces/IGame.hpp"
    #include "./EmergencyMenu.hpp"

class Core {
    public:
        Core(std::string path);
        ~Core();

        void run(void);
    protected:

    private:
        int load_display(std::string path);
        int load_game(std::string path);

        int delete_display(void);
        int delete_game(void);

        void startEmergencyMenu(void);

        bool checkQuit(std::vector<RawEvent> events);

        void renderEntities(std::map<std::string, Entity> entities);

        void saveScore(std::pair<float, std::string> score);

        DLLoader<IGame> _gameLoader;
        DLLoader<IDisplay> _graphicLoader;
        std::unique_ptr<IDisplay> _display;
        std::unique_ptr<IGame> _game;
        bool _running = true;

};

#endif /* !CORE_HPP_ */

/*
** EPITECH PROJECT, 2025
** Arcade-project
** File description:
** Core
*/

#ifndef CORE_HPP_
    #define CORE_HPP_

    #include <dlfcn.h>

    #include <filesystem>
    #include <iostream>
    #include <memory>
    #include <vector>

    #include "../interfaces/IType.hpp"
    #include "../libs/display/interfaces/IDisplay.hpp"
    #include "../libs/game/interfaces/IGame.hpp"
    #include "./EmergencyMenu.hpp"
    #include "LibLoader.hpp"
    #include "ScoreManager.hpp"

    #define PREVIOUS_DISPLAY_KEY KEYBOARD_F3
    #define NEXT_DISPLAY_KEY KEYBOARD_F4
    #define RELOAD_LIBS_KEY KEYBOARD_F5
    #define RELOAD_GAME_LIB_KEY KEYBOARD_F6
    #define RELOAD_DISPLAY_LIB_KEY KEYBOARD_F7
    #define PREVIOUS_GAME_KEY KEYBOARD_F8
    #define NEXT_GAME_KEY KEYBOARD_F9
    #define GO_TO_MENU_KEY KEYBOARD_F10
    #define QUIT_KEY KEYBOARD_F11

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
        void handleScore(void);

        void nextDisplayLibrary(void);
        void previousDisplayLibrary(void);
        void displayLibrarySwitching(std::vector<RawEvent> events);

        void nextGameLibrary(void);
        void previousGameLibrary(void);
        void gameLibrarySwitching(std::vector<RawEvent> events);

        void reloadGameLibrary(void);
        void reloadDisplayLibrary(void);
        void libraryReloading(std::vector<RawEvent> events);

        std::string getDisplayLibPathFromIndex(size_t index);
        size_t getDisplayLibIndexFromPath(std::string path);

        std::string getGameLibPathFromIndex(size_t index);
        size_t getGameLibIndexFromPath(std::string path);

        bool checkGoToMenu(std::vector<RawEvent> events);
        void goToMenu(void);

        DLLoader<IGame> _gameLoader;
        DLLoader<IDisplay> _graphicLoader;
        std::unique_ptr<IDisplay> _display;
        std::unique_ptr<IGame> _game;
        bool _running = true;
        std::vector<LibInfo> _displayLibs;
        std::vector<LibInfo> _gameLibs;
        size_t _selectedDisplayLib = 0;
        size_t _selectedGameLib = 0;
        std::string _currentGamePath = "";
        std::string _currentDisplayPath = "";
        std::string _username = "Username";
};

#endif /* !CORE_HPP_ */

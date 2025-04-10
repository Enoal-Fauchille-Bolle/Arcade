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
        void createScoreDirectory(void);
        std::vector<std::pair<float, std::string>> loadScoresFromFile(const std::string& fileName);
        void updatePlayerScore(std::vector<std::pair<float, std::string>>& scores, const std::pair<float, std::string>& score);
        bool writeScoresToFile(const std::string& fileName, const std::vector<std::pair<float, std::string>>& scores);

        void nextDisplayLibrary(void);
        void previousDisplayLibrary(void);
        void displayLibrarySwitching(std::vector<RawEvent> events);

        void reloadGameLibrary(void);
        void reloadDisplayLibrary(void);
        void libraryReloading(std::vector<RawEvent> events);

        std::string getDisplayLibPathFromIndex(size_t index);
        size_t getDisplayLibIndexFromPath(std::string path);

        DLLoader<IGame> _gameLoader;
        DLLoader<IDisplay> _graphicLoader;
        std::unique_ptr<IDisplay> _display;
        std::unique_ptr<IGame> _game;
        bool _running = true;
        std::vector<LibInfo> _displayLibs;
        size_t _selectedDisplayLib = 0;
        std::string _currentGamePath = "";
        std::string _currentDisplayPath = "";
};

#endif /* !CORE_HPP_ */

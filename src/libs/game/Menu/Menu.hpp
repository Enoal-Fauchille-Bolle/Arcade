/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Menu
*/

#ifndef MENU_HPP_
    #define MENU_HPP_

    #include <algorithm>
    #include <filesystem>
    #include <iostream>
    #include <map>
    #include <vector>

    #include "../../../libs/display/interfaces/IDisplay.hpp"
    #include "../../../libs/game/interfaces/IGame.hpp"
    #include "../AGame.hpp"
    #include "LibLoader.hpp"

    #define LIBRARY_PATH "./lib/"
    #define SCREEN_WIDTH 1024
    #define SCREEN_HEIGHT 768

class Menu : public AGame {
    public:
        Menu();
        ~Menu() = default;

        bool isGameOver(void) override;

        std::pair<float, std::string> getScore(void) override;

        bool isGameEnd(void) override;

        std::string getNewLib(void) override;

        void handleEvent(std::vector<event>) override;

        std::map<std::string, Entity> renderGame() override;

    protected:
    private:
        enum LibType {
            GAME,
            DISPLAY
        };
        struct LibInfo {
                std::string path;
                std::string name;
                LibType type;
        };

        // Library Getting
        bool isValidDirectory(const std::string &path);
        std::vector<std::string> findSharedLibraries(
            const std::string &directoryPath);
        std::vector<std::string> getLibraryFiles();

        // Library Categorization
        void sortLibraries();
        std::string isGameLibrary(const std::string &path);
        std::string isDisplayLibrary(const std::string &path);
        void categorizeLibraries(const std::vector<std::string> &paths);

        // Rendering
        Entity renderTitle();
        Entity renderDisplayTitle();
        std::map<std::string, Entity> renderLibs(std::vector<LibInfo> displayLibs,
                  size_t selectedLib,
                  bool selectingLibType);
        Entity renderGameTitle();
        Entity renderSelectedLibs(
            std::string gameName, std::string displayName);

        std::vector<LibInfo> _gameLibs;
        std::vector<LibInfo> _displayLibs;
        size_t _selectedGameLib = 0;
        size_t _selectedDisplayLib = 0;
        LibType _selectingLibType = GAME;
        bool _startGame;
};

#endif /* !MENU_HPP_ */

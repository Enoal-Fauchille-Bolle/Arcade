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
    #include "../interfaces/IGame.hpp"
    #include "../../../core/LibLoader.hpp"

    #define LIBRARY_PATH "./lib/"
    #define SCREEN_WIDTH 1024
    #define SCREEN_HEIGHT 768

class Menu : public IGame {
    public:
        Menu();
        ~Menu() = default;

        bool isGameOver(void) final;

        std::pair<float, std::string> getScore(void) final;

        bool isGameEnd(void) final;

        std::string getNewLib(void) final;

        void handleEvent(std::vector<rawEvent>) final;

        std::string getName(void) final;

        std::map<IGame::EntityName, Entity> renderGame() final;

    protected:
    private:
        std::string _name;
        struct ButtonPos {
            int x;
            int y;
            int width;
            int height;
        };
        struct LibInfo {
            std::string path;
            std::string name;
            libType type;
            ButtonPos pos;
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

        // Event Handling
        void handleLeftClick(rawEvent event);
        void handleOneEvent(rawEvent event);

        // Rendering
        Entity renderTitle();
        Entity renderDisplayTitle();
        void setupLibButton(LibInfo &lib, int x, int y);
        std::map<EntityName, Entity> renderLibs(
            std::vector<LibInfo> displayLibs, size_t selectedLib, size_t x,
            std::string libPrefix);
        Entity renderGameTitle();
        Entity renderSelectedLibs(
            std::string gameName, std::string displayName);

        std::vector<LibInfo> _gameLibs;
        std::vector<LibInfo> _displayLibs;
        size_t _selectedGameLib = 0;
        size_t _selectedDisplayLib = 0;
        bool _startGame;
};

#endif /* !MENU_HPP_ */

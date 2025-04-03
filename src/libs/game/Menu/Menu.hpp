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

    #define LIBRARY_NAME "Menu"

    #define ARCADE_TITLE_X 425
    #define ARCADE_TITLE_Y 150

    #define GAME_TITLE_X 600
    #define GAME_TITLE_Y 250

    #define DISPLAY_TITLE_X 200
    #define DISPLAY_TITLE_Y 250

    #define LIBS_HEIGHT_START 300
    #define LIBS_HEIGHT_THRESHOLD 45
    #define LIBS_HEIGHT 25
    #define LIBS_PADDING 10

    #define TEXT_WIDTH_MULTIPLIER 30

    #define SELECTED_LIBS_X 200
    #define SELECTED_LIBS_Y 600

    #define START_BUTTON_X 480
    #define START_BUTTON_Y 600
    #define START_BUTTON_WIDTH 75
    #define START_BUTTON_HEIGHT 25

class Menu : public IGame {
    public:
        Menu();
        ~Menu() = default;

        bool isGameOver(void) final;

        std::pair<float, std::string> getScore(void) final;

        bool isGameEnd(void) final;

        std::string getNewLib(void) final;

        void handleEvent(std::vector<RawEvent>) final;

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
            LibType type;
            ButtonPos pos;
        };

        // Library Getting
        bool isValidDirectory(const std::string &path);
        std::vector<std::string> findSharedLibraries(
            const std::string &directoryPath);
        std::vector<std::string> getLibraryFiles();

        // Library Categorization
        void sortLibraries(void);
        std::string isGameLibrary(const std::string &path);
        std::string isDisplayLibrary(const std::string &path);
        void categorizeLibraries(const std::vector<std::string> &paths);

        // Event Handling
        void checkGameClick(RawEvent event);
        void checkDisplayClick(RawEvent event);
        void checkStartButton(RawEvent event);
        void handleLeftClick(RawEvent event);
        void handleOneEvent(RawEvent event);

        // Rendering
        Entity renderTitle(void);
        Entity renderDisplayTitle(void);
        void setupLibButton(LibInfo &lib, int x, int y);
        std::map<EntityName, Entity> renderLibs(
            std::vector<LibInfo> &libs, size_t selectedLib, size_t x,
            std::string libPrefix);
        Entity renderGameTitle(void);
        Entity renderStartButton(void);

        std::vector<LibInfo> _gameLibs;
        std::vector<LibInfo> _displayLibs;
        size_t _selectedGameLib = 0;
        size_t _selectedDisplayLib = 0;
        bool _startGame;
};

#endif /* !MENU_HPP_ */

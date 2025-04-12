/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Menu
*/

#ifndef MENU_HPP_
    #define MENU_HPP_

    #include <iostream>
    #include <map>
    #include <vector>
    #include <cstdlib>

    #include "../../../core/LibGetter.hpp"
    #include "../../../core/ScoreManager.hpp"
    #include "../../../libs/display/interfaces/IDisplay.hpp"
    #include "../../../libs/game/interfaces/IGame.hpp"

    #define LIBRARY_PATH "./lib/"
    #define SCREEN_WIDTH 1024
    #define SCREEN_HEIGHT 768

    #define LIBRARY_NAME "Menu"

    #define ASSETS_DIR "./assets/menu/"

    #define ARCADE_TITLE_X 375
    #define ARCADE_TITLE_Y 50

    #define DISPLAY_TITLE_X 70
    #define DISPLAY_TITLE_Y 190

    #define GAME_TITLE_X 410
    #define GAME_TITLE_Y 190

    #define LIBS_HEIGHT_START 280
    #define LIBS_HEIGHT_THRESHOLD 45
    #define LIBS_HEIGHT 25
    #define LIBS_PADDING 10

    #define TEXT_WIDTH_MULTIPLIER 30

    #define DISPLAY_LIB_X 70
    #define GAME_LIB_X 410

    #define START_BUTTON_X 490
    #define START_BUTTON_Y 660

    #define QUIT_BUTTON_X 870
    #define QUIT_BUTTON_Y 33

    #define USERNAME_INPUT_X 140
    #define USERNAME_INPUT_Y 660

    #define SCOREBOARD_TITLE_X 750
    #define SCOREBOARD_TITLE_Y 190

    #define SCOREBOARD_CONTENT_X 755
    #define SCOREBOARD_CONTENT_Y 240
    #define SCOREBOARD_CONTENT_THRESHOLD 23

class Menu : public IGame {
    public:
        Menu();
        ~Menu() = default;

        bool isGameOver(void) final;

        std::pair<float, std::string> getScore(void) final;

        bool isGameEnd(void) final;

        std::string getNewLib(void) final;

        std::string getNewDisplay(void) final;

        void handleEvent(std::vector<RawEvent>) final;

        std::string getName(void) final;
        void setUsername(std::string username) final;

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
        using LibPos = std::pair<LibInfo, ButtonPos>;

        // Event Handling
        void checkGameClick(RawEvent event);
        void checkDisplayClick(RawEvent event);
        void checkStartButton(RawEvent event);
        void checkQuitButton(RawEvent event);
        void checkUsernameInputClick(RawEvent event);
        void handleLeftClick(RawEvent event);
        void checkUsernameInputKeyboard(RawEvent event);
        void checkShiftKey(RawEvent event);
        void checkControlKey(RawEvent event);
        void handleOneEvent(RawEvent event);

        // Rendering
        void renderTitle(std::map<EntityName, Entity> &entities);
        void renderDisplayTitle(std::map<EntityName, Entity> &entities);
        void renderGameTitle(std::map<EntityName, Entity> &entities);
        void setupLibButton(LibPos &libPos, int x, int y);
        void setEntityColor(Entity &cell, int r, int g, int b);
        std::map<EntityName, Entity> renderLibs(LibType libType);
        void renderStartButton(std::map<EntityName, Entity> &entities);
        void renderQuitButton(std::map<EntityName, Entity> &entities);
        void renderBackground(std::map<EntityName, Entity> &entities);
        void renderUsernameInput(std::map<EntityName, Entity> &entities);
        std::vector<std::string> getScoreboardContent(void);
        void renderScoreboardContent(std::map<EntityName, Entity> &entities,
            std::vector<std::string> content);
        void renderScoreboard(std::map<EntityName, Entity> &entities);
        void addSoundEntities(std::map<std::string, Entity> &entities);

        Entity createEntity(Shape shape,
            int x,
            int y,
            int cellWidth,
            int cellHeight,
            int offsetX,
            int offsetY,
            std::map<DisplayType, std::string> sprite);

        std::vector<LibPos> _gameLibs;
        std::vector<LibPos> _displayLibs;
        size_t _selectedGameLib = 0;
        size_t _selectedDisplayLib = 0;
        bool _startGame;
        std::string _username = "Username";
        bool _typingUsername = false;
        bool _shiftPressed = false;
        bool _controlPressed = false;
        std::vector<std::string> _scoreboardContent;
        bool _reloadScoreboard = true;
        std::vector<std::string> _sounds;
        bool _quit = false;
};

#endif /* !MENU_HPP_ */

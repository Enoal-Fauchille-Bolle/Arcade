/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Menu
*/

#include "Menu.hpp"

/**
 * @brief Construct a new Menu:: Menu object
 *
 * This constructor initializes the Menu object by scanning the
 * specified library path for shared libraries. It categorizes the
 * libraries into game and graphical libraries. If no libraries are
 * found, an error message is displayed.
 */
Menu::Menu()
{
    LibGetter libGetter = LibGetter();
    std::vector<LibInfo> gamesLibs = libGetter.getGameLibs();
    std::vector<LibInfo> displayLibs = libGetter.getDisplayLibs();

    _name = LIBRARY_NAME;
    _startGame = false;
    for (size_t i = 0; i < gamesLibs.size(); i++) {
        _gameLibs.push_back({gamesLibs[i], {0, 0, 0, 0}});
    }
    for (size_t i = 0; i < displayLibs.size(); i++) {
        _displayLibs.push_back({displayLibs[i], {0, 0, 0, 0}});
    }
}

/**
 * @brief Check if the game is over
 *
 * This function checks if the game is over. In this case, it always
 * returns false.
 *
 * @return true if the game is over
 * @return false if the game is not over
 */
bool Menu::isGameOver(void)
{
    return false;
}

/**
 * @brief Get the score of the game
 *
 * This function returns a pair containing the score and a string
 * representation of the score. In this case, it returns 0 and "0".
 *
 * @return std::pair<float, std::string> A pair containing the score and its
 * string representation
 */
std::pair<float, std::string> Menu::getScore(void)
{
    return std::pair<float, std::string>(0, "0");
}

/**
 * @brief Check if the game has ended
 *
 * This function checks if the user has selected a diplay libPos and
 * a game libPos. If so, it sets the _startGame variable to true, indicating
 * that the game should start. If not, it returns false.
 *
 * @return true if the user has selected libs
 * @return false if the user has not selected libs
 */
bool Menu::isGameEnd(void)
{
    return _startGame;
}

/**
 * @brief Get the name of the new library
 *
 * This function returns the name of the new library based on the
 * selected game library. If no game library is selected, it returns
 * the first game library in the list.
 *
 * @return std::string The name of the new library
 */
std::string Menu::getNewLib(void)
{
    return (_selectedGameLib >= _gameLibs.size())
               ? _gameLibs[0].first.path
               : _gameLibs[_selectedGameLib].first.path;
}

/**
 * @brief Get the name of the menu
 *
 * This function returns the name of the menu.
 *
 * @return std::string The name of the menu
 */
std::string Menu::getNewDisplay(void)
{
    if (!_startGame)
        return "";
    return (_selectedDisplayLib >= _displayLibs.size())
               ? _displayLibs[0].first.path
               : _displayLibs[_selectedDisplayLib].first.path;
}

////////////////////////////// Event Handling ///////////////////////////////

/**
 * @brief Check if the mouse click is on a game library button
 *
 * This function checks if the mouse click event is within the bounds
 * of any game library button. If so, it updates the selected game
 * library index.
 *
 * @param event The event to check
 */
void Menu::checkGameClick(RawEvent event)
{
    for (size_t i = 0; i < _gameLibs.size(); i++) {
        if (event.x >= _gameLibs[i].second.x - LIBS_PADDING &&
            event.x <= _gameLibs[i].second.x + _gameLibs[i].second.width +
                           LIBS_PADDING &&
            event.y <= (_gameLibs[i].second.y + 15) + LIBS_PADDING &&
            event.y >= (_gameLibs[i].second.y + 15) -
                           _gameLibs[i].second.height - LIBS_PADDING) {
            _selectedGameLib = i;
            return;
        }
    }
}

/**
 * @brief Check if the mouse click is on a display library button
 *
 * This function checks if the mouse click event is within the bounds
 * of any display library button. If so, it updates the selected
 * display library index.
 *
 * @param event The event to check
 */
void Menu::checkDisplayClick(RawEvent event)
{
    for (size_t i = 0; i < _displayLibs.size(); i++) {
        if (event.x >= _displayLibs[i].second.x - LIBS_PADDING &&
            event.x <= _displayLibs[i].second.x +
                           _displayLibs[i].second.width + LIBS_PADDING &&
            event.y <= (_displayLibs[i].second.y + 15) + LIBS_PADDING &&
            event.y >= (_displayLibs[i].second.y + 15) -
                           _displayLibs[i].second.height - LIBS_PADDING) {
            _selectedDisplayLib = i;
            return;
        }
    }
}

/**
 * @brief Check if the mouse click is on the start button
 *
 * This function checks if the mouse click event is within the bounds
 * of the start button. If so, it sets the _startGame variable to true.
 *
 * @param event The event to check
 */
void Menu::checkStartButton(RawEvent event)
{
    if (event.x >= START_BUTTON_X - LIBS_PADDING &&
        event.x <= START_BUTTON_X + START_BUTTON_WIDTH + LIBS_PADDING &&
        event.y <= (START_BUTTON_Y + 15) + LIBS_PADDING &&
        event.y >=
            (START_BUTTON_Y + 15) - START_BUTTON_HEIGHT - LIBS_PADDING) {
        _startGame = true;
    }
}

/**
 * @brief Handle a left mouse button click event
 *
 * This function checks if the left mouse button was clicked on a
 * library button. If so, it updates the selected library and sets
 * the selectingLibType to either DISPLAY or GAME.
 *
 * @param event The event to handle
 */
void Menu::handleLeftClick(RawEvent event)
{
    checkGameClick(event);
    checkDisplayClick(event);
    checkStartButton(event);
}

/**
 * @brief Handle a single event
 *
 * This function takes an event and processes it. If the event is a
 * left mouse button press, it calls the handleLeftClick function.
 *
 * @param event The event to handle
 */
void Menu::handleOneEvent(RawEvent event)
{
    if (event.type == PRESS && event.key == MOUSE_LEFT) {
        handleLeftClick(event);
    }
}

/**
 * @brief Handle events
 *
 * This function takes a vector of events and processes each event
 * using the handleOneEvent function.
 *
 * @param events A vector of events to handle
 */
void Menu::handleEvent(std::vector<RawEvent> events)
{
    for (const auto &event : events) {
        handleOneEvent(event);
    }
}

///////////////////////////////// Rendering /////////////////////////////////

/**
 * @brief Render the title of the menu
 *
 * This function creates an Entity object representing the title of
 * the menu. It sets the position, color, and text of the title.
 *
 * @return Entity The title entity
 */
Entity Menu::renderTitle(void)
{
    Entity titleText;

    titleText.type = TEXT;
    titleText.x = ARCADE_TITLE_X;
    titleText.y = ARCADE_TITLE_Y;
    titleText.width = 30;
    titleText.height = 0;
    titleText.rotate = 0;
    titleText.RGB[0] = 255;
    titleText.RGB[1] = 255;
    titleText.RGB[2] = 255;
    titleText.sprites[DisplayType::GRAPHICAL] = "Arcade Menu";
    titleText.sprites[DisplayType::TERMINAL] = "Arcade Menu";
    return titleText;
}

/**
 * @brief Render the display title
 *
 * This function creates an Entity object representing the display
 * title. It sets the position, color, and text of the display title.
 *
 * @return Entity The display title entity
 */
Entity Menu::renderDisplayTitle(void)
{
    Entity displaysTitle;

    displaysTitle.type = TEXT;
    displaysTitle.x = DISPLAY_TITLE_X;
    displaysTitle.y = DISPLAY_TITLE_Y;
    displaysTitle.width = 30;
    displaysTitle.height = 0;
    displaysTitle.rotate = 0;
    displaysTitle.RGB[0] = 255;
    displaysTitle.RGB[1] = 255;
    displaysTitle.RGB[2] = 255;
    displaysTitle.sprites[DisplayType::GRAPHICAL] = "Display Libraries:";
    displaysTitle.sprites[DisplayType::TERMINAL] = "Display Libraries:";
    return displaysTitle;
}

/**
 * @brief Setup the button position for a library
 *
 * This function sets up the position of a library button based on
 * its name and the specified coordinates.
 *
 * @param libPos The library information
 * @param x The x-coordinate of the button
 * @param y The y-coordinate of the button
 */
void Menu::setupLibButton(LibPos &libPos, int x, int y)
{
    libPos.second.x = x;
    libPos.second.y = y;
    libPos.second.width = libPos.first.name.length() * TEXT_WIDTH_MULTIPLIER;
    libPos.second.height = LIBS_HEIGHT;
}

void Menu::setEntityColor(Entity &entity, int r, int g, int b)
{
    entity.RGB[0] = r;
    entity.RGB[1] = g;
    entity.RGB[2] = b;
}

/**
 * @brief Render the libraries
 *
 * This function creates a map of Entity objects representing the
 * libraries. It sets the position, color, and text of each library
 * based on the selected library and whether the user is selecting
 * a game or display library.
 *
 * @param libs The vector of library information
 * @param selectedLib The index of the selected library
 * @param x The x-coordinate of the button
 * @return std::map<EntityName, Entity> A map of Entity objects representing
 * the libraries
 */
std::map<IGame::EntityName, Entity> Menu::renderLibs(LibType libType)
{
    std::map<EntityName, Entity> entities;
    std::string prefix;
    Entity libEntity;
    std::string libPrefix = (libType == DISPLAY) ? "display_" : "game_";
    std::vector<LibPos> &libs = (libType == DISPLAY) ? _displayLibs : _gameLibs;
    size_t selectedLib =
        (libType == DISPLAY) ? _selectedDisplayLib : _selectedGameLib;

    int x = (libType == DISPLAY) ? DISPLAY_LIB_X : GAME_LIB_X;
    int yPos = LIBS_HEIGHT_START;
    for (size_t i = 0; i < libs.size(); i++) {
        libEntity.type = TEXT;
        libEntity.x = x;
        libEntity.y = yPos;
        libEntity.width = 20;
        libEntity.height = 0;
        libEntity.rotate = 0;
        setupLibButton(libs[i], x, yPos);
        if (i == selectedLib) {
            prefix = " > ";
            setEntityColor(libEntity, 0, 255, 0);
        } else {
            prefix = "   ";
            setEntityColor(libEntity, 180, 180, 180);
        }
        libEntity.sprites[DisplayType::GRAPHICAL] =
            prefix + libs[i].first.name;
        libEntity.sprites[DisplayType::TERMINAL] = prefix + libs[i].first.name;
        entities[libPrefix + std::to_string(i)] = libEntity;
        yPos += LIBS_HEIGHT_THRESHOLD;
    }
    return entities;
}

/**
 * @brief Render the game title
 *
 * This function creates an Entity object representing the game title.
 * It sets the position, color, and text of the game title.
 *
 * @return Entity The game title entity
 */
Entity Menu::renderGameTitle(void)
{
    Entity gamesTitle;

    gamesTitle.type = TEXT;
    gamesTitle.x = GAME_TITLE_X;
    gamesTitle.y = GAME_TITLE_Y;
    gamesTitle.width = 30;
    gamesTitle.height = 0;
    gamesTitle.rotate = 0;
    setEntityColor(gamesTitle, 255, 255, 255);
    gamesTitle.sprites[DisplayType::GRAPHICAL] = "Game Libraries:";
    gamesTitle.sprites[DisplayType::TERMINAL] = "Game Libraries:";
    return gamesTitle;
}

/**
 * @brief Render the selected libraries
 *
 * This function creates an Entity object representing the selected
 * libraries. It sets the position, color, and text of the selected
 * libraries.
 *
 * @param gameName The name of the game library
 * @param displayName The name of the display library
 * @return Entity The selected libraries entity
 */
Entity Menu::renderStartButton(void)
{
    Entity selectedLibs;

    selectedLibs.type = TEXT;
    selectedLibs.x = START_BUTTON_X;
    selectedLibs.y = START_BUTTON_Y;
    selectedLibs.width = 30;
    selectedLibs.height = 0;
    selectedLibs.rotate = 0;
    setEntityColor(selectedLibs, 255, 255, 0);
    selectedLibs.sprites[DisplayType::GRAPHICAL] = "Start";
    selectedLibs.sprites[DisplayType::TERMINAL] = "Start";
    return selectedLibs;
}

/**
 * @brief Render the game menu
 *
 * This function creates a map of Entity objects representing the
 * game menu. It sets the position, color, and text of each entity
 * based on the selected libraries.
 *
 * @return std::map<EntityName, Entity> A map of Entity objects representing
 * the game menu
 */
std::map<IGame::EntityName, Entity> Menu::renderGame(void)
{
    std::map<EntityName, Entity> entities;
    std::map<EntityName, Entity> tempEntities;

    entities["title"] = renderTitle();
    entities["display_title"] = renderDisplayTitle();
    tempEntities = renderLibs(DISPLAY);
    for (const auto &pair : tempEntities) {
        entities[pair.first] = pair.second;
    }
    entities["games_title"] = renderGameTitle();
    tempEntities = renderLibs(GAME);
    for (const auto &pair : tempEntities) {
        entities[pair.first] = pair.second;
    }
    entities["start_button"] = renderStartButton();
    return entities;
}

/**
 * @brief Get the name of the menu
 *
 * This function returns the name of the menu.
 *
 * @return std::string The name of the menu
 */
std::string Menu::getName(void)
{
    return _name;
}

/**
 * @brief extern c
 *
 */
extern "C"
{
    __attribute__((constructor)) void constructor()
    {
    }

    __attribute__((destructor)) void destructor()
    {
    }

    Menu *GameEntryPoint(void)
    {
        return new Menu();
    }

    LibraryName getName(void)
    {
        return LIBRARY_NAME;
    }

    LibType getType(void)
    {
        return GAME;
    }
}

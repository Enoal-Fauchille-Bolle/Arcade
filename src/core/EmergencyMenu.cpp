/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** EmergencyMenu
*/

#include "EmergencyMenu.hpp"

EmergencyMenu::EmergencyMenu()
{
    LibGetter libGetter = LibGetter();
    std::vector<LibInfo> gamesLibs = libGetter.getGameLibs();
    std::vector<LibInfo> displayLibs = libGetter.getDisplayLibs();

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
bool EmergencyMenu::isGameOver(void)
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
std::pair<float, std::string> EmergencyMenu::getScore(void)
{
    return std::pair<float, std::string>(0, "0");
}

/**
 * @brief Check if the game has ended
 *
 * This function checks if the user has selected a diplay lib and
 * a game lib. If so, it sets the _startGame variable to true, indicating
 * that the game should start. If not, it returns false.
 *
 * @return true if the user has selected libs
 * @return false if the user has not selected libs
 */
bool EmergencyMenu::isGameEnd(void)
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
std::string EmergencyMenu::getNewLib(void)
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
std::string EmergencyMenu::getNewDisplay(void)
{
    if (!_startGame)
        return "";
    return (_selectedDisplayLib >= _displayLibs.size())
               ? _displayLibs[0].first.path
               : _displayLibs[_selectedDisplayLib].first.path;
}

/**
 * @brief Set the username
 *
 * This function sets the username for the player.
 *
 * @param username The username to set
 */
void EmergencyMenu::setUsername(std::string username)
{
    (void)username;
}

////////////////////////////// Event Handling ///////////////////////////////

/**
 * @brief Handle the Enter key event
 *
 * This function checks if the user has selected a game library and
 * a display library. If so, it sets the _startGame variable to true,
 * indicating that the game should start.
 */
void EmergencyMenu::handleHorizontalArrow(void)
{
    if (_libTypeSelection == DISPLAY) {
        _libTypeSelection = GAME;
        _selectingGameLib = _selectingDisplayLib;
        if (_selectingGameLib >= _gameLibs.size()) {
            _selectingGameLib = _gameLibs.size() - 1;
        }
    } else {
        _libTypeSelection = DISPLAY;
        _selectingDisplayLib = _selectingGameLib;
        if (_selectingDisplayLib >= _displayLibs.size()) {
            _selectingDisplayLib = _displayLibs.size() - 1;
        }
    }
}

/**
 * @brief Handle the Enter key event
 *
 * This function checks if the user has selected a game library and
 * a display library. If so, it sets the _startGame variable to true,
 * indicating that the game should start.
 */
void EmergencyMenu::handleDownArrow(void)
{
    if (_libTypeSelection == DISPLAY) {
        if (_selectingDisplayLib < _displayLibs.size() - 1) {
            _selectingDisplayLib++;
        } else if (!_selectingStartButton) {
            _selectingStartButton = true;
        } else {
            _selectingDisplayLib = 0;
            _selectingStartButton = false;
        }
    } else {
        if (_selectingGameLib < _gameLibs.size() - 1) {
            _selectingGameLib++;
        } else if (!_selectingStartButton) {
            _selectingStartButton = true;
        } else {
            _selectingGameLib = 0;
            _selectingStartButton = false;
        }
    }
}

/**
 * @brief Handle the Enter key event
 *
 * This function checks if the user has selected a game library and
 * a display library. If so, it sets the _startGame variable to true,
 * indicating that the game should start.
 */
void EmergencyMenu::handleUpArrow(void)
{
    if (_libTypeSelection == DISPLAY) {
        if (_selectingStartButton) {
            _selectingDisplayLib = _displayLibs.size() - 1;
            _selectingStartButton = false;
        } else if (_selectingDisplayLib > 0) {
            _selectingDisplayLib--;
        } else {
            _selectingStartButton = true;
        }
    } else {
        if (_selectingStartButton) {
            _selectingGameLib = _gameLibs.size() - 1;
            _selectingStartButton = false;
        } else if (_selectingGameLib > 0) {
            _selectingGameLib--;
        } else {
            _selectingStartButton = true;
        }
    }
}

void EmergencyMenu::handleEnter(void)
{
    if (_selectingStartButton) {
        _startGame = true;
        return;
    }
    if (_libTypeSelection == DISPLAY) {
        _selectedDisplayLib = _selectingDisplayLib;
    } else {
        _selectedGameLib = _selectingGameLib;
    }
}

/**
 * @brief Handle a single event
 *
 * This function takes an event and processes it. If the event is a
 * left mouse button press, it calls the handleLeftClick function.
 *
 * @param event The event to handle
 */
void EmergencyMenu::handleOneEvent(RawEvent event)
{
    if (event.type == PRESS && event.key == KEYBOARD_UP)
        handleUpArrow();
    if (event.type == PRESS && event.key == KEYBOARD_DOWN)
        handleDownArrow();
    if (event.type == PRESS &&
        (event.key == KEYBOARD_RIGHT || event.key == KEYBOARD_LEFT))
        handleHorizontalArrow();
    if (event.type == PRESS && event.key == KEYBOARD_ENTER)
        handleEnter();
}

/**
 * @brief Handle events
 *
 * This function takes a vector of events and processes each event
 * using the handleOneEvent function.
 *
 * @param events A vector of events to handle
 */
void EmergencyMenu::handleEvent(std::vector<RawEvent> events)
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
Entity EmergencyMenu::renderTitle(void)
{
    Entity titleText;

    titleText.type = TEXT;
    titleText.x = ARCADE_TITLE_X;
    titleText.y = ARCADE_TITLE_Y;
    titleText.width = 20;
    titleText.height = 0;
    titleText.rotate = 0;
    setEntityColor(titleText, 255, 255, 255);
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
Entity EmergencyMenu::renderDisplayTitle(void)
{
    Entity displaysTitle;

    displaysTitle.type = TEXT;
    displaysTitle.x = DISPLAY_TITLE_X;
    displaysTitle.y = DISPLAY_TITLE_Y;
    displaysTitle.width = 20;
    displaysTitle.height = 0;
    displaysTitle.rotate = 0;
    setEntityColor(displaysTitle, 255, 255, 255);
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
 * @param lib The library information
 * @param x The x-coordinate of the button
 * @param y The y-coordinate of the button
 */
void EmergencyMenu::setupLibButton(LibPos &lib, int x, int y)
{
    lib.second.x = x;
    lib.second.y = y;
    lib.second.width = lib.first.name.length() * TEXT_WIDTH_MULTIPLIER;
    lib.second.height = LIBS_HEIGHT;
}

void EmergencyMenu::setEntityColor(Entity &entity, int r, int g, int b)
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
std::map<IGame::EntityName, Entity> EmergencyMenu::renderLibs(LibType libType)
{
    std::map<EntityName, Entity> entities;
    std::string prefix;
    Entity libEntity;
    std::string libPrefix = (libType == DISPLAY) ? "display_" : "game_";
    std::vector<LibPos> &libs =
        (libType == DISPLAY) ? _displayLibs : _gameLibs;
    size_t selectedLib =
        (libType == DISPLAY) ? _selectedDisplayLib : _selectedGameLib;
    size_t selectingLib =
        (libType == DISPLAY) ? _selectingDisplayLib : _selectingGameLib;

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
        if (i == selectingLib && libType == _libTypeSelection &&
            !_selectingStartButton) {
            prefix = " * ";
            setEntityColor(libEntity, 0, 255, 255);
        } else if (i == selectedLib) {
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
Entity EmergencyMenu::renderGameTitle(void)
{
    Entity gamesTitle;

    gamesTitle.type = TEXT;
    gamesTitle.x = GAME_TITLE_X;
    gamesTitle.y = GAME_TITLE_Y;
    gamesTitle.width = 20;
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
Entity EmergencyMenu::renderStartButton(void)
{
    Entity selectedLibs;
    std::string startText = _selectingStartButton ? "> Start <" : "Start";

    selectedLibs.type = TEXT;
    selectedLibs.x =
        _selectingStartButton ? START_BUTTON_X - 15 : START_BUTTON_X;
    selectedLibs.y = START_BUTTON_Y;
    selectedLibs.width = 20;
    selectedLibs.height = 0;
    selectedLibs.rotate = 0;
    setEntityColor(selectedLibs, 255, 255, 0);
    if (_selectingStartButton)
        setEntityColor(selectedLibs, 0, 255, 255);
    selectedLibs.sprites[DisplayType::GRAPHICAL] = startText;
    selectedLibs.sprites[DisplayType::TERMINAL] = startText;
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
std::map<IGame::EntityName, Entity> EmergencyMenu::renderGame(void)
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
std::string EmergencyMenu::getName(void)
{
    return "Emergency Menu";
}

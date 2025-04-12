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
    _sounds.push_back("assets/music_menu.ogg");
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
    return _startGame;
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
    return std::pair<float, std::string>(0, _username);
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
 * @brief Set the username
 *
 * This function sets the username for the player.
 *
 * @param username The username to set
 */
void Menu::setUsername(std::string username)
{
    _username = username;
}

////////////////////////////// Event Handling ///////////////////////////////

//-------------------------------- Game Lib --------------------------------//

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
            if (_selectedGameLib != i) {
                _sounds.push_back(std::string(ASSETS_DIR) + "click2.ogg");
            }
            _selectedGameLib = i;
            _reloadScoreboard = true;
            return;
        }
    }
}

//------------------------------ Display Lib ------------------------------//

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
            if (_selectedDisplayLib != i) {
                _sounds.push_back(std::string(ASSETS_DIR) + "click2.ogg");
            }
            _selectedDisplayLib = i;
            return;
        }
    }
}

//------------------------------ Start Button ------------------------------//

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
    if (event.x >= START_BUTTON_X - 105 &&
        event.x <= (START_BUTTON_X - 105) + 629 / 2 &&
        event.y >= START_BUTTON_Y - 20 &&
        event.y <= (START_BUTTON_Y - 20) + 197 / 2) {
        _startGame = true;
        _sounds.push_back("");
        _sounds.push_back(std::string(ASSETS_DIR) + "start.ogg");
    }
}

//----------------------------- Username Input -----------------------------//

/**
 * @brief Check if the mouse click is on the username input field
 *
 * This function checks if the mouse click event is within the bounds
 * of the username input field. If so, it sets the _typingUsername
 * variable to true.
 *
 * @param event The event to check
 */
void Menu::checkUsernameInputClick(RawEvent event)
{
    if (event.x >= USERNAME_INPUT_X - 105 &&
        event.x <= (USERNAME_INPUT_X - 105) + 629 / 2 &&
        event.y >= USERNAME_INPUT_Y - 20 &&
        event.y <= (USERNAME_INPUT_Y - 20) + 197 / 2) {
        if (!_typingUsername) {
            _sounds.push_back(std::string(ASSETS_DIR) + "click2.ogg");
        }
        _typingUsername = true;
    } else {
        if (_typingUsername) {
            _sounds.push_back(std::string(ASSETS_DIR) + "click2.ogg");
        }
        _typingUsername = false;
    }
}

/**
 * @brief Check if the username input is valid
 *
 * This function checks if the username input is valid. If the
 * backspace key is pressed, it removes the last character from the
 * username. If the shift key is pressed, it sets the _shiftPressed
 * variable to true. If a letter key is pressed, it adds the
 * corresponding character to the username.
 *
 * @param event The event to check
 */
void Menu::checkUsernameInputKeyboard(RawEvent event)
{
    if (event.key == EventKey::KEYBOARD_BACKSPACE && !_username.empty()) {
        if (!_controlPressed) {
            _username.pop_back();
        } else {
            _username = "";
        }
        return;
    }

    if (event.key == EventKey::KEYBOARD_BACKSPACE) {
        return;
    }

    if (event.key >= EventKey::KEYBOARD_A &&
        event.key <= EventKey::KEYBOARD_Z) {
        if (_username.length() < 8) {
            char character = (_shiftPressed ? 'A' : 'a') +
                             (static_cast<int>(event.key) -
                                 static_cast<int>(EventKey::KEYBOARD_A));
            _username += character;
        }
    }
}

/**
 * @brief Check if the shift key is pressed
 *
 * This function checks if the shift key is pressed or released.
 * If pressed, it sets the _shiftPressed variable to true. If
 * released, it sets it to false.
 *
 * @param event The event to check
 */
void Menu::checkShiftKey(RawEvent event)
{
    if (event.type == PRESS &&
        (event.key == KEYBOARD_LSHIFT || event.key == KEYBOARD_RSHIFT)) {
        _shiftPressed = true;
    } else if (event.type == RELEASE && (event.key == KEYBOARD_LSHIFT ||
                                            event.key == KEYBOARD_RSHIFT)) {
        _shiftPressed = false;
    }
}

/**
 * @brief Check if the control key is pressed
 *
 * This function checks if the control key is pressed or released.
 * If pressed, it sets the _controlPressed variable to true. If
 * released, it sets it to false.
 *
 * @param event The event to check
 */
void Menu::checkControlKey(RawEvent event)
{
    if (event.type == PRESS &&
        (event.key == KEYBOARD_LCTRL || event.key == KEYBOARD_RCTRL)) {
        _controlPressed = true;
    } else if (event.type == RELEASE &&
               (event.key == KEYBOARD_LCTRL || event.key == KEYBOARD_RCTRL)) {
        _controlPressed = false;
    }
}

//-------------------------------- Handling --------------------------------//

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
    checkUsernameInputClick(event);
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
    } else if (event.type == PRESS) {
        checkUsernameInputKeyboard(event);
    }
    checkShiftKey(event);
    checkControlKey(event);
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
 * @brief Create an entity with standard parameters
 *
 * This function creates an Entity object with the specified shape,
 * position, size, and sprite.
 *
 * @param shape The shape type for the entity
 * @param x The x-coordinate of the entity
 * @param y The y-coordinate of the entity
 * @param cellWidth The width of the entity
 * @param cellHeight The height of the entity
 * @param offsetX The x offset to apply
 * @param offsetY The y offset to apply
 * @param sprite A map of display types to sprite strings
 * @return Entity The created Entity object
 */
Entity Menu::createEntity(Shape shape,
    int x,
    int y,
    int cellWidth,
    int cellHeight,
    int offsetX,
    int offsetY,
    std::map<DisplayType, std::string> sprite)
{
    Entity cell;

    cell.type = shape;
    cell.x = offsetX + x * cellWidth;
    cell.y = offsetY + y * cellHeight;
    cell.width = cellWidth;
    cell.height = cellHeight;
    cell.rotate = 0;
    cell.RGB[0] = 255;
    cell.RGB[1] = 255;
    cell.RGB[2] = 255;
    for (auto &it : sprite) {
        cell.sprites[it.first] = it.second;
    }
    return cell;
}

/**
 * @brief Set the color of an entity
 *
 * This function sets the RGB color of an entity.
 *
 * @param entity The entity to set the color for
 * @param r The red component
 * @param g The green component
 * @param b The blue component
 */
void Menu::setEntityColor(Entity &entity, int r, int g, int b)
{
    entity.RGB[0] = r;
    entity.RGB[1] = g;
    entity.RGB[2] = b;
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

    renderTitle(entities);
    renderDisplayTitle(entities);
    tempEntities = renderLibs(DISPLAY);
    for (const auto &pair : tempEntities) {
        entities[pair.first] = pair.second;
    }
    renderGameTitle(entities);
    tempEntities = renderLibs(GAME);
    for (const auto &pair : tempEntities) {
        entities[pair.first] = pair.second;
    }
    renderStartButton(entities);
    renderBackground(entities);
    renderUsernameInput(entities);
    renderScoreboard(entities);
    addSoundEntities(entities);
    return entities;
}

//--------------------------------- Title ---------------------------------//

/**
 * @brief Render the title of the menu
 *
 * This function creates an Entity object representing the title of
 * the menu. It sets the position, color, and text of the title.
 *
 * @return Entity The title entity
 */
void Menu::renderTitle(std::map<EntityName, Entity> &entities)
{
    Entity titleText;
    Entity titleFrame = createEntity(Shape::RECTANGLE, 0, 0, 629 / 1.75,
        197 / 1.75, ARCADE_TITLE_X - 38, ARCADE_TITLE_Y - 25,
        {{DisplayType::TERMINAL, ""},
            {DisplayType::GRAPHICAL, std::string(ASSETS_DIR) + "button.png"}});

    titleText.type = TEXT;
    titleText.x = ARCADE_TITLE_X;
    titleText.y = ARCADE_TITLE_Y;
    titleText.width = 50;
    titleText.height = 0;
    titleText.rotate = 0;
    setEntityColor(titleText, 78, 200, 245);
    titleText.sprites[DisplayType::GRAPHICAL] = "Arcade Menu";
    titleText.sprites[DisplayType::TERMINAL] = "Arcade Menu";
    entities["C-title"] = titleText;
    setEntityColor(titleFrame, 0, 0, 0);
    entities["B-arcadeMenu"] = titleFrame;
}

//----------------------------- Display Title -----------------------------//

/**
 * @brief Render the display title
 *
 * This function creates an Entity object representing the display
 * title. It sets the position, color, and text of the display title.
 *
 * @return Entity The display title entity
 */
void Menu::renderDisplayTitle(std::map<EntityName, Entity> &entities)
{
    Entity displaysTitle;
    Entity displaysFrame = createEntity(Shape::RECTANGLE, 0, 0, 629 / 2.4,
        197 / 2.4, DISPLAY_TITLE_X - 20, DISPLAY_TITLE_Y - 21,
        {{DisplayType::TERMINAL, ""},
            {DisplayType::GRAPHICAL, std::string(ASSETS_DIR) + "button.png"}});

    displaysTitle.type = TEXT;
    displaysTitle.x = DISPLAY_TITLE_X;
    displaysTitle.y = DISPLAY_TITLE_Y;
    displaysTitle.width = 30;
    displaysTitle.height = 0;
    displaysTitle.rotate = 0;
    setEntityColor(displaysTitle, 78, 200, 245);
    displaysTitle.sprites[DisplayType::GRAPHICAL] = "Display Libraries";
    displaysTitle.sprites[DisplayType::TERMINAL] = "Display Libraries";
    entities["C-displayTitle"] = displaysTitle;
    setEntityColor(displaysFrame, 0, 0, 0);
    entities["B-displayMenu"] = displaysFrame;
}

//------------------------------ Game Title ------------------------------//

/**
 * @brief Render the game title
 *
 * This function creates an Entity object representing the game title.
 * It sets the position, color, and text of the game title.
 *
 * @return Entity The game title entity
 */
void Menu::renderGameTitle(std::map<EntityName, Entity> &entities)
{
    Entity gamesTitle;
    Entity gamesFrame = createEntity(Shape::RECTANGLE, 0, 0, 629 / 2.4,
        197 / 2.4, GAME_TITLE_X - 20, GAME_TITLE_Y - 21,
        {{DisplayType::TERMINAL, ""},
            {DisplayType::GRAPHICAL, std::string(ASSETS_DIR) + "button.png"}});

    gamesTitle.type = TEXT;
    gamesTitle.x = GAME_TITLE_X + 10;
    gamesTitle.y = GAME_TITLE_Y;
    gamesTitle.width = 30;
    gamesTitle.height = 0;
    gamesTitle.rotate = 0;
    setEntityColor(gamesTitle, 78, 200, 245);
    gamesTitle.sprites[DisplayType::GRAPHICAL] = "Game Libraries";
    gamesTitle.sprites[DisplayType::TERMINAL] = "Game Libraries";
    entities["C-gameTitle"] = gamesTitle;
    setEntityColor(gamesFrame, 0, 0, 0);
    entities["B-gameMenu"] = gamesFrame;
}

//------------------------------- Libraries -------------------------------//

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
    std::vector<LibPos> &libs =
        (libType == DISPLAY) ? _displayLibs : _gameLibs;
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
            setEntityColor(libEntity, 0, 255, 255);
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

//------------------------------ Start Button ------------------------------//

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
void Menu::renderStartButton(std::map<EntityName, Entity> &entities)
{
    Entity startText;
    Entity startFrame = createEntity(Shape::RECTANGLE, 0, 0, 629 / 2, 197 / 2,
        START_BUTTON_X - 105, START_BUTTON_Y - 20,
        {{DisplayType::TERMINAL, ""},
            {DisplayType::GRAPHICAL, std::string(ASSETS_DIR) + "button.png"}});

    startText.type = TEXT;
    startText.x = START_BUTTON_X - 5;
    startText.y = START_BUTTON_Y;
    startText.width = 50;
    startText.height = 0;
    startText.rotate = 0;
    setEntityColor(startText, 78, 200, 245);
    startText.sprites[DisplayType::GRAPHICAL] = "Start";
    startText.sprites[DisplayType::TERMINAL] = "Start";
    entities["C-startText"] = startText;
    setEntityColor(startFrame, 0, 0, 0);
    entities["B-startFrame"] = startFrame;
}

//------------------------------- Background -------------------------------//

/**
 * @brief Render the background
 *
 * This function creates an Entity object representing the background
 * of the menu. It sets the position, color, and sprite of the
 * background.
 *
 * @return Entity The background entity
 */
void Menu::renderBackground(std::map<EntityName, Entity> &entities)
{
    Entity background =
        createEntity(Shape::RECTANGLE, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0,
            {{DisplayType::TERMINAL, " "},
                {DisplayType::GRAPHICAL,
                    std::string(ASSETS_DIR) + "background2.jpg"}});
    setEntityColor(background, 0, 0, 0);
    entities["A-background"] = background;
}

//----------------------------- Username Input -----------------------------//

/**
 * @brief Render the username input field
 *
 * This function creates an Entity object representing the username
 * input field. It sets the position, color, and text of the input
 * field.
 *
 * @return Entity The username input entity
 */
void Menu::renderUsernameInput(std::map<EntityName, Entity> &entities)
{
    Entity startText;
    Entity usernameInputFrame = createEntity(Shape::RECTANGLE, 0, 0, 629 / 2,
        197 / 2, USERNAME_INPUT_X - 105, USERNAME_INPUT_Y - 20,
        {{DisplayType::TERMINAL, ""},
            {DisplayType::GRAPHICAL, std::string(ASSETS_DIR) + "button.png"}});
    std::string username = _username;

    startText.type = TEXT;
    startText.x = USERNAME_INPUT_X - 70;
    startText.y = USERNAME_INPUT_Y - 3;
    startText.width = 50;
    startText.height = 0;
    startText.rotate = 0;
    if (_typingUsername)
        setEntityColor(startText, 255, 255, 255);
    else
        setEntityColor(startText, 180, 180, 180);
    if (_typingUsername) {
        static int blinkCount = 0;
        blinkCount = (blinkCount + 1) % 60;
        if (blinkCount < 30) {
            username += "|";
        }
    }
    startText.sprites[DisplayType::GRAPHICAL] = username;
    startText.sprites[DisplayType::TERMINAL] = username;
    entities["C-v"] = startText;
    setEntityColor(usernameInputFrame, 0, 0, 0);
    entities["B-userInput"] = usernameInputFrame;
}

//------------------------------- Scoreboard -------------------------------//

/**
 * @brief Get the content of the scoreboard
 *
 * This function retrieves the scores from the ScoreManager and
 * formats them into a string for display.
 *
 * @return std::string The formatted scoreboard content
 */
std::vector<std::string> Menu::getScoreboardContent(void)
{
    ScoreManager scoreManager;
    std::string gameName = _gameLibs[_selectedGameLib].first.name;
    std::string fileName = "score/score_" + gameName + ".txt";
    std::vector<std::pair<float, std::string>> scores =
        scoreManager.loadScoresFromFile(fileName);

    _scoreboardContent.clear();
    for (size_t i = 0; i < scores.size() && i < 20; i++) {
        _scoreboardContent.push_back(
            scores[i].second + ": " +
            std::to_string(static_cast<int>(scores[i].first)));
    }

    if (_scoreboardContent.empty()) {
        _scoreboardContent.push_back("No scores available");
    }

    _reloadScoreboard = false;
    return _scoreboardContent;
}

void Menu::renderScoreboardContent(
    std::map<EntityName, Entity> &entities, std::vector<std::string> content)
{
    Entity scoreboardContent;
    size_t y = 0;

    for (size_t i = 0; i < content.size(); i++) {
        scoreboardContent.type = TEXT;
        scoreboardContent.x = SCOREBOARD_CONTENT_X;
        scoreboardContent.y = SCOREBOARD_CONTENT_Y + y;
        scoreboardContent.width = 20;
        scoreboardContent.height = 0;
        scoreboardContent.rotate = 0;
        setEntityColor(scoreboardContent, 78, 200, 245);
        scoreboardContent.sprites[DisplayType::GRAPHICAL] = content[i];
        scoreboardContent.sprites[DisplayType::TERMINAL] = content[i];
        entities["C-scoreboardContent" + std::to_string(i)] =
            scoreboardContent;
        y += SCOREBOARD_CONTENT_THRESHOLD;
    }
}

/**
 * @brief Render the scoreboard
 *
 * This function creates an Entity object representing the scoreboard.
 * It sets the position, color, and text of the scoreboard.
 *
 * @return Entity The scoreboard entity
 */
void Menu::renderScoreboard(std::map<EntityName, Entity> &entities)
{
    Entity scoreboardTitle;
    std::vector<std::string> content =
        _reloadScoreboard ? getScoreboardContent() : _scoreboardContent;
    Entity scoreboardFrame = createEntity(Shape::RECTANGLE, 0, 0, 629 / 2.4,
        1380 / 2.4, SCOREBOARD_TITLE_X - 20, SCOREBOARD_TITLE_Y - 21,
        {{DisplayType::TERMINAL, ""},
            {DisplayType::GRAPHICAL,
                std::string(ASSETS_DIR) + "scoreboard.png"}});

    scoreboardTitle.type = TEXT;
    scoreboardTitle.x = SCOREBOARD_TITLE_X + 30;
    scoreboardTitle.y = SCOREBOARD_TITLE_Y;
    scoreboardTitle.width = 30;
    scoreboardTitle.height = 0;
    scoreboardTitle.rotate = 0;
    setEntityColor(scoreboardTitle, 78, 200, 245);
    scoreboardTitle.sprites[DisplayType::GRAPHICAL] = "Leaderboard";
    scoreboardTitle.sprites[DisplayType::TERMINAL] = "Leaderboard";
    entities["C-scoreboardTitle"] = scoreboardTitle;
    setEntityColor(scoreboardFrame, 0, 0, 0);
    entities["B-scoreboardMenu"] = scoreboardFrame;
    renderScoreboardContent(entities, content);
}

//--------------------------------- Sounds ---------------------------------//

/**
 * @brief Add sound entities to the map
 *
 * This function creates Entity objects representing sound effects
 * and adds them to the entities map. It clears the _sounds vector
 * after adding the entities.
 *
 * @param entities The map of entities to add the sound entities to
 */
void Menu::addSoundEntities(std::map<std::string, Entity> &entities)
{
    for (size_t i = 0; i < _sounds.size(); i++) {
        Entity sound = createEntity(Shape::MUSIC, 0, 0, 0, 0, 0, 0,
            {{DisplayType::TERMINAL, " "},
                {DisplayType::GRAPHICAL, _sounds[i]}});
        entities["sound" + std::to_string(i)] = sound;
    }
    _sounds.clear();
}

///////////////////////////// Extern C Functions /////////////////////////////

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

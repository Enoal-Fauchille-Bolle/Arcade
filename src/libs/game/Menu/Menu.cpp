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
    std::vector<std::string> libPaths = getLibraryFiles();

    _name = LIBRARY_NAME;
    _startGame = false;
    if (libPaths.empty()) {
        std::cerr << "No libraries found in " << LIBRARY_PATH << std::endl;
        return;
    }
    categorizeLibraries(libPaths);
}

/**
 * @brief Check if a directory is valid
 *
 * This function checks if the given path exists and is a directory.
 *
 * @param path The path to check
 * @return true if the path is a valid directory
 * @return false if the path does not exist or is not a directory
 */
bool Menu::isValidDirectory(const std::string &path)
{
    return std::filesystem::exists(path) &&
           std::filesystem::is_directory(path);
}

/**
 * @brief Find all shared libraries in a directory
 *
 * This function scans the specified directory for shared libraries
 * (files with a .so extension) and returns their paths in a vector.
 *
 * @param directoryPath The path to the directory to scan
 * @return std::vector<std::string> A vector of strings containing the paths to
 * the shared libraries
 */
std::vector<std::string> Menu::findSharedLibraries(
    const std::string &directoryPath)
{
    std::vector<std::string> libraryPaths;

    for (const auto &entry :
        std::filesystem::directory_iterator(directoryPath)) {
        if (entry.is_regular_file() && entry.path().extension() == ".so") {
            libraryPaths.push_back(entry.path().string());
        }
    }
    return libraryPaths;
}

/**
 * @brief Get all shared libraries in the library path
 *
 * This function scans the LIBRARY_PATH directory for shared libraries
 * (files with a .so extension) and returns their paths in a vector.
 * If the directory does not exist or an error occurs during scanning,
 * an empty vector is returned.
 *
 * @return std::vector<std::string> A vector of strings containing the paths
 */
std::vector<std::string> Menu::getLibraryFiles()
{
    std::string libPath = LIBRARY_PATH;

    if (!isValidDirectory(libPath)) {
        std::cerr << "Library directory not found: " << libPath << std::endl;
        return {};
    }
    try {
        return findSharedLibraries(libPath);
    } catch (const std::exception &e) {
        std::cerr << "Error scanning library directory: " << e.what()
                  << std::endl;
        return {};
    }
}

/**
 * @brief Sort the game and display libraries
 *
 * This function sorts the game and display libraries in alphabetical
 * order based on their names. It uses the std::sort algorithm to
 * perform the sorting.
 */
void Menu::sortLibraries()
{
    std::sort(_gameLibs.begin(), _gameLibs.end(),
        [](const LibInfo &a, const LibInfo &b) { return a.name < b.name; });
    std::sort(_displayLibs.begin(), _displayLibs.end(),
        [](const LibInfo &a, const LibInfo &b) { return a.name < b.name; });
}

/**
 * @brief Check if the library is a game library
 *
 * This function attempts to load a game library from the given path
 * and returns its name if successful. If the library cannot be loaded,
 * an empty string is returned.
 *
 * @param path The path to the library
 * @return std::string The name of the game library, or an empty string
 */
std::string Menu::isGameLibrary(const std::string &path)
{
    DLLoader<LibraryName> loader;
    LibraryName name;
    libType type;

    try {
        name = loader.getName(path);
        type = loader.getType(path);
        if (type != GAME) {
            return "";
        }
        return name;
    } catch (const std::exception &) {
        return "";
    }
}

/**
 * @brief Check if the library is a display library
 *
 * This function attempts to load a display library from the given path
 * and returns its name if successful. If the library cannot be loaded,
 * an empty string is returned.
 *
 * @param path The path to the library
 * @return std::string The name of the display library, or an empty string
 */
std::string Menu::isDisplayLibrary(const std::string &path)
{
    DLLoader<LibraryName> loader;
    LibraryName name;
    libType type;

    try {
        name = loader.getName(path);
        type = loader.getType(path);
        if (type != DISPLAY) {
            return "";
        }
        return name;
    } catch (const std::exception &) {
        return "";
    }
}

/**
 * @brief Categorize libraries into game and display libraries
 *
 * This function takes a vector of library paths and categorizes them
 * into game and display libraries. It uses the tryLoadGameLibrary and
 * tryLoadDisplayLibrary functions to attempt to load each library.
 *
 * @param paths A vector of strings containing the paths to the libraries
 */
void Menu::categorizeLibraries(const std::vector<std::string> &paths)
{
    std::string libName;

    _gameLibs.clear();
    _displayLibs.clear();
    for (const auto &path : paths) {
        std::cout << "  " << path << std::endl;
    }
    for (const auto &path : paths) {
        if (path.find("arcade_menu.so") != std::string::npos)
            continue;
        libName = isGameLibrary(path);
        if (!libName.empty()) {
            _gameLibs.push_back({path, libName, GAME, {0, 0, 0, 0}});
            std::cout << "Found game library: " << libName << " at " << path
                      << std::endl;
            continue;
        }
        libName = isDisplayLibrary(path);
        if (!libName.empty()) {
            _displayLibs.push_back({path, libName, DISPLAY, {0, 0, 0, 0}});
            std::cout << "Found graphical library: " << libName << " at "
                      << path << std::endl;
        } else {
            std::cerr << "Failed to identify library type for " << path
                      << std::endl;
        }
    }
    sortLibraries();
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
 * This function checks if the user has selected a diplay lib and
 * a game lib. If so, it sets the _startGame variable to true, indicating
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
               ? _gameLibs[0].path
               : _gameLibs[_selectedGameLib].path;
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
void Menu::checkGameClick(rawEvent event)
{
    for (size_t i = 0; i < _gameLibs.size(); i++) {
        if (event.x >= _gameLibs[i].pos.x - LIBS_PADDING &&
            event.x <=
                _gameLibs[i].pos.x + _gameLibs[i].pos.width + LIBS_PADDING &&
            event.y <= _gameLibs[i].pos.y + LIBS_PADDING &&
            event.y >=
                _gameLibs[i].pos.y - _gameLibs[i].pos.height - LIBS_PADDING) {
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
void Menu::checkDisplayClick(rawEvent event)
{
    for (size_t i = 0; i < _displayLibs.size(); i++) {
        if (event.x >= _displayLibs[i].pos.x - LIBS_PADDING &&
            event.x <= _displayLibs[i].pos.x + _displayLibs[i].pos.width +
                           LIBS_PADDING &&
            event.y <= _displayLibs[i].pos.y + LIBS_PADDING &&
            event.y >= _displayLibs[i].pos.y - _displayLibs[i].pos.height -
                           LIBS_PADDING) {
            _selectedDisplayLib = i;
            return;
        }
    }
}

void Menu::checkStartButton(rawEvent event)
{
    if (event.x >= START_BUTTON_X - LIBS_PADDING &&
        event.x <= START_BUTTON_X + START_BUTTON_WIDTH + LIBS_PADDING &&
        event.y <= START_BUTTON_Y + LIBS_PADDING &&
        event.y >= START_BUTTON_Y - START_BUTTON_HEIGHT - LIBS_PADDING) {
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
void Menu::handleLeftClick(rawEvent event)
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
void Menu::handleOneEvent(rawEvent event)
{
    if (event.type == PRESS && event.key == MOUSE_LEFT) {
        handleLeftClick(event);
    }
    if (event.type == PRESS && event.key == KEY_ESCAPE) {
        _startGame = true;
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
void Menu::handleEvent(std::vector<rawEvent> events)
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
    titleText.width = 0;
    titleText.height = 0;
    titleText.rotate = 0;
    titleText.RGB[0] = 255;
    titleText.RGB[1] = 255;
    titleText.RGB[2] = 255;
    titleText.sprites["SFML"] = "Arcade Menu";
    titleText.sprites["SDL"] = "Arcade Menu";
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
    displaysTitle.width = 0;
    displaysTitle.height = 0;
    displaysTitle.rotate = 0;
    displaysTitle.RGB[0] = 255;
    displaysTitle.RGB[1] = 255;
    displaysTitle.RGB[2] = 255;
    displaysTitle.sprites["SFML"] = "Display Libraries:";
    displaysTitle.sprites["SDL"] = "Display Libraries:";
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
void Menu::setupLibButton(LibInfo &lib, int x, int y)
{
    lib.pos.x = x;
    lib.pos.y = y;
    lib.pos.width = lib.name.length() * TEXT_WIDTH_MULTIPLIER;
    lib.pos.height = LIBS_HEIGHT;
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
std::map<IGame::EntityName, Entity> Menu::renderLibs(
    std::vector<LibInfo> &libs,
    size_t selectedLib,
    size_t x,
    std::string libPrefix)
{
    std::map<EntityName, Entity> entities;

    int yPos = LIBS_HEIGHT_START;
    for (size_t i = 0; i < libs.size(); i++) {
        Entity libEntity;
        libEntity.type = TEXT;
        libEntity.x = x;
        libEntity.y = yPos;
        libEntity.width = 0;
        libEntity.height = 0;
        libEntity.rotate = 0;
        setupLibButton(libs[i], x, yPos);

        std::string prefix;
        if (i == selectedLib) {
            prefix = "> ";
            libEntity.RGB[0] = 0;
            libEntity.RGB[1] = 255;
            libEntity.RGB[2] = 0;
        } else {
            prefix = "   ";
            libEntity.RGB[0] = 180;
            libEntity.RGB[1] = 180;
            libEntity.RGB[2] = 180;
        }

        libEntity.sprites["SFML"] = prefix + libs[i].name;
        libEntity.sprites["SDL"] = prefix + libs[i].name;
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
    gamesTitle.width = 0;
    gamesTitle.height = 0;
    gamesTitle.rotate = 0;
    gamesTitle.RGB[0] = 255;
    gamesTitle.RGB[1] = 255;
    gamesTitle.RGB[2] = 255;
    gamesTitle.sprites["SFML"] = "Game Libraries:";
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
    selectedLibs.width = 0;
    selectedLibs.height = 0;
    selectedLibs.rotate = 0;
    selectedLibs.RGB[0] = 255;
    selectedLibs.RGB[1] = 255;
    selectedLibs.RGB[2] = 0;
    selectedLibs.sprites["SFML"] = "Start";
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
std::map<IGame::EntityName, Entity> Menu::renderGame()
{
    std::map<EntityName, Entity> entities;
    std::map<EntityName, Entity> tempEntities;

    entities["title"] = renderTitle();

    entities["display_title"] = renderDisplayTitle();

    tempEntities =
        renderLibs(_displayLibs, _selectedDisplayLib, 200, "display_");
    for (const auto &pair : tempEntities) {
        entities[pair.first] = pair.second;
    }

    entities["games_title"] = renderGameTitle();

    tempEntities = renderLibs(_gameLibs, _selectedGameLib, 600, "game_");
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

    libType getType(void)
    {
        return GAME;
    }
}

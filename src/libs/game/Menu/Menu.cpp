/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Menu
*/

#include "Menu.hpp"

// Screen size: 1024x768

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

    _name = "Menu";
    if (libPaths.empty()) {
        std::cerr << "No libraries found in the lib directory." << std::endl;
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
    try {
        DLLoader<IGame> loader(path);
        IGame *instance = loader.getInstance();
        instance->isGameOver();
        std::string name = instance->getName();
        delete instance;
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
    try {
        DLLoader<IDisplay> loader(path);
        IDisplay *instance = loader.getInstance();
        instance->clear();
        std::string name = instance->getName();
        delete instance;
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
               ? _gameLibs[0].name
               : _gameLibs[_selectedGameLib].name;
}

////////////////////////////// Event Handling ///////////////////////////////

/**
 * @brief Handle a left mouse button click event
 *
 * This function checks if the left mouse button was clicked on a
 * library button. If so, it updates the selected library and sets
 * the selectingLibType to either DISPLAY or GAME.
 *
 * @param event The event to handle
 */
void Menu::handleLeftClick(event event)
{
    for (size_t i = 0; i < _gameLibs.size(); i++) {
        if (event.x >= _gameLibs[i].pos.x &&
            event.x <= _gameLibs[i].pos.x + _gameLibs[i].pos.width &&
            event.y >= _gameLibs[i].pos.y &&
            event.y <= _gameLibs[i].pos.y + _gameLibs[i].pos.height) {
            _selectedGameLib = i;
            _selectingLibType = DISPLAY;
            return;
        }
    }
    for (size_t i = 0; i < _displayLibs.size(); i++) {
        if (event.x >= _displayLibs[i].pos.x &&
            event.x <= _displayLibs[i].pos.x + _displayLibs[i].pos.width &&
            event.y >= _displayLibs[i].pos.y &&
            event.y <= _displayLibs[i].pos.y + _displayLibs[i].pos.height) {
            _selectedDisplayLib = i;
            _selectingLibType = GAME;
            return;
        }
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
void Menu::handleOneEvent(event event)
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
void Menu::handleEvent(std::vector<event> events)
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
Entity Menu::renderTitle()
{
    Entity titleText;
    titleText.type = TEXT;
    titleText.x = 400;
    titleText.y = 50;
    titleText.width = 0;
    titleText.height = 0;
    titleText.rotate = 0;
    titleText.RGB[0] = 255;
    titleText.RGB[1] = 255;
    titleText.RGB[2] = 255;
    titleText.sprites["text"] = "Arcade Menu";
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
Entity Menu::renderDisplayTitle()
{
    Entity displaysTitle;
    displaysTitle.type = TEXT;
    displaysTitle.x = 200;
    displaysTitle.y = 120;
    displaysTitle.width = 0;
    displaysTitle.height = 0;
    displaysTitle.rotate = 0;
    displaysTitle.RGB[0] = 0;
    displaysTitle.RGB[1] = 0;
    displaysTitle.RGB[2] = 0;
    displaysTitle.sprites["text"] = "Display Libraries:";
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
    lib.pos.width = lib.name.length();
    lib.pos.height = 30;
}

/**
 * @brief Render the libraries
 *
 * This function creates a map of Entity objects representing the
 * libraries. It sets the position, color, and text of each library
 * based on the selected library and whether the user is selecting
 * a game or display library.
 *
 * @param displayLibs The vector of library information
 * @param selectedLib The index of the selected library
 * @param x The x-coordinate of the button
 * @return std::map<std::string, Entity> A map of Entity objects representing
 * the libraries
 */
std::map<std::string, Entity> Menu::renderLibs(
    std::vector<LibInfo> displayLibs, size_t selectedLib, size_t x)
{
    std::map<std::string, Entity> entities;

    int yPos = 150;
    for (size_t i = 0; i < displayLibs.size(); i++) {
        Entity libEntity;
        libEntity.type = TEXT;
        libEntity.x = x;
        libEntity.y = yPos;
        libEntity.width = 0;
        libEntity.height = 0;
        libEntity.rotate = 0;
        setupLibButton(displayLibs[i], x, yPos);

        std::string prefix;
        if (i == selectedLib) {
            prefix = "-> ";
            libEntity.RGB[0] = 0;
            libEntity.RGB[1] = 255;
            libEntity.RGB[2] = 0;  // Green
        } else {
            prefix = "   ";
            libEntity.RGB[0] = 180;
            libEntity.RGB[1] = 180;
            libEntity.RGB[2] = 180;  // Lighter gray
        }

        libEntity.sprites["text"] = prefix + displayLibs[i].name;
        entities["display_" + std::to_string(i)] = libEntity;
        yPos += 30;
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
Entity Menu::renderGameTitle()
{
    Entity gamesTitle;
    gamesTitle.type = TEXT;
    gamesTitle.x = 600;
    gamesTitle.y = 120;
    gamesTitle.width = 0;
    gamesTitle.height = 0;
    gamesTitle.rotate = 0;
    gamesTitle.RGB[0] = 0;
    gamesTitle.RGB[1] = 0;
    gamesTitle.RGB[2] = 0;
    gamesTitle.sprites["text"] = "Game Libraries:";
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
Entity Menu::renderSelectedLibs(std::string gameName, std::string displayName)
{
    Entity selectedLibs;
    selectedLibs.type = TEXT;
    selectedLibs.x = 400;
    selectedLibs.y = 350;
    selectedLibs.width = 0;
    selectedLibs.height = 0;
    selectedLibs.rotate = 0;
    selectedLibs.RGB[0] = 255;
    selectedLibs.RGB[1] = 255;
    selectedLibs.RGB[2] = 255;  // White
    selectedLibs.sprites["text"] =
        "Selected: " + gameName + " with " + displayName;
    return selectedLibs;
}

/**
 * @brief Render the game menu
 *
 * This function creates a map of Entity objects representing the
 * game menu. It sets the position, color, and text of each entity
 * based on the selected libraries.
 *
 * @return std::map<std::string, Entity> A map of Entity objects representing
 * the game menu
 */
std::map<std::string, Entity> Menu::renderGame()
{
    std::map<std::string, Entity> entities;
    std::map<std::string, Entity> tempEntities;

    entities["title"] = renderTitle();

    entities["display_title"] = renderDisplayTitle();

    tempEntities = renderLibs(_displayLibs, _selectedDisplayLib, 200);
    for (const auto &pair : tempEntities) {
        entities[pair.first] = pair.second;
    }

    entities["games_title"] = renderGameTitle();

    tempEntities = renderLibs(_gameLibs, _selectedGameLib, 600);
    for (const auto &pair : tempEntities) {
        entities[pair.first] = pair.second;
    }

    entities["selection_text"] = renderSelectedLibs(
        _gameLibs.empty() ? "Default" : _gameLibs[_selectedGameLib].name,
        _displayLibs.empty() ? "Default"
                             : _displayLibs[_selectedDisplayLib].name);

    return entities;
}

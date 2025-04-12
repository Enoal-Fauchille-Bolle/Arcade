/*
** EPITECH PROJECT, 2025
** Arcade-project
** File description:
** Core
*/

#include "Core.hpp"

#include <filesystem>
#include <fstream>

#include "LibLoader.hpp"

///////////////////////// Constructor and Destructor /////////////////////////

/**
 * @brief Constructor for the Core class.
 * @param path The path to the initial display library.
 */
Core::Core(std::string path)
{
    LibGetter libGetter = LibGetter();

    _displayLibs = libGetter.getDisplayLibs();
    _gameLibs = libGetter.getGameLibs();
    if (load_display(path) != 0) {
        std::cerr << "Error loading display library" << std::endl;
        _running = false;
        return;
    }
    if (load_game("./lib/arcade_menu.so") == 1) {
        std::cerr << "Error loading default menu" << std::endl;
        std::cerr << "Launching emergency menu..." << std::endl;
        startEmergencyMenu();
    }
}

/**
 * @brief Destructor for the Core class.
 */
Core::~Core()
{
}

/////////////////////////////// Emergency Menu ///////////////////////////////

/**
 * @brief Starts the emergency menu if the game fails to load.
 * This function creates an instance of the EmergencyMenu class and enters a
 * loop to handle events and render the menu until a game is selected or the
 * application is quit.
 */
void Core::startEmergencyMenu(void)
{
    bool gameSelected = false;
    std::map<std::string, Entity> entities;
    std::string newDisplay;
    std::string newGamePath;

    _game = std::make_unique<EmergencyMenu>();
    while (!gameSelected && _running) {
        std::vector<RawEvent> events = _display->pollEvent();
        if (checkQuit(events)) {
            _running = false;
            break;
        }
        _game->handleEvent(events);
        entities = _game->renderGame();
        renderEntities(entities);
        if (_game->isGameEnd()) {
            newDisplay = _game->getNewDisplay();
            if (!newDisplay.empty()) {
                delete_display();
                if (load_display(newDisplay) == 1) {
                    std::cerr
                        << "Failed to load display library: " << newDisplay
                        << std::endl;
                }
            }
            newGamePath = _game->getNewLib();
            if (load_game(newGamePath) == 0) {
                gameSelected = true;
            } else {
                std::cerr << "Failed to load selected game: " << newGamePath
                          << std::endl;
                _game = std::make_unique<EmergencyMenu>();
            }
        }
    }
}

///////////////////////////// Quit Key Checking //////////////////////////////

/**
 * @brief Checks if the QUIT event is present in the events vector.
 * @param events The vector of RawEvent objects to check.
 * @return true if a QUIT event is found, false otherwise.
 */
bool Core::checkQuit(std::vector<RawEvent> events)
{
    for (auto it = events.begin(); it != events.end();) {
        if (it->type == QUIT || (it->type == PRESS && it->key == QUIT_KEY)) {
            it = events.erase(it);
            return true;
        } else {
            ++it;
        }
    }
    return false;
}

//////////////////////// Display Library Switching Key ////////////////////////

/**
 * @brief Switches to the next display library.
 * This function increments the selected display library index and loads
 * the corresponding library. If it reaches the end of the list, it wraps
 * around to the first library.
 */
void Core::nextDisplayLibrary(void)
{
    std::string newDisplayPath;

    delete_display();
    _selectedDisplayLib++;
    if (_selectedDisplayLib >= _displayLibs.size()) {
        _selectedDisplayLib = 0;
    }
    newDisplayPath = getDisplayLibPathFromIndex(_selectedDisplayLib);
    if (load_display(newDisplayPath) == 1) {
        std::cerr << "Failed to load display library: " << newDisplayPath
                  << std::endl;
    }
}

/**
 * @brief Switches to the previous display library.
 * This function decrements the selected display library index and loads
 * the corresponding library. If it reaches the beginning of the list, it
 * wraps around to the last library.
 */
void Core::previousDisplayLibrary(void)
{
    std::string newDisplayPath;

    delete_display();
    if (_selectedDisplayLib == 0) {
        _selectedDisplayLib = _displayLibs.size() - 1;
    } else {
        _selectedDisplayLib--;
    }
    newDisplayPath = getDisplayLibPathFromIndex(_selectedDisplayLib);
    if (load_display(newDisplayPath) == 1) {
        std::cerr << "Failed to load display library: " << newDisplayPath
                  << std::endl;
    }
}

/**
 * @brief Switches to the previous display library.
 * This function decrements the selected display library index and loads
 * the corresponding library. If it reaches the beginning of the list, it
 * wraps around to the last library.
 */
void Core::displayLibrarySwitching(std::vector<RawEvent> events)
{
    for (auto it = events.begin(); it != events.end();) {
        if (it->type == PRESS && it->key == PREVIOUS_DISPLAY_KEY) {
            nextDisplayLibrary();
            it = events.erase(it);
        } else if (it->type == PRESS && it->key == NEXT_DISPLAY_KEY) {
            previousDisplayLibrary();
            it = events.erase(it);
        } else {
            ++it;
        }
    }
}

///////////////////////// Game Library Switching Key /////////////////////////

/**
 * @brief Switches to the next game library.
 * This function increments the selected game library index and loads
 * the corresponding library. If it reaches the end of the list, it wraps
 * around to the first library.
 */
void Core::nextGameLibrary(void)
{
    std::string newGamePath;

    delete_game();
    _selectedGameLib++;
    if (_selectedGameLib >= _gameLibs.size()) {
        _selectedGameLib = 0;
    }
    newGamePath = getGameLibPathFromIndex(_selectedGameLib);
    if (load_game(newGamePath) == 1) {
        std::cerr << "Failed to load game library: " << newGamePath
                  << std::endl;
    }
}

/**
 * @brief Switches to the previous game library.
 * This function decrements the selected game library index and loads
 * the corresponding library. If it reaches the beginning of the list, it
 * wraps around to the last library.
 */
void Core::previousGameLibrary(void)
{
    std::string newGamePath;

    delete_game();
    if (_selectedGameLib == 0) {
        _selectedGameLib = _gameLibs.size() - 1;
    } else {
        _selectedGameLib--;
    }
    newGamePath = getGameLibPathFromIndex(_selectedGameLib);
    if (load_game(newGamePath) == 1) {
        std::cerr << "Failed to load game library: " << newGamePath
                  << std::endl;
    }
}

/**
 * @brief Switches to the previous game library.
 * This function decrements the selected game library index and loads
 * the corresponding library. If it reaches the beginning of the list, it
 * wraps around to the last library.
 */
void Core::gameLibrarySwitching(std::vector<RawEvent> events)
{
    for (auto it = events.begin(); it != events.end();) {
        if (it->type == PRESS && it->key == PREVIOUS_GAME_KEY) {
            nextGameLibrary();
            it = events.erase(it);
        } else if (it->type == PRESS && it->key == NEXT_GAME_KEY) {
            previousGameLibrary();
            it = events.erase(it);
        } else {
            ++it;
        }
    }
}

//////////////////////////// Library Reloading Key ////////////////////////////

/**
 * @brief Reloads the game library.
 * This function deletes the current game library and loads the
 * previously loaded game library again.
 */
void Core::reloadGameLibrary(void)
{
    delete_game();
    _gameLoader.resetHandle();
    if (load_game(_currentGamePath) == 1) {
        std::cerr << "Failed to reload game library: " << _currentGamePath
                  << std::endl;
        startEmergencyMenu();
    }
}

/**
 * @brief Reloads the display library.
 * This function deletes the current display library and loads the
 * previously loaded display library again.
 */
void Core::reloadDisplayLibrary(void)
{
    delete_display();
    _graphicLoader.resetHandle();
    if (load_display(_currentDisplayPath) == 1) {
        std::cerr << "Failed to reload game library: " << _currentDisplayPath
                  << std::endl;
        startEmergencyMenu();
    }
}

/**
 * @brief Reloads the game and display libraries when F5, F6, or F7 is pressed.
 * @param events The vector of RawEvent objects to check for reload events.
 */
void Core::libraryReloading(std::vector<RawEvent> events)
{
    for (auto it = events.begin(); it != events.end();) {
        if (it->type == PRESS && it->key == RELOAD_LIBS_KEY) {
            reloadGameLibrary();
            reloadDisplayLibrary();
            it = events.erase(it);
        } else if (it->type == PRESS && it->key == RELOAD_GAME_LIB_KEY) {
            reloadGameLibrary();
            it = events.erase(it);
        } else if (it->type == PRESS && it->key == RELOAD_DISPLAY_LIB_KEY) {
            reloadDisplayLibrary();
            it = events.erase(it);
        } else {
            ++it;
        }
    }
}

/////////////////////////////// Go To Menu Key ///////////////////////////////

/**
 * @brief Checks if the GO_TO_MENU_KEY event is present in the events vector.
 * @param events The vector of RawEvent objects to check.
 * @return true if a GO_TO_MENU_KEY event is found, false otherwise.
 */
bool Core::checkGoToMenu(std::vector<RawEvent> events)
{
    for (auto it = events.begin(); it != events.end(); ++it) {
        if (it->type == PRESS && it->key == GO_TO_MENU_KEY) {
            events.erase(it);
            renderObject musicObj;
            musicObj.type = MUSIC;
            musicObj.sprite = "";
            _display->drawObject(musicObj);
            return true;
        }
    }
    return false;
}

/**
 * @brief Switches to the menu game.
 * This function deletes the current game library and loads the menu game
 * library. If it fails to load the menu game, it starts the emergency
 * menu.
 */
void Core::goToMenu(void)
{
    delete_game();
    if (load_game("./lib/arcade_menu.so") == 1) {
        std::cerr << "Failed to load menu game" << std::endl;
        startEmergencyMenu();
    }
}

///////////////////////////////// Game Loop /////////////////////////////////

/**
 * @brief Renders the entities on the display.
 * @param entities A map of entity names to Entity objects to render.
 */
void Core::renderEntities(std::map<std::string, Entity> entities)
{
    if (entities.size() > 0) {
        _display->clear();
        for (const auto &pair : entities) {
            Entity val = pair.second;
            renderObject obj;
            obj.x = val.x;
            obj.y = val.y;
            obj.type = val.type;
            obj.width = val.width;
            obj.height = val.height;
            obj.rotate = val.rotate;
            if (val.sprites.find(_display->getDType()) == val.sprites.end()) {
                continue;
            }
            obj.sprite = val.sprites.find(_display->getDType())->second;
            obj.RGB[0] = val.RGB[0];
            obj.RGB[1] = val.RGB[1];
            obj.RGB[2] = val.RGB[2];
            _display->drawObject(obj);
        }
        _display->display();
    }
}

/**
 * @brief Handles the score when the game is over.
 * This function retrieves the score from the game, saves it using the
 * ScoreManager, and updates the username if the game is "Menu".
 */
void Core::handleScore(void)
{
    auto score = _game->getScore();
    ScoreManager scoreManager;

    if (_game->getName() == "Menu") {
        _username = score.second;
    }
    scoreManager.saveScore(_game->getName(), score);
}

/**
 * @brief Main loop of the Core class. Handles game logic, events, and
 * rendering.
 */
void Core::run()
{
    while (_running) {
        if (_game->isGameOver() == true) {
            handleScore();
        }
        if (_game->getNewDisplay() != "") {
            std::string newDisplay = _game->getNewDisplay();
            delete_display();
            load_display(newDisplay);
            _game->getNewDisplay();
        }
        if (_game->isGameEnd()) {
            std::string newLib = _game->getNewLib();
            delete_game();
            if (newLib.empty()) {
                _running = false;
                break;
            }
            if (load_game(newLib) == 1) {
                std::cerr << "Failed to load selected game: " << newLib
                          << std::endl;
                startEmergencyMenu();
            }
        }
        std::vector<RawEvent> events = _display->pollEvent();
        if (checkQuit(events)) {
            _running = false;
            break;
        }
        if (checkGoToMenu(events))
            goToMenu();
        displayLibrarySwitching(events);
        gameLibrarySwitching(events);
        libraryReloading(events);
        _game->handleEvent(events);
        std::map<std::string, Entity> entities = _game->renderGame();
        renderEntities(entities);
    }
}

////////////////////////////// Library Loading //////////////////////////////

/**
 * @brief Loads the display library.
 * @param path The path to the display library.
 * @return 0 on success, 1 on failure.
 */
int Core::load_display(std::string path)
{
    try {
        _graphicLoader = DLLoader<IDisplay>("DisplayEntryPoint");
        _display = std::unique_ptr<IDisplay>(_graphicLoader.getInstance(path));
        _currentDisplayPath = path;
        _selectedDisplayLib = getDisplayLibIndexFromPath(path);
        return 0;
    } catch (const std::exception &e) {
        std::cerr << "Error loading display library: " << e.what()
                  << std::endl;
        return 1;
    }
}

/**
 * @brief Loads the game library.
 * @param path The path to the game library.
 * @return 0 on success, 1 on failure.
 */
int Core::load_game(std::string path)
{
    try {
        _gameLoader = DLLoader<IGame>("GameEntryPoint");
        _game = std::unique_ptr<IGame>(_gameLoader.getInstance(path));
        _currentGamePath = path;
        _selectedGameLib = getGameLibIndexFromPath(path);
        _game->setUsername(_username);
        return 0;
    } catch (const std::exception &e) {
        std::cerr << "Error loading game library: " << e.what() << std::endl;
        return 1;
    }
}

/**
 * @brief Deletes the currently loaded display library.
 * @return 0 on success.
 */
int Core::delete_display()
{
    if (_display) {
        _display.reset();
    }
    return 0;
}

/**
 * @brief Deletes the currently loaded game library.
 * @return 0 on success.
 */
int Core::delete_game()
{
    if (_game) {
        _game.reset();
    }
    return 0;
}

////////////////////// Display and Game Library Indexing //////////////////////

/**
 * @brief Gets the display library path from the index.
 * @param index The index of the display library.
 * @return The path of the display library.
 */
std::string Core::getDisplayLibPathFromIndex(size_t index)
{
    if (index >= _displayLibs.size()) {
        return 0;
    }
    return _displayLibs[index].path;
}

/**
 * @brief Gets the index of the display library from the path.
 * @param path The path of the display library.
 * @return The index of the display library.
 */
size_t Core::getDisplayLibIndexFromPath(std::string path)
{
    for (size_t i = 0; i < _displayLibs.size(); i++) {
        if (_displayLibs[i].path == path) {
            return i;
        }
    }
    return 0;
}

/**
 * @brief Gets the game library path from the index.
 * @param index The index of the game library.
 * @return The path of the game library.
 */
std::string Core::getGameLibPathFromIndex(size_t index)
{
    if (index >= _gameLibs.size()) {
        return 0;
    }
    return _gameLibs[index].path;
}

/**
 * @brief Gets the index of the game library from the path.
 * @param path The path of the game library.
 * @return The index of the game library.
 */
size_t Core::getGameLibIndexFromPath(std::string path)
{
    for (size_t i = 0; i < _gameLibs.size(); i++) {
        if (_gameLibs[i].path == path) {
            return i;
        }
    }
    return 0;
}

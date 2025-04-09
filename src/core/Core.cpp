/*
** EPITECH PROJECT, 2025
** Arcade-project
** File description:
** Core
*/

#include "Core.hpp"

#include "LibLoader.hpp"

/**
 * @brief Constructor for the Core class.
 * @param path The path to the initial display library.
 */
Core::Core(std::string path)
{
    if (load_display(path) != 0) {
        std::cerr << "Error loading display library" << std::endl;
        running = false;
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

void Core::startEmergencyMenu(void)
{
    bool gameSelected = false;

    _game = std::make_unique<EmergencyMenu>();
    while (!gameSelected && running) {
        std::vector<RawEvent> events = _display->pollEvent();
        if (checkQuit(events)) {
            running = false;
            break;
        }
        _game->handleEvent(events);
        std::map<std::string, Entity> entities = _game->renderGame();
        renderEntities(entities);
        if (dynamic_cast<EmergencyMenu *>(_game.get())->isGameEnd()) {
            std::string newGamePath = _game->getNewLib();
            _game.reset();
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

/**
 * @brief Checks if the QUIT event is present in the events vector.
 * @param events The vector of RawEvent objects to check.
 * @return true if a QUIT event is found, false otherwise.
 */
bool Core::checkQuit(std::vector<RawEvent> events)
{
    for (const auto& event : events) {
        if (event.type == QUIT) {
            return true;
        }
    }
    return false;
}

/**
 * @brief Renders the entities on the display.
 * @param entities A map of entity names to Entity objects to render.
 */
void Core::renderEntities(std::map<std::string, Entity> entities)
{
    if (entities.size() > 0) {
        _display->clear();
        for (const auto& pair : entities) {
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
 * @brief Main loop of the Core class. Handles game logic, events, and rendering.
 */
void Core::run()
{
    while (running) {
        if (_game->isGameOver() == true) {
            auto score = _game->getScore();
            printf("Score: %f\n", score.first);
        }
        if (_game->isGameEnd()) {
            std::string newLib = _game->getNewLib();
            delete_game();
            load_game(newLib);
        }
        if (_game->getNewDisplay(false) != "") {
            std::string newDisplay = _game->getNewDisplay(false);
            printf("New display: %s\n", newDisplay.c_str());
            delete_display();
            load_display(newDisplay);
            _game->getNewDisplay(true);
        }
        std::vector<RawEvent> events = _display->pollEvent();
        if (checkQuit(events)) {
            running = false;
            break;
        }
        _game->handleEvent(events);
        std::map<std::string, Entity> entities = _game->renderGame();
        renderEntities(entities);
    }
}

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
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error loading display library: " << e.what() << std::endl;
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
        return 0;
    } catch (const std::exception& e) {
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
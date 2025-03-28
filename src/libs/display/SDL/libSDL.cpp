/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** cpp for SDL
*/

#include "libSDL.hpp"

/**
 * @brief Constructor for the LibSDL class.
 *
 * This constructor initializes the SDL library by creating a unique pointer
 * to an SDL object. It sets up an SDL window with the title "Arcade", centered
 * on the screen, with a resolution of 800x600 pixels, and makes it visible.
 * Additionally, it creates an SDL renderer for the window with hardware
 * acceleration enabled.
 */
LibSDL::LibSDL()
{
    _sdl = std::make_unique<SDL>();
    _sdl->createWindow("Arcade", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    _sdl->createRenderer(_sdl->getWindow(), -1, SDL_RENDERER_ACCELERATED);
}

/**
 * @brief Destructor for the LibSDL class.
 *
 * This destructor ensures that all SDL resources are properly destroyed
 * when the LibSDL object is no longer needed.
 */
LibSDL::~LibSDL()
{
    if (_sdl) {
        _sdl->destroyAll(_sdl->getWindow(), _sdl->getRenderer());
    }
}

/**
 * @brief Polls events from the SDL event queue.
 *
 * @return A vector of rawEvent objects representing the events polled.
 */
std::vector<rawEvent> LibSDL::pollEvent(void)
{
    std::vector<rawEvent> events;

    return events;
}

/**
 * @brief Draws a render object on the screen.
 *
 * @param obj The renderObject to be drawn.
 */
void LibSDL::drawObject(renderObject obj)
{
    obj = obj;
}

/**
 * @brief Clears the current rendering target.
 */
void LibSDL::clear(void)
{
    SDL_RenderClear(_sdl->getRenderer());
}

/**
 * @brief Updates the screen with any rendering performed since the last call.
 */
void LibSDL::display(void)
{
    SDL_RenderPresent(_sdl->getRenderer());
}

/**
 * @brief Retrieves the name of the library.
 *
 * @return A string containing the name "SDL".
 */
std::string LibSDL::getName(void)
{
    return ("SDL");
}

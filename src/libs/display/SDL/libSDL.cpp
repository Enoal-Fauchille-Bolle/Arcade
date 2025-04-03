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
 * on the screen, with a resolution of 1024x768 pixels, and makes it visible.
 * Additionally, it creates an SDL renderer for the window with hardware
 * acceleration enabled.
 */
LibSDL::LibSDL()
{
    _sdl = std::make_unique<SDL>();
    _sdl->createWindow("Arcade", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, SDL_WINDOW_SHOWN);
    _sdl->createRenderer(-1, SDL_RENDERER_ACCELERATED);
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
        _sdl->destroyAll();
    }
}

/**
 * @brief Polls events from the SDL event queue.
 *
 * @return A vector of RawEvent objects representing the events polled.
 */
std::vector<RawEvent> LibSDL::pollEvent(void)
{
    return _sdl->pollEvent();
}

/**
 * @brief Draws a render object on the screen.
 *
 * @param obj The renderObject to be drawn.
 */
void LibSDL::drawObject(renderObject obj)
{
    if (obj.type == RECTANGLE)
        _sdl->drawRectangle(obj);
    else if (obj.type == CIRCLE)
        _sdl->drawCircle(obj);
    else if (obj.type == TEXT)
        _sdl->drawText(obj);
}

/**
 * @brief Clears the current rendering target.
 */
void LibSDL::clear(void)
{
    _sdl->renderClear();
}

/**
 * @brief Updates the screen with any rendering performed since the last call.
 */
void LibSDL::display(void)
{
    _sdl->renderPresent();
}

/**
 * @brief Retrieves the name of the library.
 *
 * @return A string containing the name "SDL".
 */
DisplayType LibSDL::getDType(void)
{
    return DisplayType::GRAPHICAL;
}

std::string LibSDL::getName(void)
{
    return LIBRARY_NAME;
}



extern "C" {
    /**
     * @brief Constructor for the shared library.
     */
    __attribute__((constructor))
    void constructor()
    {
    }

    /**
     * @brief Destructor for the shared library.
     */
    __attribute__((destructor))
    void destructor()
    {
    }

    /**
     * @brief Entry point for the libSDL display library.
     * @return A pointer to a new libSDL instance.
     */
    LibSDL *DisplayEntryPoint()
    {
        return new LibSDL();
    }

    std::string getName(void)
    {
        return LIBRARY_NAME;
    }

    LibType getType(void)
    {
        return DISPLAY;
    }
}
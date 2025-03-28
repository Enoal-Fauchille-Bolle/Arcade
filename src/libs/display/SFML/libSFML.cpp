/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** libSFML
*/

#include "libSFML.hpp"

/**
 * @brief Constructor for the libSFML class.
 */
libSFML::libSFML()
{
    _name = "SFML";
    this->_window.create(sf::VideoMode(1024, 768), "Arcade");
    this->_window.setFramerateLimit(60);
}

/**
 * @brief Destructor for the libSFML class.
 */
libSFML::~libSFML()
{
}

/**
 * @brief Polls events from the SFML window.
 * @return A vector of rawEvent objects representing the polled events.
 */
std::vector<rawEvent> libSFML::pollEvent(void)
{
    std::vector<rawEvent> events;
    sf::Event event;

    while (_window.pollEvent(event)) {
        // rawEvent e;
        // e.type = "KEYBOARD";
        // e.key = "";
        // e.x = 0;
        // e.y = 0;
        // if (event.type == sf::Event::Closed) {
        //     e.type = "CLOSE";
        // }
        // if (event.type == sf::Event::KeyPressed) {
        //     e.key = std::to_string(event.key.code);
        // }
        // events.push_back(e);
    }
    return events;
}

/**
 * @brief Draws a render object on the SFML window.
 * @param obj The renderObject to be drawn.
 */
void libSFML::drawObject(renderObject obj)
{
    if (obj.type == RECTANGLE)
        drawRectangle(obj);
    if (obj.type == CIRCLE)
        drawCircle(obj);
    if (obj.type == TEXT)
        drawText(obj);
    if (obj.type == MUSIC)
        drawMusic(obj);
}

/**
 * @brief Draws a rectangle on the SFML window.
 * @param obj The renderObject containing rectangle properties.
 */
void libSFML::drawRectangle(renderObject obj)
{
    sf::RectangleShape rectangle(sf::Vector2f(obj.width, obj.height));
    rectangle.setFillColor(sf::Color(obj.RGB[0], obj.RGB[1], obj.RGB[2]));
    rectangle.setPosition(obj.x, obj.y);
    _window.draw(rectangle);
}

/**
 * @brief Draws a circle on the SFML window.
 * @param obj The renderObject containing circle properties.
 */
void libSFML::drawCircle(renderObject obj)
{
    sf::CircleShape circle(obj.width);
    circle.setPosition(obj.x, obj.y);
    _window.draw(circle);
}

/**
 * @brief Draws text on the SFML window.
 * @param obj The renderObject containing text properties.
 */
void libSFML::drawText(renderObject obj)
{
    sf::Text text;
    sf::Font font;
    font.loadFromFile("arial.ttf");
    text.setFont(font);
    text.setString(obj.sprite);
    text.setCharacterSize(obj.width);
    text.setPosition(obj.x, obj.y);
    _window.draw(text);
}

/**
 * @brief Handles music-related rendering (currently a placeholder).
 * @param obj The renderObject containing music properties.
 */
void libSFML::drawMusic(renderObject obj)
{
    (void)obj;
}

/**
 * @brief Clears the SFML window.
 */
void libSFML::clear(void)
{
    _window.clear();
}

/**
 * @brief Displays the contents of the SFML window.
 */
void libSFML::display(void)
{
    _window.display();
}

/**
 * @brief Retrieves the name of the display library.
 * @return A string representing the name of the library.
 */
std::string libSFML::getName(void)
{
    return _name;
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
     * @brief Entry point for the libSFML display library.
     * @return A pointer to a new libSFML instance.
     */
    libSFML *DisplayEntryPoint()
    {
        return new libSFML();
    }
}
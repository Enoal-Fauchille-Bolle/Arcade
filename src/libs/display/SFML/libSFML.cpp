/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** libSFML
*/

#include "libSFML.hpp"

libSFML::libSFML()
{
    _name = "SFML";
    _window.create(sf::VideoMode(1024, 768), "Arcade");
}

libSFML::~libSFML()
{
}

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

void libSFML::drawRectangle(renderObject obj)
{
    sf::RectangleShape rectangle(sf::Vector2f(obj.width, obj.height));
    rectangle.setFillColor(sf::Color(obj.RGB[0], obj.RGB[1], obj.RGB[2]));
    rectangle.setPosition(obj.x, obj.y);
    _window.draw(rectangle);
}

void libSFML::drawCircle(renderObject obj)
{
    sf::CircleShape circle(obj.width);
    circle.setPosition(obj.x, obj.y);
    _window.draw(circle);
}

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

void libSFML::drawMusic(renderObject obj)
{
    (void)obj;
}

void libSFML::clear(void)
{
    _window.clear();
}

void libSFML::display(void)
{
    _window.display();
}

extern "C" libSFML *createLib(void)
{
    return new libSFML();
}
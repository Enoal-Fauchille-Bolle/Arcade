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
    _name = LIBRARY_NAME;
    _dtype = LIBRARY_DTYPE;
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
std::vector<RawEvent> libSFML::pollEvent(void)
{
    std::vector<RawEvent> events;
    sf::Event event;

    while (_window.pollEvent(event))
    {
        RawEvent raw;
        switch (event.type)
        {
            case sf::Event::Closed:
                raw.type = QUIT;
                events.push_back(raw);
                break;
            case sf::Event::KeyPressed:
                raw.type = PRESS;
                switch (event.key.code) {
                    case sf::Keyboard::A: raw.key = KEY_A; break;
                    case sf::Keyboard::B: raw.key = KEY_B; break;
                    case sf::Keyboard::C: raw.key = KEY_C; break;
                    case sf::Keyboard::D: raw.key = KEY_D; break;
                    case sf::Keyboard::E: raw.key = KEY_E; break;
                    case sf::Keyboard::F: raw.key = KEY_F; break;
                    case sf::Keyboard::G: raw.key = KEY_G; break;
                    case sf::Keyboard::H: raw.key = KEY_H; break;
                    case sf::Keyboard::I: raw.key = KEY_I; break;
                    case sf::Keyboard::J: raw.key = KEY_J; break;
                    case sf::Keyboard::K: raw.key = KEY_K; break;
                    case sf::Keyboard::L: raw.key = KEY_L; break;
                    case sf::Keyboard::M: raw.key = KEY_M; break;
                    case sf::Keyboard::N: raw.key = KEY_N; break;
                    case sf::Keyboard::O: raw.key = KEY_O; break;
                    case sf::Keyboard::P: raw.key = KEY_P; break;
                    case sf::Keyboard::Q: raw.key = KEY_Q; break;
                    case sf::Keyboard::R: raw.key = KEY_R; break;
                    case sf::Keyboard::S: raw.key = KEY_S; break;
                    case sf::Keyboard::T: raw.key = KEY_T; break;
                    case sf::Keyboard::U: raw.key = KEY_U; break;
                    case sf::Keyboard::V: raw.key = KEY_V; break;
                    case sf::Keyboard::W: raw.key = KEY_W; break;
                    case sf::Keyboard::X: raw.key = KEY_X; break;
                    case sf::Keyboard::Y: raw.key = KEY_Y; break;
                    case sf::Keyboard::Z: raw.key = KEY_Z; break;
                    case sf::Keyboard::Num0: raw.key = KEY_0; break;
                    case sf::Keyboard::Num1: raw.key = KEY_1; break;
                    case sf::Keyboard::Num2: raw.key = KEY_2; break;
                    case sf::Keyboard::Num3: raw.key = KEY_3; break;
                    case sf::Keyboard::Num4: raw.key = KEY_4; break;
                    case sf::Keyboard::Num5: raw.key = KEY_5; break;
                    case sf::Keyboard::Num6: raw.key = KEY_6; break;
                    case sf::Keyboard::Num7: raw.key = KEY_7; break;
                    case sf::Keyboard::Num8: raw.key = KEY_8; break;
                    case sf::Keyboard::Num9: raw.key = KEY_9; break;
                    case sf::Keyboard::Escape: raw.key = KEY_ESCAPE; break;
                    case sf::Keyboard::Return: raw.key = KEY_RETURN; break;
                    case sf::Keyboard::Space: raw.key = KEY_SPACE; break;
                    case sf::Keyboard::Backspace: raw.key = KEY_BACKSPACE; break;
                    case sf::Keyboard::Tab: raw.key = KEY_TAB; break;
                    case sf::Keyboard::Up: raw.key = KEY_UP; break;
                    case sf::Keyboard::Down: raw.key = KEY_DOWN; break;
                    case sf::Keyboard::Left: raw.key = KEY_LEFT; break;
                    case sf::Keyboard::Right: raw.key = KEY_RIGHT; break;
                    case sf::Keyboard::LShift: raw.key = KEY_LSHIFT; break;
                    case sf::Keyboard::RShift: raw.key = KEY_RSHIFT; break;
                    case sf::Keyboard::LControl: raw.key = KEY_LCTRL; break;
                    case sf::Keyboard::RControl: raw.key = KEY_RCTRL; break;
                    case sf::Keyboard::LAlt: raw.key = KEY_LALT; break;
                    case sf::Keyboard::RAlt: raw.key = KEY_RALT; break;
                    case sf::Keyboard::Home: raw.key = KEY_HOME; break;
                    case sf::Keyboard::End: raw.key = KEY_END; break;
                    case sf::Keyboard::Delete: raw.key = KEY_DELETE; break;
                    case sf::Keyboard::Insert: raw.key = KEY_INSERT; break;
                    case sf::Keyboard::PageUp: raw.key = KEY_PAGEUP; break;
                    case sf::Keyboard::PageDown: raw.key = KEY_PAGEDOWN; break;
                    default:
                        continue; // Skip unmapped keys
                }
                events.push_back(raw);
                break;
            case sf::Event::KeyReleased:
                raw.type = RELEASE;
                switch (event.key.code) {
                    case sf::Keyboard::A: raw.key = KEY_A; break;
                    case sf::Keyboard::B: raw.key = KEY_B; break;
                    case sf::Keyboard::C: raw.key = KEY_C; break;
                    case sf::Keyboard::D: raw.key = KEY_D; break;
                    case sf::Keyboard::E: raw.key = KEY_E; break;
                    case sf::Keyboard::F: raw.key = KEY_F; break;
                    case sf::Keyboard::G: raw.key = KEY_G; break;
                    case sf::Keyboard::H: raw.key = KEY_H; break;
                    case sf::Keyboard::I: raw.key = KEY_I; break;
                    case sf::Keyboard::J: raw.key = KEY_J; break;
                    case sf::Keyboard::K: raw.key = KEY_K; break;
                    case sf::Keyboard::L: raw.key = KEY_L; break;
                    case sf::Keyboard::M: raw.key = KEY_M; break;
                    case sf::Keyboard::N: raw.key = KEY_N; break;
                    case sf::Keyboard::O: raw.key = KEY_O; break;
                    case sf::Keyboard::P: raw.key = KEY_P; break;
                    case sf::Keyboard::Q: raw.key = KEY_Q; break;
                    case sf::Keyboard::R: raw.key = KEY_R; break;
                    case sf::Keyboard::S: raw.key = KEY_S; break;
                    case sf::Keyboard::T: raw.key = KEY_T; break;
                    case sf::Keyboard::U: raw.key = KEY_U; break;
                    case sf::Keyboard::V: raw.key = KEY_V; break;
                    case sf::Keyboard::W: raw.key = KEY_W; break;
                    case sf::Keyboard::X: raw.key = KEY_X; break;
                    case sf::Keyboard::Y: raw.key = KEY_Y; break;
                    case sf::Keyboard::Z: raw.key = KEY_Z; break;
                    case sf::Keyboard::Num0: raw.key = KEY_0; break;
                    case sf::Keyboard::Num1: raw.key = KEY_1; break;
                    case sf::Keyboard::Num2: raw.key = KEY_2; break;
                    case sf::Keyboard::Num3: raw.key = KEY_3; break;
                    case sf::Keyboard::Num4: raw.key = KEY_4; break;
                    case sf::Keyboard::Num5: raw.key = KEY_5; break;
                    case sf::Keyboard::Num6: raw.key = KEY_6; break;
                    case sf::Keyboard::Num7: raw.key = KEY_7; break;
                    case sf::Keyboard::Num8: raw.key = KEY_8; break;
                    case sf::Keyboard::Num9: raw.key = KEY_9; break;
                    case sf::Keyboard::Escape: raw.key = KEY_ESCAPE; break;
                    case sf::Keyboard::Return: raw.key = KEY_RETURN; break;
                    case sf::Keyboard::Space: raw.key = KEY_SPACE; break;
                    case sf::Keyboard::Backspace: raw.key = KEY_BACKSPACE; break;
                    case sf::Keyboard::Tab: raw.key = KEY_TAB; break;
                    case sf::Keyboard::Up: raw.key = KEY_UP; break;
                    case sf::Keyboard::Down: raw.key = KEY_DOWN; break;
                    case sf::Keyboard::Left: raw.key = KEY_LEFT; break;
                    case sf::Keyboard::Right: raw.key = KEY_RIGHT; break;
                    case sf::Keyboard::LShift: raw.key = KEY_LSHIFT; break;
                    case sf::Keyboard::RShift: raw.key = KEY_RSHIFT; break;
                    case sf::Keyboard::LControl: raw.key = KEY_LCTRL; break;
                    case sf::Keyboard::RControl: raw.key = KEY_RCTRL; break;
                    case sf::Keyboard::LAlt: raw.key = KEY_LALT; break;
                    case sf::Keyboard::RAlt: raw.key = KEY_RALT; break;
                    case sf::Keyboard::Home: raw.key = KEY_HOME; break;
                    case sf::Keyboard::End: raw.key = KEY_END; break;
                    case sf::Keyboard::Delete: raw.key = KEY_DELETE; break;
                    case sf::Keyboard::Insert: raw.key = KEY_INSERT; break;
                    case sf::Keyboard::PageUp: raw.key = KEY_PAGEUP; break;
                    case sf::Keyboard::PageDown: raw.key = KEY_PAGEDOWN; break;
                    default:
                        continue;
                }
                events.push_back(raw);
                break;

            case sf::Event::MouseButtonPressed:
                raw.type = PRESS;
                if (event.mouseButton.button == sf::Mouse::Left)
                    raw.key = MOUSE_LEFT;
                else if (event.mouseButton.button == sf::Mouse::Right)
                    raw.key = MOUSE_RIGHT;
                else if (event.mouseButton.button == sf::Mouse::Middle)
                    raw.key = MOUSE_MIDDLE;
                raw.x = event.mouseButton.x;
                raw.y = event.mouseButton.y;
                events.push_back(raw);
                break;

            case sf::Event::MouseButtonReleased:
                raw.type = RELEASE;
                if (event.mouseButton.button == sf::Mouse::Left)
                    raw.key = MOUSE_LEFT;
                else if (event.mouseButton.button == sf::Mouse::Right)
                    raw.key = MOUSE_RIGHT;
                else if (event.mouseButton.button == sf::Mouse::Middle)
                    raw.key = MOUSE_MIDDLE;
                raw.x = event.mouseButton.x;
                raw.y = event.mouseButton.y;
                events.push_back(raw);
                break;

            case sf::Event::MouseWheelScrolled:
                raw.type = PRESS;
                if (event.mouseWheelScroll.delta > 0)
                    raw.key = MOUSE_WHEEL_UP;
                else if (event.mouseWheelScroll.delta < 0)
                    raw.key = MOUSE_WHEEL_DOWN;
                raw.x = event.mouseWheelScroll.x;
                raw.y = event.mouseWheelScroll.y;
                events.push_back(raw);
                break;

            default:
                break;
        }
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

    if (!obj.sprite.empty()) {
        sf::Texture texture;
        if (texture.loadFromFile(obj.sprite)) {
            sf::Sprite sprite(texture);
            sprite.setPosition(obj.x, obj.y);
            sprite.setScale(
                static_cast<float>(obj.width) / texture.getSize().x,
                static_cast<float>(obj.height) / texture.getSize().y
            );
            _window.draw(sprite);
            return;
        }
    }

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
    font.loadFromFile("./assets/arial.ttf");
    text.setFont(font);
    text.setString(obj.sprite);
    text.setCharacterSize(obj.width);
    text.setPosition(obj.x, obj.y);
    text.setFillColor(sf::Color(obj.RGB[0], obj.RGB[1], obj.RGB[2]));
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
DisplayType libSFML::getDType(void)
{
    return _dtype;
}

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
    libSFML *DisplayEntryPoint(void)
    {
        return new libSFML();
    }

    /**
     * @brief Retrieves the name of the display library.
     * @return A string representing the name of the library.
     */
    std::string getName(void)
    {
        return LIBRARY_NAME;
    }

    /**
     * @brief Retrieves the type of the library.
     * @return The type of the library (DISPLAY).
     */
    LibType getType(void)
    {
        return DISPLAY;
    }
}

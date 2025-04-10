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
    this->_window.create(sf::VideoMode(1024, 768), "Arcade", sf::Style::Titlebar | sf::Style::Close);
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
                    case sf::Keyboard::A: raw.key = KEYBOARD_A; break;
                    case sf::Keyboard::B: raw.key = KEYBOARD_B; break;
                    case sf::Keyboard::C: raw.key = KEYBOARD_C; break;
                    case sf::Keyboard::D: raw.key = KEYBOARD_D; break;
                    case sf::Keyboard::E: raw.key = KEYBOARD_E; break;
                    case sf::Keyboard::F: raw.key = KEYBOARD_F; break;
                    case sf::Keyboard::G: raw.key = KEYBOARD_G; break;
                    case sf::Keyboard::H: raw.key = KEYBOARD_H; break;
                    case sf::Keyboard::I: raw.key = KEYBOARD_I; break;
                    case sf::Keyboard::J: raw.key = KEYBOARD_J; break;
                    case sf::Keyboard::K: raw.key = KEYBOARD_K; break;
                    case sf::Keyboard::L: raw.key = KEYBOARD_L; break;
                    case sf::Keyboard::M: raw.key = KEYBOARD_M; break;
                    case sf::Keyboard::N: raw.key = KEYBOARD_N; break;
                    case sf::Keyboard::O: raw.key = KEYBOARD_O; break;
                    case sf::Keyboard::P: raw.key = KEYBOARD_P; break;
                    case sf::Keyboard::Q: raw.key = KEYBOARD_Q; break;
                    case sf::Keyboard::R: raw.key = KEYBOARD_R; break;
                    case sf::Keyboard::S: raw.key = KEYBOARD_S; break;
                    case sf::Keyboard::T: raw.key = KEYBOARD_T; break;
                    case sf::Keyboard::U: raw.key = KEYBOARD_U; break;
                    case sf::Keyboard::V: raw.key = KEYBOARD_V; break;
                    case sf::Keyboard::W: raw.key = KEYBOARD_W; break;
                    case sf::Keyboard::X: raw.key = KEYBOARD_X; break;
                    case sf::Keyboard::Y: raw.key = KEYBOARD_Y; break;
                    case sf::Keyboard::Z: raw.key = KEYBOARD_Z; break;
                    case sf::Keyboard::Num0: raw.key = KEYBOARD_0; break;
                    case sf::Keyboard::Num1: raw.key = KEYBOARD_1; break;
                    case sf::Keyboard::Num2: raw.key = KEYBOARD_2; break;
                    case sf::Keyboard::Num3: raw.key = KEYBOARD_3; break;
                    case sf::Keyboard::Num4: raw.key = KEYBOARD_4; break;
                    case sf::Keyboard::Num5: raw.key = KEYBOARD_5; break;
                    case sf::Keyboard::Num6: raw.key = KEYBOARD_6; break;
                    case sf::Keyboard::Num7: raw.key = KEYBOARD_7; break;
                    case sf::Keyboard::Num8: raw.key = KEYBOARD_8; break;
                    case sf::Keyboard::Num9: raw.key = KEYBOARD_9; break;
                    case sf::Keyboard::Escape: raw.key = KEYBOARD_ESCAPE; break;
                    case sf::Keyboard::Return: raw.key = KEYBOARD_ENTER; break;
                    case sf::Keyboard::Space: raw.key = KEYBOARD_SPACE; break;
                    case sf::Keyboard::Backspace: raw.key = KEYBOARD_BACKSPACE; break;
                    case sf::Keyboard::Tab: raw.key = KEYBOARD_TAB; break;
                    case sf::Keyboard::Up: raw.key = KEYBOARD_UP; break;
                    case sf::Keyboard::Down: raw.key = KEYBOARD_DOWN; break;
                    case sf::Keyboard::Left: raw.key = KEYBOARD_LEFT; break;
                    case sf::Keyboard::Right: raw.key = KEYBOARD_RIGHT; break;
                    case sf::Keyboard::LShift: raw.key = KEYBOARD_LSHIFT; break;
                    case sf::Keyboard::RShift: raw.key = KEYBOARD_RSHIFT; break;
                    case sf::Keyboard::LControl: raw.key = KEYBOARD_LCTRL; break;
                    case sf::Keyboard::RControl: raw.key = KEYBOARD_RCTRL; break;
                    case sf::Keyboard::LAlt: raw.key = KEYBOARD_LALT; break;
                    case sf::Keyboard::RAlt: raw.key = KEYBOARD_RALT; break;
                    case sf::Keyboard::Home: raw.key = KEYBOARD_HOME; break;
                    case sf::Keyboard::End: raw.key = KEYBOARD_END; break;
                    case sf::Keyboard::Delete: raw.key = KEYBOARD_DELETE; break;
                    case sf::Keyboard::Insert: raw.key = KEYBOARD_INSERT; break;
                    case sf::Keyboard::PageUp: raw.key = KEYBOARD_PAGEUP; break;
                    case sf::Keyboard::PageDown: raw.key = KEYBOARD_PAGEDOWN; break;
                    case sf::Keyboard::F1: raw.key = KEYBOARD_F1; break;
                    case sf::Keyboard::F2: raw.key = KEYBOARD_F2; break;
                    case sf::Keyboard::F3: raw.key = KEYBOARD_F3; break;
                    case sf::Keyboard::F4: raw.key = KEYBOARD_F4; break;
                    case sf::Keyboard::F5: raw.key = KEYBOARD_F5; break;
                    case sf::Keyboard::F6: raw.key = KEYBOARD_F6; break;
                    case sf::Keyboard::F7: raw.key = KEYBOARD_F7; break;
                    case sf::Keyboard::F8: raw.key = KEYBOARD_F8; break;
                    case sf::Keyboard::F9: raw.key = KEYBOARD_F9; break;
                    case sf::Keyboard::F10: raw.key = KEYBOARD_F10; break;
                    case sf::Keyboard::F11: raw.key = KEYBOARD_F11; break;
                    case sf::Keyboard::F12: raw.key = KEYBOARD_F12; break;
                    default:
                        continue; // Skip unmapped keys
                }
                events.push_back(raw);
                break;
            case sf::Event::KeyReleased:
                raw.type = RELEASE;
                switch (event.key.code) {
                    case sf::Keyboard::A: raw.key = KEYBOARD_A; break;
                    case sf::Keyboard::B: raw.key = KEYBOARD_B; break;
                    case sf::Keyboard::C: raw.key = KEYBOARD_C; break;
                    case sf::Keyboard::D: raw.key = KEYBOARD_D; break;
                    case sf::Keyboard::E: raw.key = KEYBOARD_E; break;
                    case sf::Keyboard::F: raw.key = KEYBOARD_F; break;
                    case sf::Keyboard::G: raw.key = KEYBOARD_G; break;
                    case sf::Keyboard::H: raw.key = KEYBOARD_H; break;
                    case sf::Keyboard::I: raw.key = KEYBOARD_I; break;
                    case sf::Keyboard::J: raw.key = KEYBOARD_J; break;
                    case sf::Keyboard::K: raw.key = KEYBOARD_K; break;
                    case sf::Keyboard::L: raw.key = KEYBOARD_L; break;
                    case sf::Keyboard::M: raw.key = KEYBOARD_M; break;
                    case sf::Keyboard::N: raw.key = KEYBOARD_N; break;
                    case sf::Keyboard::O: raw.key = KEYBOARD_O; break;
                    case sf::Keyboard::P: raw.key = KEYBOARD_P; break;
                    case sf::Keyboard::Q: raw.key = KEYBOARD_Q; break;
                    case sf::Keyboard::R: raw.key = KEYBOARD_R; break;
                    case sf::Keyboard::S: raw.key = KEYBOARD_S; break;
                    case sf::Keyboard::T: raw.key = KEYBOARD_T; break;
                    case sf::Keyboard::U: raw.key = KEYBOARD_U; break;
                    case sf::Keyboard::V: raw.key = KEYBOARD_V; break;
                    case sf::Keyboard::W: raw.key = KEYBOARD_W; break;
                    case sf::Keyboard::X: raw.key = KEYBOARD_X; break;
                    case sf::Keyboard::Y: raw.key = KEYBOARD_Y; break;
                    case sf::Keyboard::Z: raw.key = KEYBOARD_Z; break;
                    case sf::Keyboard::Num0: raw.key = KEYBOARD_0; break;
                    case sf::Keyboard::Num1: raw.key = KEYBOARD_1; break;
                    case sf::Keyboard::Num2: raw.key = KEYBOARD_2; break;
                    case sf::Keyboard::Num3: raw.key = KEYBOARD_3; break;
                    case sf::Keyboard::Num4: raw.key = KEYBOARD_4; break;
                    case sf::Keyboard::Num5: raw.key = KEYBOARD_5; break;
                    case sf::Keyboard::Num6: raw.key = KEYBOARD_6; break;
                    case sf::Keyboard::Num7: raw.key = KEYBOARD_7; break;
                    case sf::Keyboard::Num8: raw.key = KEYBOARD_8; break;
                    case sf::Keyboard::Num9: raw.key = KEYBOARD_9; break;
                    case sf::Keyboard::Escape: raw.key = KEYBOARD_ESCAPE; break;
                    case sf::Keyboard::Return: raw.key = KEYBOARD_ENTER; break;
                    case sf::Keyboard::Space: raw.key = KEYBOARD_SPACE; break;
                    case sf::Keyboard::Backspace: raw.key = KEYBOARD_BACKSPACE; break;
                    case sf::Keyboard::Tab: raw.key = KEYBOARD_TAB; break;
                    case sf::Keyboard::Up: raw.key = KEYBOARD_UP; break;
                    case sf::Keyboard::Down: raw.key = KEYBOARD_DOWN; break;
                    case sf::Keyboard::Left: raw.key = KEYBOARD_LEFT; break;
                    case sf::Keyboard::Right: raw.key = KEYBOARD_RIGHT; break;
                    case sf::Keyboard::LShift: raw.key = KEYBOARD_LSHIFT; break;
                    case sf::Keyboard::RShift: raw.key = KEYBOARD_RSHIFT; break;
                    case sf::Keyboard::LControl: raw.key = KEYBOARD_LCTRL; break;
                    case sf::Keyboard::RControl: raw.key = KEYBOARD_RCTRL; break;
                    case sf::Keyboard::LAlt: raw.key = KEYBOARD_LALT; break;
                    case sf::Keyboard::RAlt: raw.key = KEYBOARD_RALT; break;
                    case sf::Keyboard::Home: raw.key = KEYBOARD_HOME; break;
                    case sf::Keyboard::End: raw.key = KEYBOARD_END; break;
                    case sf::Keyboard::Delete: raw.key = KEYBOARD_DELETE; break;
                    case sf::Keyboard::Insert: raw.key = KEYBOARD_INSERT; break;
                    case sf::Keyboard::PageUp: raw.key = KEYBOARD_PAGEUP; break;
                    case sf::Keyboard::PageDown: raw.key = KEYBOARD_PAGEDOWN; break;
                    case sf::Keyboard::F1: raw.key = KEYBOARD_F1; break;
                    case sf::Keyboard::F2: raw.key = KEYBOARD_F2; break;
                    case sf::Keyboard::F3: raw.key = KEYBOARD_F3; break;
                    case sf::Keyboard::F4: raw.key = KEYBOARD_F4; break;
                    case sf::Keyboard::F5: raw.key = KEYBOARD_F5; break;
                    case sf::Keyboard::F6: raw.key = KEYBOARD_F6; break;
                    case sf::Keyboard::F7: raw.key = KEYBOARD_F7; break;
                    case sf::Keyboard::F8: raw.key = KEYBOARD_F8; break;
                    case sf::Keyboard::F9: raw.key = KEYBOARD_F9; break;
                    case sf::Keyboard::F10: raw.key = KEYBOARD_F10; break;
                    case sf::Keyboard::F11: raw.key = KEYBOARD_F11; break;
                    case sf::Keyboard::F12: raw.key = KEYBOARD_F12; break;
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
        drawMusic(obj); // draw xD
}

/**
 * @brief Draws a rectangle on the SFML window.
 * @param obj The renderObject containing rectangle properties.
 */
void libSFML::drawRectangle(renderObject obj)
{
    sf::RectangleShape rectangle(sf::Vector2f(obj.width, obj.height));

    rectangle.setOrigin(obj.width / 2.0f, obj.height / 2.0f);
    rectangle.setPosition(obj.x + obj.width / 2.0f, obj.y + obj.height / 2.0f);
    rectangle.setRotation(static_cast<float>(obj.rotate));

    static std::map<std::string, sf::Texture> textureCache;
    if (!obj.sprite.empty()) {
        if (textureCache.find(obj.sprite) == textureCache.end()) {
            sf::Texture texture;
            if (texture.loadFromFile(obj.sprite)) {
                textureCache[obj.sprite] = texture;
            }
        }
        if (textureCache.find(obj.sprite) != textureCache.end()) {
            rectangle.setTexture(&textureCache[obj.sprite], true);
        } else {
            rectangle.setFillColor(sf::Color(obj.RGB[0], obj.RGB[1], obj.RGB[2]));
        }
    } else {
        rectangle.setFillColor(sf::Color(obj.RGB[0], obj.RGB[1], obj.RGB[2]));
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
    font.loadFromFile("./assets/Tahoma.ttf");
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
    static sf::Music backgroundMusic;
    static bool isBackgroundMusicPlaying = false;

    if (obj.sprite.find("assets/music_") == 0) {
        if (!isBackgroundMusicPlaying || backgroundMusic.getStatus() != sf::Music::Playing) {
            if (!backgroundMusic.openFromFile(obj.sprite)) {
                std::cerr << "Error loading background music file: " << obj.sprite << std::endl;
                return;
            }
            backgroundMusic.setLoop(true);
            backgroundMusic.setVolume(12);
            backgroundMusic.play();
            isBackgroundMusicPlaying = true;
        }
    } else if (obj.sprite == "assets/gameover.mp3") {
        if (isBackgroundMusicPlaying) {
            backgroundMusic.stop();
            isBackgroundMusicPlaying = false;
        }
        sf::Music gameOverSound;
        if (!gameOverSound.openFromFile(obj.sprite)) {
            std::cerr << "Error loading game over sound file: " << obj.sprite << std::endl;
            return;
        }
        gameOverSound.setVolume(12);
        gameOverSound.play();
        while (gameOverSound.getStatus() == sf::Music::Playing) {
            sf::sleep(sf::milliseconds(100));
        }
    } else {
        sf::Music soundEffect;
        if (!soundEffect.openFromFile(obj.sprite)) {
            std::cerr << "Error loading sound effect file: " << obj.sprite << std::endl;
            return;
        }
        soundEffect.setVolume(12);
        soundEffect.play();
        while (soundEffect.getStatus() == sf::Music::Playing) {
            sf::sleep(sf::milliseconds(100));
        }
    }
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

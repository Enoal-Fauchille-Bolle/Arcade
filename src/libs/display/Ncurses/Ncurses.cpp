/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Ncurses
*/

#include "Ncurses.hpp"

static const std::unordered_map<int, EventKey> keyMap = {{KEY_UP, KEYBOARD_UP},
    {KEY_DOWN, KEYBOARD_DOWN}, {KEY_LEFT, KEYBOARD_LEFT},
    {KEY_RIGHT, KEYBOARD_RIGHT}, {27, KEYBOARD_ESCAPE}, {' ', KEYBOARD_SPACE},
    {'\n', KEYBOARD_ENTER}, {KEY_ENTER, KEYBOARD_ENTER},
    {KEY_BACKSPACE, KEYBOARD_BACKSPACE}, {KEY_HOME, KEYBOARD_HOME},
    {KEY_END, KEYBOARD_END}, {KEY_DC, KEYBOARD_DELETE},
    {KEY_IC, KEYBOARD_INSERT}, {KEY_PPAGE, KEYBOARD_PAGEUP},
    {KEY_NPAGE, KEYBOARD_PAGEDOWN}, {'\t', KEYBOARD_TAB}, {'a', KEYBOARD_A},
    {'b', KEYBOARD_B}, {'c', KEYBOARD_C}, {'d', KEYBOARD_D}, {'e', KEYBOARD_E},
    {'f', KEYBOARD_F}, {'g', KEYBOARD_G}, {'h', KEYBOARD_H}, {'i', KEYBOARD_I},
    {'j', KEYBOARD_J}, {'k', KEYBOARD_K}, {'l', KEYBOARD_L}, {'m', KEYBOARD_M},
    {'n', KEYBOARD_N}, {'o', KEYBOARD_O}, {'p', KEYBOARD_P}, {'q', KEYBOARD_Q},
    {'r', KEYBOARD_R}, {'s', KEYBOARD_S}, {'t', KEYBOARD_T}, {'u', KEYBOARD_U},
    {'v', KEYBOARD_V}, {'w', KEYBOARD_W}, {'x', KEYBOARD_X}, {'y', KEYBOARD_Y},
    {'z', KEYBOARD_Z}, {'0', KEYBOARD_0}, {'1', KEYBOARD_1}, {'2', KEYBOARD_2},
    {'3', KEYBOARD_3}, {'4', KEYBOARD_4}, {'5', KEYBOARD_5}, {'6', KEYBOARD_6},
    {'7', KEYBOARD_7}, {'8', KEYBOARD_8}, {'9', KEYBOARD_9},
    {KEY_F(2), KEYBOARD_F2}, {KEY_F(3), KEYBOARD_F3}, {KEY_F(4), KEYBOARD_F4},
    {KEY_F(5), KEYBOARD_F5}, {KEY_F(6), KEYBOARD_F6}, {KEY_F(7), KEYBOARD_F7},
    {KEY_F(8), KEYBOARD_F8}, {KEY_F(9), KEYBOARD_F9},
    {KEY_F(10), KEYBOARD_F10}, {KEY_F(11), KEYBOARD_F11},
    {KEY_F(12), KEYBOARD_F12}};

const std::map<Ncurses::NcursesColor, RgbColor> predefinedColors = {
    {COLOR_BLACK, {0, 0, 0}}, {COLOR_RED, {255, 0, 0}},
    {COLOR_GREEN, {0, 255, 0}}, {COLOR_YELLOW, {255, 255, 0}},
    {COLOR_BLUE, {0, 0, 255}}, {COLOR_MAGENTA, {255, 0, 255}},
    {COLOR_CYAN, {0, 255, 255}}, {COLOR_WHITE, {255, 255, 255}}};

/**
 * @brief Construct a new Ncurses:: Ncurses object
 *
 * This constructor initializes the NCurses library by creating a new screen
 */
Ncurses::Ncurses()
{
    _name = LIBRARY_NAME;
    _dtype = LIBRARY_DTYPE;
    SCREEN *screen = newterm(NULL, stderr, stdin);

    if (!screen) {
        throw std::runtime_error("Failed to initialize NCurses terminal");
    }
    setlocale(LC_ALL, "");
    set_term(screen);
    cbreak();
    noecho();
    start_color();
    curs_set(0);
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
    keypad(stdscr, TRUE);
    mouseinterval(0);
    _buffer = newwin(0, 0, 0, 0);
    keypad(_buffer, TRUE);
    initColors();
}

/**
 * @brief Destroy the Ncurses:: Ncurses object
 *
 * This destructor cleans up the NCurses library by calling endwin().
 */
Ncurses::~Ncurses()
{
    if (_buffer)
        delwin(_buffer);
    endwin();
}

/**
 * @brief Initializes the colors for the NCurses library
 *
 * This function initializes the colors for the NCurses library by
 * mapping predefined colors to their RGB values.
 */
void Ncurses::initColors(void)
{
    for (const auto &[color, rgb] : predefinedColors) {
        init_color(
            color, rgb.r * 1000 / 255, rgb.g * 1000 / 255, rgb.b * 1000 / 255);
        init_pair(color, color, COLOR_BLACK);
    }
}

/**
 * @brief Finds the closest predefined color to a given RGB color
 * @param color The RGB color to match
 * @return Color The closest predefined color
 */
Ncurses::NcursesColor Ncurses::getClosestPredefinedColor(const RgbColor &color)
{
    int closestColor = COLOR_WHITE;
    int minDistance = INT_MAX;
    int dr = 0;
    int dg = 0;
    int db = 0;
    int distance = 0;

    for (const auto &[colorId, predefinedColor] : predefinedColors) {
        dr = color.r - predefinedColor.r;
        dg = color.g - predefinedColor.g;
        db = color.b - predefinedColor.b;
        distance = dr * dr + dg * dg + db * db;
        if (distance < minDistance) {
            minDistance = distance;
            closestColor = colorId;
        }
    }
    return closestColor;
}

////////////////////////////// Event Handling ///////////////////////////////

/**
 * @brief Polls events from the NCurses library
 *
 * This function retrieves events from the NCurses library and returns them
 * as a vector of RawEvent objects.
 *
 * @return std::vector<RawEvent> A vector of RawEvent objects representing the
 * polled events.
 */
RawEvent Ncurses::pollMouseEvent(MEVENT mouseEvent)
{
    RawEvent event;
    int offsetX = (this->_screenWidth / 2) - (SCREEN_WIDTH / 2);
    int offsetY = (this->_screenHeight / 2) - (SCREEN_HEIGHT / 2);
    int adjustedX = mouseEvent.x + 1 - offsetX;
    int adjustedY = mouseEvent.y + 1 - offsetY;
    Coordinates mouseCoordinates =
        terminalCoordinatesToGraphical(Coordinates{adjustedX, adjustedY});

    event.x = mouseCoordinates.x;
    event.y = mouseCoordinates.y;
    if (mouseEvent.bstate & BUTTON1_PRESSED) {
        event.type = PRESS;
        event.key = MOUSE_LEFT;
    } else if (mouseEvent.bstate & BUTTON1_RELEASED) {
        event.type = RELEASE;
        event.key = MOUSE_LEFT;
    } else if (mouseEvent.bstate & BUTTON3_PRESSED) {
        event.type = PRESS;
        event.key = MOUSE_RIGHT;
    } else if (mouseEvent.bstate & BUTTON3_RELEASED) {
        event.type = RELEASE;
        event.key = MOUSE_RIGHT;
    } else if (mouseEvent.bstate & BUTTON2_PRESSED) {
        event.type = PRESS;
        event.key = MOUSE_MIDDLE;
    } else if (mouseEvent.bstate & BUTTON2_RELEASED) {
        event.type = RELEASE;
        event.key = MOUSE_MIDDLE;
    } else if (mouseEvent.bstate & BUTTON4_PRESSED) {
        event.type = PRESS;
        event.key = MOUSE_WHEEL_UP;
    } else if (mouseEvent.bstate & BUTTON5_PRESSED) {
        event.type = PRESS;
        event.key = MOUSE_WHEEL_DOWN;
    }
    return event;
}

/**
 * @brief Polls keyboard events from the NCurses library
 *
 * This function retrieves keyboard events from the NCurses library and
 * returns them as a RawEvent object.
 *
 * @param key The key code of the pressed key
 * @return RawEvent A RawEvent object representing the polled keyboard event
 */
RawEvent Ncurses::pollKeyboardEvent(int key)
{
    RawEvent keyEvent;

    keyEvent.type = PRESS;
    auto it = keyMap.find(key);
    if (it != keyMap.end()) {
        keyEvent.key = it->second;
    }
    return keyEvent;
}

/**
 * @brief Polls events from the terminal.
 * @return A vector of RawEvent objects representing the polled events.
 */
std::vector<RawEvent> Ncurses::pollEvent(void)
{
    std::vector<RawEvent> events;
    int key;
    MEVENT mouseEvent;

    // nodelay(stdscr, TRUE);
    timeout(50);
    key = getch();
    if (key == ERR)
        return events;

    if (key == KEY_MOUSE) {
        if (getmouse(&mouseEvent) == OK) {
            events.push_back(pollMouseEvent(mouseEvent));
        }
    }
    events.push_back(pollKeyboardEvent(key));
    return events;
}

///////////////////////////////// Rendering /////////////////////////////////

/**
 * @brief Get the screen size of the terminal.
 * @return ScreenSize The width and height of the terminal screen.
 */
ScreenSize Ncurses::getScreenSize(void)
{
    getmaxyx(stdscr, this->_screenHeight, this->_screenWidth);
    return ScreenSize{static_cast<int>(this->_screenWidth),
        static_cast<int>(this->_screenHeight)};
}

/**
 * @brief Check if the terminal screen size is sufficient.
 * @return true if the screen size is sufficient, false otherwise.
 */
bool Ncurses::checkScreenSize(void)
{
    char str[100];

    snprintf(str, 100, "Please enlarge your terminal (%dx%d)", SCREEN_WIDTH,
        SCREEN_HEIGHT);
    if (this->_screenWidth < SCREEN_WIDTH ||
        this->_screenHeight < SCREEN_HEIGHT) {
        mvwprintw(_buffer, (this->_screenHeight - 1) / 2,
            (this->_screenWidth / 2) - (strlen(str) / 2), "%s", str);
        return false;
    }
    return true;
}

/**
 * @brief Check if the terminal screen box is sufficient.
 * @return true if the screen box is sufficient, false otherwise.
 */
bool Ncurses::checkScreenBox(void)
{
    return _screenWidth - SCREEN_WIDTH >= 2 &&
           _screenHeight - SCREEN_HEIGHT >= 2;
}

/**
 * @brief Display the screen box on the terminal.
 *
 * This function draws a box around the screen area.
 */
void Ncurses::displayScreenBox(void)
{
    int offsetX = (this->_screenWidth / 2) - (SCREEN_WIDTH / 2);
    int offsetY = (this->_screenHeight / 2) - (SCREEN_HEIGHT / 2);

    mvwaddch(_buffer, offsetY - 1, offsetX - 1, ACS_ULCORNER);
    mvwhline(_buffer, offsetY - 1, offsetX, ACS_HLINE, SCREEN_WIDTH);
    mvwaddch(_buffer, offsetY - 1, offsetX + SCREEN_WIDTH, ACS_URCORNER);
    mvwvline(_buffer, offsetY, offsetX - 1, ACS_VLINE, SCREEN_HEIGHT);
    mvwvline(
        _buffer, offsetY, offsetX + SCREEN_WIDTH, ACS_VLINE, SCREEN_HEIGHT);
    mvwaddch(_buffer, offsetY + SCREEN_HEIGHT, offsetX - 1, ACS_LLCORNER);
    mvwhline(
        _buffer, offsetY + SCREEN_HEIGHT, offsetX, ACS_HLINE, SCREEN_WIDTH);
    mvwaddch(_buffer, offsetY + SCREEN_HEIGHT, offsetX + SCREEN_WIDTH,
        ACS_LRCORNER);
}

/**
 * @brief Converts graphical coordinates to terminal coordinates.
 * @param graphicalCoordinates The graphical coordinates to convert.
 * @return The converted terminal coordinates.
 */
Coordinates Ncurses::graphicalCoordinatesToTerminal(
    Coordinates graphicalCoordinates)
{
    int x = graphicalCoordinates.x;
    int y = graphicalCoordinates.y;
    float terminalX =
        static_cast<float>(SCREEN_WIDTH * x) / GRAPHICAL_SCREEN_WIDTH;
    float terminalY =
        static_cast<float>(SCREEN_HEIGHT * y) / GRAPHICAL_SCREEN_HEIGHT;

    return Coordinates{static_cast<int>(std::floor(terminalX)),
        static_cast<int>(std::floor(terminalY))};
}

/**
 * @brief Converts terminal coordinates to graphical coordinates.
 * @param terminalCoordinates The terminal coordinates to convert.
 * @return The converted graphical coordinates.
 */
Coordinates Ncurses::terminalCoordinatesToGraphical(
    Coordinates terminalCoordinates)
{
    int x = terminalCoordinates.x;
    int y = terminalCoordinates.y;
    float graphicalX =
        static_cast<float>(GRAPHICAL_SCREEN_WIDTH * x) / SCREEN_WIDTH;
    float graphicalY =
        static_cast<float>(GRAPHICAL_SCREEN_HEIGHT * y) / SCREEN_HEIGHT;

    return Coordinates{static_cast<int>(std::floor(graphicalX)),
        static_cast<int>(std::floor(graphicalY))};
}

/**
 * @brief Check if a string contains UTF-8 characters
 * @param str The string to check
 * @return true if the string contains UTF-8 characters
 */
bool Ncurses::isUtf8String(const std::string &str)
{
    for (unsigned char c : str) {
        if (c > 127) {
            return true;
        }
    }
    return false;
}

/**
 * @brief Get the display width of a UTF-8 character in terminal columns
 * @param utf8_char The UTF-8 character to check
 * @return int The width (1 for box-drawing chars, 2 for emojis, etc)
 */
int Ncurses::getCharWidth(const std::string &utf8_char)
{
    wchar_t wc;

    mbstowcs(&wc, utf8_char.c_str(), 1);
    return wcwidth(wc);
}

void Ncurses::drawCharacter(
    Coordinates terminalCoordinates, const std::string &sprite)
{
    wchar_t wstr[1024];
    int x =
        (this->_screenWidth / 2) - (SCREEN_WIDTH / 2) + terminalCoordinates.x;
    int y = (this->_screenHeight / 2) - (SCREEN_HEIGHT / 2) +
            terminalCoordinates.y;

    if (isUtf8String(sprite)) {
        mbstowcs(wstr, sprite.c_str(), 1024);
        mvwaddwstr(_buffer, y, x, wstr);
    } else {
        mvwprintw(_buffer, y, x, "%s", sprite.c_str());
    }
}

/**
 * @brief Draws a render object on the terminal.
 * @param obj The renderObject to be drawn.
 */
void Ncurses::drawObject(renderObject obj)
{
    ScreenSize screenSize = getScreenSize();

    _screenHeight = screenSize.height;
    _screenWidth = screenSize.width;
    if (!checkScreenSize() || obj.sprite.empty())
        return;
    if (obj.type == RECTANGLE)
        drawRectangle(obj);
    if (obj.type == CIRCLE)
        drawCircle(obj);
    if (obj.type == TEXT)
        drawText(obj);
    if (obj.type == MUSIC)
        drawMusic(obj);
    if (checkScreenBox())
        displayScreenBox();
}

/**
 * @brief Draws a rectangle on the terminal.
 * @param obj The renderObject containing rectangle properties.
 */
void Ncurses::drawRectangle(renderObject obj)
{
    Coordinates terminalCoordinates =
        graphicalCoordinatesToTerminal(Coordinates{obj.x, obj.y});
    Coordinates terminalSize =
        graphicalCoordinatesToTerminal(Coordinates{obj.width, obj.height});
    NcursesColor color = getClosestPredefinedColor(RgbColor{
        static_cast<uint8_t>(obj.RGB[0]), static_cast<uint8_t>(obj.RGB[1]),
        static_cast<uint8_t>(obj.RGB[2])});

    wattron(_buffer, COLOR_PAIR(color));
    for (int i = 0; i < terminalSize.y; i++) {
        for (int j = 0; j < terminalSize.x / getCharWidth(obj.sprite); j++) {
            drawCharacter(Coordinates{terminalCoordinates.x + j,
                              terminalCoordinates.y + i},
                obj.sprite);
        }
    }
    wattroff(_buffer, COLOR_PAIR(color));
}

/**
 * @brief Draws a circle on the terminal.
 * @param obj The renderObject containing circle properties.
 */
void Ncurses::drawCircle(renderObject obj)
{
    (void)obj;
}

/**
 * @brief Draws text on the terminal.
 * @param obj The renderObject containing text properties.
 */
void Ncurses::drawText(renderObject obj)
{
    Coordinates terminalCoordinates =
        graphicalCoordinatesToTerminal(Coordinates{obj.x, obj.y});
    NcursesColor color = getClosestPredefinedColor(RgbColor{
        static_cast<uint8_t>(obj.RGB[0]), static_cast<uint8_t>(obj.RGB[1]),
        static_cast<uint8_t>(obj.RGB[2])});

    wattron(_buffer, COLOR_PAIR(color));
    drawCharacter(terminalCoordinates, obj.sprite);
    wattroff(_buffer, COLOR_PAIR(color));
}

/**
 * @brief Draws music-related objects (currently a placeholder).
 * @param obj The renderObject containing music properties.
 */
void Ncurses::drawMusic(renderObject obj)
{
    (void)obj;
}

/**
 * @brief Clears the terminal screen.
 */
void Ncurses::clear(void)
{
    werase(_buffer);
}

/**
 * @brief Refresh the terminal screen.
 */
void Ncurses::display(void)
{
    wnoutrefresh(_buffer);
    doupdate();
}

////////////////////////////////// Getters //////////////////////////////////

/**
 * @brief Retrieves the name of the display library.
 * @return A string representing the name of the library.
 */
std::string Ncurses::getName(void)
{
    return _name;
}

/**
 * @brief Retrieves the display type of the library.
 * @return The display type (TERMINAL).
 */
DisplayType Ncurses::getDType(void)
{
    return _dtype;
}

extern "C"
{
    /**
     * @brief Constructor for the shared library.
     */
    __attribute__((constructor)) void constructor()
    {
    }

    /**
     * @brief Destructor for the shared library.
     */
    __attribute__((destructor)) void destructor()
    {
    }

    /**
     * @brief Entry point for the Ncurses display library.
     * @return A pointer to a new Ncurses instance.
     */
    Ncurses *DisplayEntryPoint(void)
    {
        return new Ncurses();
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

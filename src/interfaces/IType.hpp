/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** IType
*/

#ifndef ITYPE_HPP_
    #define ITYPE_HPP_

enum LibType {
    GAME,
    DISPLAY,
    UNKNOW = -1
};

enum DisplayType {
    GRAPHICAL,
    TERMINAL
};

enum Shape {
    RECTANGLE,
    CIRCLE,
    TEXT,
    MUSIC
};

enum EventType {
    PRESS,
    RELEASE,
    QUIT
};

enum EventKey {
    // Mouse events
    MOUSE_LEFT,
    MOUSE_RIGHT,
    MOUSE_MIDDLE,
    MOUSE_WHEEL_UP,
    MOUSE_WHEEL_DOWN,

    // Alphabetical keys
    KEYBOARD_A,
    KEYBOARD_B,
    KEYBOARD_C,
    KEYBOARD_D,
    KEYBOARD_E,
    KEYBOARD_F,
    KEYBOARD_G,
    KEYBOARD_H,
    KEYBOARD_I,
    KEYBOARD_J,
    KEYBOARD_K,
    KEYBOARD_L,
    KEYBOARD_M,
    KEYBOARD_N,
    KEYBOARD_O,
    KEYBOARD_P,
    KEYBOARD_Q,
    KEYBOARD_R,
    KEYBOARD_S,
    KEYBOARD_T,
    KEYBOARD_U,
    KEYBOARD_V,
    KEYBOARD_W,
    KEYBOARD_X,
    KEYBOARD_Y,
    KEYBOARD_Z,

    // Numeric keys
    KEYBOARD_0,
    KEYBOARD_1,
    KEYBOARD_2,
    KEYBOARD_3,
    KEYBOARD_4,
    KEYBOARD_5,
    KEYBOARD_6,
    KEYBOARD_7,
    KEYBOARD_8,
    KEYBOARD_9,

    // Function keys
    KEYBOARD_F1,
    KEYBOARD_F2,
    KEYBOARD_F3,
    KEYBOARD_F4,
    KEYBOARD_F5,
    KEYBOARD_F6,
    KEYBOARD_F7,
    KEYBOARD_F8,
    KEYBOARD_F9,
    KEYBOARD_F10,
    KEYBOARD_F11,
    KEYBOARD_F12,

    // Special keys
    KEYBOARD_ESCAPE,
    KEYBOARD_ENTER,
    KEYBOARD_SPACE,
    KEYBOARD_BACKSPACE,
    KEYBOARD_TAB,
    KEYBOARD_UP,
    KEYBOARD_DOWN,
    KEYBOARD_LEFT,
    KEYBOARD_RIGHT,
    KEYBOARD_LSHIFT,
    KEYBOARD_RSHIFT,
    KEYBOARD_LCTRL,
    KEYBOARD_RCTRL,
    KEYBOARD_LALT,
    KEYBOARD_RALT,
    KEYBOARD_HOME,
    KEYBOARD_END,
    KEYBOARD_DELETE,
    KEYBOARD_INSERT,
    KEYBOARD_PAGEUP,
    KEYBOARD_PAGEDOWN,

    // Other common keys
    KEYBOARD_MINUS,
    KEYBOARD_PLUS,
    KEYBOARD_COMMA,
    KEYBOARD_PERIOD,
    KEYBOARD_SLASH,
    KEYBOARD_SEMICOLON,
    KEYBOARD_APOSTROPHE,
    KEYBOARD_BACKSLASH,
    KEYBOARD_GRAVE,
    KEYBOARD_LBRACKET,
    KEYBOARD_RBRACKET,
};

struct RawEvent {
    EventType type;
    EventKey key;
    int x;
    int y;
};

struct Coordinates {
    int x;
    int y;
};

struct ScreenSize {
    int width;
    int height;
};

struct RgbColor {
    int r;
    int g;
    int b;
};

#endif /* !ITYPE_HPP_ */

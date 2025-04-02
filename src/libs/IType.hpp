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
    DISPLAY
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
    KEY_A,
    KEY_B,
    KEY_C,
    KEY_D,
    KEY_E,
    KEY_F,
    KEY_G,
    KEY_H,
    KEY_I,
    KEY_J,
    KEY_K,
    KEY_L,
    KEY_M,
    KEY_N,
    KEY_O,
    KEY_P,
    KEY_Q,
    KEY_R,
    KEY_S,
    KEY_T,
    KEY_U,
    KEY_V,
    KEY_W,
    KEY_X,
    KEY_Y,
    KEY_Z,

    // Numeric keys
    KEY_0,
    KEY_1,
    KEY_2,
    KEY_3,
    KEY_4,
    KEY_5,
    KEY_6,
    KEY_7,
    KEY_8,
    KEY_9,

    // Function keys
    KEY_F2,
    KEY_F3,
    KEY_F4,
    KEY_F5,
    KEY_F6,
    KEY_F7,
    KEY_F8,
    KEY_F9,
    KEY_F10,
    KEY_F11,
    KEY_F12,

    // Special keys
    KEY_ESCAPE,
    KEY_RETURN,
    KEY_SPACE,
    KEY_BACKSPACE,
    KEY_TAB,
    KEY_UP,
    KEY_DOWN,
    KEY_LEFT,
    KEY_RIGHT,
    KEY_LSHIFT,
    KEY_RSHIFT,
    KEY_LCTRL,
    KEY_RCTRL,
    KEY_LALT,
    KEY_RALT,
    KEY_HOME,
    KEY_END,
    KEY_DELETE,
    KEY_INSERT,
    KEY_PAGEUP,
    KEY_PAGEDOWN,

    // Other common keys
    KEY_MINUS,
    KEY_PLUS,
    KEY_COMMA,
    KEY_PERIOD,
    KEY_SLASH,
    KEY_SEMICOLON,
    KEY_APOSTROPHE,
    KEY_BACKSLASH,
    KEY_GRAVE,
    KEY_LBRACKET,
    KEY_RBRACKET,
};

struct RawEvent {
    EventType type;
    EventKey key;
    int x;
    int y;
};

#endif /* !ITYPE_HPP_ */

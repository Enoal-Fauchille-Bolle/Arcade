/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Interface for display
*/

#ifndef IDisplay_HPP_
    #define IDisplay_HPP_

    #include <string>
    #include <map>
    #include <vector>
    #include "../../IType.hpp"

    struct rawEvent {
        eventType type;
        eventKey key;
        int x;
        int y;
    };

    struct renderObject {
        int x;
        int y;
        int width;
        int height;
        int rotate;
        int RGB[3];
        shape type;
        std::string sprite;
    };

class IDisplay {
    public:
        virtual ~IDisplay() = default;

        virtual std::vector<rawEvent> pollEvent(void) = 0;

        virtual void drawObject(renderObject) = 0;

        virtual void clear(void) = 0;
        virtual void display(void) = 0;

        virtual std::string getName(void) = 0;

    protected:
    private:
};

#endif /* !IDisplay_HPP_ */

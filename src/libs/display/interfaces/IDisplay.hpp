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
    #include "../../../interfaces/IType.hpp"

    struct renderObject {
        int x;
        int y;
        int width;
        int height;
        int rotate;
        int RGB[3];
        Shape type;
        std::string sprite;
    };

class IDisplay {
    public:
        virtual ~IDisplay() = default;

        virtual std::vector<RawEvent> pollEvent(void) = 0;

        virtual void drawObject(renderObject) = 0;

        virtual void clear(void) = 0;
        virtual void display(void) = 0;

        virtual std::string getName(void) = 0;
        virtual DisplayType getDType(void) = 0;

    protected:
    private:
};

#endif /* !IDisplay_HPP_ */

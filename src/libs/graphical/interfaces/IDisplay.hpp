/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Interface for graphical
*/

#ifndef IGRAPHICAL_HPP_
    #define IGRAPHICAL_HPP_

    #include <string>
    #include <map>

    struct rawEvent {
        std::string type;
        std::string key;
        int x;
        int y;
    };

    struct renderObject {
        int x;
        int y;
        int width;
        int height;
        int rotate;
        std::string sprite;
    };

class IGraphical {
    public:
        IGraphical() = default;
        virtual ~IGraphical() = default;

        virtual std::vector<rawEvent> pollEvent(void) = 0;

        virtual void drawObject(renderObject) = 0;
        virtual void drawText(renderObject) = 0;

        virtual void clear(void) = 0;
        virtual void display(void) = 0;

        virtual std::string getName(void) = 0;

    protected:
    private:
};

#endif /* !IGRAPHICAL_HPP_ */

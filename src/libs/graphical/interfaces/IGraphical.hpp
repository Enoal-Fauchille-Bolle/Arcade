/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Interface for graphical
*/

#ifndef IGRAPHICAL_HPP_
    #define IGRAPHICAL_HPP_

    #include <string>

class IGraphical {
    public:
        virtual ~IGraphical() = default;

        virtual error init(void) = 0;
        virtual void fini(void) = 0;
        virtual rawEvent pollEvent(void) = 0;
        virtual void clear(void) = 0;
        virtual void drawObject(renderObject) = 0;
        virtual void drawText(struct { std::string text; props }) = 0;
        virtual void drawDynamicObject(renderObject) = 0;
        virtual void display(void) = 0;
        virtual std::string getName(void) = 0;

    protected:
    private:
};

#endif /* !IGRAPHICAL_HPP_ */

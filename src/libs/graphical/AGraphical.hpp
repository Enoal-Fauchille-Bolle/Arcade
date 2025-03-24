/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Abstract class for graphical libraries
*/

#ifndef AGRAPHICAL_HPP_
    #define AGRAPHICAL_HPP_

    #include "IGraphical.hpp"
    #include <string>
    #include <vector>

class AGraphical : public IGraphical {
    public:
        AGraphical(const std::string &name);
        virtual ~AGraphical() = default;

        virtual std::vector<rawEvent> pollEvent(void) = 0;

        virtual void drawObject(renderObject) = 0;
        virtual void drawText(renderObject) = 0;

        virtual void clear(void) = 0;
        virtual void display(void) = 0;

        std::string getName(void) override;

    protected:
        std::string _name;
        std::vector<rawEvent> _events;
        bool _isOpen;

    private:
};

#endif /* !AGRAPHICAL_HPP_ */
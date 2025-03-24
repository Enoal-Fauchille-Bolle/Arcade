/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Abstract class for graphical libraries
*/

#ifndef ADISPLAY_HPP_
    #define ADISPLAY_HPP_

    #include "IDisplay.hpp"
    #include <string>
    #include <vector>

class ADisplay : public IGraphical {
    public:
    ADisplay(const std::string &name);
        virtual ~ADisplay() = default;

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

#endif /* !ADISPLAY_HPP_ */
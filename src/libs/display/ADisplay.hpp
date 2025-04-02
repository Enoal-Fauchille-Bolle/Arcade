/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Abstract class for display libraries
*/

#ifndef ADISPLAY_HPP_
    #define ADISPLAY_HPP_

    #include "./interfaces/IDisplay.hpp"
    #include <string>
    #include <vector>

class ADisplay : public IDisplay {
    public:
        virtual ~ADisplay() = default;

        virtual std::vector<RawEvent> pollEvent(void) = 0;

        virtual void drawObject(renderObject) = 0;

        virtual void clear(void) = 0;
        virtual void display(void) = 0;

        std::string getName(void) override;

    protected:
        std::string _name;
        std::vector<RawEvent> _events;
        bool _isOpen;

    private:
};

#endif /* !ADISPLAY_HPP_ */
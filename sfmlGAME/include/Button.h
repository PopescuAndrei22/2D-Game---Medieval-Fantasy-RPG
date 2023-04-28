#ifndef BUTTON_H
#define BUTTON_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>

class Button
{
    public:
        /* getters */
        bool getIsVisible() const;
        sf::Vector2f getButtonPosition();
        float getButtonWidth();
        float getButtonHeight();
        std::string getButtonName();

        /* setters */
        void setIsVisible(bool);
        void setButtonPosition(sf::Vector2f);

        /* class methods */
        void hoverButton(sf::Vector2i);
        bool isMouseCursorOnButton(sf::Vector2i);
        bool isButtonClicked(sf::Vector2i,bool);

        void setValues(sf::Vector2f, std::string);

        void draw(sf::RenderWindow&);

        Button();
        ~Button();

    private:

        sf::RectangleShape button;

        sf::Text buttonText;

        sf::Font font;

        std::string buttonName;

        bool isVisible;

        sf::Color defaultButtonColor;
        sf::Color hoverButtonColor;
};

#endif // BUTTON_H

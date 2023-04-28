#ifndef MENU_H
#define MENU_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>
#include "Button.h"

class Menu
{
    public:
        /* getters */
        bool getIsButtonPressed() const;
        std::string getButtonPressedName() const;

        /* setters */
        void setWindowSize(sf::Vector2f);
        void setIsButtonClicked(bool);

        void LayoutManager();

        void setButtonsVisibility(std::string);

        void manageMenu(sf::RenderWindow&);

        void draw(sf::RenderWindow&);

        Menu();
        ~Menu();

    private:

        sf::Vector2f windowSize;

        std::vector <Button*> buttons;

        // game name

        sf::Text gameName;
        sf::Font font;

        // buttons logic

        bool isButtonPressed;
        std::string buttonPressedName;

        bool isButtonClicked;

        // Menu background

        sf::Texture backgroundTexture;
        sf::Sprite backgroundSprite;
};

#endif // MENU_H

#ifndef BUTTON_H
#define BUTTON_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include "ManageText.h"

using namespace std;
using namespace sf;

class Button
{
private:
    RectangleShape button;
    ManageText button_text;
    bool isPressed;
    Color STATE_1,STATE_2,STATE_3;

    vector <Button> SubButtons;

public:

    Button(bool, float, float, sf::Color, sf::Color, sf::Color, sf::Font&, string, sf::Color); //constructor

    ~Button();

    Vector2f getSize() const;

    // setters for color state
    Color getNormalColor() const;
    Color getHoverColor() const;
    Color getPressColor() const;

    void setPos(float,float); // setter
    Vector2f getPos() const; // setter

    void draw(RenderWindow&);

    void checkHover(RenderWindow&);

    RectangleShape getButton() const; //getter

    void setPressState(bool); // setter

    bool getPressState() const;

    void setNewColor(sf::Color); // setter

    void addSubButton(string);

    float getSubButtonsSize();

    string getText();

    bool haveSubButtons() const;

    bool buttonIsPressed(float,float) const;

    vector <Button> getSubButtons();

    void setStateSubButtons(int);

    void deleteSubButtons();

};

#endif // BUTTON_H

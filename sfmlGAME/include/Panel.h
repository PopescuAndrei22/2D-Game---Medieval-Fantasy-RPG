#ifndef PANEL_H
#define PANEL_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Button.h"
#include <vector>
#include <map>

using namespace std;
using namespace sf;

class Panel
{
private:

    RectangleShape rectangle;
    vector <Button> PanelButtons;

public:

    Panel(int,int,sf::Color); // constructor

    ~Panel(); // destructor

    void addButton(Button);

    void printButtons(RenderWindow&);

    RectangleShape getRectangle() const; //getter

    void HoverButtons(RenderWindow&);

    void ButtonPressedEvent(int,int);

    void createSubButton(string,string);

    bool ButtonIsSelected(string);

    Vector2f getPanelSize() const;

    bool doesTheButtonExist(string);

    void setPos(float, float);
};

#endif // PANEL_H

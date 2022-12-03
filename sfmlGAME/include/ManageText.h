#ifndef MANAGETEXT_H
#define MANAGETEXT_H
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class ManageText
{
private:
    Text text;

public:
    ManageText(sf::Font&,string,sf::Color); // constructor

    void setCharSize(int); // setter

    void setPos(float, float); // setter

    FloatRect getSize() const; // getter

    Text getText() const; // getter

    string getString() const;

    void setText(string);

    const Font* getFont() const;

    Color getFillColor() const;
};

#endif // MANAGETEXT_H

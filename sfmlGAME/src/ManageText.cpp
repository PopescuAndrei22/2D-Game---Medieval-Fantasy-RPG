#include "ManageText.h"

ManageText::ManageText(sf::Font &font, string txt, sf::Color color)
{
    this->text.setFont(font);
    this->text.setString(txt);
    this->text.setFillColor(color);
}

Text ManageText::getText() const
{
    return this->text;
}

void ManageText::setCharSize(int chr_size)
{
    this->text.setCharacterSize(chr_size);
}

void ManageText::setPos(float x, float y)
{
    this->text.setPosition(sf::Vector2f(x,y));
}

FloatRect ManageText::getSize() const
{
    return this->text.getGlobalBounds();
}

string ManageText::getString() const
{
    return this->text.getString();
}

const Font* ManageText::getFont() const
{
    return this->text.getFont();
}

Color ManageText::getFillColor() const
{
    return this->text.getFillColor();
}

void ManageText::setText(string txt)
{
    this->text.setString(txt);
}

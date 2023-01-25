#include "Bar.h"

void Bar::manageBar(int value)
{
    int numberOfFilledBars = value / this->barBlock;

    for(int i=0;i<numberOfFilledBars;i++)
        this->bars[i].setTexture(this->textureBar);
    for(int i=numberOfFilledBars;i<this->bars.size();i++)
        this->bars[i].setTexture(this->textureEmptyBar);
}

// setters
void Bar::setPosition(Vector2f newPosition)
{
    this->icon.setPosition(newPosition);

    int posx = this->icon.getPosition().x;
    int posy = this->icon.getPosition().y;

    if(!this->bars.empty())
        {
            int iconWidth = this->icon.getTextureRect().width;

            int barsWidth = this->bars[0].getTextureRect().width;

            this->bars[0].setPosition(Vector2f(posx+iconWidth,posy));

            for(int i=1; i<this->bars.size(); i++)
                {
                    Vector2f positionPreviousElement = this->bars[i-1].getPosition();

                    this->bars[i].setPosition(Vector2f(positionPreviousElement.x+barsWidth,positionPreviousElement.y));
                }
        }
}

void Bar::draw(RenderWindow *window)
{
    window->draw(this->icon);

    for(int i=0; i<this->bars.size(); i++)
        window->draw(this->bars[i]);
}

Bar::Bar(string fileNameBar, string fileNameEmptyBar, int barValue)
{
    this->barBlock = 25;

    string pathTextureBar = "sprites/bars/" + fileNameBar + ".png";
    string pathTextureEmptyBar = "sprites/bars/" + fileNameEmptyBar + ".png";

    this->textureBar.loadFromFile(pathTextureBar); // getting the texture
    this->textureEmptyBar.loadFromFile(pathTextureEmptyBar);

    // hard coding for the current health bar
    this->icon.setTexture(this->textureBar);
    this->icon.setTextureRect(IntRect(0,35,33,45));

    Sprite sprite;
    sprite.setTexture(this->textureBar);
    sprite.setTextureRect(IntRect(0,15,33,25));

    for(int i=0; i<(barValue / this->barBlock); i++)
        this->bars.push_back(sprite);

    a.setTextureRect(IntRect(0,15,33,25));
}

Bar::~Bar()
{

}

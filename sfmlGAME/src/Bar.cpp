#include "Bar.h"

void Bar::manageBar(int value)
{
    int numberOfFilledBars = value / this->barBlock;

    for(int i=0; i<numberOfFilledBars; i++)
        this->bars[i].setTexture(this->textureBar);
    for(int i=numberOfFilledBars; i<this->bars.size(); i++)
        this->bars[i].setTexture(this->textureEmptyBar);
}

// setters
void Bar::setPosition(Vector2f newPosition)
{
    this->icon.setPosition(newPosition);

    float posx = this->icon.getPosition().x;
    float posy = this->icon.getPosition().y;

    if(!this->bars.empty())
        {
            float iconWidth = this->icon.getTextureRect().width * this->icon.getScale().x;;

            float barsWidth = this->bars[0].getTextureRect().width * this->bars[0].getScale().x;

            this->bars[0].setPosition(Vector2f(posx+iconWidth,posy));

            for(int i=1; i<this->bars.size(); i++)
                {
                    Vector2f positionPreviousElement = this->bars[i-1].getPosition();

                    this->bars[i].setPosition(Vector2f(positionPreviousElement.x+barsWidth,positionPreviousElement.y));
                }
        }
}

void Bar::setPositionEnemy(Vector2f enemyPosition, Vector2f enemySize)
{
    float sizeBar = 0.0;

    Vector2f newPosition = enemyPosition;

    // i could set the scales in constructor instead

    this->icon.setScale(0,0); // setScale(0,0) if we don't want to see the icon

    if(this->icon.getScale().x != 0)
        sizeBar += this->icon.getTextureRect().width;

    if(this->bars.size() > 0)
        sizeBar += this->bars.size() * this->bars[0].getTextureRect().width;

    for(int i=0; i<this->bars.size(); i++)
        {
            this->bars[i].setScale(enemySize.x / sizeBar,0.5);
        }

    if(this->bars.size())
        newPosition.y -= this->bars[0].getTextureRect().height * this->bars[0].getScale().y;

    this->setPosition(newPosition);
}

void Bar::draw(RenderWindow *window)
{
    window->draw(this->icon);

    for(int i=0; i<this->bars.size(); i++)
        window->draw(this->bars[i]);
}

Bar::Bar(string fileNameBar, string fileNameEmptyBar, int barValue)
{
    // can be auto-adjusted, will think about this
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

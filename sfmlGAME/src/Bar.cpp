#include "Bar.h"

/* class methods */
void Bar::updateBar(int value)
{
    int sum = 0;

    for(unsigned int i=0; i<this->bars.size(); i++)
        {
            sum += this->barValue;

            if(sum > value)
                {
                    int dif = sum - value;

                    if(dif > this->barValue)
                        dif = 0;

                    float procentBar = ((float) dif / (float)this->barValue) * 100.0f;

                    if(procentBar == 0)
                        procentBar = 100;

                    float newRGB = procentBar/100.0f * 255;

                    int rgb = std::min((int)newRGB,255);

                    this->bars[i].setColor(sf::Color(179, rgb, rgb));
                }
            else
                {
                    this->bars[i].setColor(sf::Color(179, 0, 0));
                }
        }
}

void Bar::setPosition(sf::Vector2f position)
{
    this->iconSprite.setPosition(position);

    float posx = this->iconSprite.getPosition().x;
    float posy = this->iconSprite.getPosition().y;

    if(!this->bars.empty())
        {
            float iconWidth = this->iconSprite.getTextureRect().width * this->iconSprite.getScale().x;;

            float barsWidth = this->bars[0].getTextureRect().width * this->bars[0].getScale().x;

            this->bars[0].setPosition(sf::Vector2f(posx+iconWidth,posy));

            for(unsigned i=1; i<this->bars.size(); i++)
                {
                    sf::Vector2f positionPreviousElement = this->bars[i-1].getPosition();

                    this->bars[i].setPosition(sf::Vector2f(positionPreviousElement.x+barsWidth,positionPreviousElement.y));
                }
        }
}

void Bar::setPositionEnemy(sf::Vector2f enemyPosition, sf::Vector2f enemySize)
{
    float sizeBar = 0.0;

    sf::Vector2f newPosition = enemyPosition;

    // i could set the scales in constructor instead

    this->iconSprite.setScale(0,0); // setScale(0,0) if we don't want to see the icon

    if(this->iconSprite.getScale().x != 0)
        sizeBar += this->iconSprite.getTextureRect().width;

    if(this->bars.size() > 0)
        sizeBar += this->bars.size() * this->bars[0].getTextureRect().width;

    for(unsigned i=0; i<this->bars.size(); i++)
        {
            this->bars[i].setScale(enemySize.x / sizeBar,0.5);
        }

    if(this->bars.size())
        newPosition.y -= this->bars[0].getTextureRect().height * this->bars[0].getScale().y;

    this->setPosition(newPosition);
}

void Bar::setBar(std::string fileName, int value)
{
    std::string filePath = "sprites/bars/" + fileName + ".png";

    this->textureBar.loadFromFile(filePath);
    this->textureEmptyBar.loadFromFile("sprites/bars/empty_bar.png");

    this->iconSprite.setTexture(this->textureBar);
    this->barSprite.setTexture(this->textureEmptyBar);

    std::string pathValues = "values/bars/" + fileName + ".json";
    std::ifstream file(pathValues);
    nlohmann::json data = nlohmann::json::parse(file);

    auto icon = data.at("icon");
    auto bar = data.at("bar");

    try
        {
            sf::IntRect rectIcon = sf::IntRect(icon[0],icon[1],icon[2],icon[3]);

            sf::IntRect rectBar = sf::IntRect(bar[0],bar[1],bar[2],bar[3]);

            this->iconSprite.setTextureRect(rectIcon);
            this->barSprite.setTextureRect(rectBar);

            this->barValue = (int)data.at("barValue");

        }
    catch(const nlohmann::json::exception& e)
        {
            std::cout << e.what() << '\n';
        }

    for(unsigned int i=0; i<value / this->barValue; i++)
        this->bars.push_back(this->barSprite);

    file.close();
}

void Bar::draw(sf::RenderWindow &renderWindow)
{
    renderWindow.draw(this->iconSprite);

    for(unsigned int i=0; i<this->bars.size(); i++)
        {
            renderWindow.draw(this->bars[i]);
        }
}

/* constructors */
Bar::Bar()
{

}

/* destructors */
Bar::~Bar()
{

}

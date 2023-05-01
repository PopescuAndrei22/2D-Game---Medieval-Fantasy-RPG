#include "TransparentObstacle.h"

void TransparentObstacle::setValues(std::string mapName, std::string fileName, sf::Vector2f position)
{
    std::string filePath = "resources/maps/" + mapName + "/" + mapName + ".png";

    this->texture.loadFromFile(filePath);

    this->sprite.setTexture(this->texture);

    this->sprite.setPosition(position);

    std::string pathValues = "values/maps/" + mapName + "/obstacles/" + fileName + ".json";
    std::ifstream file(pathValues);
    nlohmann::json data = nlohmann::json::parse(file);

    try
        {
            sf::IntRect rect = sf::IntRect(data["rect"][0],data["rect"][1],data["rect"][2],data["rect"][3]);

            this->sprite.setTextureRect(rect);
        }
    catch(const nlohmann::json::exception& e)
        {
            std::cout << e.what() << '\n';
        }
}

void TransparentObstacle::checkTransparency(sf::Vector2f characterPosition)
{
    sf::FloatRect dimensions = this->sprite.getGlobalBounds();

    bool isInRange = false;

    if(characterPosition.x >= dimensions.left && characterPosition.x <= (dimensions.left + dimensions.width))
        {
            if(characterPosition.y >= dimensions.top && characterPosition.y <= (dimensions.top + dimensions.height))
                {
                    isInRange = true;
                }
        }

    if(isInRange)
        {
            this->sprite.setColor(sf::Color(255,255,255,100));
        }
    else
        {
            this->sprite.setColor(sf::Color::White);
        }
}

void TransparentObstacle::draw(sf::RenderWindow &renderWindow)
{
    renderWindow.draw(this->sprite);
}

TransparentObstacle::TransparentObstacle()
{

}

TransparentObstacle::~TransparentObstacle()
{

}

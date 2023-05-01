#include "Portal.h"

/* setters */
void Portal::setPosition(sf::Vector2f position)
{
    this->sprite.setPosition(position);
}

/* class methods */
void Portal::draw(sf::RenderWindow &renderWindow)
{
    renderWindow.draw(this->sprite);
}

bool Portal::isInRange(sf::Vector2f characterPosition)
{
    sf::FloatRect dimensions = this->sprite.getGlobalBounds();

    if(characterPosition.x >= dimensions.left && characterPosition.x <= (dimensions.left + dimensions.width))
        {
            if(characterPosition.y >= dimensions.top && characterPosition.y <= (dimensions.top + dimensions.height))
                {
                    return true;
                }
        }

    return false;
}

Portal::Portal()
{
    std::string filePath = "resources/maps/map1/Entities.png";

    this->texture.loadFromFile(filePath);

    this->sprite.setTexture(this->texture);

    std::string pathValues = "values/maps/map1/entities/portal.json";
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

    file.close();
}

Portal::~Portal()
{

}

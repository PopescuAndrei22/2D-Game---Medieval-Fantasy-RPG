#include "AnimatedObject.h"

void AnimatedObject::setValues(std::string mapName, std::string fileName, sf::Vector2f position)
{
    std::string filePath = "resources/maps/" + mapName + "/" + mapName + "_animations" + ".png";

    this->texture.loadFromFile(filePath);

    this->sprite.setTexture(this->texture);

    this->sprite.setPosition(position);

    std::string pathValues = "values/maps/" + mapName + "/animatedObjects/" + fileName + ".json";
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


void AnimatedObject::draw(sf::RenderWindow &renderWindow)
{
    renderWindow.draw(this->sprite);
}


AnimatedObject::AnimatedObject()
{

}

AnimatedObject::~AnimatedObject()
{

}

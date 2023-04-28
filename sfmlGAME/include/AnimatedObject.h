#ifndef ANIMATEDOBJECT_H
#define ANIMATEDOBJECT_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <vector>
#include <algorithm>

class AnimatedObject
{
public:

    void setValues(std::string,std::string,sf::Vector2f);

    void draw(sf::RenderWindow&);

    AnimatedObject();
    ~AnimatedObject();

private:

    sf::Texture texture;
    sf::Sprite sprite;
};

#endif // ANIMATEDOBJECT_H

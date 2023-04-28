#ifndef TRANSPARENTOBSTACLE_H
#define TRANSPARENTOBSTACLE_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <vector>
#include <algorithm>

class TransparentObstacle
{
    public:

        /* class methods */
        void setValues(std::string,std::string,sf::Vector2f);

        void checkTransparency(sf::Vector2f, sf::Vector2f);

        void draw(sf::RenderWindow&);

        TransparentObstacle();
        ~TransparentObstacle();

    private:

        sf::Texture texture;
        sf::Sprite sprite;
};

#endif // TRANSPARENTOBSTACLE_H

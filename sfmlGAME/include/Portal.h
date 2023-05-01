#ifndef PORTAL_H
#define PORTAL_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>

class Portal
{
    public:

        /* setters */
        void setPosition(sf::Vector2f);

        /* class methods */
        void draw(sf::RenderWindow&);

        bool isInRange(sf::Vector2f);

        Portal();
        ~Portal();

    private:

        sf::Texture texture;
        sf::Sprite sprite;
};

#endif // PORTAL_H

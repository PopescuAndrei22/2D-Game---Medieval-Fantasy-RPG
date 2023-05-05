#ifndef PROJECTILE_H
#define PROJECTILE_H
#include <iostream>
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>
#include <SFML/Graphics.hpp>

class Projectile
{
    public:
        Projectile();
        ~Projectile();

    private:

        sf::Vector2f destination;

        // sf::Vector2f projectileSize;
};

#endif // PROJECTILE_H

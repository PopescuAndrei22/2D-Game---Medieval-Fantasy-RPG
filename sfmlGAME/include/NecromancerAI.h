#ifndef NECROMANCERAI_H
#define NECROMANCERAI_H
#include <iostream>
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>
#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include "Boss.h"
#include "Projectile.h"
#include <cmath>

class NecromancerAI
{
    public:
        std::string getNewDirection(Boss&);
        bool isInRadius(Boss&);

        float getEuclidianDistance(sf::Vector2f, sf::Vector2f);

        void passiveAI(Boss&);
        void agressiveAI(Boss&);

        void manageAI(Boss&, float);

        NecromancerAI();
        ~NecromancerAI();

    private:

};

#endif // NECROMANCERAI_H

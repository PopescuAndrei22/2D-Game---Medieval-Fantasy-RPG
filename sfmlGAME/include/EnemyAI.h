#ifndef ENEMYAI_H
#define ENEMYAI_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>
#include "Enemy.h"

class EnemyAI
{
    public:

        /* class methods */
        float getEuclidianDistance(sf::Vector2f, sf::Vector2f);

        std::string getNewDirection(Enemy&);

        bool isInRadius(Enemy&);

        void passiveAI(Enemy&);

        void agressiveAI(Enemy&);

        void manageAI(Enemy&,float);

        /* constructors */
        EnemyAI();

        /* destructors */
        ~EnemyAI();

    private:

};

#endif // ENEMYAI_H

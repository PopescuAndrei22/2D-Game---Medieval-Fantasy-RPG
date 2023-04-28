#ifndef COMBATSYSTEM_H
#define COMBATSYSTEM_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>
#include "Character.h"
#include "Enemy.h"
#include "Player.h"

class CombatSystem
{
    public:

        /* class methods*/
        float getEuclidianDistance(sf::Vector2f, sf::Vector2f);
        void update(Player&, Enemy&);

        /* constructors */
        CombatSystem();

        /* destructors */
        ~CombatSystem();

    private:
};

#endif // COMBATSYSTEM_H

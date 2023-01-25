#ifndef CHARACTERMANAGEMENT_H
#define CHARACTERMANAGEMENT_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Character.h"
#include "Enemy.h"

using namespace sf;
using namespace std;

// Managing player, enemies and NPCs

class CharacterManagement
{
    public:
        CharacterManagement();
        ~CharacterManagement();

    private:
        vector <Enemy> enemies;
};

#endif // CHARACTERMANAGEMENT_H

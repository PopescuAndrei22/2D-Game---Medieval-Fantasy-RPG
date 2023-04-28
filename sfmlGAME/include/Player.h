#ifndef PLAYER_H
#define PLAYER_H
#include "Character.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>
#include <SFML/Graphics.hpp>

class Player: public Character
{
    public:
        /* constructors */
        Player();
        /* destructors */
        ~Player();

    private:
};

#endif // PLAYER_H

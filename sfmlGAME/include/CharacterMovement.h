#ifndef CHARACTERMOVEMENT_H
#define CHARACTERMOVEMENT_H
#include "Controls.h"
#include "Map.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Character.h"
#include <vector>

class CharacterMovement
{
    public:

        /* class methods */
        void manageMovement(Character&,float,Map&);

        bool isInRange(Character&,Map&,sf::Vector2f);

        sf::Vector2f getKnockbackPosition(Character&,Map&);

        /* constructors */
        CharacterMovement();

        /* destructors */
        ~CharacterMovement();

    private:
        float timeMove, timeMoveReset;
};

#endif // CHARACTERMOVEMENT_H

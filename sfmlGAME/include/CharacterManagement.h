#ifndef CHARACTERMANAGEMENT_H
#define CHARACTERMANAGEMENT_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>
#include "Controls.h"
#include "Player.h"
#include "AnimationState.h"

class CharacterManagement
{
    public:

        /* class methods */
        void managePlayerControls(sf::Keyboard::Key, Controls, Player&);

        void manageCharacterActions(Character&, AnimationState&, float);

        /* constructors */
        CharacterManagement();

        /* destructors */
        ~CharacterManagement();

    private:

};

#endif // CHARACTERMANAGEMENT_H

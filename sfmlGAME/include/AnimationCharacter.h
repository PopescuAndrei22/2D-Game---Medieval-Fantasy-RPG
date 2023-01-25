#ifndef ANIMATIONCHARACTER_H
#define ANIMATIONCHARACTER_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Animation.h"
#include "Controls.h"
#include "Character.h"
#include <fstream>
#include <nlohmann/json.hpp>

using namespace sf;
using namespace std;

class AnimationCharacter: public Animation
{
    public:
        // processing when the character is hit
        void hitMode(Character*,float);

        // animation for IDLE
        void idleMode(Character*);

        // animation for walking
        void walkMode(Character*);

        // animation for attack
        void attackMode(Character*);

        // animation for spellcasting
        void spellCastMode(Character*);

        // animation for death
        void deathMode(Character*);

        // handling animation of the character
        void handleAnimation(Character*,float);

        //constructors
        AnimationCharacter(string);

        //destructors
        ~AnimationCharacter();

    private:
        // we specify the line we want to animate and then how many frames that line has
        int walkLeft,walkRight,walkUp,walkDown;
        int attackLeft,attackRight,attackUp,attackDown;
        int idleLeft,idleRight,idleUp,idleDown;
        int spellCastLeft,spellCastRight,spellCastUp,spellCastDown;
        int death;

        int custom; // custom animation in case the frame is higher than the default size of frame

        int hitCounter; // while it is different from 0, character gains immunity from being hit again
        int currentHitCounter;

        float isHitTime,isHitTimeReset; // time management for getting hit
};

#endif // ANIMATIONCHARACTER_H

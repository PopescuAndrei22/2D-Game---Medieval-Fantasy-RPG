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
    // animation for IDLE
    void idleMode();

    // animation for walking
    void walkMode();

    /*
    animation for attack
    it is custom because is not an ordinary animation,
    its dimension is higher and has to be customized for this texture
    however, i will design another class "attackMode" for other textures
    */
    void attackMode();

    // handling animation
    void handleAnimation(Character,Controls,float);

    // animation for spellcasting
    void spellCastMode();

    //
    void changeAnimation(int);

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

    // the direction the character is facing
    /*
    UP -> 1
    LEFT -> 2
    DOWN -> 3
    RIGHT -> 4
    */
    int direction;

    int custom; // custom animation because of the texture i am using
};

#endif // ANIMATIONCHARACTER_H

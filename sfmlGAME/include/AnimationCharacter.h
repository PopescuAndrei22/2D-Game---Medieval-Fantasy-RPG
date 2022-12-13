#ifndef ANIMATIONCHARACTER_H
#define ANIMATIONCHARACTER_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Animation.h"
#include "Controls.h"
#include <fstream>
#include <nlohmann/json.hpp>

using namespace sf;
using namespace std;

class AnimationCharacter: public Animation
{
public:
    // setting window size
    void setWindowSize(Vector2u);

    // animation for IDLE
    void idleMode();

    // animation for walking
    void walkMode(float);

    /*
    animation for attack
    it is custom because is not an ordinary animation,
    its dimension is higher and has to be customized for this texture
    however, i will design another class "attackMode" for other textures
    */
    void attackMode(float);

    // handling animation
    void handleAnimation(Controls, Keyboard::Key,float);

    // moving the character
    void moveCharacter(Vector2f,float);

    // animation for spellcasting
    void spellCastMode(float);

    //
    void changeAnimation(int);

    // check if the character exceeds the borders
    bool isInRange(Vector2f);

    //constructors
    AnimationCharacter(string, int,int);

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

    /*
    the time after which the characters moves
    timeMove -> accumulates the time
    timeResetMove -> when "timeMove" exceeds this value, reset "timeMove" then the character is moving
    */
    float timeMove, timeResetMove;

    int custom; // custom animation because of the texture i am using

    Vector2f playerPosition;

    // variable to get windowSize so we can check if the character exceeds the borders while moving
    Vector2u windowSize;
};

#endif // ANIMATIONCHARACTER_H

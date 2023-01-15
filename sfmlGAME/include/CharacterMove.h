#ifndef CHARACTERMOVE_H
#define CHARACTERMOVE_H
#include "Controls.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Character.h"
#include "Map.h"
#include <vector>

using namespace std;
using namespace sf;

class CharacterMove
{
public:
    // handling movement for the main character
    void handleMovement(Character*,float,Map*);

    // function that moves character to the new position if it is possible
    void moveCharacter(Vector2f,Character*,Map*);

    /* check if the character can be moved to the new position
    first argument is the new position
    the second argument is the character size for calculating an accurate collision
    the third argument is the map so that we get the collision array
    */
    bool isInRange(Vector2f,Character*,Map*);

    void increaseTime(float);

    void resetTime();


    // constructors
    CharacterMove();

    // destructors
    ~CharacterMove();

private:

    /*
    the time after which the characters moves
    timeMove -> accumulates the time
    timeMoveReset -> when "timeMove" exceeds this value, reset "timeMove" then the character is moving
    */
    float timeMove, timeMoveReset;
};

#endif // CHARACTERMOVE_H

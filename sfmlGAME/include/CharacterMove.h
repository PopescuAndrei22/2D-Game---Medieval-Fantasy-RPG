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
    void handleMovement(Controls,Character*,float);
    /* need another function like this that has as parameter the direction, needed for moving enemies, and probably for cutscenes*/

    // function that moves character to the new position if it is possible
    void moveCharacter(Vector2f,Character*);

    /* check if the new position the character is moving to is a collision
    first argument is the new position
    the second argument is the character size for calculating an accurate collision
    */
    bool isCollision(Vector2f, Vector2f);

    /* check if the character can be moved to the new position
    first argument is the new position
    the second argument is the character size for calculating an accurate collision
    */
    bool isInRange(Vector2f,Vector2f);

    void increaseTime(float);

    void resetTime();

    /*
    getting details about the current level such as the array of collisions and grid size
    */
    void updateLevelDetails(Map);

    // deleting the array of collisions
    void deleteArray();

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

    Vector2f mapSize;

    int gridSize;

    // l -> lines
    // c -> columns
    struct Pair
    {
        int l,c;
    }dimensions;

    int** collisionArray;
};

#endif // CHARACTERMOVE_H

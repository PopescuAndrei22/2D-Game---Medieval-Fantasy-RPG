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
    // 1 more function like this, but giving direct direction to it so i can use polymorphism and use the function for npcs or combat system
    void handleMovement(Controls,Character*,float);

    // to modify
    void moveCharacter(Vector2f,Character*);

    bool isCollision(Vector2f, Vector2f);

    bool isInRange(Vector2f,Vector2f);

    void increaseTime(float);

    void resetTime();

    void updateLevelDetails(Map);

    void deleteArray();

    CharacterMove();
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

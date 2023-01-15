#ifndef CHARACTER_H
#define CHARACTER_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using namespace sf;
using namespace std;

// things to add: energy

class Character
{
    public:
        //getters
        int getHealth() const;
        int getMana() const;
        int getSpeedMovement() const;
        int getSpeedAttack() const;
        int getDirection() const;
        bool getKnockback() const;
        bool getIsAttacking() const;
        bool getIsMoving() const;
        bool getIsSpellCasting() const;
        bool getIsIdle() const;
        bool getDidChangeDirection() const;
        bool getActionInProgress() const;
        bool getWalkIntoObstacle() const;
        Vector2f getCharacterPosition() const;
        Vector2f getCharacterSize() const;

        //setters
        void setHealth(int);
        void setMana(int);
        void setSpeedMovement(int);
        void setSpeedAttack(int);
        void setKnockback(bool);
        void setIsMoving(bool);
        void setIsAttacking(bool);
        void setIsIdle(bool);
        void setActionInProgress(bool);
        void setDidChangeDirection(bool);
        void setIsSpellCasting(bool);
        void setWalkIntoObstacle(bool);
        void setCharacterPosition(Vector2f);
        void setCharacterSize(Vector2f);
        void setDirection(int);

        //constructors
        Character(string);

        //destructors
        ~Character();

    private:

        int health; // health, initially it is 300
        int mana; // mana, initially it is 200
        int speedMovement; // movement speed
        int speedAttack; // attack speed
        bool knockback; // tells us if the character can be knocked back or not
        bool isAttacking; // tells us if the character is currently attacking
        bool isSpellCasting; // tells us if the character is currently spellCasting
        bool isMoving; // tells us if the character is moving
        bool isIdle; // if character is idle
        bool didChangeDirection; // if character changed his direction
        bool walkIntoObstacle; // tells us if the character tries to walk into an obstacle
        bool actionInProgress; // tells us if the character has an action in progress such as attacking or spellcasting
        Vector2f characterPosition; // getting the current position of the player
        Vector2f characterSize; // dimensions of the character

        // the direction the character is facing
        /*
        UP -> 1
        LEFT -> 2
        DOWN -> 3
        RIGHT -> 4
        */
        int direction;
};

#endif // CHARACTER_H

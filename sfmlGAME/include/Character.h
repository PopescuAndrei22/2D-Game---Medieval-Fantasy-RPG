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
        // revive the character with its stats
        virtual void revive();

        //getters
        int getHealth() const;
        int getCurrentHealth() const;
        int getMana() const;
        int getSpeedMovement() const;
        int getSpeedAttack() const;
        int getDirection() const;
        int getBaseDamage() const;
        int getEnemyDirection() const;
        bool getKnockback() const;
        bool getIsAttacking() const;
        bool getIsMoving() const;
        bool getIsSpellCasting() const;
        bool getIsIdle() const;
        bool getDidChangeDirection() const;
        bool getActionInProgress() const;
        bool getWalkIntoObstacle() const;
        bool getIsHit() const;
        bool getIsDamaging() const;
        bool getIsKnockbacked() const;
        bool getIsDead() const;
        Vector2f getCharacterPosition() const;
        Vector2f getCharacterSize() const;
        Vector2f getSpawnPoint() const;
        float getRadiusAttack() const;
        float getKnockbackDistance() const;

        //setters
        void setHealth(int);
        void setCurrentHealth(int);
        void setMana(int);
        void setSpeedMovement(int);
        void setSpeedAttack(int);
        void setBaseDamage(int);
        void setEnemyDirection(int);
        void setKnockback(bool);
        void setIsMoving(bool);
        void setIsAttacking(bool);
        void setIsIdle(bool);
        void setActionInProgress(bool);
        void setDidChangeDirection(bool);
        void setIsSpellCasting(bool);
        void setWalkIntoObstacle(bool);
        void setIsHit(bool);
        void setIsDamaging(bool);
        void setIsKnockbacked(bool);
        void setIsDead(bool);
        void setCharacterPosition(Vector2f);
        void setCharacterSize(Vector2f);
        void setSpawnPoint(Vector2f);
        void setDirection(int);
        void setRadiusAttack(float);
        void setKnockbackDistance(float);

        //constructors
        Character(string);

        //destructors
        ~Character();

    private:

        int health; // health, initially it is 300
        int currentHealth;
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
        bool isDamaging; // if the character does damage
        bool isHit; // if the character received damage
        bool isKnockbacked;
        bool isDead;
        bool actionInProgress; // tells us if the character has an action in progress such as attacking or spellcasting
        float radiusAttack;
        float knockbackDistance; // the distance the character is going to be pushed back after is being attacked
        Vector2f characterPosition; // getting the current position of the player
        Vector2f characterSize; // dimensions of the character
        Vector2f spawnPoint; // spawn point
        int baseDamage;
        int enemyDirection; // it helps us on calculating the knockbackdirection

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

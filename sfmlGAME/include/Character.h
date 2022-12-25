#ifndef CHARACTER_H
#define CHARACTER_H
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

// things i could add: energy, speed attack

class Character
{
    public:
        //getters
        int getHealth() const;
        int getMana() const;
        int getSpeedMovement() const;
        int getSpeedAttack() const;
        bool getKnockback() const;
        Vector2f getCharacterPosition() const;
        Vector2f getCharacterSize() const;

        //setters
        void setHealth(int);
        void setMana(int);
        void setSpeedMovement(int);
        void setSpeedAttack(int);
        void setKnockback(bool);
        void setCharacterPosition(Vector2f);
        void setCharacterSize(Vector2f);

        //constructors
        Character();

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

        Vector2f characterPosition; // getting the current position of the player
        Vector2f characterSize; // dimensions of the character
};

#endif // CHARACTER_H

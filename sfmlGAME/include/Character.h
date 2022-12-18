#ifndef CHARACTER_H
#define CHARACTER_H
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

// things i could add: energy

class Character
{
    public:
        //getters
        int getSpeed() const;
        int getHealth() const;
        int getMana() const;
        Vector2f getCharacterPosition() const;
        Vector2f getCharacterSize() const;

        //setters
        void setSpeed(int);
        void setHealth(int);
        void setMana(int);
        void setCharacterPosition(Vector2f);
        void setCharacterSize(Vector2f);

        //constructors
        Character();

        //destructors
        ~Character();

    private:
        int speed; // speed, measured in procents, initially it is 100%
        int health; // health, initially it is 300
        int mana; // mana, initially it is 200

        Vector2f characterPosition; // getting the current position of the player
        Vector2f characterSize; // dimensions of the character
};

#endif // CHARACTER_H

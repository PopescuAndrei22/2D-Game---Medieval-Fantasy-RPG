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

        //setters
        void setSpeed(int);
        void setHealth(int);
        void setMana(int);

        //constructors
        Character();

        //destructors
        ~Character();

    private:
        int speed; // speed, measured in procents, initially it is 5%
        int health; // health, initially it is 300
        int mana; // mana, initially it is 200
};

#endif // CHARACTER_H

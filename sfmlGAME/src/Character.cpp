#include "Character.h"

//getters
int Character::getSpeed() const
{
    return this->speed;
}

int Character::getHealth() const
{
    return this->health;
}

int Character::getMana() const
{
    return this->mana;
}

//setters
void Character::setSpeed(int speed)
{
    this->speed = speed;
}

void Character::setHealth(int health)
{
    this->health = health;
}

void Character::setMana(int mana)
{
    this->mana = mana;
}

//constructors
Character::Character()
{
    this->speed = 100;
    this->health = 300;
    this->mana = 200;
}

//destructors
Character::~Character()
{

}

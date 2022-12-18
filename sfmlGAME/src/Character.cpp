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

Vector2f Character::getCharacterPosition() const
{
    return this->characterPosition;
}

Vector2f Character::getCharacterSize() const
{
    return this->characterSize;
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

void Character::setCharacterPosition(Vector2f newPosition)
{
    this->characterPosition.x = newPosition.x;
    this->characterPosition.y = newPosition.y;
}

void Character::setCharacterSize(Vector2f characterSize)
{
    this->characterSize = characterSize;
}

//constructors
Character::Character()
{
    // i can get these values from json file

    this->speed = 100;
    this->health = 300;
    this->mana = 200;

    // starting positions
    Vector2f startPosition(Vector2f(0,0));
    this->setCharacterPosition(startPosition);
}

//destructors
Character::~Character()
{

}

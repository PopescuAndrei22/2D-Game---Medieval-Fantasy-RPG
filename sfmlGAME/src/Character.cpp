#include "Character.h"

//getters
int Character::getHealth() const
{
    return this->health;
}

int Character::getMana() const
{
    return this->mana;
}

int Character::getSpeedMovement() const
{
    return this->speedMovement;
}

int Character::getSpeedAttack() const
{
    return this->speedAttack;
}

bool Character::getKnockback() const
{
    return this->knockback;
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

void Character::setHealth(int health)
{
    this->health = health;
}

void Character::setMana(int mana)
{
    this->mana = mana;
}

void Character::setSpeedMovement(int speedMovement)
{
    this->speedMovement = speedMovement;
}

void Character::setSpeedAttack(int speedAttack)
{
    this->speedAttack = speedAttack;
}

void Character::setKnockback(bool knockback)
{
    this->knockback = knockback;
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

    this->setHealth(300);
    this->setMana(200);
    this->setSpeedMovement(100);
    this->setSpeedAttack(100);
    this->setKnockback(true);

    this->isAttacking=false;
    this->isSpellCasting=false;

    // starting positions
    Vector2f startPosition(Vector2f(0,800));
    this->setCharacterPosition(startPosition);
}

//destructors
Character::~Character()
{

}

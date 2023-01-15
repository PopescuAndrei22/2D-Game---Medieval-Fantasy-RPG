#include "Character.h"

//getters
int Character::getDirection() const
{
    return this->direction;
}

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

bool Character::getDidChangeDirection() const
{
    return this->didChangeDirection;
}

bool Character::getActionInProgress() const
{
    return this->actionInProgress;
}

bool Character::getIsIdle() const
{
    return this->isIdle;
}

bool Character::getKnockback() const
{
    return this->knockback;
}

bool Character::getIsMoving() const
{
    return this->isMoving;
}

bool Character::getWalkIntoObstacle() const
{
    return this->walkIntoObstacle;
}

bool Character::getIsAttacking() const
{
    return this->isAttacking;
}

bool Character::getIsSpellCasting() const
{
    return this->isSpellCasting;
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
void Character::setDirection(int direction)
{
    this->direction = direction;
}

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

void Character::setWalkIntoObstacle(bool walkIntoObstacle)
{
    this->walkIntoObstacle = walkIntoObstacle;
}

void Character::setKnockback(bool knockback)
{
    this->knockback = knockback;
}

void Character::setIsAttacking(bool isAttacking)
{
    this->isAttacking = isAttacking;
}

void Character::setDidChangeDirection(bool didChangeDirection)
{
    this->didChangeDirection = didChangeDirection;
}

void Character::setIsIdle(bool isIdle)
{
    this->isIdle = isIdle;
}

void Character::setIsMoving(bool isMoving)
{
    this->isMoving = isMoving;
}

void Character::setIsSpellCasting(bool isSpellCasting)
{
    this->isSpellCasting = isSpellCasting;
}

void Character::setActionInProgress(bool actionInProgress)
{
    this->actionInProgress = actionInProgress;
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
Character::Character(string fileName)
{
    // i can get these values from json file

    string pathValues = "values/characters/" + fileName + ".json";
    ifstream file(pathValues);
    nlohmann::json data = nlohmann::json::parse(file);

    float x = ((data["startPositionX"].is_null()==true)?0:(int)data["startPositionX"]);
    float y = ((data["startPositionY"].is_null()==true)?0:(int)data["startPositionY"]);
    this->setCharacterPosition(Vector2f(x,y));

    this->direction = 3; // by default the character is facing downwards
    this->setActionInProgress(false);

    this->setHealth(300);
    this->setMana(200);
    this->setSpeedMovement(100);
    this->setSpeedAttack(100);
    this->setKnockback(true);

    this->setIsSpellCasting(false);
    this->setIsMoving(false);
    this->setIsAttacking(false);
    this->setIsIdle(false);
    this->setDidChangeDirection(false);
    this->setWalkIntoObstacle(false);
}

//destructors
Character::~Character()
{

}

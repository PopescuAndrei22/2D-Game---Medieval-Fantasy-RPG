#include "CharacterMove.h"

float CharacterMove::getTimeMoveReset() const
{
    return this->timeMoveReset;
}

float CharacterMove::getDistance(Character *character) const
{
    float distance = 1; // default distance

    return (character->getSpeedMovement() / 100.0) * distance;
}

void CharacterMove::handleMovement(Character *character, float timer, Map *map)
{
    if(character->getIsDead() == true)
        return;

    Vector2f newPositionKnockback = character->getCharacterPosition();

    // can be altered by knockbackDistance (altered by items as well)
    if(character->getIsKnockbacked()==true)
        {
            /*
            UP -> 1
            LEFT -> 2
            DOWN -> 3
            RIGHT -> 4
            */

            // the knockback direction is the direction of the enemy's direction

            int enemyDirection = character->getEnemyDirection();
            float distance = character->getKnockbackDistance();

            if(enemyDirection == 1)
                {
                    newPositionKnockback.y-=distance;
                }
            if(enemyDirection == 2)
                {
                    newPositionKnockback.x-=distance;
                }
            if(enemyDirection == 3)
                {
                    newPositionKnockback.y+=distance;
                }
            if(enemyDirection == 4)
                {
                    newPositionKnockback.x+=distance;
                }

            // to make function to check the tiles between the current position and the new position to check if there are obstacles, otherwise is gonna be bugged (can jump over obstacles)
            if(this->isInRange(newPositionKnockback,character,map))
                character->setCharacterPosition(newPositionKnockback);

            character->setIsKnockbacked(false);
        }

    Vector2f newPosition = character->getCharacterPosition();

    if(character->getIsMoving()==true)
        {
            int direction = character->getDirection();

            if(direction == 1) // UP
                newPosition.y-=this->getDistance(character);
            else if(direction == 2) // LEFT
                newPosition.x-=this->getDistance(character);
            else if(direction == 3) // DOWN
                newPosition.y+=this->getDistance(character);
            else if(direction == 4) // RIGHT
                newPosition.x+=this->getDistance(character);

            this->increaseTime(timer);
            this->moveCharacter(newPosition,character,map);
        }
}

bool CharacterMove::isInRange(Vector2f newPosition, Character *character, Map *map)
{
    Vector2f characterSize = character->getCharacterSize();
    Vector2f mapSize = map->getMapSize();

    if(!(newPosition.x >=0 && newPosition.y >=0))
        return false;

    if(!(newPosition.x + characterSize.x <= mapSize.x))
        return false;

    if(!(newPosition.y + characterSize.y <= mapSize.y))
        return false;

    if(map->isCollision(newPosition,characterSize))
        return false;

    return true;
}

void CharacterMove::moveCharacter(Vector2f newPosition, Character *character, Map *map)
{
    if(this->timeMove >= this->getTimeMoveReset())
        {
            this->resetTime();

            if(this->isInRange(newPosition,character,map))
                {
                    character->setWalkIntoObstacle(false);
                    character->setCharacterPosition(newPosition);
                }
            else
                character->setWalkIntoObstacle(true);
        }
}

void CharacterMove::increaseTime(float timer)
{
    this->timeMove += timer;
}

void CharacterMove::resetTime()
{
    this->timeMove = 0.0f;
}

// constructors
CharacterMove::CharacterMove()
{
    this->timeMove = 0.0f;
    this->timeMoveReset = 0.001f;
}

// destructors
CharacterMove::~CharacterMove()
{

}

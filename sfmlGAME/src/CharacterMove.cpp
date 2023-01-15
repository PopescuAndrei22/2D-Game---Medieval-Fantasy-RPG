#include "CharacterMove.h"

void CharacterMove::handleMovement(Character *character, float timer, Map *map)
{
    Vector2f newPosition = character->getCharacterPosition();

    if(character->getIsMoving()==true)
        {
            int direction = character->getDirection();

            if(direction == 1) // UP
                newPosition.y--;
            else if(direction == 2) // LEFT
                newPosition.x--;
            else if(direction == 3) // DOWN
                newPosition.y++;
            else if(direction == 4) // RIGHT
                newPosition.x++;

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
    if(this->timeMove >= this->timeMoveReset)
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

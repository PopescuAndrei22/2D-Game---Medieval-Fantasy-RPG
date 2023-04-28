#include "CharacterMovement.h"

/* class methods */
sf::Vector2f CharacterMovement::getKnockbackPosition(Character &character, Map &currentMap)
{
    float receivedKnockbackDistance = character.getReceivedKnockbackDistance();

    sf::Vector2f newPosition = character.getCharacterPosition();

    // we are moving the character to the direction of direction the opponent was when he gave knockback damage to character

    std::string direction = character.getDirectionKnockback();

    if(direction == "left")
        newPosition.x -= receivedKnockbackDistance;
    else if(direction == "right")
        newPosition.x += receivedKnockbackDistance;
    else if(direction == "up")
        newPosition.y -= receivedKnockbackDistance;
    else if(direction == "down")
        newPosition.y += receivedKnockbackDistance;

    character.setIsKnockbacked(false);

    character.setReceivedKnockbackDistance(0.0f);

    character.setDirectionKnockback("");

    return newPosition;

}

void CharacterMovement::manageMovement(Character &character, float timer, Map &currentMap)
{
    sf::Vector2f newCharacterPosition = character.getCharacterPosition();

    character.setIsWalkingIntoObstacle(false);

    float distance = 1.0f * character.getSpeedMovement() / 100;

    if(character.getIsDashing() && character.getIsAbleToDash())
        {
            std::string direction = character.getDirection();

            float dashDistance = character.getLeapDistanceInDash();

            if(direction == "left")
                newCharacterPosition.x-=dashDistance;
            if(direction == "right")
                newCharacterPosition.x+=dashDistance;
            if(direction == "up")
                newCharacterPosition.y-=dashDistance;
            if(direction == "down")
                newCharacterPosition.y+=dashDistance;
        }

    else if(character.getIsKnockbacked())
        {
            newCharacterPosition = this->getKnockbackPosition(character,currentMap);
        }

    else if(character.getIsMoving() == true)
        {
            std::string direction = character.getDirection();

            if(direction == "left")
                newCharacterPosition.x-=distance;
            if(direction == "right")
                newCharacterPosition.x+=distance;
            if(direction == "up")
                newCharacterPosition.y-=distance;
            if(direction == "down")
                newCharacterPosition.y+=distance;
        }

    this->timeMove += timer;

    if(this->timeMove > this->timeMoveReset)
        {
            this->timeMove = 0.0f;

            if(this->isInRange(character,currentMap,newCharacterPosition) == true)
                {
                    character.setCharacterPosition(newCharacterPosition);
                }
            else
                {
                    character.setIsWalkingIntoObstacle(true);
                }
        }
}

bool CharacterMovement::isInRange(Character &character, Map &currentMap, sf::Vector2f newPosition)
{
    sf::Vector2f characterSize = character.getCharacterSize();
    sf::Vector2f mapSize = currentMap.getMapSize();

    if(!(newPosition.x >=0 && newPosition.y >=0))
        return false;

    if(!(newPosition.x + characterSize.x <= mapSize.x))
        return false;

    if(!(newPosition.y + characterSize.y <= mapSize.y))
        return false;

    if(currentMap.isCollision(newPosition,characterSize))
        return false;

    return true;
}

/* constructors */
CharacterMovement::CharacterMovement()
{
    this->timeMove = 0.0f;
    this->timeMoveReset = 0.001f;
}

/* destructors */
CharacterMovement::~CharacterMovement()
{

}

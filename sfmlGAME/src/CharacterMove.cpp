#include "CharacterMove.h"

void CharacterMove::handleMovement(Controls controls, Character *character, float timer)
{
    Vector2f newPosition = character->getCharacterPosition();

    Keyboard::Key keyCode = controls.checkIfKeyIsPressed();

    bool isMoving = false;

    if(keyCode == controls.getMoveLeft())
        {
            isMoving = true;
            newPosition.x--;
        }
    else if(keyCode == controls.getMoveRight())
        {
            isMoving = true;
            newPosition.x++;
        }
    else if(keyCode == controls.getMoveUp())
        {
            isMoving = true;
            newPosition.y--;
        }
    else if(keyCode == controls.getMoveDown())
        {
            isMoving = true;
            newPosition.y++;
        }

    if(isMoving)
        {
            this->increaseTime(timer);
            this->moveCharacter(newPosition,character);
        }
}

bool CharacterMove::isCollision(Vector2f position, Vector2f characterSize)
{
    int xLeft = position.x / this->gridSize;
    int xRight = (position.x + characterSize.x) / this->gridSize;

    int yUp = position.y / this->gridSize;
    int yDown = (position.y + characterSize.y) / this->gridSize;

    // data validation, have to improve it and add more like ydown 0 if below 0
    if(yUp < 0)
        yUp = 0;
    if(yDown >= this->dimensions.l)
        yDown = this->dimensions.l - 1;
    if(xLeft < 0)
        xLeft = 0;
    if(xRight >= this->dimensions.c)
        xRight = this->dimensions.c - 1;

    /*
    this works well now but is going to be bad for very high textures ( ex huge bosses )
    */
    for(int i=yUp; i<yDown; i++)
        {
            for(int j=xLeft; j<xRight; j++)
                {
                    if(this->collisionArray[i][j] == 1)
                        return true;
                }
        }

    return false;
}

bool CharacterMove::isInRange(Vector2f position, Vector2f characterSize)
{
    if(!(position.x >=0 && position.y >=0))
        return false;

    if(!(position.x + characterSize.x <= this->mapSize.x))
        return false;

    if(!(position.y + characterSize.y <= this->mapSize.y))
        return false;

    if(this->isCollision(position,characterSize))
        return false;

    return true;
}

void CharacterMove::moveCharacter(Vector2f newPosition, Character *character)
{
    if(this->timeMove >= this->timeMoveReset)
        {
            this->resetTime();

            if(this->isInRange(newPosition,character->getCharacterSize()))
                {
                    character->setCharacterPosition(newPosition);
                }
        }
}

void CharacterMove::updateLevelDetails(Map map)
{
    this->mapSize = map.getMapSize();
    this->gridSize = map.getGridSize();

    dimensions.c = this->mapSize.x / this->gridSize; // number of grids horizontally
    dimensions.l = this->mapSize.y / this->gridSize; // number of grids vertically

    // IMPORTANT!!!!, must delete after updating this function again
    this->collisionArray = new int*[dimensions.l];

    vector <int> arr = map.getCollisionArray();

    for(int i=0; i<dimensions.l; i++)
        {
            this->collisionArray[i] = new int[dimensions.c];

            for(int j=0; j<dimensions.c; j++)
                {
                    this->collisionArray[i][j] = arr[i*dimensions.c+j];
                }
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

void CharacterMove::deleteArray()
{
    for(int i = 0; i < dimensions.l; ++i)
        delete[] this->collisionArray[i];

    delete[] this->collisionArray;
}

CharacterMove::CharacterMove()
{
    this->timeMove = 0.0f;
    this->timeMoveReset = 0.005f;
}

CharacterMove::~CharacterMove()
{
    this->deleteArray();
}

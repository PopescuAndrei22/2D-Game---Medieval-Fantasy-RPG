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

    // data validation for xLeft, xRight, yUp, yDown, what if gridSize is 0 or the values exceeds the map, or values are below 0

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

bool CharacterMove::isInRange(Vector2f newPosition, Vector2f characterSize)
{
    if(!(newPosition.x >=0 && newPosition.y >=0))
        return false;

    if(!(newPosition.x + characterSize.x <= this->mapSize.x))
        return false;

    if(!(newPosition.y + characterSize.y <= this->mapSize.y))
        return false;

    if(this->isCollision(newPosition,characterSize))
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
    this->deleteArray();

    this->mapSize = map.getMapSize();
    this->gridSize = map.getGridSize();

    if(this->gridSize != 0)
        {
            dimensions.c = this->mapSize.x / this->gridSize; // number of grids horizontally
            dimensions.l = this->mapSize.y / this->gridSize; // number of grids vertically
        }

    if(dimensions.l > 0)
        this->collisionArray = new int*[dimensions.l];

    vector <int> arr = map.getCollisionArray();

    for(int i=0; i<dimensions.l; i++)
        {
            if(dimensions.c > 0)
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
        {
            if(dimensions.c > 0)
                delete[] this->collisionArray[i];
        }

    if(dimensions.l > 0)
        delete[] this->collisionArray;
}

// constructors
CharacterMove::CharacterMove()
{
    this->timeMove = 0.0f;
    this->timeMoveReset = 0.005f;

    this->dimensions.l = this->dimensions.c = 0;
}

// destructors
CharacterMove::~CharacterMove()
{
    this->deleteArray();
}

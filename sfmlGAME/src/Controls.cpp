#include "Controls.h"

// getters
int Controls::getMoveLeft() const
{
    return this->moveLeft;
}

int Controls::getMoveRight() const
{
    return this->moveRight;
}

int Controls::getMoveUp() const
{
    return this->moveUp;
}

int Controls::getMoveDown() const
{
    return this->moveDown;
}

// setters
void Controls::setMoveLeft(int newBind)
{
    this->moveLeft = newBind;
}

void Controls::setMoveRight(int newBind)
{
    this->moveRight = newBind;
}

void Controls::setMoveUp(int newBind)
{
    this->moveUp = newBind;
}

void Controls::setMoveDown(int newBind)
{
    this->moveDown = newBind;
}

// constructors
Controls::Controls()
{
    // initial binds, can be modified later from options -> key bindings
    this->moveLeft=71;
    this->moveRight=72;
    this->moveUp=73;
    this->moveDown=74;
}

// destructors
Controls::~Controls()
{

}

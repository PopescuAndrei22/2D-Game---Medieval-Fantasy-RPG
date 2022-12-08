#include "Controls.h"

//
Keyboard::Key Controls::checkIfKeyIsPressed()
{
    // perhaps modify this code later?
    if(Keyboard::isKeyPressed(this->moveUp))
        return this->moveUp;
    if(Keyboard::isKeyPressed(this->moveDown))
        return this->moveDown;
    if(Keyboard::isKeyPressed(this->moveLeft))
        return this->moveLeft;
    if(Keyboard::isKeyPressed(this->moveRight))
        return this->moveRight;

    return Keyboard::P; // must modify here to set something else as default
}

// getters
Keyboard::Key Controls::getMoveLeft() const
{
    return this->moveLeft;
}

Keyboard::Key Controls::getMoveRight() const
{
    return this->moveRight;
}

Keyboard::Key Controls::getMoveUp() const
{
    return this->moveUp;
}

Keyboard::Key Controls::getMoveDown() const
{
    return this->moveDown;
}

// setters
void Controls::setMoveLeft(Keyboard::Key newBind)
{
    this->moveLeft = newBind;
}

void Controls::setMoveRight(Keyboard::Key newBind)
{
    this->moveRight = newBind;
}

void Controls::setMoveUp(Keyboard::Key newBind)
{
    this->moveUp = newBind;
}

void Controls::setMoveDown(Keyboard::Key newBind)
{
    this->moveDown = newBind;
}

// constructors
Controls::Controls()
{
    // initial binds, can be modified later from options -> key bindings
    this->moveLeft=Keyboard::Left;
    this->moveRight=Keyboard::Right;
    this->moveUp=Keyboard::Up;
    this->moveDown=Keyboard::Down;
}

// destructors
Controls::~Controls()
{

}

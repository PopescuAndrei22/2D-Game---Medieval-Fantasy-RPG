#include "Controls.h"

// checking if any of the controls was used
Keyboard::Key Controls::checkIfKeyIsPressed()
{
    if(Keyboard::isKeyPressed(this->moveUp))
        return this->moveUp;
    if(Keyboard::isKeyPressed(this->moveDown))
        return this->moveDown;
    if(Keyboard::isKeyPressed(this->moveLeft))
        return this->moveLeft;
    if(Keyboard::isKeyPressed(this->moveRight))
        return this->moveRight;
    if(Keyboard::isKeyPressed(this->attack))
        return this->attack;
    if(Keyboard::isKeyPressed(this->spellCast))
        return this->spellCast;

    return Keyboard::Unknown;
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

Keyboard::Key Controls::getAttack() const
{
    return this->attack;
}

Keyboard::Key Controls::getSpellCast() const
{
    return this->spellCast;
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

void Controls::setAttack(Keyboard::Key newBind)
{
    this->attack = newBind;
}

void Controls::setSpellCast(Keyboard::Key newBind)
{
    this->spellCast = newBind;
}

// constructors
Controls::Controls()
{
    // initial binds, can be modified later from options -> key bindings
    this->moveLeft=Keyboard::Left;
    this->moveRight=Keyboard::Right;
    this->moveUp=Keyboard::Up;
    this->moveDown=Keyboard::Down;

    this->attack = Keyboard::Space;

    this->spellCast = Keyboard::X;
}

// destructors
Controls::~Controls()
{

}

#include "Controls.h"

/* getters */
sf::Keyboard::Key Controls::getMoveLeft() const
{
    return this->moveLeft;
}

sf::Keyboard::Key Controls::getMoveRight() const
{
    return this->moveRight;
}

sf::Keyboard::Key Controls::getMoveUp() const
{
    return this->moveUp;
}

sf::Keyboard::Key Controls::getMoveDown() const
{
    return this->moveDown;
}

sf::Keyboard::Key Controls::getAttack() const
{
    return this->attack;
}

sf::Keyboard::Key Controls::getSpellCast() const
{
    return this->spellCast;
}

sf::Keyboard::Key Controls::getDash() const
{
    return this->dash;
}

/* setters */
void Controls::setMoveLeft(sf::Keyboard::Key newBind)
{
    this->moveLeft = newBind;
}

void Controls::setMoveRight(sf::Keyboard::Key newBind)
{
    this->moveRight = newBind;
}

void Controls::setMoveUp(sf::Keyboard::Key newBind)
{
    this->moveUp = newBind;
}

void Controls::setMoveDown(sf::Keyboard::Key newBind)
{
    this->moveDown = newBind;
}

void Controls::setAttack(sf::Keyboard::Key newBind)
{
    this->attack = newBind;
}

void Controls::setSpellCast(sf::Keyboard::Key newBind)
{
    this->spellCast = newBind;
}

void Controls::setDash(sf::Keyboard::Key newBind)
{
    this->dash = newBind;
}

/* class methods */

// checking if any of the controls was used
sf::Keyboard::Key Controls::checkIfKeyIsPressed()
{
    if(sf::Keyboard::isKeyPressed(this->moveUp))
        return this->moveUp;
    if(sf::Keyboard::isKeyPressed(this->moveDown))
        return this->moveDown;
    if(sf::Keyboard::isKeyPressed(this->moveLeft))
        return this->moveLeft;
    if(sf::Keyboard::isKeyPressed(this->moveRight))
        return this->moveRight;
    if(sf::Keyboard::isKeyPressed(this->attack))
        return this->attack;
    if(sf::Keyboard::isKeyPressed(this->spellCast))
        return this->spellCast;
    if(sf::Keyboard::isKeyPressed(this->dash))
        return this->dash;

    return sf::Keyboard::Unknown;
}

/* constructors */
Controls::Controls()
{
    // initial binds, can be modified later from options -> key bindings
    this->moveLeft=sf::Keyboard::Left;
    this->moveRight=sf::Keyboard::Right;
    this->moveUp=sf::Keyboard::Up;
    this->moveDown=sf::Keyboard::Down;

    this->attack = sf::Keyboard::Space;

    this->spellCast = sf::Keyboard::X;

    this->dash = sf::Keyboard::C;
}

/* destructors */
Controls::~Controls()
{

}

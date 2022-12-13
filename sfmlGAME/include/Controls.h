#ifndef CONTROLS_H
#define CONTROLS_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Controls.h"

using namespace sf;
using namespace std;

class Controls
{
public:
    // checking if a key used for controls was pressed
    Keyboard::Key checkIfKeyIsPressed();

    //getters
    Keyboard::Key getMoveLeft() const;
    Keyboard::Key getMoveRight() const;
    Keyboard::Key getMoveUp() const;
    Keyboard::Key getMoveDown() const;

    Keyboard::Key getAttack() const;

    //setters
    void setMoveLeft(Keyboard::Key);
    void setMoveRight(Keyboard::Key);
    void setMoveUp(Keyboard::Key);
    void setMoveDown(Keyboard::Key);

    void setAttack(Keyboard::Key);

    //constructors
    Controls();

    //destructors
    ~Controls();

private:
    Keyboard::Key moveUp,moveDown,moveLeft,moveRight; // controls for moving the character
    Keyboard::Key attack; // control for basic attack
};

#endif // CONTROLS_H

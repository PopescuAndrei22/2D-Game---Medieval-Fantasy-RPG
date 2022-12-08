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
    //getters
    int getMoveLeft() const;
    int getMoveRight() const;;
    int getMoveUp() const;;
    int getMoveDown() const;;

    //setters
    void setMoveLeft(int);
    void setMoveRight(int);
    void setMoveUp(int);
    void setMoveDown(int);

    //constructors
    Controls();

    //destructors
    ~Controls();

private:
    int moveUp,moveDown,moveLeft,moveRight; // controls for moving the character
};

#endif // CONTROLS_H

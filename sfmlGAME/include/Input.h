#ifndef INPUT_H
#define INPUT_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Animation.h"

class Input
{
public:
    void movementInput(int, Animation&);
    //void movement(int, Animation&);

    Input();
    ~Input();

private:
};

#endif // INPUT_H

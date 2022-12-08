#ifndef ANIMATION_H
#define ANIMATION_H
#include <iostream>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include "Controls.h"

using namespace sf;
using namespace std;

class Animation
{
private:
    Texture texture; // the texture
    Sprite sprite; // the sprite
    Vector2f frameSize; // size of a frame
    int direction; // the direction of the character
    float timeFrame,timeResetFrame; // handling time between animations
    // time -> the the time that has accumulated so far
    // timeReset -> when the variable "time" value exceeds this value, we change the animation

    float timeMove,timeMoveReset; // handling the move of the character

    struct Pair
    {
        int x,y;
    }currentFrame; // this helps us knowing which frame we are using at the current time

public:
    //getters
    Sprite getSprite() const; // getting the sprite

    //setters
    void setFrame(int, int); // changing the frame, parameters: column-row
    void setDirection(int); // changing the direction of the character

    void handleAnimation(float); // increase time and change frame to create an animation
    void moveCharacter(Controls, Keyboard::Key, int, float);

    //constructors
    Animation(string,int,int); // constructor, receiving as arguments the name of the texture and the number of frames horizontally, respectively vertically

    //destructors
    ~Animation();
};

#endif // ANIMATION_H

#ifndef ANIMATION_H
#define ANIMATION_H
#include <iostream>
#include <algorithm>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Animation
{
private:
    Sprite sprite;
    Vector2f frameSize; // size of a frame
    float time,timeReset; // handling time between animations

    struct Pair
    {
        int x,y;
    }currentFrame;

public:
    Sprite getSprite();
    Vector2f getFrameSize();

    void increaseTimer(float);
    void setFrame(int, int);
    void handleAnimation(float);

    Animation(Texture,int,int);
    ~Animation();
};

#endif // ANIMATION_H

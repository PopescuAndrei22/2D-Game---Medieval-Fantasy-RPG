#ifndef ANIMATION1_H
#define ANIMATION1_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>

using namespace sf;
using namespace std;

class Animation
{
public:
    //getters
    Sprite getSprite() const;

    Vector2f getFrameSize() const;

    //setters
    /*
    this function has 2 optional parameters, multipliers of the actual size of the frame
    to make animations for attack possible
    is customized just for the types of textures i have for my characters
    */
    void setFrame(int,int,int=1,int=1);

    // constructors

    /* constructor, receiving as arguments the path to the texture and
    a path to a file that says how many frames each line has
    and the number of frames horizontally, respectively vertically */
    Animation(string);

    // destructors
    ~Animation();

protected:

    Vector2f getSpriteLocation() const;
    void setSpriteLocation(float, float);

    void increaseTime(float);

    void resetTime();

    void renderAnimation(bool);

    struct Pair
    {
        int x,y;
    } currentFrame; // this helps us knowing which frame we are using at the current time

    vector <int> numberOfFrames; // to see how many frames are on each line

private:
    Texture texture;
    Sprite sprite;

    Vector2f frameSize; // size of a frame

    float timeFrame,timeResetFrame; // handling time between animations
    // time -> the the time that has accumulated so far
    // timeReset -> when the variable "time" value exceeds this value, we change the animation and reset "time" value
};

#endif // ANIMATION1_H

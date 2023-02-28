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
    pair<int,int> getCurrentFrame() const;

    //setters
    /*
    this function has 2 optional parameters, multipliers of the actual size of the frame
    to make animations for attack possible
    is customized just for the types of textures that i am using for my characters
    */
    void setFrame(int,int,int=1,int=1);
    void setScale(float, float);

    // constructors

    /* constructor, receiving the name of the file that we are going to animate */
    Animation(string);

    // destructors
    ~Animation();

protected:
    // getters
    Vector2f getSpriteLocation() const;
    float getTimeFrame() const;
    float getTimeResetFrame() const;

    // setters
    void setSpriteLocation(float, float);
    void setSpriteColor(Color);

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

#include "Animation.h"

using namespace sf;
using namespace std;

// getters
Sprite Animation::getSprite()
{
    return this->sprite;
}

// setters
void Animation::setFrame(int column, int row)
{
    this->sprite.setTextureRect(IntRect(frameSize.x*(column-1),this->frameSize.y*(row-1),this->frameSize.x,this->frameSize.y));
}

// other functions
void Animation::increaseTimer(float time)
{
    this->time+=time;
}

void Animation::handleAnimation(float time)
{
    this->increaseTimer(time);

    if(this->time >= this->timeReset)
        {
            this->time = 0.0;
        }
}

// constructors and destructors
Animation::Animation(Texture texture, int x, int y)
{
    Vector2u textureSize = texture.getSize(); // getting texture's sizes

    this->sprite.setTexture(texture);

    this->frameSize.x = textureSize.x / x;
    this->frameSize.y = textureSize.y / y;

    this->time = 0.0;

    this->timeReset = 0.15f; // animation changing every x seconds

    this->currentFrame.x = 1;
    this->currentFrame.y = 11;

    this->setFrame(this->currentFrame.x,this->currentFrame.y);
}

Animation::~Animation()
{

}

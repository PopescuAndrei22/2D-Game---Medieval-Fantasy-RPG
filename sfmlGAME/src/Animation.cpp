#include "Animation.h"

/* getters */
sf::IntRect Animation::getFrame()
{
    return this->frames[this->currentFrame].rect;
}

unsigned int Animation::getFrameIndex() const
{
    return this->currentFrame;
}

unsigned int Animation::getSize() const
{
    return this->frames.size();
}

bool Animation::getIsFinished() const
{
    return this->isFinished;
}

/* setters */
void Animation::setIsLooped(bool isLooped)
{
    this->isLooped = isLooped;
}

/* class methods */

// adding frames to the vector
void Animation::addFrame(sf::IntRect rect, float duration)
{
    this->frames.push_back({ rect, duration });
}

void Animation::play()
{
    this->isPlaying = true;
}

void Animation::pause()
{
    this->isPlaying = false;
}

void Animation::stop()
{
    this->isPlaying = false;
    this->isLooped = true;
    this->isFinished = false;
    this->currentFrame = 0;
    this->elapsedTime = 0.0f;
}

void Animation::update(float timer)
{
    if(this->isPlaying == false || this->isFinished == true)
        return;

    this->elapsedTime += timer;

    float totalDuration = 0.0f;
    for(unsigned int i=0; i<this->frames.size(); i++)
        {
            totalDuration += this->frames[i].duration;
            if(this->elapsedTime < totalDuration)
                {
                    this->currentFrame = i;
                    break;
                }
        }

    // loop the animation
    if(this->elapsedTime > totalDuration)
        {
            if(this->isLooped == true)
                {
                    this->currentFrame = 0;
                    this->elapsedTime = 0.0f;
                }
            else
                {
                    this->isFinished = true;
                }
        }
}

/* constructors */
Animation::Animation()
{
    this->currentFrame = 0;

    this->elapsedTime = 0.0f;

    this->isPlaying = true;

    this->isLooped = true;

    this->isFinished = false;
}

/* destructors */
Animation::~Animation()
{

}

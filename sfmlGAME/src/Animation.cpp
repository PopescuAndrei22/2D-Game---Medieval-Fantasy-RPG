#include "Animation.h"

using namespace sf;
using namespace std;

// getters
Sprite Animation::getSprite() const
{
    return this->sprite;
}

// setters
void Animation::setFrame(int column, int row)
{
    this->sprite.setTextureRect(IntRect(frameSize.x*(column-1),this->frameSize.y*(row-1),this->frameSize.x,this->frameSize.y));
}

void Animation::setDirection(int direction)
{
    this->direction = direction;
}

// manipulating the frames
void Animation::handleAnimation(float time)
{
    // i have to modify this code

    if(this->direction == 0)
        this->currentFrame.x = 1;

    if(this->currentFrame.y != this->direction+8 && this->direction!=0)
        {
            this->currentFrame.y = this->direction+8;
            this->currentFrame.x = 1;
        }

    if(this->direction!=0)
        this->timeFrame+=time;

    if(this->timeFrame >= this->timeResetFrame)
        {
            this->timeFrame = 0.0;

            this->currentFrame.x++;
            if(this->currentFrame.x > 9)
                this->currentFrame.x = 2;
        }

    this->setFrame(this->currentFrame.x,this->currentFrame.y);
}

// moving the character
void Animation::moveCharacter(Controls controls, Keyboard::Key keyCode, int speed, float timer)
{
    float distance = (float)min(this->frameSize.x,this->frameSize.y) * ((float)speed/100); // how much the character has moved, value calculated as minimum between horizontally and vertically size of the frame

    Vector2f spriteLocation = this->sprite.getPosition(); // getting the current position of the sprite

    // declaring x and y for an easier notation to get coordinates of current sprite's position
    int x = spriteLocation.x;
    int y = spriteLocation.y;

    this-> direction = 0; // the direction where the character goes
    /*
    UP -> 1
    LEFT -> 2
    DOWN -> 3
    RIGHT -> 4
    */

    float newX=x,newY=y; // the new position of the sprite

    if(keyCode == controls.getMoveLeft())
        {
            newX-=distance;
            this->direction = 2;
        }

    if(keyCode == controls.getMoveRight())
        {
            newX+=distance;
            this->direction = 4;
        }
    if(keyCode == controls.getMoveUp())
        {

            newY-=distance;
            this->direction = 1;
        }
    if(keyCode == controls.getMoveDown())
        {
            newY+=distance;
            this->direction = 3;
        }

    if(this->direction == 0)
        {
            this->timeMove=0.0f;
        }
    else
        {
            this->timeMove+=timer;

            if(this->timeMove >= this->timeMoveReset)
                {
                    this->timeMove = 0.0f;

                    this->sprite.setPosition(newX,newY);
                }
        }
}

// constructors
Animation::Animation(string fileName, int x, int y)
{
    this->texture.loadFromFile(fileName); // getting the texture

    Vector2u textureSize = this->texture.getSize(); // getting texture's sizes

    this->sprite.setTexture(this->texture); // setting the sprite

    // getting the size of a frame
    this->frameSize.x = textureSize.x / x;
    this->frameSize.y = textureSize.y / y;

    // initializing the time
    this->timeFrame = 0.0f;

    // the time after which the animation changes
    this->timeResetFrame = 0.06f;

    // initializing the current frame, by default is on walking mode facing downwards
    this->currentFrame.x = 1;
    this->currentFrame.y = 11;
    this->setFrame(this->currentFrame.x,this->currentFrame.y);

    this->direction = 0;

    this->timeMove = 0.0f;
    this->timeMoveReset = 0.01f;
}

//destructors
Animation::~Animation()
{

}

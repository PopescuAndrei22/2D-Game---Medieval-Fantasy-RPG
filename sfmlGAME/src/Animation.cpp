#include "Animation.h"

//getters
Sprite Animation::getSprite() const
{
    return this->sprite;
}

float Animation::getTimeFrame() const
{
    return this->timeFrame;
}

float Animation::getTimeResetFrame() const
{
    return this->timeResetFrame;
}

Vector2f Animation::getSpriteLocation() const
{
    return this->sprite.getPosition();
}

Vector2f Animation::getFrameSize() const
{
    return this->frameSize;
}

// setters
void Animation::setFrame(int column, int row, int customX, int customY)
{
    // for easier notation
    int x = this->frameSize.x;
    int y = this->frameSize.y;

    this->sprite.setTextureRect(IntRect(x*(column-1),y*(row-1),x,y));

    if(customX==1 && customY==1)
        return;

    // custom function
    this->sprite.setTextureRect(IntRect(customX*x*(column-1),y*(row-1),x*customX,y*customY)); // customized attack for a specific texture
}

void Animation::setSpriteLocation(float x, float y)
{
    this->sprite.setPosition(x,y);
}

void Animation::increaseTime(float timer)
{
    this->timeFrame += timer;
}

void Animation::resetTime()
{
    this->timeFrame = 0.0f;
}

void Animation::renderAnimation(bool ok)
{
    /*
    for "ok" values:
    false -> continue animation
    true -> reset animation
    */

    if(ok == true)
        {
            this->resetTime();
            this->currentFrame.x=1;
        }
    else
        {
            if(this->timeFrame > this->timeResetFrame)
                {
                    this->resetTime();
                    this->currentFrame.x++;

                    if(this->currentFrame.x > this->numberOfFrames[this->currentFrame.y-1])
                        this->currentFrame.x=1;
                }
        }
}


// constructors
Animation::Animation(string fileName)
{
    // it could contain paths to make animated background as well, not only characters, i will modify it

    string pathValues = "values/characters/" + fileName + ".json";
    ifstream file(pathValues);
    nlohmann::json data = nlohmann::json::parse(file);

    int x = (data["numberOfFramesX"].is_null()?0:(int)data["numberOfFramesX"]);
    int y = (data["numberOfFramesY"].is_null()?0:(int)data["numberOfFramesY"]);

    string pathTexture = "sprites/characters/" + fileName + ".png";

    this->texture.loadFromFile(pathTexture); // getting the texture

    Vector2u textureSize = this->texture.getSize(); // getting texture's sizes

    this->sprite.setTexture(this->texture); // setting the sprite

    // getting the size of a frame
    this->frameSize.x = textureSize.x / x;
    this->frameSize.y = textureSize.y / y;

    // initializing the time
    this->timeFrame = 0.0f;

    // the time after which the animation changes
    this->timeResetFrame = 0.06f;

    // specifying the starting column and row for an animation, by default it is 1-1
    this->currentFrame.x = 1;
    this->currentFrame.y = 1;

    if(!data["numberOfFramesArray"].is_null())
        {
            for(unsigned i=0; i<data["numberOfFramesArray"].size(); i++)
                this->numberOfFrames.push_back(data["numberOfFramesArray"][i]);
        }

    if(this->numberOfFrames.size()!=y)
        cout<<"The number of lines read from the file "<<pathValues<<" is wrong."<<'\n';

    file.close();
}

// destructors
Animation::~Animation()
{
    this->numberOfFrames.clear();
}

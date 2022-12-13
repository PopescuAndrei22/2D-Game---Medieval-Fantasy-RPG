#include "Animation.h"

//getters
Sprite Animation::getSprite() const
{
    return this->sprite;
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

    if(customX==1)
        this->sprite.setTextureRect(IntRect(x*(column-1),y*(row-1),x,y));
    else
        this->sprite.setTextureRect(IntRect(customX*x*(column-1),y*(row-1),x*customX,y*customY)); // customized attack for a specific texture
}

void Animation::setSpriteLocation(float x, float y)
{
    this->sprite.setPosition(x,y);
}

//constructors
Animation::Animation(string fileName, int x, int y)
{
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
    this->timeResetFrame = 0.1f;

    // specifying the starting column and row for an animation, by default it is 1-1
    this->currentFrame.x = 1;
    this->currentFrame.y = 1;

    string pathValues = "values/characters/" + fileName + ".json";

    // getting the number of frames for each line from a file
    ifstream file(pathValues);

    nlohmann::json data = nlohmann::json::parse(file);

    if(!data["numberOfFrames"].is_null())
        {
            for(unsigned i=0; i<data["numberOfFrames"].size(); i++)
                this->numberOfFrames.push_back(data["numberOfFrames"][i]);
        }

    if(this->numberOfFrames.size()!=y)
        cout<<"The number of lines read from the file "<<pathValues<<" is wrong."<<'\n';

    file.close();

    /*
    ifstream file("values/numberOfFrames/hero.txt");

    int nr;

    while(file >> nr)
    {
        this->numberOfFrames.push_back(nr);
    }
    */
}

//destructors
Animation::~Animation()
{
    this->numberOfFrames.clear();
}

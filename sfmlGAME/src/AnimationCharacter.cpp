#include "AnimationCharacter.h"

void AnimationCharacter::setWindowSize(Vector2u newWindowSize)
{
    this->windowSize = newWindowSize;
}

bool AnimationCharacter::isInRange(Vector2f position)
{
    if(!(position.x >=0 && position.y >=0))
        return false;

    if(!(position.x + this->getFrameSize().x <= this->windowSize.x))
        return false;

    if(!(position.y + this->getFrameSize().y <= this->windowSize.y))
        return false;

    return true;
}

// moving the character
void AnimationCharacter::moveCharacter(Vector2f newPosition, float timer)
{
    this->timeMove += timer;

    if(this->timeMove >= this->timeResetMove)
        {
            this->timeMove = 0;

            if(this->isInRange(newPosition))
                {
                    this->setSpriteLocation(newPosition.x,newPosition.y);
                    this->playerPosition = newPosition;
                }
        }
}

// animation for spellcasting
void AnimationCharacter::spellCastMode(float timer)
{

}

// animation for IDLE mode
void AnimationCharacter::idleMode()
{
    /*
    This texture actually doesn't have an animation for idle, so
    i just selected the first frame from walking mode when the
    character is on idle mode
    */

    this->timeFrame = 0;

    this->currentFrame.x = 1;
    this->currentFrame.y = 1;

    if(this->direction==1)
        {
            this->currentFrame.y = walkUp;
        }
    else if(this->direction==2)
        {
            this->currentFrame.y = walkLeft;
        }
    else if(this->direction==3)
        {
            this->currentFrame.y = walkDown;
        }
    else if(this->direction==4)
        {
            this->currentFrame.y = walkRight;
        }
}

void AnimationCharacter::walkMode(float timer)
{
    int ok = 1;

    if(this->direction==1)
        {
            ok = this->currentFrame.y == walkUp;
            this->currentFrame.y = walkUp;
        }
    else if(this->direction==2)
        {
            ok = this->currentFrame.y == walkLeft;
            this->currentFrame.y = walkLeft;
        }
    else if(this->direction==3)
        {
            ok = this->currentFrame.y == walkDown;
            this->currentFrame.y = walkDown;
        }
    else if(this->direction==4)
        {
            ok = this->currentFrame.y == walkRight;
            this->currentFrame.y = walkRight;
        }

    this->changeAnimation(ok);
}

void AnimationCharacter::attackMode(float timer)
{
    int ok = 1;

    if(this->direction==1)
        {
            ok = this->currentFrame.y == attackUp;
            this->currentFrame.y = attackUp;
        }
    else if(this->direction==2)
        {
            ok = this->currentFrame.y == attackLeft;
            this->currentFrame.y = attackLeft;
        }
    else if(this->direction==3)
        {
            ok = this->currentFrame.y == attackDown;
            this->currentFrame.y = attackDown;
        }
    else if(this->direction==4)
        {
            ok = this->currentFrame.y == attackRight;
            this->currentFrame.y = attackRight;
        }

    this->changeAnimation(ok);
}

void AnimationCharacter::changeAnimation(int ok)
{
    /*
    for "ok" values:
    1 -> the direction is the same and we go to the next frame
    0 -> the direction has changed and we start from the first frame
    */

    if(!ok)
        {
            this->timeFrame=0;
            this->currentFrame.x=1;
        }
    else
        {
            if(this->timeFrame > this->timeResetFrame)
                {
                    this->timeFrame=0;
                    this->currentFrame.x++;

                    if(this->currentFrame.x > this->numberOfFrames[this->currentFrame.y])
                        this->currentFrame.x=1;
                }
        }
}

// getting the direction the character is facing
void AnimationCharacter::handleAnimation(Controls controls, Keyboard::Key keyCode, float timer)
{
    /*
    possible values for variable "direction"
    UP -> 1
    LEFT -> 2
    DOWN -> 3
    RIGHT -> 4
    */

    this->timeFrame += timer;

    Vector2f position = this->getSpriteLocation();

    bool isWalking = false, isAttacking=false;

    if(keyCode == controls.getMoveLeft())
        {
            position.x--;
            isWalking=true;
            this->direction = 2;
        }
    else if(keyCode == controls.getMoveRight())
        {
            position.x++;
            isWalking=true;
            this->direction = 4;
        }
    else if(keyCode == controls.getMoveUp())
        {
            position.y--;
            isWalking=true;
            this->direction = 1;
        }
    else if(keyCode == controls.getMoveDown())
        {
            position.y++;
            isWalking=true;
            this->direction = 3;
        }

    if(keyCode == controls.getAttack()) // character is using its basic attack
        {
            isAttacking=true;
            this->attackMode(timer);
        }

    if(keyCode == Keyboard::Unknown) // IDLE mode, character isn't doing anything
        this->idleMode();

    if(isWalking) // character is in walking mode
        {
            this->walkMode(timer);
            this->moveCharacter(position,timer);
        }

    // for easier notation
    int x=this->currentFrame.x;
    int y=this->currentFrame.y;

    if(custom==1)
        {
            if(isAttacking)
                {
                    Vector2f p = this->getFrameSize();

                    this->setSpriteLocation(this->playerPosition.x-p.x,this->playerPosition.y-p.y);
                    this->setFrame(x,y,3,3);
                }
            else
                {
                    this->setSpriteLocation(this->playerPosition.x,this->playerPosition.y);
                    this->setFrame(x,y);
                }
        }
    else
        this->setFrame(x,y);
}

// constructors
AnimationCharacter::AnimationCharacter(string fileName, int x, int y): Animation(fileName,x,y)
{
    this->direction = 3; // by default the character is facing downwards
    this->timeMove = 0;
    this->timeResetMove = 0.005;
    this->custom = 1;
    this->playerPosition = this->getSpriteLocation();

    /*
    this->walkLeft = 10;
    this->walkRight=12;
    this->walkUp=9;
    this->walkDown=11;

    this->attackLeft = 25;
    this->attackRight= 31;
    this->attackUp=22;
    this->attackDown=28;
    */

    string pathValues = "values/characters/" + fileName + ".json";
    ifstream file(pathValues);
    nlohmann::json data = nlohmann::json::parse(file);

    this->walkLeft = ((data["walkLeft"].is_null()==true)?0:(int)data["walkLeft"]);
    this->walkRight = (data["walkRight"].is_null()?0:(int)data["walkRight"]);
    this->walkUp = (data["walkUp"].is_null()?0:(int)data["walkUp"]);
    this->walkDown = (data["walkDown"].is_null()?0:(int)data["walkDown"]);

    this->attackLeft = (data["attackLeft"].is_null()?0:(int)data["attackLeft"]);
    this->attackRight = (data["attackRight"].is_null()?0:(int)data["attackRight"]);
    this->attackUp = (data["attackUp"].is_null()?0:(int)data["attackUp"]);
    this->attackDown = (data["attackDown"].is_null()?0:(int)data["attackDown"]);

    // animation for idle and spellcast

    file.close();
}

// destructors
AnimationCharacter::~AnimationCharacter()
{

}

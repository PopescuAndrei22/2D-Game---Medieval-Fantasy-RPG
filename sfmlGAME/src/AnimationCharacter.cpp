#include "AnimationCharacter.h"

// animation for spellcasting
void AnimationCharacter::spellCastMode(Character *character)
{
    bool ok = character->getDidChangeDirection();

    if(character->getDirection()==1)
        {
            this->currentFrame.y = spellCastUp;
        }
    else if(character->getDirection()==2)
        {
            this->currentFrame.y = spellCastLeft;
        }
    else if(character->getDirection()==3)
        {
            this->currentFrame.y = spellCastDown;
        }
    else if(character->getDirection()==4)
        {
            this->currentFrame.y = spellCastRight;
        }

    // render animation for spellcast mode
    if(ok == true)
        {
            this->resetTime();
            this->currentFrame.x=1;
        }
    else
        {
            if(this->getTimeFrame() > this->getTimeResetFrame())
                {
                    this->resetTime();
                    this->currentFrame.x++;

                    if(this->currentFrame.x > this->numberOfFrames[this->currentFrame.y-1])
                        {
                            this->currentFrame.x=1;
                            character->setActionInProgress(false);
                            character->setIsSpellCasting(false);
                        }
                }
        }
}

// animation for IDLE mode
void AnimationCharacter::idleMode(Character *character)
{
    /*
    This texture actually doesn't have an animation for idle, so
    i just selected the first frame from walking mode when the
    character is on idle mode
    */

    if(custom==1)
        {
            this->resetTime();

            this->currentFrame.x = 1;
            this->currentFrame.y = 1;

            if(character->getDirection()==1)
                {
                    this->currentFrame.y = walkUp;
                }
            else if(character->getDirection()==2)
                {
                    this->currentFrame.y = walkLeft;
                }
            else if(character->getDirection()==3)
                {
                    this->currentFrame.y = walkDown;
                }
            else if(character->getDirection()==4)
                {
                    this->currentFrame.y = walkRight;
                }

            return;
        }

    bool ok = character->getDidChangeDirection();

    if(character->getDirection()==1)
        {
            this->currentFrame.y = idleUp;
        }
    else if(character->getDirection()==2)
        {
            this->currentFrame.y = idleLeft;
        }
    else if(character->getDirection()==3)
        {
            this->currentFrame.y = idleDown;
        }
    else if(character->getDirection()==4)
        {
            this->currentFrame.y = idleRight;
        }

    this->renderAnimation(ok);
}

void AnimationCharacter::walkMode(Character *character)
{
    bool ok = character->getDidChangeDirection();

    if(character->getDirection()==1)
        {
            this->currentFrame.y = walkUp;
        }
    else if(character->getDirection()==2)
        {
            this->currentFrame.y = walkLeft;
        }
    else if(character->getDirection()==3)
        {
            this->currentFrame.y = walkDown;
        }
    else if(character->getDirection()==4)
        {
            this->currentFrame.y = walkRight;
        }

    this->renderAnimation(ok);
}

void AnimationCharacter::attackMode(Character *character)
{
    bool ok = character->getDidChangeDirection();

    if(character->getDirection()==1)
        {
            this->currentFrame.y = attackUp;
        }
    else if(character->getDirection()==2)
        {
            this->currentFrame.y = attackLeft;
        }
    else if(character->getDirection()==3)
        {
            this->currentFrame.y = attackDown;
        }
    else if(character->getDirection()==4)
        {
            this->currentFrame.y = attackRight;
        }

    // render animation for attack
    if(ok == true)
        {
            this->resetTime();
            this->currentFrame.x=1;
        }
    else
        {
            if(this->getTimeFrame() > this->getTimeResetFrame())
                {
                    this->resetTime();
                    this->currentFrame.x++;

                    if(this->currentFrame.x > this->numberOfFrames[this->currentFrame.y-1])
                        {
                            this->currentFrame.x=1;
                            character->setActionInProgress(false);
                            character->setIsAttacking(false);
                            character->setIsDamaging(true);
                        }
                }
        }
}

void AnimationCharacter::deathMode(Character *character)
{
    // de modificat aici ca e codu nasol si trebuie sa pun frame x la 1

    this->currentFrame.y = this->death;

    if(this->getTimeFrame() > this->getTimeResetFrame())
        {
            this->resetTime();
            this->currentFrame.x++;

            if(this->currentFrame.x > this->numberOfFrames[this->currentFrame.y-1])
                {
                    this->currentFrame.x=1;

                    character->revive();
                }
        }
}

void AnimationCharacter::hitMode(Character *character, float timer)
{
    this->isHitTime += timer;

    if(this->isHitTime > this->isHitTimeReset)
        {
            this->isHitTime = 0;

            if(this->currentHitCounter > 0)
                {
                    if(this->currentHitCounter%2!=0)
                        this->setSpriteColor(Color::Red);
                    else
                        this->setSpriteColor(Color::White);

                    this->currentHitCounter--;
                }
            else
                {
                    this->currentHitCounter = this->hitCounter;
                    this->setSpriteColor(Color::White);
                    character->setIsHit(false);
                }
        }
}

void AnimationCharacter::handleAnimation(Character *character, float timer)
{
    /*
    possible values for variable "direction"
    UP -> 1
    LEFT -> 2
    DOWN -> 3
    RIGHT -> 4
    */

    this->increaseTime(timer);

    character->setIsDamaging(false); // because i set this on true in this class ( when character is attacking )

    if(character->getIsDead() == true)
        {
            this->deathMode(character);
        }
    else
        {

            if(character->getIsMoving() == true)
                {
                    if(character->getWalkIntoObstacle()==false)
                        this->walkMode(character);
                    else
                        this->idleMode(character);
                }

            if(character->getIsAttacking() == true)
                {
                    this->attackMode(character);
                }

            if(character->getIsSpellCasting() == true)
                {
                    this->spellCastMode(character);
                }

            if(character->getIsIdle())
                {
                    this->idleMode(character);
                }
            if(character->getIsHit())
                {
                    this->hitMode(character,timer);
                }
        }

    // for easier notation
    int x=this->currentFrame.x;
    int y=this->currentFrame.y;

    Vector2f characterPosition = character->getCharacterPosition();

    this->setSpriteLocation(characterPosition.x,characterPosition.y);
    this->setFrame(x,y);

    if(custom==1 && character->getIsAttacking()==true)
        {
            Vector2f b = this->getFrameSize();

            this->setSpriteLocation(characterPosition.x-b.x,characterPosition.y-b.y);
            this->setFrame(x,y,3,3);
        }
}

// constructors
AnimationCharacter::AnimationCharacter(string fileName): Animation(fileName)
{
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

    this->spellCastLeft = (data["spellCastLeft"].is_null()?0:(int)data["spellCastLeft"]);
    this->spellCastRight = (data["spellCastRight"].is_null()?0:(int)data["spellCastRight"]);
    this->spellCastUp = (data["spellCastUp"].is_null()?0:(int)data["spellCastUp"]);
    this->spellCastDown = (data["spellCastDown"].is_null()?0:(int)data["spellCastDown"]);

    this->idleLeft = ((data["idleLeft"].is_null()==true)?0:(int)data["idleLeft"]);
    this->idleRight = (data["idleRight"].is_null()?0:(int)data["idleRight"]);
    this->idleUp = (data["idleUp"].is_null()?0:(int)data["idleUp"]);
    this->idleDown = (data["idleDown"].is_null()?0:(int)data["idleDown"]);

    this->death = (data["death"].is_null()?0:(int)data["death"]);

    this->custom = ((data["custom"].is_null()==true)?0:(int)data["custom"]);

    this->hitCounter = this->currentHitCounter = 3;

    this->isHitTime = 0.0;
    this->isHitTimeReset = 0.06;

    file.close();
}

// destructors
AnimationCharacter::~AnimationCharacter()
{

}

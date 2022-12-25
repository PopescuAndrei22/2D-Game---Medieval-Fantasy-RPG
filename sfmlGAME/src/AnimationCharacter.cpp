#include "AnimationCharacter.h"

// animation for spellcasting
void AnimationCharacter::spellCastMode()
{
    bool ok = true;

    if(this->direction==1)
        {
            ok = this->currentFrame.y == spellCastUp;
            this->currentFrame.y = spellCastUp;
        }
    else if(this->direction==2)
        {
            ok = this->currentFrame.y == spellCastLeft;
            this->currentFrame.y = spellCastLeft;
        }
    else if(this->direction==3)
        {
            ok = this->currentFrame.y == spellCastDown;
            this->currentFrame.y = spellCastDown;
        }
    else if(this->direction==4)
        {
            ok = this->currentFrame.y == spellCastRight;
            this->currentFrame.y = spellCastRight;
        }

    this->renderAnimation(ok);
}

// animation for IDLE mode
void AnimationCharacter::idleMode()
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

            return;
        }

    bool ok = true;

    if(this->direction==1)
        {
            ok = this->currentFrame.y == idleUp;
            this->currentFrame.y = idleUp;
        }
    else if(this->direction==2)
        {
            ok = this->currentFrame.y == idleLeft;
            this->currentFrame.y = idleLeft;
        }
    else if(this->direction==3)
        {
            ok = this->currentFrame.y == idleDown;
            this->currentFrame.y = idleDown;
        }
    else if(this->direction==4)
        {
            ok = this->currentFrame.y == idleRight;
            this->currentFrame.y = idleRight;
        }

    this->renderAnimation(ok);
}

void AnimationCharacter::walkMode()
{
    bool ok = true;

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

    this->renderAnimation(ok);
}

void AnimationCharacter::attackMode()
{
    bool ok = true;

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

    this->renderAnimation(ok);
}

void AnimationCharacter::handleAnimation(Character character, Controls controls, float timer)
{
    /*
    possible values for variable "direction"
    UP -> 1
    LEFT -> 2
    DOWN -> 3
    RIGHT -> 4
    */

    Keyboard::Key keyCode = controls.checkIfKeyIsPressed();

    this->increaseTime(timer);

    bool isWalking = false, isAttacking=false;

    if(keyCode == controls.getMoveLeft())
        {
            isWalking=true;
            this->direction = 2;
        }
    else if(keyCode == controls.getMoveRight())
        {
            isWalking=true;
            this->direction = 4;
        }
    else if(keyCode == controls.getMoveUp())
        {
            isWalking=true;
            this->direction = 1;
        }
    else if(keyCode == controls.getMoveDown())
        {
            isWalking=true;
            this->direction = 3;
        }

    if(keyCode == controls.getAttack()) // character is using its basic attack
        {
            isAttacking=true;
            this->attackMode();
        }

    if(keyCode == controls.getSpellCast())
        {
            this->spellCastMode();
        }

    if(keyCode == Keyboard::Unknown) // IDLE mode, character isn't doing anything
        {
            this->idleMode();
        }

    if(isWalking) // character is in walking mode
        {
            this->walkMode();
        }

    // for easier notation
    int x=this->currentFrame.x;
    int y=this->currentFrame.y;

    Vector2f characterPosition = character.getCharacterPosition();

    this->setSpriteLocation(characterPosition.x,characterPosition.y);
    this->setFrame(x,y);

    if(custom==1 && isAttacking)
        {
            Vector2f b = this->getFrameSize();

            this->setSpriteLocation(characterPosition.x-b.x,characterPosition.y-b.y);
            this->setFrame(x,y,3,3);
        }
}

// constructors
AnimationCharacter::AnimationCharacter(string fileName): Animation(fileName)
{
    this->direction = 3; // by default the character is facing downwards

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

    this->custom = ((data["custom"].is_null()==true)?0:(int)data["custom"]);

    file.close();
}

// destructors
AnimationCharacter::~AnimationCharacter()
{

}

#include "CharacterManagement.h"

/* class methods */
void CharacterManagement::managePlayerControls(sf::Keyboard::Key key, Controls controls, Player &player)
{
    player.setIsIdle(false);
    player.setIsMoving(false);
    //player.setIsAttacking(false);
    //player.setIsSpellCasting(false);

    bool isMoving = false;
    std::string newDirection = "";

    if(key == controls.getMoveDown())
        {
            isMoving = true;
            newDirection="down";
        }

    if(key == controls.getMoveUp())
        {
            isMoving = true;
            newDirection="up";
        }

    if(key == controls.getMoveLeft())
        {
            isMoving = true;
            newDirection="left";
        }

    if(key == controls.getMoveRight())
        {
            isMoving = true;
            newDirection="right";
        }

    if(player.getIsAttacking() == true)
        return;

    if(player.getIsSpellCasting() == true)
        return;

    if(player.getIsDying() == true)
        return;

    if(player.getIsDead())
        return;

    if(player.getIsDashing())
        return;

    if(key == controls.getDash() && player.getCooldownDash() == false)
        {
            player.setIsDashing(true);
        }
    else if(isMoving == true)
        {
            player.setDirection(newDirection);
            player.setIsMoving(true);
        }
    else if(key == controls.getAttack())
        {
            player.setIsAttacking(true);
        }
    else if(key == controls.getSpellCast())
        {
            player.setIsSpellCasting(true);
        }
    else
        {
            player.setIsIdle(true);
        }
}

void CharacterManagement::manageCharacterActions(Character &character, AnimationState &animationState, float timer)
{
    character.setIsDamaging(false);

    if(character.getIsDead())
        return;

    std::string direction = character.getDirection();
    direction[0]-=32;

    std::string stateName = "";

    bool isLooped = true;

    if(character.getIsDying())
        {
            stateName = "death";
            isLooped = false;
        }
    else if(character.getIsDashing())
        {
            stateName = "walk" + direction;
        }
    else if(character.getIsMoving() && character.getIsWalkingIntoObstacle() == false)
        {
            stateName = "walk" + direction;
        }
    else if(character.getIsAttacking())
        {
            stateName = "attack" + direction;
            isLooped = false;
        }
    else if(character.getIsSpellCasting())
        {
            stateName = "spellCast" + direction;
            isLooped = false;
        }
    else
        {
            stateName = "idle" + direction;
        }

    // hotfix, is hardcoded, must fix soon
    sf::Vector2f hotfixPos = character.getCharacterPosition();
    if(character.getIsAttacking() == true && character.getIsDying() == false)
        animationState.setPosition(sf::Vector2f(hotfixPos.x-64,hotfixPos.y-64));
    else
        animationState.setPosition(character.getCharacterPosition());

    animationState.setState(stateName);
    animationState.setIsLooped(isLooped);

    if(animationState.getIsFinished() == true)
        {
            if(character.getIsAttacking() == true)
                {
                    character.setIsAttacking(false);

                    character.setIsDamaging(true);
                }

            if(character.getIsSpellCasting() == true)
                {
                    character.setIsSpellCasting(false);
                }

            if(character.getIsDying() == true)
                {
                    character.setIsDying(false);
                    character.setIsDead(true);
                }

            if(character.getIsDead() == false)
                animationState.stop();
        }
}

/* constructors */
CharacterManagement::CharacterManagement()
{

}

/* destructors */
CharacterManagement::~CharacterManagement()
{

}

#include "CharacterEvents.h"

/* getters */
sf::Text CharacterEvents::getText() const
{
    return this->text;
}

/* class methods */
void CharacterEvents::checkIsCharacterDamaged(Character &character, AnimationState &animationState, float timer)
{
    if(character.getIsDead() || character.getIsDying())
        {
            animationState.setColor(sf::Color::White);

            this->isDamagedTimer = 0.0f;

            this->damagedToggleCounter = 0;

            this->isDamagedTimerToggle = this->isDamagedTimerToggleReset;

            return;
        }

    if(character.getIsDamaged())
        {
            this->timeSinceGotDamagedTimer = 0.0f;
            this->healthRegenerationTimerReset = this->healthRegenerationDefaultTimer;

            this->isDamagedTimer += timer;

            this->isDamagedTimerToggle -= timer;

            if(this->isDamagedTimerToggle < 0)
                {
                    this->isDamagedTimerToggle = this->isDamagedTimerToggleReset;

                    this->damagedToggleCounter++;

                    if(this->damagedToggleCounter%2==0)
                        animationState.setColor(sf::Color::White);
                    else
                        animationState.setColor(sf::Color::Red);
                }

            if(this->isDamagedTimer > this->isDamagedTimerReset)
                {
                    this->isDamagedTimer = 0.0f;

                    this->damagedToggleCounter = 0;

                    this->isDamagedTimerToggle = this->isDamagedTimerToggleReset;

                    animationState.setColor(sf::Color::White);

                    character.setIsDamaged(false);
                }
        }
    else
        {
            if(this->timeSinceGotDamagedTimer < this->timeSinceGotDamagedTimerReset)
                this->timeSinceGotDamagedTimer += timer;

            animationState.setColor(sf::Color::White);
        }
}

void CharacterEvents::checkIsCharacterDead(Character &character, AnimationState &animationState, float timer)
{
    if(character.getIsDead() && character.getIsRespawnable())
        {
            std::string printText = "Respawn time: ";

            float difference = character.getRespawnTime() - this->respawnTimer;
            int timerToInt = (int)difference;

            printText += std::to_string(timerToInt);

            this->text.setString(printText);

            this->respawnTimer += timer;

            if(this->respawnTimer > character.getRespawnTime())
                {
                    this->respawnTimer = 0.0f;

                    character.setIsDead(false);
                    character.revive();
                }
        }
}

void CharacterEvents::checkIsCharacterDashing(Character &character, AnimationState &animationState, float timer)
{
    if(character.getCooldownDash())
        {
            this->dashCooldownTimer += timer;

            if(this->dashCooldownTimer > this->dashCooldownTimerReset)
                {
                    this->dashCooldownTimer = 0.0f;

                    character.setCooldownDash(false);
                }

            return;
        }

    if(character.getIsDashing())
        {
            character.setIsAbleToDash(false);

            int countLeaps = character.getLeapsInDash();

            if(this->isDashingCounter >= countLeaps)
                {
                    this->isDashingCounter = 0;

                    character.setIsDashing(false);
                    character.setIsAbleToDash(false);

                    character.setCooldownDash(true);
                }
            else
                {
                    this->isDashingTimer += timer;

                    if(this->isDashingTimer > this->isDashingTimerReset)
                        {
                            this->isDashingTimer = 0.0f;
                            this->isDashingCounter ++;

                            character.setIsAbleToDash(true);
                        }
                }
        }
}

void CharacterEvents::regenerateLife(Character &character, float timer)
{
    if(this->timeSinceGotDamagedTimer >= this->timeSinceGotDamagedTimerReset)
        {
            if(character.getCurrentHealth() < character.getHealth())
                {
                    this->healthRegenerationTimer += timer;

                    if(this->healthRegenerationTimer > this->healthRegenerationTimerReset)
                        {
                            this->healthRegenerationTimer = 0.0f;

                            if(this->healthRegenerationTimerReset > this->healthRegenerationMinTimer)
                                this->healthRegenerationTimerReset -= this->healthRegenerationTimerDecreasing;
                            else
                                this->healthRegenerationTimerReset = this->healthRegenerationMinTimer;

                            character.setCurrentHealth(character.getCurrentHealth() + this->healthRegeneration);
                        }
                }
            else
                {
                    this->healthRegenerationTimerReset = this->healthRegenerationDefaultTimer;
                }
        }
    else
        {
            this->healthRegenerationTimer = 0.0f;
        }
}

void CharacterEvents::manageCharacterEvents(Character &character, AnimationState &animationState, float timer)
{
    this->text.setString("");

    this->checkIsCharacterDamaged(character,animationState,timer);

    this->checkIsCharacterDead(character,animationState,timer);

    this->checkIsCharacterDashing(character,animationState,timer);

    this->regenerateLife(character,timer);
}

void CharacterEvents::updateTextPosition(sf::Vector2f position)
{
    this->text.setPosition(sf::Vector2f(position.x-(this->text.getGlobalBounds().width/2),position.y));
}

/* constructor */
CharacterEvents::CharacterEvents()
{
    // is hit

    this->damagedToggleCounter = 0;

    this->isDamagedTimer = 0.0f;
    this->isDamagedTimerReset = 1.0f;

    this->isDamagedTimerToggle = 0.1f;
    this->isDamagedTimerToggleReset = 0.1f;

    // respawn

    this->respawnTimer = 0.0f;

    // dashing

    this->isDashingTimer = 0.0f;
    this->isDashingTimerReset = 0.03f;
    this->isDashingCounter = 0;

    this->dashCooldownTimer = 0.0f;
    this->dashCooldownTimerReset = 0.5f;

    // text

    this->font.loadFromFile("fonts/arial.ttf");

    this->text.setFont(this->font);

    this->text.setFillColor(sf::Color::Red);

    this->text.setCharacterSize(45);

    // health regeneration

    this->healthRegeneration = 1;

    this->healthRegenerationTimer = 0.0f;
    this->healthRegenerationTimerReset = 0.5f;

    this->healthRegenerationDefaultTimer = 0.5f;
    this->healthRegenerationTimerDecreasing = 0.01f;
    this->healthRegenerationMinTimer = 0.1f;

    this->healthRegenerationTimer = 0.0f;
    this->healthRegenerationTimerReset = this->healthRegenerationDefaultTimer;

    this->timeSinceGotDamagedTimerReset = 4.0f;
    this->timeSinceGotDamagedTimer = this->timeSinceGotDamagedTimerReset;

}

/* destructor */
CharacterEvents::~CharacterEvents()
{

}

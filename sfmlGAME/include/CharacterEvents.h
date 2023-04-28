#ifndef CHARACTEREVENTS_H
#define CHARACTEREVENTS_H
#include "Map.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Character.h"
#include "Enemy.h"
#include "AnimationState.h"
#include <vector>

class CharacterEvents
{
    public:

        /* getters */
        sf::Text getText() const;

        /* setters */

        /* class methods */
        void checkIsCharacterDamaged(Character&, AnimationState&, float);

        void checkIsCharacterDead(Character&, AnimationState&, float);

        void checkIsCharacterDashing(Character&, AnimationState&, float);

        void regenerateLife(Character&, float);

        void manageCharacterEvents(Character&, AnimationState&, float);

        void updateTextPosition(sf::Vector2f);

        CharacterEvents();
        ~CharacterEvents();

    private:

        // is hit
        int damagedToggleCounter;

        float isDamagedTimer;
        float isDamagedTimerReset;

        float isDamagedTimerToggle;
        float isDamagedTimerToggleReset;

        // respawn

        float respawnTimer;

        // dashing

        float isDashingTimer;
        float isDashingTimerReset;
        int isDashingCounter;

        // i can set these for each character individually
        float dashCooldownTimer;
        float dashCooldownTimerReset;

        // health regeneration
        float healthRegenerationTimer;
        float healthRegenerationTimerReset;

        float healthRegenerationDefaultTimer;
        float healthRegenerationTimerDecreasing;
        float healthRegenerationMinTimer;

        float timeSinceGotDamagedTimer;
        float timeSinceGotDamagedTimerReset;

        int healthRegeneration;

        // text

        sf::Font font;
        sf::Text text;


};

#endif // CHARACTEREVENTS_H

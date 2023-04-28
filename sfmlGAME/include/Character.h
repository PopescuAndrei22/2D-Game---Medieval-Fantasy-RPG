#ifndef CHARACTER_H
#define CHARACTER_H
#include <iostream>
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>
#include <SFML/Graphics.hpp>

class Character
{
    public:
        /* getters */
        int getHealth() const;
        int getCurrentHealth() const;

        int getMana() const;
        int getCurrentMana() const;

        int getSpeedMovement() const;
        int getSpeedAttack() const;

        int getLeapsInDash() const;

        bool getIsKnockable() const;

        bool getIsAttacking() const;
        bool getIsSpellCasting() const;
        bool getIsMoving() const;
        bool getIsIdle() const;
        bool getIsDashing() const;

        bool getIsDying() const;
        bool getIsDead() const;
        bool getIsRespawnable() const;

        bool getIsDamaging() const;
        bool getIsDamaged() const;
        bool getIsKnockbacked() const;

        bool getIsWalkingIntoObstacle() const;

        bool getIsAbleToDash() const;

        bool getCooldownDash() const;

        bool getRegenerableLife() const;

        float getBaseDamageMelee() const;
        float getKnockbackDistance() const;
        float getReceivedKnockbackDistance() const;

        float getRadiusAttack() const;

        float getRespawnTime() const;

        float getLeapDistanceInDash() const;

        std::string getDirection() const;
        std::string getDirectionKnockback() const;

        sf::Vector2f getCharacterPosition() const;
        sf::Vector2f getSpawnPoint() const;
        sf::Vector2f getCharacterSize() const;

        /* setters */
        void setHealth(int);
        void setCurrentHealth(int);

        void setMana(int);
        void setCurrentMana(int);

        void setSpeedMovement(int);
        void setSpeedAttack(int);

        void setLeapsInDash(int);

        void setIsKnockable(bool);

        void setIsAttacking(bool);
        void setIsSpellCasting(bool);
        void setIsMoving(bool);
        void setIsIdle(bool);
        void setIsDashing(bool);

        void setIsDying(bool);
        void setIsDead(bool);
        void setIsRespawnable(bool);

        void setIsDamaging(bool);
        void setIsDamaged(bool);
        void setIsKnockbacked(bool);

        void setIsWalkingIntoObstacle(bool);

        void setIsAbleToDash(bool);
        void setCooldownDash(bool);

        void setRegenerableLife(bool);

        void setBaseDamageMelee(float);
        void setKnockbackDistance(float);
        void setReceivedKnockbackDistance(float);
        void setRadiusAttack(float);

        void setRespawnTime(float);

        void setLeapDistanceInDash(float);

        void setDirection(std::string);
        void setDirectionKnockback(std::string);

        void setCharacterPosition(sf::Vector2f);
        void setSpawnPoint(sf::Vector2f);
        void setCharacterSize(sf::Vector2f);

        /* class methods */
        virtual void revive();
        virtual void setValues(std::string);

        /* constructors */
        Character();

        /* destructors */
        ~Character();

    private:
        int health;
        int currentHealth;

        int mana;
        int currentMana;

        int speedMovement;
        int speedAttack;

        int leapsInDash;

        bool isKnockable;

        bool isAttacking;
        bool isSpellCasting;
        bool isMoving;
        bool isIdle;
        bool isDashing;

        bool isDying;
        bool isDead;

        bool isRespawnable;

        bool isDamaging;
        bool isDamaged;
        bool isKnockbacked;

        bool isWalkingIntoObstacle;

        bool isAbleToDash;

        bool cooldownDash;

        bool regenerableLife;

        float knockbackDistance;
        float receivedKnockbackDistance;

        float baseDamageMelee;

        float radiusAttack;

        float respawnTime;

        float leapDistanceInDash;

        std::string direction;
        std::string directionKnockback;

        sf::Vector2f characterPosition;
        sf::Vector2f spawnPoint;
        sf::Vector2f characterSize;

};

#endif // CHARACTER_H

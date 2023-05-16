#ifndef PROJECTILE_H
#define PROJECTILE_H
#include <iostream>
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>
#include <SFML/Graphics.hpp>
#include "AnimationState.h"
#include "AnimationManagement.h"

class Projectile
{
    public:
        bool getHasReachedDestination() const;
        bool getProjectileFinished() const;
        bool getIsProjectileDamaging() const;

        void setPosition(sf::Vector2f);
        void setTarget(sf::Vector2f);
        void setHasReachedDestination(bool);
        void setProjectileFinished(bool);
        void setIsProjectileDamaging(bool);

        void moveTowardsTarget(float);
        void moveProjectile(float);
        void adjustDirection();

        void update(float);

        bool isCollision(sf::Vector2f, sf::Vector2f);

        void draw(sf::RenderWindow&);

        void init(std::string);

        Projectile();
        ~Projectile();

    private:

        sf::Vector2f target;

        AnimationState animationStateProjectile;
        AnimationState animationStateExplosion;

        float timeElapsed,timeReset;

        bool hasReachedDestination;

        bool projectileFinished;

        bool isProjectileDamaging;
};

#endif // PROJECTILE_H

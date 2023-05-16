#include "NecromancerAI.h"

float NecromancerAI::getEuclidianDistance(sf::Vector2f a, sf::Vector2f b)
{
    return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2) * 1.0);
}

std::string NecromancerAI::getNewDirection(Boss &boss)
{
    std::vector <std::string> availableDirections = {"left","right","up","down"};

    std::string newDirection = availableDirections[rand()%(availableDirections.size())];

    sf::Vector2f a = boss.getCharacterPosition();
    sf::Vector2f b = boss.getSpawnPoint();

    float distance = this->getEuclidianDistance(a,b);

    std::string enemyDirection = boss.getDirection();

    if(distance > boss.getRadiusIdle())
        {
            if(enemyDirection == "left")
                newDirection = "right";

            else if(enemyDirection == "right")
                newDirection = "left";

            else if(enemyDirection == "down")
                newDirection = "up";

            else
                newDirection = "down";
        }

    return newDirection;
}

bool NecromancerAI::isInRadius(Boss &boss)
{
    sf::Vector2f a = boss.getCharacterPosition();
    sf::Vector2f b = boss.getPlayerPosition();

    float radius = boss.getRadiusCombat();

    if(boss.getCurrentState() == "agressive")
        radius *= 2;

    if(this->getEuclidianDistance(a,b) < radius)
        return true;

    return false;
}

void NecromancerAI::passiveAI(Boss &boss)
{
    if(boss.getTimerIdle() < (boss.getTimerIdleReset() / 2.0f))
        {
            boss.setIsMoving(true);
        }
    else
        boss.setIsIdle(true);

    if(boss.getTimerIdle() > boss.getTimerIdleReset())
        {
            boss.setDirection(this->getNewDirection(boss));
            boss.setTimerIdle(0.0f);
        }

    if(this->isInRadius(boss))
        {
            boss.setLastKnownPosition(boss.getPlayerPosition());

            if(boss.getIsPlayerDead() == false)
                {
                    boss.setCurrentState("agressive");
                }
        }
}

void NecromancerAI::agressiveAI(Boss &boss)
{
    if(this->isInRadius(boss))
        {
            if(boss.getIsAttacking() == false && boss.getProjectileRequest() == false)
                {
                    // making the boss to face the player
                    sf::Vector2f bossPosition = boss.getCharacterPosition();
                    sf::Vector2f playerPosition = boss.getPlayerPosition();

                    float horizontalDistance = abs(bossPosition.x - playerPosition.x);
                    float verticalDistance = abs(bossPosition.y - playerPosition.y);

                    if(horizontalDistance > verticalDistance)
                        {
                            if(playerPosition.x <= bossPosition.x)
                                {
                                    boss.setDirection("left");
                                }
                            else
                                {
                                    boss.setDirection("right");
                                }
                        }
                    else
                        {
                            if(playerPosition.y >= bossPosition.y)
                                {
                                    boss.setDirection("down");
                                }
                            else
                                {
                                    boss.setDirection("up");
                                }
                        }

                    boss.setTimerIdle(0.0f);

                    boss.setIsAttacking(true);

                    boss.setProjectileRequest(true);
                }
        }
    else
        {
            boss.revive();
        }
}

void NecromancerAI::manageAI(Boss &boss, float timer)
{
    boss.setIsIdle(false);
    boss.setIsMoving(false);

    if(boss.getIsDead())
        return;

    if(boss.getCurrentState() == "agressive")
        {
            this->agressiveAI(boss);
        }
    else
        {
            boss.setTimerIdle(boss.getTimerIdle() + timer);
            this->passiveAI(boss);
        }
}

NecromancerAI::NecromancerAI()
{

}

NecromancerAI::~NecromancerAI()
{

}

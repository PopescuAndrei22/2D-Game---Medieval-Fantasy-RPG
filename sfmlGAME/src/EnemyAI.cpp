#include "EnemyAI.h"

/* class methods */
float EnemyAI::getEuclidianDistance(sf::Vector2f a, sf::Vector2f b)
{
    return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2) * 1.0);
}

std::string EnemyAI::getNewDirection(Enemy &enemy)
{
    std::vector <std::string> availableDirections = {"left","right","up","down"};

    std::string newDirection = availableDirections[rand()%(availableDirections.size())];

    sf::Vector2f a = enemy.getCharacterPosition();
    sf::Vector2f b = enemy.getSpawnPoint();

    float distance = this->getEuclidianDistance(a,b);

    std::string enemyDirection = enemy.getDirection();

    if(distance > enemy.getRadiusIdle())
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

bool EnemyAI::isInRadius(Enemy &enemy)
{
    sf::Vector2f a = enemy.getCharacterPosition();
    sf::Vector2f b = enemy.getPlayerPosition();

    float radius = enemy.getRadiusCombat();

    if(enemy.getCurrentState() == "agressive")
        radius *= 2;

    if(this->getEuclidianDistance(a,b) < radius)
        return true;

    return false;
}

void EnemyAI::passiveAI(Enemy &enemy)
{
    if(enemy.getTimerIdle() < (enemy.getTimerIdleReset() / 2.0f))
        {
            enemy.setIsMoving(true);
        }
    else
        enemy.setIsIdle(true);

    if(enemy.getTimerIdle() > enemy.getTimerIdleReset())
        {
            enemy.setDirection(this->getNewDirection(enemy));
            enemy.setTimerIdle(0.0f);
        }

    if(this->isInRadius(enemy))
        {
            enemy.setLastKnownPosition(enemy.getPlayerPosition());

            if(enemy.getIsPlayerDead() == false)
                {
                    enemy.setCurrentState("agressive");
                }
        }
}

void EnemyAI::agressiveAI(Enemy &enemy)
{
    sf::Vector2f destination;

    if(this->isInRadius(enemy))
        {
            destination = enemy.getPlayerPosition();
            enemy.setLastKnownPosition(enemy.getPlayerPosition());
        }
    else
        destination = enemy.getLastKnownPosition();

    if(enemy.getIsAttacking() || enemy.getIsSpellCasting() || enemy.getIsDying())
        return;

    std::pair <int,int> nextMove = enemy.getNextStep(destination,enemy.getCharacterPosition());

    std::pair <int,int> currentTiles = enemy.getEnemyTiles();

    std::string direction = "";

    // if the enemy arrived at the last known position of the player and the player isn't there nor in the radius of the enemy
    if(nextMove.first == -1 && this->isInRadius(enemy) == false)
        {
            enemy.revive();

            return;
        }

    if(currentTiles.first > nextMove.first) // goes up
        direction = "up";

    else if(currentTiles.second > nextMove.second) // goes left
        direction = "left";

    else if(currentTiles.second < nextMove.second) // goes right
        direction = "right";

    else
        direction = "down";

    enemy.setIsMoving(true);
    enemy.setDirection(direction);
}

void EnemyAI::manageAI(Enemy &enemy, float timer)
{
    enemy.setIsIdle(false);
    enemy.setIsMoving(false);

    if(enemy.getIsDead())
        return;

    if(enemy.getCurrentState() == "agressive")
        this->agressiveAI(enemy);
    else
        {
            enemy.setTimerIdle(enemy.getTimerIdle() + timer);
            this->passiveAI(enemy);
        }
}

/* constructors */
EnemyAI::EnemyAI()
{

}

/* destructors */
EnemyAI::~EnemyAI()
{

}

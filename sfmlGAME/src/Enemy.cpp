#include "Enemy.h"

// revive
void Enemy::revive()
{
    this->Character::revive();

    this->setCombatMode(false);
}

// getters
bool Enemy::getIsRespawnable() const
{
    return this->respawnable;
}

bool Enemy::getCombatMode() const
{
    return this->combatMode;
}

float Enemy::getRadiusIdle() const
{
    return this->radiusIdle;
}

float Enemy::getRadiusCombat() const
{
    return this->radiusCombat;
}

float Enemy::getTimeMoveIdle() const
{
    return this->timeMoveIdle;
}

float Enemy::getTimeMoveIdleReset() const
{
    return this->timeMoveIdleReset;
}

float Enemy::getRespawnTime() const
{
    return this->respawnTime;
}

Vector2f Enemy::getPlayerPosition() const
{
    return this->playerPosition;
}

Vector2f Enemy::getLastKnownPosition() const
{
    return this->lastKnownPosition;
}

// setters
void Enemy::setLastKnownPosition(Vector2f lastKnownPosition)
{
    this->lastKnownPosition = lastKnownPosition;
}

void Enemy::setCombatMode(bool combatMode)
{
    this->combatMode = combatMode;
}

void Enemy::setIsRespawnable(bool respawnable)
{
    this->respawnable = respawnable;
}

void Enemy::setRespawnTime(float respawnTime)
{
    this->respawnTime = respawnTime;
}

void Enemy::setRadiusCombat(float radiusCombat)
{
    this->radiusCombat = radiusCombat;
}

void Enemy::setRadiusIdle(float radiusIdle)
{
    this->radiusIdle = radiusIdle;
}

void Enemy::increaseTimeMoveIdle(float timer)
{
    this->timeMoveIdle += timer;
}

void Enemy::resetTimeMoveIdle()
{
    this->timeMoveIdle = 0.0f;
}

void Enemy::setTimeMoveIdleReset(float timeMoveIdleReset)
{
    this->timeMoveIdleReset = timeMoveIdleReset;
}

void Enemy::setPlayerPosition(Vector2f characterPosition)
{
    this->playerPosition = characterPosition;
}

void Enemy::getPlayerState(Character *character)
{
    this->setPlayerPosition(character->getCharacterPosition());

    // enemy taking damage
    if(character->getIsDamaging() == true && this->getIsHit() == false)
        {
            if(this->getEuclidianDistance(character->getCharacterPosition(),this->getCharacterPosition()) <= character->getRadiusAttack())
                {
                    // the code below is to hit the enemy only if the player is facing it
                    int currentDirection = character->getDirection();

                    /*
                    UP -> 1
                    LEFT -> 2
                    DOWN -> 3
                    RIGHT -> 4
                    */

                    Vector2f enemyPosition = this->getCharacterPosition();
                    Vector2f playerPosition = character->getCharacterPosition();

                    bool isFacingEnemy = false;

                    if(currentDirection == 1 && playerPosition.y >= enemyPosition.y)
                        isFacingEnemy = true;
                    if(currentDirection == 2 && playerPosition.x >= enemyPosition.x)
                        isFacingEnemy = true;
                    if(currentDirection == 3 && playerPosition.y <= enemyPosition.y)
                        isFacingEnemy = true;
                    if(currentDirection == 4 && playerPosition.x <= enemyPosition.x)
                        isFacingEnemy = true;

                    if(isFacingEnemy==true)
                        {
                            this->setIsHit(true);
                            this->setCurrentHealth(this->getCurrentHealth() - character->getBaseDamage());
                            this->setEnemyDirection(character->getDirection());
                            this->setIsKnockbacked(true);
                        }
                }
        }

    // player taking damage
    if(this->getIsDamaging() == true && character->getIsHit() == false)
        {
            if(this->getEuclidianDistance(character->getCharacterPosition(),this->getCharacterPosition()) <= this->getRadiusAttack())
                {
                    character->setIsHit(true);
                    character->setCurrentHealth(character->getCurrentHealth() - this->getBaseDamage());
                    character->setEnemyDirection(this->getDirection());
                    character->setIsKnockbacked(true);
                }
        }

    if(this->getCurrentHealth() <= 0)
        {
            this->setIsDead(true);
        }
    if(character->getCurrentHealth() <= 0)
        {
            character->setIsDead(true);
        }

    //cout<<this->getCurrentHealth()<<" "<<character->getCurrentHealth()<<'\n';
}

pair <int,int> Enemy::getTiles(Vector2f characterPosition) const
{
    pair <int,int> tiles;

    tiles.first = characterPosition.y / this->gridSize;
    tiles.second = characterPosition.x / this->gridSize;

    return tiles;
}

void Enemy::moveToTile(pair <int,int> tiles)
{
    pair <int,int> currentTiles = this->getTiles(this->getCharacterPosition());

    /*
    UP -> 1
    LEFT -> 2
    DOWN -> 3
    RIGHT -> 4
    */

    // if distance <= enemy radius for attack then tiles = -1
    // also, to solve problem with radius attack -> we add charactersize to radius and then we add a bit more after

    if(this->getEuclidianDistance(this->getPlayerPosition(),this->getCharacterPosition()) <= this->getRadiusAttack())
        {
            tiles.first = -1;
        }

    if(tiles.first!=-1)
        {
            int previousDirection = this->getDirection();

            int newDirection = previousDirection;

            if(currentTiles.first > tiles.first) // goes up
                newDirection = 1;

            if(currentTiles.first < tiles.first) // goes down
                newDirection = 3;

            if(currentTiles.second > tiles.second) // goes left
                newDirection = 2;

            if(currentTiles.second < tiles.second) // goes right
                newDirection = 4;

            if(this->getActionInProgress() == false)
                {
                    if(newDirection != previousDirection)
                        this->setDidChangeDirection(true);
                    this->setIsMoving(true);
                    this->setDirection(newDirection);
                }

        }
    else // reached destination
        {
            if(!this->isInRadius()) // if the enemy lost sight of the player, it returns to the spawn point
                {
                    this->revive();
                }
            else
                {
                    /* attack and knockback animation */

                    // if can attack (variable canAttack -true/false) then attack with 1 of the available skillsets, otherwise is knockback damage

                    this->setActionInProgress(true);
                    this->setIsAttacking(true);
                }

            this->setIsMoving(false);
        }
}

void Enemy::chasePlayer()
{
    Vector2f destination;

    if(this->isInRadius())
        destination = this->getPlayerPosition();
    else
        destination = this->getLastKnownPosition();

    pair <int,int> tiles = this->graph.BFS(destination,this->getCharacterPosition());

    this->moveToTile(tiles);
}

float Enemy::getEuclidianDistance(Vector2f a, Vector2f b)
{
    return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2) * 1.0);
}

bool Enemy::isInRadius()
{
    Vector2f a = this->getPlayerPosition();
    Vector2f b = this->getCharacterPosition();

    // euclidian distance formula
    float distance = this->getEuclidianDistance(a,b);

    int radiusCombat = this->getRadiusCombat();
    if(this->getCombatMode() == true)
        radiusCombat*=2;

    if(distance <= radiusCombat)
        return true;

    return false;
}

// checking distance between player and enemy
void Enemy::checkDistance()
{
    if(this->getCombatMode() == false)
        {
            if(this->isInRadius())
                {
                    this->setCombatMode(true);

                    this->setLastKnownPosition(this->getPlayerPosition());
                }
        }
    else
        {
            if(this->isInRadius())
                {
                    this->setLastKnownPosition(this->getPlayerPosition());
                }
        }
}

// if out of idle radius, return, othwerise, get a random direction
int Enemy::newDirectionIdleMove()
{
    // can modify instead of %4 to get a variable containing number of directions (there could also be 2 directions - platformer and 8 directions - top down)
    int newDirection = rand()%4+1;

    /*
    UP -> 1
    LEFT -> 2
    DOWN -> 3
    RIGHT -> 4
    */

    Vector2f a = this->getCharacterPosition();
    Vector2f b = this->getSpawnPoint();

    float distance = this->getEuclidianDistance(a,b);

    // if out of idle radius, return
    if(distance > this->getRadiusIdle())
        {
            int previousDirection = this->getDirection();

            if(previousDirection==3)
                newDirection = 1;
            if(previousDirection==1)
                newDirection = 3;
            if(previousDirection==4)
                newDirection = 2;
            if(previousDirection==2)
                newDirection = 4;
        }

    return newDirection;
}

void Enemy::idleMove(float timer)
{
    this->increaseTimeMoveIdle(timer);

    if(this->getIsMoving() == false)
        {
            this->setIsIdle(true);
            this->setDidChangeDirection(true); // to reset the animation
        }
    else
        this->setIsIdle(false);

    if(this->getTimeMoveIdle() > this->getTimeMoveIdleReset())
        {
            this->resetTimeMoveIdle();

            int newDirection = newDirectionIdleMove();

            this->setDidChangeDirection(true); // to reset the animation
            this->setDirection(newDirection);
            this->setIsMoving(true);
        }

    else if(this->getTimeMoveIdle() > this->getTimeMoveIdleReset() / 2.0f)
        {
            this->setIsMoving(false);
        }
}

// behaviour of enemy
void Enemy::AI(float timer)
{
    if(this->getIsDead() == true)
        return;

    this->setDidChangeDirection(false);

    this->checkDistance();

    // IDLE mode in his spawn point
    if(this->getCombatMode()==false)
        {
            this->idleMove(timer);
        }
    else
        {
            this->setIsMoving(false);
            this->setIsIdle(false);

            this->chasePlayer();
        }
}

void Enemy::getGraph(Map *map)
{
    vector < vector < pair<int,int> > > newGraph = map->returnGraph(this->getCharacterSize());

    this->graph.setGraph(newGraph);

    Vector2f characterTile;

    characterTile.x = (int)this->getCharacterSize().x / map->getGridSize();
    characterTile.y = (int)this->getCharacterSize().y / map->getGridSize();

    pair <int,int> sizes = map->getArraySizes();
    this->graph.setLinesCount(sizes.first - characterTile.y + 1);
    this->graph.setColumnsCount(sizes.second - characterTile.x + 1);
    this->graph.setGridSize(map->getGridSize());

    this->gridSize = map->getGridSize();
}

// constructors
Enemy::Enemy(string fileName):Character(fileName)
{
    this->setCombatMode(false);
    this->resetTimeMoveIdle();
    this->setTimeMoveIdleReset(2.0f);

    this->setRadiusCombat(200.0f);
    this->setRadiusIdle(250.0f);

    // i will get these values from the json file
    this->setIsRespawnable(true);
    this->setRespawnTime(10.0);
}

// destructors
Enemy::~Enemy()
{

}

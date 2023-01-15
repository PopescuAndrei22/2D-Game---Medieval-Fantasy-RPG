#include "Enemy.h"

// getters
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

Vector2f Enemy::getPlayerPosition() const
{
    return this->playerPosition;
}

Vector2f Enemy::getSpawnPoint() const
{
    return this->spawnPoint;
}

// setters
void Enemy::setPlayerPosition(Vector2f playerPosition)
{
    this->playerPosition = playerPosition;
}

void Enemy::setSpawnPoint(Vector2f spawnPoint)
{
    this->spawnPoint = spawnPoint;
}

void Enemy::setCombatMode(bool combatMode)
{
    this->combatMode = combatMode;
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
    pair <int,int> playerTiles = this->getTiles(this->getPlayerPosition());

    /*
    UP -> 1
    LEFT -> 2
    DOWN -> 3
    RIGHT -> 4
    */

    //cout<<currentTiles.first<<" "<<currentTiles.second<<" ----> "<<tiles.first<<" "<<tiles.second<<'\n';

    if(currentTiles != playerTiles && tiles.first!=-1)
        {
            this->setIsMoving(true);

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

            if(newDirection != previousDirection)
                this->setDidChangeDirection(true);

            this->setDirection(newDirection);

        }
    else
        {
            cout<<"Inamicul a ajuns la jucator"<<'\n';
            this->setIsMoving(false);
        }
}

void Enemy::chasePlayer()
{
    pair <int,int> tiles = this->graph.BFS(this->getPlayerPosition(),this->getCharacterPosition());

    this->moveToTile(tiles);
}

float Enemy::getEuclidianDistance(Vector2f a, Vector2f b)
{
    return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2) * 1.0);
}

// checking distance between player and enemy
void Enemy::checkDistance()
{
    Vector2f a = this->getPlayerPosition();
    Vector2f b = this->getCharacterPosition();

    // euclidian distance formula
    float distance = this->getEuclidianDistance(a,b);

    if(this->getCombatMode() == false)
        {
            if(distance <= this->getRadiusCombat())
                {
                    this->setCombatMode(true);
                }
        }
    else
        {
            if(distance > this->getRadiusCombat())
                {
                    this->setCombatMode(false);
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
    this->setDidChangeDirection(false);
    this->chasePlayer();

    /*
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

            // action here
            this->chasePlayer();
        }
    */
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

    this->setSpawnPoint(this->getCharacterPosition());
}

// destructors
Enemy::~Enemy()
{

}

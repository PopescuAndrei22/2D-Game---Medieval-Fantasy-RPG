#include "Enemy.h"

/* getters */
std::string Enemy::getCurrentState() const
{
    return this->currentState;
}

std::string Enemy::getEnemyName() const
{
    return this->enemyName;
}

float Enemy::getRadiusIdle() const
{
    return this->radiusIdle;
}

float Enemy::getRadiusCombat() const
{
    return this->radiusCombat;
}

float Enemy::getTimerIdle() const
{
    return this->timerIdle;
}

float Enemy::getTimerIdleReset() const
{
    return this->timerIdleReset;
}

sf::Vector2f Enemy::getPlayerPosition() const
{
    return this->playerPosition;
}

sf::Vector2f Enemy::getLastKnownPosition() const
{
    return this->lastKnownPosition;
}

bool Enemy::getIsPlayerDead() const
{
    return this->isPlayerDead;
}

/* setters */
void Enemy::setCurrentState(std::string currentState)
{
    this->currentState = currentState;
}

void Enemy::setEnemyName(std::string enemyName)
{
    this->enemyName = enemyName;
}

void Enemy::setRadiusIdle(float radiusIdle)
{
    this->radiusIdle = radiusIdle;
}

void Enemy::setRadiusCombat(float radiusCombat)
{
    this->radiusCombat = radiusCombat;
}

void Enemy::setTimerIdle(float timerIdle)
{
    this->timerIdle = timerIdle;
}

void Enemy::setTimerIdleReset(float timerIdleReset)
{
    this->timerIdleReset = timerIdleReset;
}

void Enemy::setPlayerPosition(sf::Vector2f playerPosition)
{
    this->playerPosition = playerPosition;
}

void Enemy::setLastKnownPosition(sf::Vector2f lastKnownPosition)
{
    this->lastKnownPosition = lastKnownPosition;
}

void Enemy::setIsPlayerDead(bool isPlayerDead)
{
    this->isPlayerDead = isPlayerDead;
}

/* class methods */
void Enemy::getGraph(Map &currentMap)
{
    std::vector < std::vector < std::pair<int,int> > > newGraph = currentMap.returnGraph(this->getCharacterSize());

    this->graph.setGraph(newGraph);

    sf::Vector2f characterTile;

    characterTile.x = (int)this->getCharacterSize().x / currentMap.getGridSize();
    characterTile.y = (int)this->getCharacterSize().y / currentMap.getGridSize();

    std::pair <int,int> sizes = currentMap.getArraySizes();
    this->graph.setLinesCount(sizes.first - characterTile.y + 1);
    this->graph.setColumnsCount(sizes.second - characterTile.x + 1);
    this->graph.setGridSize(currentMap.getGridSize());
}

std::pair<int,int> Enemy::getNextStep(sf::Vector2f start, sf::Vector2f stop)
{
    return this->graph.BFS(start,stop);
}

std::pair<int,int> Enemy::getEnemyTiles()
{
    std::pair <int,int> tiles;

    tiles.first = this->getCharacterPosition().y / this->graph.getGridSize();
    tiles.second = this->getCharacterPosition().x / this->graph.getGridSize();

    return tiles;
}

void Enemy::revive()
{
    this->Character::revive();

    this->setCurrentState("passive");

    this->setTimerIdle(0.0f);

    this->setPlayerPosition(sf::Vector2f(0,0));
    this->setLastKnownPosition(sf::Vector2f(0,0));
}

void Enemy::setValues(std::string fileName)
{
    this->Character::setValues(fileName);

    std::string pathValues = "values/characters/" + fileName + ".json";
    std::ifstream file(pathValues);
    nlohmann::json data = nlohmann::json::parse(file);

    auto enemyValues = data.at("enemyValues");

    try
        {
            this->setRadiusIdle((float)enemyValues["radiusIdle"]);
            this->setRadiusCombat((float)enemyValues["radiusCombat"]);

        }
    catch(const nlohmann::json::exception& e)
        {
            std::cout << e.what() << '\n';
        }

    this->setIsPlayerDead(false);
    this->setEnemyName(fileName);

    file.close();
}

/* constructors */
Enemy::Enemy()
{
    this->setTimerIdle(0.0f);
    this->setTimerIdleReset(2.5f);
}

/* destructors */
Enemy::~Enemy()
{

}

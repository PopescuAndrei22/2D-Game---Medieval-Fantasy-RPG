#include "Map.h"

// getters
std::pair <int,int> Map::getArraySizes() const
{
    std::pair <int,int> sizes;
    sizes.first = this->lines;
    sizes.second = this->columns;

    return sizes;
}

sf::Vector2f Map::getMapSize() const
{
    return this->mapSize;
}

sf::Sprite Map::getMap() const
{
    return this->sprite;
}

std::vector <int> Map::getTileArray() const
{
    return this->tileArray;
}

int Map::getGridSize() const
{
    return this->gridSize;
}

int Map::sum(int i1, int j1, int i2, int j2)
{

    /*
        //cout << S[ij][jj] - S[is-1][jj] - S[ij][js-1] + S[is-1][js-1];

        int totalSum = this->sumArray[i2][j2] - this->sumArray[i1-1][j2] - this->sumArray[i2][j1-1] + this->sumArray[i1][j2-1];

        if(totalSum > 0)
            return 1;

        return 0; */

    for(int i=i1; i<=i2; i++)
        {
            for(int j=j1; j<=j2; j++)
                {
                    if(this->collisionArray[i][j]==1)
                        return 1;
                }
        }
    return 0;
}

bool Map::isCollision(sf::Vector2f position, sf::Vector2f characterSize)
{
    int xLeft = position.x / this->gridSize;
    int xRight = (position.x + characterSize.x) / this->gridSize;

    int yUp = position.y / this->gridSize;
    int yDown = (position.y + characterSize.y) / this->gridSize;

    // +1 if number%this->gridSize != 0
    // data validation for xLeft, xRight, yUp, yDown, what if gridSize is 0 or the values exceeds the map, or values are below 0

    /*
    this works well now but is going to be bad for very high textures ( ex huge bosses )
    */

    // i could use partial sums instead
    // must check why it is < and not <=

    return this->sum(yUp,xLeft,yDown-1,xRight-1);
}

void Map::deleteCollisionArray()
{
    for(int i = 0; i < this->lines; i++)
        {
            if(this->columns > 0)
                delete[] this->collisionArray[i];
        }

    if(this->lines > 0)
        delete[] this->collisionArray;

    for(int i = 0; i < this->lines; i++)
        {
            if(this->columns > 0)
                delete[] this->sumArray[i];
        }

    if(this->lines > 0)
        delete[] this->sumArray;

    this->lines = this->columns = 0;
}

void Map::updateCollisionArray()
{
    this->deleteCollisionArray();

    this->columns = this->mapSize.x / this->gridSize; // number of grids horizontally
    this->lines = this->mapSize.y / this->gridSize; // number of grids vertically

    this->collisionArray = new int*[this->lines];
    this->sumArray = new int*[this->lines];

    std::vector <int> arr = this->getTileArray();

    for(int i=0; i< this->lines; i++)
        {
            this->collisionArray[i] = new int[this->columns];

            for(int j=0; j< this->columns; j++)
                {
                    this->collisionArray[i][j] = arr[i*(this->columns)+j];
                }
        }

    for(int i=0; i< this->lines; i++)
        {
            this->sumArray[i] = new int[this->columns];

            for(int j=0; j< this->columns; j++)
                {
                    this->sumArray[i][j] = this->collisionArray[i][j];

                    if(i >= 1)
                        this->sumArray[i][j] += this->sumArray[i-1][j];

                    if(j >= 1)
                        this->sumArray[i][j] += this->sumArray[i][j-1];

                    if(i >= 1 && j >= 1)
                        this->sumArray[i][j] -= this->sumArray[i-1][j-1];

                }
        }
}

std::vector < std::vector <std::pair<int,int> > > Map::returnGraph(sf::Vector2f characterSize)
{
    std::vector < std::vector <std::pair<int,int> > > graph;

    graph.resize(lines*columns+5);

    int x = characterSize.x / this->gridSize;
    int y = characterSize.y / this->gridSize;

    // to modify and make edges just between nodes that aren't collisions
    for(int i=0; i<this->lines - y; i++)
        {
            for(int j=0; j<this->columns - x; j++)
                {
                    int valueCurrentNode = this->sum(i,j,i+y-1,j+x-1);
                    int valueRightNode = this->sum(i,j+1,i+y-1,j+x);
                    int valueDownNode = this->sum(i+1,j,i+y,j+x-1);

                    int currentNode = (this->columns-x+1) * i + j + 1;
                    int rightNode = currentNode + 1;
                    int downNode = currentNode + (this->columns-x+1);

                    graph[currentNode].push_back(std::make_pair(rightNode,std::max(valueCurrentNode,valueRightNode)));
                    graph[rightNode].push_back(std::make_pair(currentNode,std::max(valueCurrentNode,valueRightNode)));

                    graph[currentNode].push_back(std::make_pair(downNode,std::max(valueCurrentNode,valueDownNode)));
                    graph[downNode].push_back(std::make_pair(currentNode,std::max(valueCurrentNode,valueDownNode)));
                }
        }

    return graph;
}

// loading information about the current level from files
void Map::getMapDetails(std::string mapName, std::string levelName)
{
    // clear the tile array from the previous level
    this->tileArray.clear();

    this->enemyDetails.clear();
    this->transparentObstacleDetails.clear();
    this->animatedObjectDetails.clear();

    this->lines = this->columns = 0;

    std::string pathValues = "values/maps/" + mapName + "/levels/" + levelName + ".json";
    std::ifstream file(pathValues);
    nlohmann::json data = nlohmann::json::parse(file);

    // to be careful with extensions
    std::string pathImage = "sprites/maps/" + mapName + "/" + levelName + "/" + levelName + ".png";

    this->texture.loadFromFile(pathImage);
    this->sprite.setTexture(texture);

    try
        {
            // to change this code, i could search after "identifier", possible bugs here
            this->mapSize.x = (data["levels"][0]["pxWid"].is_null()?0:(float)data["levels"][0]["pxWid"]);
            this->mapSize.y = (data["levels"][0]["pxHei"].is_null()?0:(float)data["levels"][0]["pxHei"]);

            this->gridSize = (data["defs"]["layers"][0]["gridSize"].is_null()?0:(int)data["defs"]["layers"][0]["gridSize"]);

            if(!data["levels"][0]["layerInstances"].is_null())
                {
                    for(unsigned index=0; index<data["levels"][0]["layerInstances"].size(); index++)
                        {
                            if(data["levels"][0]["layerInstances"][index]["__identifier"] == "IntGrid") // getting collision array
                                {
                                    this->gridSize = (data["defs"]["layers"][index]["gridSize"].is_null()?0:(int)data["defs"]["layers"][index]["gridSize"]);

                                    if(!data["levels"][0]["layerInstances"][index]["intGridCsv"].is_null())
                                        {
                                            for(unsigned i=0; i<data["levels"][0]["layerInstances"][index]["intGridCsv"].size(); i++)
                                                {
                                                    this->tileArray.push_back(data["levels"][0]["layerInstances"][index]["intGridCsv"][i]);
                                                }
                                        }
                                }
                            else if(data["levels"][0]["layerInstances"][index]["__identifier"] == "Player") // getting player position
                                {
                                    this->playerPosition.x = (float)data["levels"][0]["layerInstances"][index]["entityInstances"][0]["px"][0];
                                    this->playerPosition.y = (float)data["levels"][0]["layerInstances"][index]["entityInstances"][0]["px"][1];
                                }
                            else if(data["levels"][0]["layerInstances"][index]["__identifier"] == "Enemies") // getting enemies positions
                                {
                                    sf::Vector2f enemyPosition;

                                    for(unsigned indexEnemy = 0; indexEnemy < data["levels"][0]["layerInstances"][index]["entityInstances"].size(); indexEnemy++)
                                        {
                                            enemyPosition.x = data["levels"][0]["layerInstances"][index]["entityInstances"][indexEnemy]["px"][0];
                                            enemyPosition.y = data["levels"][0]["layerInstances"][index]["entityInstances"][indexEnemy]["px"][1];

                                            std::string enemySpriteName = data["levels"][0]["layerInstances"][index]["entityInstances"][indexEnemy]["__identifier"];
                                            enemySpriteName[0] += 32;

                                            std::pair < sf::Vector2f, std::string > enemyDetailsPair;
                                            enemyDetailsPair.first = enemyPosition;
                                            enemyDetailsPair.second = enemySpriteName;

                                            this->enemyDetails.push_back(enemyDetailsPair);
                                        }
                                }
                            else if(data["levels"][0]["layerInstances"][index]["__identifier"] == "TransparentObstacles")
                                {
                                    sf::Vector2f transparentObstaclePosition;

                                    for(unsigned indexTransparentObstacle = 0; indexTransparentObstacle < data["levels"][0]["layerInstances"][index]["entityInstances"].size(); indexTransparentObstacle++)
                                        {
                                            transparentObstaclePosition.x = data["levels"][0]["layerInstances"][index]["entityInstances"][indexTransparentObstacle]["px"][0];
                                            transparentObstaclePosition.y = data["levels"][0]["layerInstances"][index]["entityInstances"][indexTransparentObstacle]["px"][1];

                                            std::string transparentObstacleName = data["levels"][0]["layerInstances"][index]["entityInstances"][indexTransparentObstacle]["__identifier"];
                                            transparentObstacleName[0] += 32;

                                            std::pair < sf::Vector2f, std::string > transparentObstaclePair;

                                            transparentObstaclePair.first = transparentObstaclePosition;
                                            transparentObstaclePair.second = transparentObstacleName;

                                            this->transparentObstacleDetails.push_back(transparentObstaclePair);
                                        }
                                }
                            else if(data["levels"][0]["layerInstances"][index]["__identifier"] == "AnimatedObjects")
                                {
                                    sf::Vector2f animatedObjectPosition;

                                    for(unsigned indexAnimatedObject = 0; indexAnimatedObject < data["levels"][0]["layerInstances"][index]["entityInstances"].size(); indexAnimatedObject++)
                                        {
                                            animatedObjectPosition.x = data["levels"][0]["layerInstances"][index]["entityInstances"][indexAnimatedObject]["px"][0];
                                            animatedObjectPosition.y = data["levels"][0]["layerInstances"][index]["entityInstances"][indexAnimatedObject]["px"][1];

                                            std::string animatedObjectName = data["levels"][0]["layerInstances"][index]["entityInstances"][indexAnimatedObject]["__identifier"];
                                            animatedObjectName[0] += 32;

                                            std::pair < sf::Vector2f, std::string > animatedObjectPair;

                                            animatedObjectPair.first = animatedObjectPosition;
                                            animatedObjectPair.second = animatedObjectName;

                                            this->animatedObjectDetails.push_back(animatedObjectPair);
                                        }
                                }
                            else if(data["levels"][0]["layerInstances"][index]["__identifier"] == "Portals")
                                {
                                    sf::Vector2f portal;

                                    for(unsigned indexPortals = 0; indexPortals < data["levels"][0]["layerInstances"][index]["entityInstances"].size(); indexPortals++)
                                        {
                                            std::string portalName = data["levels"][0]["layerInstances"][index]["entityInstances"][indexPortals]["__identifier"];

                                            portal.x = data["levels"][0]["layerInstances"][index]["entityInstances"][indexPortals]["px"][0];
                                            portal.y = data["levels"][0]["layerInstances"][index]["entityInstances"][indexPortals]["px"][1];

                                            if(portalName == "PortalStart")
                                                this->portalStart = portal;
                                            else
                                                this->portalEnd = portal;
                                        }
                                }
                        }
                }

            this->updateCollisionArray();

        }
    catch(const nlohmann::json::exception& e)
        {
            std::cout << e.what() << '\n';
        }

    file.close();
}

// get info about current level such as player positions, enemies, obstacles, entities etc.
sf::Vector2f Map::getPlayerPosition() const
{
    return this->playerPosition;
}

std::vector < std::pair<sf::Vector2f,std::string> > Map::getEnemyDetails()
{
    return this->enemyDetails;
}

std::vector < std::pair<sf::Vector2f,std::string> > Map::getTransparentObstacleDetails()
{
    return this->transparentObstacleDetails;
}

std::vector < std::pair<sf::Vector2f,std::string> > Map::getAnimatedObjectDetails()
{
    return this->animatedObjectDetails;
}

sf::Vector2f Map::getPortalStart() const
{
    return this->portalStart;
}

sf::Vector2f Map::getPortalEnd() const
{
    return this->portalEnd;
}

// constructors
Map::Map()
{

}

// destructors
Map::~Map()
{
    this->deleteCollisionArray();
    this->tileArray.clear();
}

#include "Map.h"

// getters
pair <int,int> Map::getArraySizes() const
{
    pair <int,int> sizes;
    sizes.first = this->lines;
    sizes.second = this->columns;

    return sizes;
}

Vector2f Map::getMapSize() const
{
    return this->mapSize;
}

Sprite Map::getMap() const
{
    return this->sprite;
}

vector <int> Map::getTileArray() const
{
    return this->tileArray;
}

int Map::getGridSize() const
{
    return this->gridSize;
}

int Map::sum(int i1, int j1, int i2, int j2)
{
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

bool Map::isCollision(Vector2f position, Vector2f characterSize)
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
    for(int i=yUp; i<yDown; i++)
        {
            for(int j=xLeft; j<xRight; j++)
                {
                    if(this->collisionArray[i][j] == 1)
                        {
                            return true;
                        }
                }
        }

    return false;
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

    this->lines = this->columns = 0;
}

void Map::updateCollisionArray()
{
    this->deleteCollisionArray();

    this->columns = this->mapSize.x / this->gridSize; // number of grids horizontally
    this->lines = this->mapSize.y / this->gridSize; // number of grids vertically

    this->collisionArray = new int*[this->lines];

    vector <int> arr = this->getTileArray();

    for(int i=0; i< this->lines; i++)
        {
            this->collisionArray[i] = new int[this->columns];

            for(int j=0; j< this->columns; j++)
                {
                    this->collisionArray[i][j] = arr[i*(this->columns)+j];
                }
        }
}

vector < vector <pair<int,int> > > Map::returnGraph(Vector2f characterSize)
{
    vector < vector <pair<int,int> > > graph;

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

                    graph[currentNode].push_back(make_pair(rightNode,max(valueCurrentNode,valueRightNode)));
                    graph[rightNode].push_back(make_pair(currentNode,max(valueCurrentNode,valueRightNode)));

                    graph[currentNode].push_back(make_pair(downNode,max(valueCurrentNode,valueDownNode)));
                    graph[downNode].push_back(make_pair(currentNode,max(valueCurrentNode,valueDownNode)));
                }
        }

    return graph;
}

// loading information about the current level from files
void Map::getMapDetails(string mapName, string levelName)
{
    // clear the tile array from the previous level
    this->tileArray.clear();

    string pathValues = "values/maps/" + mapName + "/" + levelName + ".json";
    ifstream file(pathValues);
    nlohmann::json data = nlohmann::json::parse(file);

    // to be careful with extensions
    string pathImage = "sprites/maps/" + mapName + "/" + levelName + ".png";
    this->texture.loadFromFile(pathImage);
    this->sprite.setTexture(texture);

    // to change this code, i could search after "identifier", possible bugs here
    this->mapSize.x = (data["levels"][0]["pxWid"].is_null()?0:(float)data["levels"][0]["pxWid"]);
    this->mapSize.y = (data["levels"][0]["pxHei"].is_null()?0:(float)data["levels"][0]["pxHei"]);

    this->gridSize = (data["defs"]["layers"][0]["gridSize"].is_null()?0:(int)data["defs"]["layers"][0]["gridSize"]);

    if(!data["levels"][0]["layerInstances"][0]["intGridCsv"].is_null())
        {
            for(unsigned i=0; i<data["levels"][0]["layerInstances"][0]["intGridCsv"].size(); i++)
                {
                    this->tileArray.push_back(data["levels"][0]["layerInstances"][0]["intGridCsv"][i]);
                }
        }

    this->updateCollisionArray();
}

// constructors
Map::Map(string mapName, string levelName)
{
    // to implement save file with info such as current map and position/progress of the character

    this->lines = this->columns = 0;
    getMapDetails(mapName,levelName);
}

// destructors
Map::~Map()
{
    this->deleteCollisionArray();
    this->tileArray.clear();
}

#include "Map.h"

// getters
Vector2f Map::getMapSize() const
{
    return this->mapSize;
}

Sprite Map::getMap() const
{
    return this->sprite;
}

vector <int> Map::getCollisionArray() const
{
    return this->collisionArray;
}

int Map::getGridSize() const
{
    return this->gridSize;
}

// loading information about the current level from files
void Map::getMapDetails(string mapName, string levelName)
{
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
        for(unsigned i=0;i<data["levels"][0]["layerInstances"][0]["intGridCsv"].size();i++)
        {
            this->collisionArray.push_back(data["levels"][0]["layerInstances"][0]["intGridCsv"][i]);
        }
    }
}

// constructors
Map::Map(string mapName, string levelName)
{
    // to implement save file with info such as current map and position/progress of the character

    getMapDetails(mapName,levelName);
}

// destructors
Map::~Map()
{
    this->collisionArray.clear();
}

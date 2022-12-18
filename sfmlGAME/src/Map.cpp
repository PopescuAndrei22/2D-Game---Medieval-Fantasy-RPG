#include "Map.h"

Vector2f Map::getMapSize() const
{
    return this->mapSize;
}

int Map::getGridSize() const
{
    return this->gridSize;
}

void Map::getMapDetails(string mapName, string levelName)
{
    string pathValues = "values/maps/" + mapName + "/" + levelName + ".json";
    ifstream file(pathValues);
    nlohmann::json data = nlohmann::json::parse(file);

    // sa am grija la extensii
    string pathImage = "sprites/maps/" + mapName + "/" + levelName + ".png";
    this->texture.loadFromFile(pathImage);
    this->sprite.setTexture(texture);

    // sa modific gen sa caut dupa "identifier" ca sa fiu sigur ca e totul ok, posibile bug-uri aici

    this->mapSize.x = (data["levels"][0]["pxWid"].is_null()?0:(float)data["levels"][0]["pxWid"]);
    this->mapSize.y = (data["levels"][0]["pxHei"].is_null()?0:(float)data["levels"][0]["pxHei"]);

    this->gridSize = (data["defs"]["layers"][0]["gridSize"].is_null()?0:(int)data["defs"]["layers"][0]["gridSize"]);

    // ar trebui sa fac un loading screen pt asta
    if(!data["levels"][0]["layerInstances"][0]["intGridCsv"].is_null())
    {
        for(unsigned i=0;i<data["levels"][0]["layerInstances"][0]["intGridCsv"].size();i++)
        {
            this->collisionArray.push_back(data["levels"][0]["layerInstances"][0]["intGridCsv"][i]);
        }
    }
}

Sprite Map::getMap() const
{
    return this->sprite;
}

vector <int> Map::getCollisionArray() const
{
    return this->collisionArray;
}

Map::Map(string mapName, string levelName)
{
    // sau pot face fisier de save si iau de acolo informatiile gen mapa la care am ramas si pozitia caracterului, progresul etc.
    // desi e posibil sa fac jocul mai mult roguelike, ramane de vazut

    getMapDetails(mapName,levelName);
}

Map::~Map()
{
    this->collisionArray.clear();
}

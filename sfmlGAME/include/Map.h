#ifndef MAP_H
#define MAP_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <vector>

using namespace std;
using namespace sf;

class Map
{
    public:

        Sprite getMap() const;
        void getMapDetails(string,string);
        Vector2f getMapSize() const;
        int getGridSize() const;
        vector <int> getCollisionArray() const;

        Map(string,string);
        ~Map();

    private:
        Texture texture;
        Sprite sprite;

        Vector2f mapSize;
        int gridSize;

        pair <int,int> dimensions; // number of grids horizontally and vertically for the collision array

        vector <int> collisionArray;
};

#endif // MAP_H

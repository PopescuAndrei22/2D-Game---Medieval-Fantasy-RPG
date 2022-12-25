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
        // getters
        Sprite getMap() const;
        Vector2f getMapSize() const;
        int getGridSize() const;
        vector <int> getCollisionArray() const;

        void getMapDetails(string,string); // loads the map/level and obtain information about it

        // constructors
        Map(string,string);

        // destructors
        ~Map();

    private:
        Texture texture;
        Sprite sprite;

        Vector2f mapSize;
        int gridSize; // size of a grid (helps us for array collision)

        vector <int> collisionArray; // tells us which grids are occupied
};

#endif // MAP_H

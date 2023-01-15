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
        pair<int,int> getArraySizes() const;
        vector <int> getTileArray() const;

        void getMapDetails(string,string); // loads the map and obtain information about it

        void updateCollisionArray(); // updating the collision array

        void deleteCollisionArray();

        // i will implement partial sums
        int sum(int,int,int,int);

        // checking if the given position is collision for a character
        bool isCollision(Vector2f,Vector2f);

        vector < vector<pair<int,int>> > returnGraph(Vector2f); // return the collision array as a graph, receiving the size of the character as parameter

        // constructors
        Map(string,string);

        // destructors
        ~Map();

    private:
        Texture texture;
        Sprite sprite;

        Vector2f mapSize;
        int gridSize; // size of a grid (helps us for array collision)

        vector <int> tileArray; // tells us which tiles are occupied

        int** collisionArray;

        int columns,lines; // sizes of the matrix
};

#endif // MAP_H

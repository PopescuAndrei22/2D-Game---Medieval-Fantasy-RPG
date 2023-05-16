#ifndef MAP_H
#define MAP_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <vector>
#include <algorithm>

class Map
{
    public:
        // getters
        sf::Sprite getMap() const;
        sf::Vector2f getMapSize() const;
        int getGridSize() const;
        std::pair<int,int> getArraySizes() const;
        std::vector <int> getTileArray() const;

        void getMapDetails(std::string,std::string); // loads the map and obtain information about it

        void updateCollisionArray(); // updating the collision array

        void deleteCollisionArray();

        // i will implement partial sums
        int sum(int,int,int,int);

        // checking if the given position is collision for a character
        bool isCollision(sf::Vector2f,sf::Vector2f);

        std::vector < std::vector<std::pair<int,int>> > returnGraph(sf::Vector2f); // return the collision array as a graph, receiving the size of the character as parameter

        void updateCurrentLevel(std::string,std::string);

        // get info about current level such as player positions, enemies, obstacles, entities etc.
        sf::Vector2f getPlayerPosition() const;
        std::vector < std::pair<sf::Vector2f,std::string> > getEnemyDetails();
        std::vector < std::pair<sf::Vector2f,std::string> > getBossDetails();
        std::vector < std::pair<sf::Vector2f,std::string> > getTransparentObstacleDetails();
        std::vector < std::pair<sf::Vector2f,std::string> > getAnimatedObjectDetails();

        sf::Vector2f getPortalStart() const;
        sf::Vector2f getPortalEnd() const;

        // constructors
        Map();

        // destructors
        ~Map();

    private:
        sf::Texture texture;
        sf::Sprite sprite;

        sf::Vector2f mapSize;
        int gridSize; // size of a grid (helps us for array collision)

        std::vector <int> tileArray; // tells us which tiles are occupied

        int** collisionArray;

        int** sumArray;

        int columns,lines; // sizes of the matrix

        // to set and use these variables
        std::string mapName;
        std::string levelName;

        // informations about the current level, don't forget to clear the vectors
        sf::Vector2f playerPosition;
        std::vector < std::pair<sf::Vector2f,std::string> > enemyDetails;
        std::vector < std::pair<sf::Vector2f,std::string> > bossDetails;
        std::vector < std::pair<sf::Vector2f,std::string> > transparentObstacleDetails;
        std::vector < std::pair<sf::Vector2f,std::string> > animatedObjectDetails;

        sf::Vector2f portalStart;
        sf::Vector2f portalEnd;
};
#endif // MAP_H

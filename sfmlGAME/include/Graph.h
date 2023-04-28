#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <vector>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <cstring>
#include <queue>

class Graph
{
    public:
        // setters
        void setLinesCount(int);
        void setColumnsCount(int);
        void setGridSize(int);

        // getters
        int getLinesCount() const;
        int getColumnsCount() const;
        int getGridSize() const;

        // delete graph
        void deleteGraph();

        // updating graph
        void setGraph(std::vector < std::vector <std::pair<int,int>> >);

        // find shortest path
        std::pair<int,int> BFS(sf::Vector2f, sf::Vector2f);

        int getNode(sf::Vector2f); // get the node based on the character's position

        std::pair <int,int> getTiles(int); // get the tile positions based on the node

        // constructors
        Graph();

        // destructors
        ~Graph();

    private:

        std::vector < std::vector <std::pair<int,int>> > graph;

        // these values will help us to transform the nodes in matrix positions and vice versa
        int lines,columns;
        int gridSize;

};

#endif // GRAPH_H

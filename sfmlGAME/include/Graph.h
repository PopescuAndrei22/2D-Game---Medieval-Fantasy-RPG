#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <vector>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <cstring>
#include <queue>

using namespace std;
using namespace sf;

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
        void setGraph(vector < vector <pair<int,int>> >);

        // find shortest path
        pair<int,int> BFS(Vector2f, Vector2f);

        int getNode(Vector2f); // get the node based on the character's position

        pair <int,int> getTiles(int); // get the tile positions based on the node

        // constructors
        Graph();

        // destructors
        ~Graph();

    private:

        vector < vector <pair<int,int>> > graph;

        // these values will help us to transform the nodes in matrix positions and vice versa
        int lines,columns;
        int gridSize;

};

#endif // GRAPH_H

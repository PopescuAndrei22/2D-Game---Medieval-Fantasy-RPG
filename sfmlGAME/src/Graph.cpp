#include "Graph.h"

// setters
void Graph::setLinesCount(int lines)
{
    this->lines = lines;
}

void Graph::setColumnsCount(int columns)
{
    this->columns = columns;
}

void Graph::setGridSize(int gridSize)
{
    this->gridSize = gridSize;
}

// getters
int Graph::getLinesCount() const
{
    return this->lines;
}

int Graph::getColumnsCount() const
{
    return this->columns;
}

int Graph::getGridSize() const
{
    return this->gridSize;
}

// get node based on character's position
int Graph::getNode(Vector2f characterPosition)
{
    int x = characterPosition.x / this->gridSize;
    int y = characterPosition.y / this->gridSize;

    int node = y*(columns) + x + 1;

    return node;
}

pair <int,int> Graph::getTiles(int node)
{
    pair <int,int> tile;

    if(node<=0)
        {
            tile.first = tile.second = -1;
            return tile;
        }

    tile.first = node / this->columns;

    tile.second = node % this->columns;
    if(node % this->columns != 0)
        tile.second--;
    else
        {
            tile.first --;

            tile.second = this->columns - 1;
        }

    return tile;
}

// find shortest path
pair<int,int> Graph::BFS(Vector2f startPosition, Vector2f stopPosition)
{
    int Dist[this->graph.size()+5];

    memset(Dist,0,sizeof(Dist));

    queue < int > Q;

    Q.push(getNode(startPosition));
    Dist[getNode(startPosition)] == 1;

    int stopNode = getNode(stopPosition);

    while(!Q.empty())
        {
            int currentNode = Q.front();

            /*
            if(currentNode == stopNode)
                break;
            */

            Q.pop();

            for(int i=0; i<this->graph[currentNode].size(); i++)
                {
                    int nextNode = this->graph[currentNode][i].first;
                    int value = this->graph[currentNode][i].second;

                    // value = 0 means there is an edge between the nodes ( 1 - collision, 0 - not collision )
                    if(Dist[nextNode]==0 && value==0)
                        {
                            Dist[nextNode]=Dist[currentNode]+1;
                            Q.push(nextNode);
                        }
                }
        }

    // getting the next node that the enemy should move to to get closer to the player
    int moveToNode = 0;

    for(int i=0; i<this->graph[stopNode].size(); i++)
        {
            int nextNode = this->graph[stopNode][i].first;
            int value = this->graph[stopNode][i].second;

            if(value==0 && Dist[nextNode] + 1 == Dist[stopNode])
                {
                    moveToNode = nextNode;
                    break;
                }
        }

    return this->getTiles(moveToNode);
}

// delete graph
void Graph::deleteGraph()
{
    for(int i=0; i<this->graph.size(); i++)
        this->graph[i].clear();
    this->graph.clear();
}

// updating graph
void Graph::setGraph(vector < vector <pair<int,int>> > newGraph)
{
    this->deleteGraph();

    this->graph.resize(newGraph.size());

    for(int i=0; i<newGraph.size(); i++)
        {
            for(int j=0; j<newGraph[i].size(); j++)
                {
                    this->graph[i].push_back(newGraph[i][j]);
                }
        }
}

// constructors
Graph::Graph()
{
    this->lines = this->columns = this->gridSize = 0;
}

// destructors
Graph::~Graph()
{
    this->deleteGraph();
}

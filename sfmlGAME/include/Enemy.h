#ifndef ENEMY_H
#define ENEMY_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>
#include "Character.h"
#include "Graph.h"
#include "Map.h"

class Enemy: public Character
{
    public:

        /* getters */
        std::string getCurrentState() const;
        std::string getEnemyName() const;
        float getRadiusIdle() const;
        float getRadiusCombat() const;
        float getTimerIdle() const;
        float getTimerIdleReset() const;
        sf::Vector2f getPlayerPosition() const;
        sf::Vector2f getLastKnownPosition() const;
        bool getIsPlayerDead() const;

        /* setters */
        void setCurrentState(std::string);
        void setEnemyName(std::string);
        void setRadiusIdle(float);
        void setRadiusCombat(float);
        void setTimerIdle(float);
        void setTimerIdleReset(float);
        void setPlayerPosition(sf::Vector2f);
        void setLastKnownPosition(sf::Vector2f);
        void setIsPlayerDead(bool);

        /* class methods */
        std::pair<int,int> getNextStep(sf::Vector2f, sf::Vector2f);
        std::pair<int,int> getEnemyTiles();
        void revive();
        void getGraph(Map&);
        void setValues(std::string);

        /* constructors */
        Enemy();

        /* destructors */
        ~Enemy();

    private:

        sf::Vector2f playerPosition; // can be modified for multiple players or when NPC fights along the player or enemies fight each other

        sf::Vector2f lastKnownPosition;

        Graph graph;

        std::string currentState;

        std::string enemyName;

        float radiusIdle;
        float radiusCombat;

        float timerIdle;
        float timerIdleReset;

        bool isPlayerDead;

};

#endif // ENEMY_H

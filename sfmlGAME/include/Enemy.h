#ifndef ENEMY_H
#define ENEMY_H
#include "Character.h"
#include <fstream>
#include <nlohmann/json.hpp>
#include <cstdlib>
#include "Map.h"
#include "Graph.h"
#include "Map.h"
#include "Animation.h"
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
using namespace sf;

class Enemy: public Character
{
    public:
        // implementing the behaviour of the enemies, more like an "AI"
        void AI(float);
        // behaviour for moving while is out of combat
        void idleMove(float);
        // chasing the player when it enters enemy's radius
        void chasePlayer();
        // check distance between player and enemy
        void checkDistance();
        // getting the new direction for idle movement of the enemy, if out of idle radius, return, othwerise, pick a random direction
        int newDirectionIdleMove();
        // getting the euclidian distance between two points
        float getEuclidianDistance(Vector2f, Vector2f);
        // getting the grid graph
        void getGraph(Map*);
        // get the tiles a character is currently on
        pair <int,int> getTiles(Vector2f) const;
        // moving the enemy to specified tiles
        void moveToTile(pair<int,int>);
        // check if the player is in enemy's radius
        bool isInRadius();
        // get player state
        void getPlayerState(Character*);
        // revive
        void revive();

        // getters
        bool getCombatMode() const;
        bool getIsRespawnable() const;
        float getTimeMoveIdle() const;
        float getTimeMoveIdleReset() const;
        Vector2f getPlayerPosition() const;
        Vector2f getLastKnownPosition() const;
        float getRadiusCombat() const;
        float getRadiusIdle() const;
        float getRespawnTime() const;

        // setters
        void setCombatMode(bool);
        void increaseTimeMoveIdle(float);
        void resetTimeMoveIdle();
        void setTimeMoveIdleReset(float);
        void setPlayerPosition(Vector2f);
        void setLastKnownPosition(Vector2f);
        void setRadiusCombat(float);
        void setRadiusIdle(float);
        void setRespawnTime(float);
        void setIsRespawnable(bool);

        // constructors
        Enemy(string);

        // destructors
        ~Enemy();

    private:

        float radiusIdle; // the zone the enemy should stay in when is out of combat

        float radiusCombat; // when the player enters this radius, the enemy will chase the player

        /* The enemy needs to know the position of the player in order to change its state
        also i can declare an array instead of player's position in case the enemy wants to attack multiple players(or npcs) at once
        */
        Vector2f playerPosition;

        /*
        when the player exit the enemy's radius, the enemy will check the player's last position
        */
        Vector2f lastKnownPosition;

        bool combatMode; // true -> in combat, false -> not in combat
        bool respawnable; // if the enemy can be respawned

        // time after which the character moves into a random direction in his radius while he's not in combat mode
        float timeMoveIdle,timeMoveIdleReset;

        float respawnTime; // the time after which the enemy respawns to its spawn point

        Graph graph;

        int gridSize;
};

#endif // ENEMY_H

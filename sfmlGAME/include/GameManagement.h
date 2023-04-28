#ifndef GAMEMANAGEMENT_H
#define GAMEMANAGEMENT_H
#include "AnimationState.h"
#include "Animation.h"
#include "AnimationManagement.h"
#include "Controls.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>
#include "CharacterManagement.h"
#include "Player.h"
#include "Character.h"
#include "CharacterMovement.h"
#include "Map.h"
#include "Camera.h"
#include "Enemy.h"
#include "EnemyAI.h"
#include "Bar.h"
#include "CombatSystem.h"
#include "CharacterEvents.h"
#include "Menu.h"
#include "TransparentObstacle.h"

class GameManagement
{
    public:

        /* getters */
        bool getGameExit() const;

        /* setters */
        void setDidGameStart(bool);
        void setGameExit(bool);
        void setMouseClicked(bool);

        /* class methods */
        void manageZoom(int);

        void createAnimations();

        void windowManagement(float);

        void draw();

        void drawDeadCharacters();

        void drawAliveCharacters();

        void setCharacterEvents();

        /* constructors */
        GameManagement(sf::RenderWindow&);

        /* destructors */
        ~GameManagement();

    private:
        sf::RenderWindow& m_window;

        AnimationState animationState;

        Controls controls;

        Player player;

        Bar playerHealthBar;

        Bar enemyHealthBar;

        CharacterManagement characterManagement;

        CharacterMovement characterMovement;

        Map currentMap;

        Camera camera;

        CharacterEvents playerEvents;

        std::vector <Enemy> enemies;
        std::vector <AnimationState> enemiesAnimationState;
        std::vector <CharacterEvents> enemiesEvents;
        std::vector <Bar*> enemiesHealthBar;

        EnemyAI enemyAI;

        CombatSystem combatSystem;

        // map entities

        std::vector <TransparentObstacle*> transparentObstacles;

        std::vector <AnimationState> animatedObjects;

        // Menu

        //Menu menu;

        Menu *menu;

        // game logic

        bool isGamePaused;
        bool didGameStart;
        bool gameExit;
};

#endif // GAMEMANAGEMENT_H

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
#include "CameraEffects.h"
#include "GameEvents.h"
#include "Portal.h"
#include "Boss.h"
#include "BarManager.h"
#include "NecromancerAI.h"
#include "Projectile.h"

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

        void resetGame();

        void drawDeadCharacters();

        void drawAliveCharacters();

        void setCharacterEvents();

        /* important methods */
        void changeLevel(std::string, std::string);

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

        // implement boss here
        std::vector <Boss> bossList;
        std::vector <AnimationState> bossAnimationState;
        std::vector <CharacterEvents> bossEvents;
        std::vector <Bar*> bossHealthBar;
        NecromancerAI necromancerAI;

        CombatSystem combatSystem;

        // map entities

        std::vector <TransparentObstacle*> transparentObstacles;

        std::vector <AnimationState> animatedObjects;

        // Menu

        Menu *menu;

        // Camera effects

        CameraEffects *cameraEffects;

        // Game events manager

        GameEvents *gameEvents;

        // game logic

        bool isGamePaused;
        bool didGameStart;
        bool gameExit;

        // details about the game

        int numberOfMaps;
        std::vector <int> numberOfLevels;

        Portal *portalStart;
        Portal *portalEnd;

        int currentMapIndex;
        int currentLevelIndex;

        std::vector <Projectile> enemiesProjectiles;
        std::vector <Projectile> playerProjectiles;
};

#endif // GAMEMANAGEMENT_H

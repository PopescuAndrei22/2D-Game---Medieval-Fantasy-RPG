#ifndef CHARACTERMANAGEMENT_H
#define CHARACTERMANAGEMENT_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Character.h"
#include "Enemy.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include "AnimationCharacter.h"
#include "Controls.h"
#include "AnimationCharacter.h"
#include "Camera.h"
#include "CharacterMove.h"
#include "Map.h"
#include "Bar.h"

using namespace sf;
using namespace std;

// Managing player, enemies and NPCs

class GameManagement
{
    public:
        void setCharacters();

        void manageInsideWindow(float);

        void draw(RenderWindow*);

        void manageZoom(int);

        GameManagement();
        ~GameManagement();

    private:
        vector <Enemy> enemies;
        Character player;

        vector <AnimationCharacter*> enemyAnimation;
        AnimationCharacter playerAnimation;

        Controls controls;

        Camera camera;

        Map map;

        Bar playerHealthBar;

        CharacterMove characterMove;
};

#endif // CHARACTERMANAGEMENT_H

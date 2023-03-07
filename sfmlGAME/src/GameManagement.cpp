#include "GameManagement.h"

void GameManagement::setCharacters()
{
    // sa am grija la memory leaks, ma gandesc daca trebuie sterse manual
    this->enemies.clear();
    this->enemyAnimation.clear();

    // de modificat aici
    string pathValues = "values/maps/map1/enemies/level1.json";

    ifstream file(pathValues);
    nlohmann::json data = nlohmann::json::parse(file);

    vector < pair<int,int> > positions;
    vector <string> sprites;

    if(!data["positions"].is_null())
        {
            for(int i=0; i<data["positions"].size(); i++)
                {
                    // check for null values and positions with obstacles

                    int x = data["positions"][i][0];
                    int y = data["positions"][i][1];

                    positions.push_back(make_pair(x,y));
                }
        }

    if(!data["sprites"].is_null())
        {
            for(int i=0; i<data["sprites"].size(); i++)
                {
                    string sprite = data["sprites"][i];

                    sprites.push_back(sprite);
                }
        }

    for(int i=0; i<positions.size(); i++)
        {
            Enemy enemy(sprites[i]);
            AnimationCharacter *animation = new AnimationCharacter(sprites[i]);
            float x = positions[i].first;
            float y = positions[i].second;

            enemy.setSpawnPoint(Vector2f(x,y));
            enemy.setCharacterPosition(Vector2f(x,y));

            enemy.setCharacterSize(animation->getFrameSize());

            enemy.getGraph(&this->map);

            Bar *enemyHP = new Bar("health_bar","empty_bar",enemy.getHealth());

            this->enemyHealthBar.push_back(enemyHP);

            this->enemies.push_back(enemy);
            this->enemyAnimation.push_back(animation);
        }
}

void GameManagement::manageInsideWindow(float timer)
{
    for(int i=0; i<this->enemies.size(); i++)
        {
            this->enemies[i].getPlayerState(&this->player);
            this->enemies[i].AI(timer);
            characterMove.handleMovement(&this->enemies[i],timer,&this->map);

            this->enemyAnimation[i]->handleAnimation(&this->enemies[i],timer);

            // placing the health bar above the enemy
            this->enemyHealthBar[i]->setPositionEnemy(this->enemies[i].getCharacterPosition(),this->enemies[i].getCharacterSize());

            this->enemyHealthBar[i]->manageBar(this->enemies[i].getCurrentHealth());
        }

    this->controls.handleControls(&this->player);
    this->playerAnimation.handleAnimation(&this->player,timer);
    characterMove.handleMovement(&this->player,timer,&this->map);

    // placing the health bar in the top left corner
    this->playerHealthBar.setPosition(this->camera.getTopLeftCorner());
    this->playerHealthBar.manageBar(this->player.getCurrentHealth());

    this->camera.handleView(this->player);
}

void GameManagement::draw(RenderWindow *window)
{
    window->setView(this->camera.getView());

    window->draw(this->map.getMap());

    window->draw(this->playerAnimation.getSprite());

    for(int i=0; i<this->enemyAnimation.size(); i++)
        window->draw(this->enemyAnimation[i]->getSprite());

    for(int i=0; i<this->enemyHealthBar.size(); i++)
        {
            if(this->enemies[i].getCombatMode()==true)
                this->enemyHealthBar[i]->draw(window);
        }

    // drawing some of the obstacles over the characters, for example the leaves of the trees, because it would be weird if those are drawn before the characters
    window->draw(this->map.getTransparentObstacles());

    this->playerHealthBar.draw(window);
}

void GameManagement::manageZoom(int value)
{
    this->camera.zoomEvent(value);
}

GameManagement::GameManagement():player("hero"),playerAnimation("hero"),map("map1","level1"),playerHealthBar("health_bar","empty_bar",this->player.getHealth())
{
    this->player.setCharacterSize(this->playerAnimation.getFrameSize());

    camera.setMapSize(map.getMapSize());

}

GameManagement::~GameManagement()
{

}

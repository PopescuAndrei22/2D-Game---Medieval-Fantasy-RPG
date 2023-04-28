#include "GameManagement.h"

/* getters */
bool GameManagement::getGameExit() const
{
    return this->gameExit;
}

/* setters */
void GameManagement::setDidGameStart(bool didGameStart)
{
    this->didGameStart = didGameStart;
}

void GameManagement::setGameExit(bool gameExit)
{
    this->gameExit = gameExit;
}

void GameManagement::setMouseClicked(bool isMouseClicked)
{
    this->menu->setIsButtonClicked(isMouseClicked);
}

/* class methods */
void GameManagement::windowManagement(float timer)
{
    if(this->didGameStart == false)
        {
            /* there might be a bug because the window will draw entities without this method executing updates of entities first time */

            this->menu->setButtonsVisibility("default");
            this->menu->manageMenu(m_window);
            this->menu->LayoutManager();

            if(this->menu->getIsButtonPressed())
                {
                    if(menu->getButtonPressedName() == "Start")
                        {
                            this->setDidGameStart(true);
                        }
                    else if(menu->getButtonPressedName() == "Exit")
                        {
                            this->setGameExit(true);
                        }
                }

            return;
        }

    if(this->isGamePaused)
        {
            this->menu->setButtonsVisibility("resume");
            this->menu->manageMenu(m_window);
            this->menu->LayoutManager();

            if(this->menu->getIsButtonPressed())
                {
                    if(menu->getButtonPressedName() == "Resume")
                        {
                            this->isGamePaused = false;
                        }
                    else if(menu->getButtonPressedName() == "Main Menu")
                        {
                            this->isGamePaused = false;
                            this->didGameStart = false;
                        }
                    else if(menu->getButtonPressedName() == "Exit")
                        {
                            this->setGameExit(true);
                        }
                }

            return;
        }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            this->isGamePaused = true;
        }

    sf::Keyboard::Key key = this->controls.checkIfKeyIsPressed();

    this->characterManagement.managePlayerControls(key,controls,this->player);

    this->characterMovement.manageMovement(this->player,timer,this->currentMap);
    this->characterManagement.manageCharacterActions(this->player,this->animationState,timer);

    this->playerEvents.manageCharacterEvents(this->player,this->animationState,timer);

    this->animationState.update(timer);

    for(unsigned i=0; i<this->enemiesAnimationState.size(); i++)
        {
            this->enemies[i].setPlayerPosition(this->player.getCharacterPosition());
            this->enemies[i].setIsPlayerDead(this->player.getIsDead());

            this->combatSystem.update(this->player,this->enemies[i]);
            this->enemyAI.manageAI(this->enemies[i],timer);

            this->characterMovement.manageMovement(this->enemies[i],timer,this->currentMap);
            this->characterManagement.manageCharacterActions(this->enemies[i],this->enemiesAnimationState[i],timer);

            this->enemiesEvents[i].manageCharacterEvents(this->enemies[i],this->enemiesAnimationState[i],timer);

            this->enemiesAnimationState[i].update(timer);

            this->enemiesHealthBar[i]->setPositionEnemy(this->enemies[i].getCharacterPosition(),this->enemies[i].getCharacterSize());

            this->enemiesHealthBar[i]->updateBar(this->enemies[i].getCurrentHealth());
        }

    this->camera.handleView(this->player);

    this->playerHealthBar.setPosition(this->camera.getTopLeftCorner());
    this->playerHealthBar.updateBar(this->player.getCurrentHealth());

    this->playerEvents.updateTextPosition(this->camera.getCenter());

    // animated objects

    for(unsigned i=0; i<this->animatedObjects.size(); i++)
        {
            this->animatedObjects[i].update(timer);
        }
}

void GameManagement::drawDeadCharacters()
{
    if(this->player.getIsDead())
        m_window.draw(animationState);

    for(unsigned i=0; i<this->enemiesAnimationState.size(); i++)
        {
            if(this->enemies[i].getIsDead())
                m_window.draw(this->enemiesAnimationState[i]);
        }
}

void GameManagement::drawAliveCharacters()
{
    if(this->player.getIsDead() == false)
        {
            m_window.draw(animationState);

            // !this->player.getIsWalkingIntoObstacle() isn't working, maybe i disable it in one of the previous functions?
            if(this->player.getIsDashing() && !this->player.getIsWalkingIntoObstacle())
                {
                    AnimationState altAnimationState_1 = this->animationState;
                    AnimationState altAnimationState_2 = this->animationState;

                    sf::Vector2f newPosition_1 = this->player.getCharacterPosition();
                    sf::Vector2f newPosition_2 = this->player.getCharacterPosition();

                    sf::Vector2f characterSize = this->player.getCharacterSize();
                    characterSize.x /= 2;
                    characterSize.y /= 2;

                    std::string direction = this->player.getDirection();

                    if(direction == "left")
                        {
                            newPosition_1.x += characterSize.x;
                            newPosition_2.x += characterSize.x * 2;
                        }
                    else if(direction == "right")
                        {
                            newPosition_1.x -= characterSize.x;
                            newPosition_2.x -= characterSize.x * 2;
                        }
                    else if(direction == "up")
                        {
                            newPosition_1.y += characterSize.y;
                            newPosition_2.y += characterSize.y * 2;
                        }
                    else
                        {
                            newPosition_1.y -= characterSize.y;
                            newPosition_2.y -= characterSize.y * 2;
                        }

                    altAnimationState_1.setPosition(newPosition_1);
                    altAnimationState_2.setPosition(newPosition_2);

                    altAnimationState_1.setColor(sf::Color(255,255,255,150));
                    altAnimationState_2.setColor(sf::Color(255,255,255,120));

                    m_window.draw(altAnimationState_2);
                    m_window.draw(altAnimationState_1);
                }

        }

    for(unsigned i=0; i<this->enemiesAnimationState.size(); i++)
        {
            if(this->enemies[i].getIsDead() == false)
                {
                    m_window.draw(this->enemiesAnimationState[i]);

                    if(this->enemies[i].getIsDashing())
                        {
                            // to write here
                        }
                }
        }
}

void GameManagement::draw()
{
    m_window.clear(sf::Color::Black);

    if(this->didGameStart == false || this->isGamePaused == true)
        {
            this->menu->draw(m_window);

            m_window.display();

            return;
        }

    m_window.setView(this->camera.getView());

    m_window.draw(this->currentMap.getMap());

    this->drawDeadCharacters();
    this->drawAliveCharacters();

    m_window.draw(this->playerEvents.getText());

    // draw entities

    for(unsigned i=0; i<this->transparentObstacles.size(); i++)
        {
            this->transparentObstacles[i]->draw(m_window);
        }

    for(unsigned i=0; i<this->animatedObjects.size(); i++)
        {
            m_window.draw(this->animatedObjects[i]);
        }


    // health bars

    this->playerHealthBar.draw(m_window);

    for(unsigned int i=0; i<this->enemies.size(); i++)
        {
            if(this->enemies[i].getCurrentState() == "agressive" && this->enemies[i].getIsDead() == false && this->enemies[i].getIsDying() == false)
                this->enemiesHealthBar[i]->draw(m_window);
        }

    m_window.display();
}

void GameManagement::createAnimations()
{
    AnimationManagement ob;

    this->animationState = ob.typeOfAnimation("hero","character");

    for(unsigned i=0; i<this->enemies.size(); i++)
        {
            AnimationState animationStateEnemy;
            animationStateEnemy = ob.typeOfAnimation(this->enemies[i].getEnemyName(),"character");
            this->enemiesAnimationState.push_back(animationStateEnemy);
        }

    // animated objects

    std::vector < std::pair<sf::Vector2f,std::string> > animatedObjectDetails = this->currentMap.getAnimatedObjectDetails();

    for(unsigned i=0; i<animatedObjectDetails.size(); i++)
        {
            AnimationState animationStateObject;
            animationStateObject = ob.typeOfAnimation(animatedObjectDetails[i].second,"object");
            animationStateObject.setPosition(animatedObjectDetails[i].first);

            this->animatedObjects.push_back(animationStateObject);
        }
}

void GameManagement::setCharacterEvents()
{
    for(unsigned i=0; i<this->enemies.size(); i++)
        {
            CharacterEvents characterEvents;

            this->enemiesEvents.push_back(characterEvents);
        }
}

void GameManagement::manageZoom(int value)
{
    this->camera.zoomEvent(value);
}

/* constructors */
GameManagement::GameManagement(sf::RenderWindow& window):m_window(window)
{
    this->currentMap.getMapDetails("map1","level2");

    this->player.setValues("hero");

    this->player.setSpawnPoint(this->currentMap.getPlayerPosition());
    this->player.setCharacterPosition(this->player.getSpawnPoint());

    this->camera.setMapSize(this->currentMap.getMapSize());

    std::vector < std::pair<sf::Vector2f,std::string> > enemyDetails = this->currentMap.getEnemyDetails();

    for(unsigned i=0; i<enemyDetails.size(); i++)
        {
            Enemy enemy;
            enemy.setValues(enemyDetails[i].second);
            enemy.getGraph(this->currentMap);

            enemy.setSpawnPoint(enemyDetails[i].first);
            enemy.setCharacterPosition(enemy.getSpawnPoint());

            this->enemies.push_back(enemy);
        }

    this->createAnimations();

    this->setCharacterEvents();

    this->playerHealthBar.setBar("health_bar",this->player.getHealth());

    for(unsigned i=0; i<this->enemies.size(); i++)
        {
            Bar *enemyBar = new Bar();
            enemyBar->setBar("health_bar",this->enemies[i].getHealth());
            this->enemiesHealthBar.push_back(enemyBar);
        }

    // map entities

    std::vector < std::pair<sf::Vector2f,std::string> > transparentObstacleDetails = this->currentMap.getTransparentObstacleDetails();

    for(unsigned i=0; i<transparentObstacleDetails.size(); i++)
        {
            TransparentObstacle *transparentObstacle = new TransparentObstacle();

            transparentObstacle->setValues("map1",transparentObstacleDetails[i].second,transparentObstacleDetails[i].first);

            this->transparentObstacles.push_back(transparentObstacle);
        }

    // game logic

    this->didGameStart = false;
    this->isGamePaused = false;
    this->gameExit = false;

    this->menu = new Menu();
}

/* destructors */
GameManagement::~GameManagement()
{

}

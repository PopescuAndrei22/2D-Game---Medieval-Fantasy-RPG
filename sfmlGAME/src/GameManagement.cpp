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
    if(this->didGameStart == false || this->isGamePaused == true)
        {
            this->menu->setIsButtonClicked(isMouseClicked);
        }
}

/* class methods */
void GameManagement::windowManagement(float timer)
{
    if(this->gameEvents->getIsGameOver())
        {
            this->gameEvents->manageGameOver(this->cameraEffects, timer);

            if(this->gameEvents->getIsAbleToEndGame())
                {
                    this->gameEvents->setIsAbleToEndGame(false);
                    this->gameEvents->setIsGameOver(false);

                    this->resetGame();

                }

            return;
        }

    if(this->gameEvents->getLevelTransitionInProgress())
        {
            this->gameEvents->manageLevelTransition(this->cameraEffects, timer);

            if(!this->cameraEffects->getIsFadeInFinished())
                {
                    return;
                }
            else
                {
                    if(this->gameEvents->getLevelTransitionRequest())
                        {
                            // changing level
                            this->gameEvents->setLevelTransitionRequest(false);

                            std::string nextMapName = "map";
                            std::string nextLevelName = "level";

                            if(this->currentLevelIndex <= 0)
                                {
                                    this->currentLevelIndex = 1;
                                }
                            else
                                {
                                    this->currentLevelIndex ++;
                                }

                            if(this->currentLevelIndex < 1 || this->currentLevelIndex > this->numberOfLevels[this->currentMapIndex])
                                {
                                    // in case of a bug
                                    this->currentLevelIndex = 1;
                                }

                            nextMapName += std::to_string(this->currentMapIndex);
                            nextLevelName += std::to_string(this->currentLevelIndex);

                            this->changeLevel(nextMapName,nextLevelName);
                        }
                }
        }

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

                            this->gameEvents->setLevelTransitionRequest(true);
                            this->gameEvents->setLevelTransitionInProgress(true);
                            this->gameEvents->setTransitionWhileInMenu(true);

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

    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            // to check if we can use spell, for example if character isn't attacking or spellcasting etc., to modify here later
            if(this->animationState.getIsLooped() == true)
                {
                    this->player.setIsAttacking(true);

                    Projectile projectile;
                    projectile.init(this->player.getProjectile());

                    // adjusting the placement
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(m_window);
                    sf::Vector2f viewPosition = this->m_window.mapPixelToCoords(mousePosition, this->camera.getView());

                    projectile.setTarget(sf::Vector2f(viewPosition.x,viewPosition.y));

                    projectile.setPosition(sf::Vector2f(this->player.getCharacterPosition().x + (this->player.getCharacterSize().x/2),
                                                        this->player.getCharacterPosition().y + (this->player.getCharacterSize().y/2)));
                    projectile.adjustDirection();

                    this->playerProjectiles.push_back(projectile);
                }
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
            this->combatSystem.updateProjectiles(this->enemies[i], this->playerProjectiles);
            this->enemyAI.manageAI(this->enemies[i],timer);

            this->characterMovement.manageMovement(this->enemies[i],timer,this->currentMap);
            this->characterManagement.manageCharacterActions(this->enemies[i],this->enemiesAnimationState[i],timer);

            this->enemiesEvents[i].manageCharacterEvents(this->enemies[i],this->enemiesAnimationState[i],timer);

            this->enemiesAnimationState[i].update(timer);

            this->enemiesHealthBar[i]->setPositionEnemy(this->enemies[i].getCharacterPosition(),this->enemies[i].getCharacterSize());

            this->enemiesHealthBar[i]->updateBar(this->enemies[i].getCurrentHealth());
        }

    bool isGameOver = false;
    for(unsigned i=0; i<this->bossAnimationState.size(); i++)
        {
            this->bossList[i].setPlayerPosition(this->player.getCharacterPosition());
            this->bossList[i].setIsPlayerDead(this->player.getIsDead());

            this->combatSystem.update(this->player,this->bossList[i]);
            this->combatSystem.updateProjectiles(this->bossList[i], this->playerProjectiles);

            if(this->bossList[i].getEnemyName() == "necromancer")
                {
                    this->necromancerAI.manageAI(this->bossList[i],timer);
                    //this->enemyAI.manageAI(this->bossList[i],timer);
                }

            if(this->bossList[i].getProjectileRequest() == true)
                {
                    this->bossList[i].setProjectileRequest(false);

                    Projectile projectile;
                    projectile.init(this->bossList[i].getProjectile());

                    // adjusting the placement
                    projectile.setTarget(sf::Vector2f(this->player.getCharacterPosition().x + (this->player.getCharacterSize().x/2),
                                                      this->player.getCharacterPosition().y + (this->player.getCharacterSize().y/2)));

                    projectile.setPosition(sf::Vector2f(this->bossList[i].getCharacterPosition().x + (this->bossList[i].getCharacterSize().x/2),
                                                        this->bossList[i].getCharacterPosition().y + (this->bossList[i].getCharacterSize().y/2)));
                    projectile.adjustDirection();

                    this->enemiesProjectiles.push_back(projectile);
                }

            this->characterMovement.manageMovement(this->bossList[i],timer,this->currentMap);
            this->characterManagement.manageCharacterActions(this->bossList[i],this->bossAnimationState[i],timer);

            this->bossEvents[i].manageCharacterEvents(this->bossList[i],this->bossAnimationState[i],timer);

            this->bossAnimationState[i].update(timer);

            this->bossHealthBar[i]->setPositionEnemy(this->bossList[i].getCharacterPosition(),this->bossList[i].getCharacterSize());

            this->bossHealthBar[i]->updateBar(this->bossList[i].getCurrentHealth());

            if(this->bossList[i].getIsDead())
                {
                    isGameOver = true;
                }
        }

    // only for demo, this will be fixed in the future
    if(isGameOver)
        {
            this->gameEvents->setIsGameOver(true);
        }

    this->combatSystem.updateProjectiles(this->player, this->enemiesProjectiles);

    this->camera.handleView(this->player);
    this->cameraEffects->updateCamera(this->camera);

    this->playerHealthBar.setPosition(this->camera.getTopLeftCorner());
    this->playerHealthBar.updateBar(this->player.getCurrentHealth());

    this->playerEvents.updateTextPosition(this->camera.getCenter());
    this->cameraEffects->updateTextPosition(this->camera.getCenter());

    // transparent obstacles
    for(unsigned i=0; i<this->transparentObstacles.size(); i++)
        {
            this->transparentObstacles[i]->checkTransparency(this->player.getCharacterPosition());
        }

    // animated objects
    for(unsigned i=0; i<this->animatedObjects.size(); i++)
        {
            this->animatedObjects[i].update(timer);
        }

    // managing projectiles
    /* to use another data structure or more efficient algorithm to do that */
    for (unsigned i = 0; i < this->enemiesProjectiles.size(); i++)
        {
            this->enemiesProjectiles[i].update(timer);

            if (this->enemiesProjectiles[i].getProjectileFinished())
                {
                    // Remove the element at index i
                    this->enemiesProjectiles.erase(this->enemiesProjectiles.begin() + i);

                    // Adjust the loop counter and vector size
                    i--;
                }
        }

    for (unsigned i = 0; i < this->playerProjectiles.size(); i++)
        {
            this->playerProjectiles[i].update(timer);

            if (this->playerProjectiles[i].getProjectileFinished())
                {
                    // Remove the element at index i
                    this->playerProjectiles.erase(this->playerProjectiles.begin() + i);

                    // Adjust the loop counter and vector size
                    i--;
                }
        }

    // check if the player is near the portal to teleport to the next level

    // to modify here
    if(this->currentLevelIndex < this->numberOfLevels[this->currentMapIndex])
        {
            if(this->portalEnd->isInRange(this->player.getCharacterPosition()))
                {
                    this->gameEvents->setLevelTransitionRequest(true);
                    this->gameEvents->setLevelTransitionInProgress(true);
                }
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

    for(unsigned i=0; i<this->bossAnimationState.size(); i++)
        {
            if(this->bossList[i].getIsDead())
                m_window.draw(this->bossAnimationState[i]);
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

    for(unsigned i=0; i<this->bossAnimationState.size(); i++)
        {
            if(this->bossList[i].getIsDead() == false)
                {
                    m_window.draw(this->bossAnimationState[i]);

                    if(this->bossList[i].getIsDashing())
                        {
                            // to write here
                        }
                }
        }
}

void GameManagement::draw()
{
    m_window.clear(sf::Color::Black);

    if(this->gameEvents->getTransitionWhileInMenu())
        {
            this->menu->draw(m_window);

            this->cameraEffects->setPosition(sf::Vector2f(0.0f,0.0f));
            this->cameraEffects->draw(m_window);

            m_window.display();

            return;
        }

    if(this->didGameStart == false || this->isGamePaused == true)
        {
            this->menu->draw(m_window);

            m_window.display();

            return;
        }

    m_window.setView(this->camera.getView());

    m_window.draw(this->currentMap.getMap());
    this->portalStart->draw(m_window);

    if(this->currentMapIndex > this->numberOfLevels.size())
        {
            std::cout<<"Error with the map/level index"<<'\n';
        }
    else
        {
            if(this->currentLevelIndex < this->numberOfLevels[this->currentMapIndex])
                {
                    this->portalEnd->draw(m_window);
                }
        }

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

    // projectiles
    for(unsigned i=0; i<this->enemiesProjectiles.size(); i++)
        {
            this->enemiesProjectiles[i].draw(m_window);
        }

    for(unsigned i=0; i<this->playerProjectiles.size(); i++)
        {
            this->playerProjectiles[i].draw(m_window);
        }

    // health bars

    this->playerHealthBar.draw(m_window);

    for(unsigned int i=0; i<this->enemies.size(); i++)
        {
            if(this->enemies[i].getCurrentState() == "agressive" && this->enemies[i].getIsDead() == false && this->enemies[i].getIsDying() == false)
                this->enemiesHealthBar[i]->draw(m_window);
        }

    for(unsigned int i=0; i<this->bossList.size(); i++)
        {
            if(this->bossList[i].getCurrentState() == "agressive" && this->bossList[i].getIsDead() == false && this->bossList[i].getIsDying() == false)
                this->bossHealthBar[i]->draw(m_window);
        }

    if(this->gameEvents->getLevelTransitionInProgress())
        {
            this->cameraEffects->draw(m_window);
        }

    if(this->gameEvents->getIsGameOver())
        {
            this->cameraEffects->draw(m_window);
            m_window.draw(this->cameraEffects->getText());
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

    for(unsigned i=0; i<this->bossList.size(); i++)
        {
            AnimationState animationStateBoss;
            animationStateBoss = ob.typeOfAnimation(this->bossList[i].getEnemyName(),"character");
            this->bossAnimationState.push_back(animationStateBoss);
        }

    // animated objects

    std::vector < std::pair<sf::Vector2f,std::string> > animatedObjectDetails = this->currentMap.getAnimatedObjectDetails();

    for(unsigned i=0; i<animatedObjectDetails.size(); i++)
        {
            AnimationState animationStateObject;
            animationStateObject = ob.objectAnimation(animatedObjectDetails[i].second,"map1_animations");
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

    for(unsigned i=0; i<this->bossList.size(); i++)
        {
            CharacterEvents characterEvents;

            this->bossEvents.push_back(characterEvents);
        }
}

void GameManagement::manageZoom(int value)
{
    this->camera.zoomEvent(value);
}

void GameManagement::changeLevel(std::string mapName, std::string levelName)
{
    // deleting projectiles
    this->enemiesProjectiles.clear();
    this->playerProjectiles.clear();

    // deleting entities from the previous level
    this->enemies.clear();
    this->enemiesAnimationState.clear();
    this->enemiesEvents.clear();
    this->enemiesHealthBar.clear(); // does it work for pointer types?

    this->bossList.clear();
    this->bossAnimationState.clear();
    this->bossEvents.clear();
    this->bossHealthBar.clear();

    this->transparentObstacles.clear();
    this->animatedObjects.clear();

    this->playerHealthBar = Bar();
    this->animationState = AnimationState();

    this->enemyHealthBar = Bar();

    // setting the current level

    this->currentMap.getMapDetails(mapName,levelName);

    this->player.setValues("hero");

    this->player.setSpawnPoint(this->currentMap.getPlayerPosition());
    this->player.setSpawnPoint(this->currentMap.getPortalStart());
    this->player.setCharacterPosition(this->player.getSpawnPoint());

    this->camera.setMapSize(this->currentMap.getMapSize());
    this->camera.handleView(this->player);
    this->cameraEffects->updateCamera(this->camera);

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

    std::vector < std::pair<sf::Vector2f,std::string> > bossDetails = this->currentMap.getBossDetails();
    for(unsigned i=0; i<bossDetails.size(); i++)
        {
            Boss boss;
            boss.setValues(bossDetails[i].second);
            boss.getGraph(this->currentMap);

            boss.setSpawnPoint(bossDetails[i].first);
            boss.setCharacterPosition(boss.getSpawnPoint());

            this->bossList.push_back(boss);
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

    for(unsigned i=0; i<this->bossList.size(); i++)
        {
            Bar *bossBar = new Bar();
            bossBar->setBar("health_bar",this->bossList[i].getHealth());
            this->bossHealthBar.push_back(bossBar);
        }

    // map entities

    std::vector < std::pair<sf::Vector2f,std::string> > transparentObstacleDetails = this->currentMap.getTransparentObstacleDetails();

    for(unsigned i=0; i<transparentObstacleDetails.size(); i++)
        {
            TransparentObstacle *transparentObstacle = new TransparentObstacle();

            // to modify here
            transparentObstacle->setValues("map1",transparentObstacleDetails[i].second,transparentObstacleDetails[i].first);

            this->transparentObstacles.push_back(transparentObstacle);
        }

    this->portalStart->setPosition(this->currentMap.getPortalStart());
    this->portalEnd->setPosition(this->currentMap.getPortalEnd());
}

void GameManagement::resetGame()
{
    // game logic

    // apply level transition here

    this->didGameStart = false;
    this->isGamePaused = false;
    this->gameExit = false;

    this->menu = new Menu();
    this->cameraEffects = new CameraEffects();

    // to set the camera default view on position (0,0) because the menu is drawn on (0,0)
    this->gameEvents = new GameEvents();

    this->cameraEffects->updateCamera(this->camera);

    this->portalStart = new Portal();
    this->portalEnd = new Portal();

    // to get these values from a json file

    this->numberOfLevels.clear();

    this->numberOfMaps = 1;
    this->numberOfLevels.push_back(0); // filling position 0
    this->numberOfLevels.push_back(2); // map 1 has 2 levels

    this->currentMapIndex = 1;
    this->currentLevelIndex = 0;

    // to get the number of maps and levels from each map from a file
}

/* constructors */
GameManagement::GameManagement(sf::RenderWindow& window):m_window(window)
{
    this->resetGame();
}

/* destructors */
GameManagement::~GameManagement()
{

}

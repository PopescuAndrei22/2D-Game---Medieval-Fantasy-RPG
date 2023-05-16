#include "GameEvents.h"

/* getters */
bool GameEvents::getLevelTransitionRequest() const
{
    return this->levelTransitionRequest;
}

bool GameEvents::getLevelTransitionInProgress() const
{
    return this->levelTransitionInProgress;
}

bool GameEvents::getTransitionWhileInMenu() const
{
    return this->transitionWhileInMenu;
}

bool GameEvents::getIsGameOver() const
{
    return this->isGameOver;
}

bool GameEvents::getIsAbleToEndGame() const
{
    return this->isAbleToEndGame;
}

/* setters */
void GameEvents::setLevelTransitionRequest(bool levelTransitionRequest)
{
    this->levelTransitionRequest = levelTransitionRequest;
}

void GameEvents::setLevelTransitionInProgress(bool levelTransitionInProgress)
{
    this->levelTransitionInProgress = levelTransitionInProgress;
}

void GameEvents::setTransitionWhileInMenu(bool transitionWhileInMenu)
{
    this->transitionWhileInMenu = transitionWhileInMenu;
}

void GameEvents::setIsGameOver(bool isGameOver)
{
    this->isGameOver = isGameOver;
}

void GameEvents::setIsAbleToEndGame(bool isAbleToEndGame)
{
    this->isAbleToEndGame = isAbleToEndGame;
}

/* class methods */

void GameEvents::manageLevelTransition(CameraEffects *cameraEffect, float timer)
{
    if(!cameraEffect->getIsFadeInFinished())
        {
            cameraEffect->fadeIn(timer);
        }
    else if(!cameraEffect->getIsFadeOutFinished())
        {
            this->setTransitionWhileInMenu(false);
            cameraEffect->fadeOut(timer);
        }
    else
        {
            cameraEffect->setIsFadeInFinished(false);
            cameraEffect->setIsFadeOutFinished(false);

            this->setTransitionWhileInMenu(false);
            this->setLevelTransitionInProgress(false);
        }
}

void GameEvents::manageGameOver(CameraEffects *cameraEffect, float timer)
{
    if(!cameraEffect->getIsFadeInFinished())
        {
            cameraEffect->fadeIn(timer);
        }
    else
        {
            if(!cameraEffect->getIsFadeTextFinished())
                {
                    cameraEffect->fadeText(timer);
                }
            else
                {
                    this->timerGameEnd += timer;

                    if(this->timerGameEnd > this->timerGameEndReset)
                        {
                            cameraEffect->setIsFadeInFinished(false);
                            cameraEffect->setIsFadeOutFinished(false);
                            this->setIsAbleToEndGame(true);
                        }
                }
        }
}

void GameEvents::manageGameEvents(CameraEffects *cameraEffect, float timer)
{

}

GameEvents::GameEvents()
{
    this->setLevelTransitionRequest(false);
    this->setLevelTransitionInProgress(false);
    this->setTransitionWhileInMenu(false);

    this->setIsGameOver(false);
    this->setIsAbleToEndGame(false);

    this->timerGameEnd = 0.0;
    this->timerGameEndReset = 3.0f;
}

GameEvents::~GameEvents()
{

}

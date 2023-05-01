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

void GameEvents::manageGameEvents(CameraEffects *cameraEffect, float timer)
{

}

GameEvents::GameEvents()
{
    this->setLevelTransitionRequest(false);
    this->setLevelTransitionInProgress(false);
    this->setTransitionWhileInMenu(false);
}

GameEvents::~GameEvents()
{

}

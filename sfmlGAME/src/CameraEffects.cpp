#include "CameraEffects.h"

/* getters */
bool CameraEffects::getIsFadeInFinished() const
{
    return this->isFadeInFinished;
}

bool CameraEffects::getIsFadeOutFinished() const
{
    return this->isFadeOutFinished;
}

/* setters */
void CameraEffects::setIsFadeInFinished(bool isFadeInFinished)
{
    this->isFadeInFinished = isFadeInFinished;
}

void CameraEffects::setIsFadeOutFinished(bool isFadeOutFinished)
{
    this->isFadeOutFinished = isFadeOutFinished;
}

void CameraEffects::setPosition(sf::Vector2f windowPosition)
{
    this->cameraEffect.setPosition(windowPosition);
}

/* fade methods */
void CameraEffects::fadeIn(float timer)
{
    if(this->getIsFadeInFinished())
        return;

    this->timerFade += timer;

    if(this->timerFade > this->timerFadeReset)
        {
            this->timerFade = 0.0f;

            this->currentPosition ++;
        }

    if(this->currentPosition > this->maxColorValue)
        {
            this->currentPosition = this->maxColorValue;

            this->setIsFadeInFinished(true);
        }
    else
        {
            this->cameraEffect.setFillColor(sf::Color(55,55,55,this->currentPosition));
        }
}

void CameraEffects::fadeOut(float timer)
{
    if(this->getIsFadeOutFinished())
        return;

    this->timerFade += timer;

    if(this->timerFade > this->timerFadeReset)
        {
            this->timerFade = 0.0f;

            this->currentPosition --;
        }

    if(this->currentPosition < 0)
        {
            this->currentPosition = 0;

            this->setIsFadeOutFinished(true);
        }
    else
        {
            this->cameraEffect.setFillColor(sf::Color(55,55,55,this->currentPosition));
        }
}

/* class methods */
void CameraEffects::updateCamera(Camera &camera)
{
    this->cameraEffect.setSize(camera.getView().getSize());
    this->cameraEffect.setPosition(camera.getTopLeftCorner());
}

void CameraEffects::draw(sf::RenderWindow &renderWindow)
{
    renderWindow.draw(this->cameraEffect);
}

CameraEffects::CameraEffects()
{
    this->currentPosition = 0;

    this->maxColorValue = 255;

    // timer fade effect
    this->timerFade = 0.0f;
    this->timerFadeReset = 0.001f;

    this->setIsFadeInFinished(false);
    this->setIsFadeOutFinished(false);
}

CameraEffects::~CameraEffects()
{

}

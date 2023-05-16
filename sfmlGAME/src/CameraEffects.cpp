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

bool CameraEffects::getIsFadeTextFinished() const
{
    return this->isFadeTextFinished;
}

sf::Text CameraEffects::getText() const
{
    return this->text;
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

void CameraEffects::setIsFadeTextFinished(bool isFadeTextFinished)
{
    this->isFadeTextFinished = isFadeTextFinished;
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

void CameraEffects::fadeText(float timer)
{
    // to modify here to set it from setter
    this->text.setString("Game over!");

    if(this->getIsFadeTextFinished())
        {
            return;
        }

    this->timerFadeText += timer;

    if(this->timerFadeText > this->timerFadeTextReset)
        {
            this->timerFadeText = 0.0f;

            this->currentPositionTextFade++;
        }

    if(this->currentPositionTextFade > this->maxColorValue)
        {
            this->currentPositionTextFade = this->maxColorValue;

            this->setIsFadeTextFinished(true);
        }
    else
        {
            this->text.setFillColor(sf::Color(255,255,255,this->currentPositionTextFade));
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

void CameraEffects::updateTextPosition(sf::Vector2f position)
{
    // hotfix because it is not working properly, text.globalBounds width shows 0, to fix later
    this->text.setPosition(sf::Vector2f(position.x - 140, position.y - 300));
}

CameraEffects::CameraEffects()
{
    this->currentPosition = 0;

    this->currentPositionTextFade = 0;

    this->maxColorValue = 255;

    // timer fade effect
    this->timerFade = 0.0f;
    this->timerFadeReset = 0.001f;

    this->timerFadeText = 0.0f;
    this->timerFadeTextReset = 0.04f;

    this->setIsFadeInFinished(false);
    this->setIsFadeOutFinished(false);

    this->setIsFadeTextFinished(false);

    this->font.loadFromFile("fonts/ARCADECLASSIC.ttf");

    this->text.setFont(this->font);

    this->text.setString("");

    this->text.setFillColor(sf::Color::White);

    this->text.setCharacterSize(40);
}

CameraEffects::~CameraEffects()
{

}

#ifndef CAMERAEFFECTS_H
#define CAMERAEFFECTS_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>
#include "Camera.h"

class CameraEffects
{
public:
    /* getters */
    bool getIsFadeInFinished() const;
    bool getIsFadeOutFinished() const;
    bool getIsFadeTextFinished() const;
    sf::Text getText() const;

    /* setters */
    void setIsFadeInFinished(bool);
    void setIsFadeOutFinished(bool);

    void setIsFadeTextFinished(bool);

    void setPosition(sf::Vector2f);

    /* fade methods */
    void fadeIn(float);
    void fadeOut(float);

    void fadeText(float);

    /* class methods */
    void updateCamera(Camera&);

    void draw(sf::RenderWindow&);

    void updateTextPosition(sf::Vector2f);

    CameraEffects();
    ~CameraEffects();

private:

    sf::RectangleShape cameraEffect;

    int currentPosition;

    int currentPositionTextFade;

    int maxColorValue;

    float timerFade;
    float timerFadeReset;

    bool isFadeInFinished;
    bool isFadeOutFinished;

    float timerFadeText;
    float timerFadeTextReset;

    bool isFadeTextFinished;

    sf::Font font;
    sf::Text text;
};

#endif // CAMERAEFFECTS_H

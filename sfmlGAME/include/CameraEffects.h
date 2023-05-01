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

    /* setters */
    void setIsFadeInFinished(bool);
    void setIsFadeOutFinished(bool);

    void setPosition(sf::Vector2f);

    /* fade methods */
    void fadeIn(float);
    void fadeOut(float);

    /* class methods */
    void updateCamera(Camera&);

    void draw(sf::RenderWindow&);

    CameraEffects();
    ~CameraEffects();

private:

    sf::RectangleShape cameraEffect;

    int currentPosition;

    int maxColorValue;

    float timerFade;
    float timerFadeReset;

    bool isFadeInFinished;
    bool isFadeOutFinished;
};

#endif // CAMERAEFFECTS_H

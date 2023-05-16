#ifndef GAMEEVENTS_H
#define GAMEEVENTS_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>
#include "CameraEffects.h"

class GameEvents
{
    public:
        /* getters */
        bool getLevelTransitionRequest() const;
        bool getLevelTransitionInProgress() const;
        bool getTransitionWhileInMenu() const;

        bool getIsGameOver() const;
        bool getIsAbleToEndGame() const;

        /* setters */
        void setLevelTransitionRequest(bool);
        void setLevelTransitionInProgress(bool);
        void setTransitionWhileInMenu(bool);

        void setIsGameOver(bool);
        void setIsAbleToEndGame(bool);

        /* class methods */
        void manageLevelTransition(CameraEffects*, float);
        void manageGameOver(CameraEffects*, float);

        void manageGameEvents(CameraEffects*, float);

        GameEvents();
        ~GameEvents();

    private:

        bool levelTransitionRequest;

        bool levelTransitionInProgress;

        bool transitionWhileInMenu;

        bool isGameOver;
        bool isAbleToEndGame;

        float timerGameEnd;
        float timerGameEndReset;

};

#endif // GAMEEVENTS_H

#ifndef ANIMATIONMANAGEMENT_H
#define ANIMATIONMANAGEMENT_H
#include "AnimationState.h"
#include "Animation.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>

class AnimationManagement
{
    public:

        /* class methods */
        AnimationState typeOfAnimation(std::string,std::string);

        AnimationState characterAnimation(std::string);

        AnimationState objectAnimation(std::string);

        Animation createAnimation(std::string,nlohmann::json&);

        /* constructors */
        AnimationManagement();

        /* destructors */
        ~AnimationManagement();

    private:
        AnimationState animationState;
};

#endif // ANIMATIONMANAGEMENT_H

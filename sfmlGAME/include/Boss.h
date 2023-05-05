#ifndef BOSS_H
#define BOSS_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>
#include "Character.h"
#include "Enemy.h"

class Boss: public Enemy
{
    public:

        /* class methods */
        void revive();
        void setValues(std::string);

        Boss();
        ~Boss();

    private:

        std::string name;
};

#endif // BOSS_H
